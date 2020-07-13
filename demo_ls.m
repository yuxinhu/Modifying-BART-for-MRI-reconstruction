% Demonstration of the low-rank + sparse model for multi-shot DWI
% reconstruction

%% Load data and set parameters

% Please do not forget to include BART into path!

load('example.mat')
% k: nx - ny - ncoil - nshot
% sens: nx - ny - ncoil

iter = 100; % number of iterations
lambda = 0.0008; % regularization parameter for LLR term

%% shot-LLR recon by BART
k_bart = permute(k(:,:,:,:,1), [1 2 11 3 5:10 4]); 
% This is just to permute the dimension of the k-space to satisify BART's 
% requirement: the first three should be x-y-z, then the forth dimension is
% the coil dimension. We are putting the shot dimension as the time
% dimension in BART and apply LLR along that direction.

sens = permute(sens,[1 2 4 3]);
% Same here, but eaiser since no shot dimension for sensitivity map.

ls = squeeze(bart('pics -m -R X:0.002 -R Y:7:7:0.002 -w 1 -i 100', k_bart,sens));

res = ls(:,:,2:5) + ls(:,:,1);
figure,imshow(fftshift(mean(abs(res),3)',1),[])
