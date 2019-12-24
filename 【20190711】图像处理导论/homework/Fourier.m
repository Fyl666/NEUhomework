imo = imread('tx.jpg');% data
im = rgb2gray(imo);
% compute differencing operator in the frequency domain
nx = size(im, 2);
hx = ceil(nx/2)-1;
ftdiff = (2i*pi/nx)*(0:hx);     % ik 
ftdiff(nx:-1:nx-hx+1) = -ftdiff(2:hx+1);  % correct conjugate symmetry
% compute "gradient" in x using fft
g = ifft2( bsxfun(@times, fft2(im), ftdiff) );
%imshow(g, []);      % see result
figure;
subplot(2,1,1);imshow(imo);title('原图像：');
subplot(2,1,2);imshow(g,[]);title('处理后：');