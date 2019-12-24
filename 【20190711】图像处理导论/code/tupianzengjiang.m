clear;
pic = imread('test.jpg');
pic = rgb2gray(pic);
[m,n] = size(pic);
pic1 = zeros(m,n);

g = imadjust(pic,[0,1],[0.7,1]);
imshow(g);