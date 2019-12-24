clear;
pic = imread('t2.jpg');
pic = rgb2gray(pic);
[m,n] = size(pic);
pic1 = zeros(m,n);
for i=1:20
    J(:,:,i)=imnoise(pic,'gaussian',0.01);
    pic1 = pic1+double(J(:,:,i));
    if or(or(i==1,i==4),or(i==8,i==16));
        figure,imshow(uint8(pic1/i))
    end
end
%imshow(pic);
%subplot(2, 2, 1);
%imshow(pic);