# Modifying-BART-for-MRI-reconstruction

[BART](https://mrirecon.github.io/bart/) is a well-designed reconstruction tool for magnetic resonance imaging. There are also plenty examples on their website explaining how to use BART. Here, I want to explain my understanding of BART (more specifically, the pics function in BART), hopefully it will make the use of BART eaiser for you, and even help you write you own reconstruction method. 



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

There are several algorithms to solve this kind of problems (L2 term + constraints, and the proximal operator of commonly used constraints is easy to calculate). FISTA (for one constraint) and ADMM (for more than one constraint) have been implemented. I would recommend [Prof. Stephen Boyd's convex optimization class](http://web.stanford.edu/class/ee364a/) and book if you have interest in how these algorithms work. 

## How to write you own reconstruction based on BART
Sometimes, we may want to change the data consistency term. Here we give one example of including another linear operator (function ** about the forward operator ** about the conjugate operator in .*c) in the data consistency term, so that it becomes $DFSAx - y$. To achieve this, we only need to define the operator A and its transpose operator for gradient calculation. The $A$ we are implementing is equal to [I, I], which can be used for low-rank + sparse reconstruction. 


## Notes
The plan for this repository is to share my implementation of Low-rank + Sparse reconstruction based on BART. However, very unfortunately I could not find my implementation (this is probably one reason why I should use Github). But the implementation should be pretty straightforward after you understand how BART works and what changes you want to make. Hopefully the comments are helpful enough so you do not need to suffer my code. 
