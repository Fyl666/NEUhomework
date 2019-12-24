clear;
pic = imread('t3.jpg');
pich = rgb2gray(pic);

[width, height] = size(pich);
T1=180;
for i=1:width
    for j=1:height
        if(pich(i,j)<T1)
            BW1(i,j)=0;
        else
            BW1(i,j)=1;
        end
    end
end
T2=graythresh(pic);
BW2=im2bw(pic,T2);
L = watershed(pich);
Lrgb = label2rgb(L);
figure;
subplot(3,3,1);imshow(pich);title('1');
subplot(3,3,2);imshow(BW1);title('2');
subplot(3,3,3);imshow(BW2);title('3');
subplot(3,3,4);imshow(Lrgb);title('4');