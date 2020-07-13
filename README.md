# Modifying-BART-for-MRI-reconstruction

[BART](https://mrirecon.github.io/bart/) is a well-designed reconstruction tool for magnetic resonance imaging. There are also plenty of examples on their website explaining how to use BART. Here, I want to explain my understanding of BART (more specifically, the pics function in BART), hopefully it will make the use of BART easier for you, and even help you implement your own reconstruction method. 



## Explanation of BART
BART (version 0.3.01) provides different solvers (e.g., ISTA, POCS, FISTA, ADMM) to solve the problem in the following format,

<div align="left">
  <img = src="pics/fig1.png" width=“50px” />
</div>

where:
<div align="left">
  <img = src="pics/fig3.png" width=“50px” />
</div>

The first term is the data consistency term, which is about how the data is acquired, the second term is the sum of the regularization terms (usually one or two terms) you want to apply. 

The input to the solver (which is the pics function) is simply the k-space (y) and sensitivity map (S), and it will output the image (x). While you need to define what regularization terms you want to use (check by '-h' option or read the code). I have a list of the existed terms in slide 2 in "pics/BART.pptx". You may want to check their website for the latest versions.

There are several algorithms to solve this kind of problem (L2 term + constraints). FISTA and ADMM have been implemented in BART. I would recommend [Prof. Stephen Boyd's convex optimization class](http://web.stanford.edu/class/ee364a/) and book if you have an interest in how these algorithms work. Here we only need to know that only proximal operator of the regularization is needed for these algorithms.

## How to write you own reconstruction based on BART
The good thing of BART is that it has well implementation of these algorithms. To you have own reconstruction, usually, you only need to define some operators: (1) linear operators in the data consistency term, (2) the [proximal operator](https://en.wikipedia.org/wiki/Proximal_operator) for the regularization term. 

The previous loss function can be simplified as the following one:
<div align="left">
  <img = src="pics/fig2.png" width=“50px” />
</div>

where A is the combination of sampling (D), Fourier transform (F), and sensitivity encoding (S) operators (track the "forward_op" in pics.c). What BART does in pics is first to define each operator and then chain/combine them with the "linop_chain" operator. For the low-rank + sparse reconstruction, we only need to add another linear operator (T) before the sensitivity encoding operator, which sums up these two components. If you only want to change the regularization term, you do not even need to touch this part. 


Then the next part is about the regularization term, BART is very flexible since it requires a linear transform operator (T) associated with each regularization term (usually it is identity operator). Again for the low-rank + sparse reconstruction, we want to have 

(1) one regularization term on the low-rank component, which is pretty the same as previous low-rank operator except we need to change the identity transform to a linear transform that takes the low-rank part;

(2) the other regularization term on the sparse component. Similarly, this is pretty the same as the previous l1-loss operator, except we need to change the identity transform to a linear transform that takes the sparse part.

You also probably need to name your new constraint in the function, and I would suggest you just to follow BART's implementation. Then you can run your own reconstruction. 

To summarize, to implementation your own reconstruction (BART may not be a good option for some complicated exponential models or non-linear models?), you only need to define you own linear transform operator (for both the data consistency term and the regularization term), and the proximal operator of the regularization term. BART has implemented many linear operators under /scr/linops and many proximal operators under /src/iter. I would suggest you do a survey before you implement your owns.

## Low rank + sparse model as an example
In this model, we assume the multi-frame image we have is composed by two components: low-rank component which has the same size of the multi-frame image (Nx-Ny-Nt), sparse component which only has 1 time frame. So the size of the output should be Nx-Ny-(Nt+1).

For the data consistency term, we need to define a linear transform which outputs the final image given these two components. This operator (named yuxinT0) is defined in someops.c, similar to other operators in BART. It will be chained with the forward_op operator as the forward operator in the data consistency term (in pics.c).

One minor change in function sense_recon2 in recon.c is to add one variable img_dims as the input of the function, which contains the size of the new output (add the time dimension by 1).

For the regularization term, it is pretty similar to the original locally low-rank term and the L1-wavelet term, except we need to define the corresponding linear transforms. These transforms will take the needed part from the final output (size Nx-Ny-(Nt+1)). These two transforms are defined in someops.c (yuxinT1 and yuxinT2), and are called in pics.c.

## Usage
Download the complete code of BART (version 0.3.01). Replace recon.c, recon.h (under /src/sense), someopsc. someops.h (under /src/linops), pics.c (under src) with ones here. 

## Notes
I would suggest you think careufully before you want to make some changes in BART, about where to make these changes, and how to organize the dimension of the data. Usually lots of previous code can be used as a reference.

<!---The plan for this repository is to share my implementation of low-rank + sparse reconstruction based on BART. However, very unfortunately, I could not find my implementation (this is probably one reason why I should use Github). But the implementation should be pretty straightforward after you understand how BART works and what changes you want to make. Hopefully, the comments are helpful enough, so you do not need to suffer my code. --->
