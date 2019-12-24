clear;
pic = imread('t3.jpg');
pic1 = rgb2gray(pic);
pic2 = histeq(pic1);

figure,
subplot(2,2,1);imshow(pic);title('Ori:');
subplot(2,2,2);imshow(uint8(pic1));title('Trans:');
subplot(2,2,3);imshow(uint8(pic2));title('Now:');

figure,
subplot(121);imhist(pic1);title('Ori:');
subplot(122);imhist(pic2);title('Now:');
%imshow(pic);