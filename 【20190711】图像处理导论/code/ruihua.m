clear;
pic = imread('test.jpg');
pich = rgb2gray(pic);
pict = imgradient(pich);
[width, height] = size(pict);
T1=120;
for i=1:width
    for j=1:height
        if(pict(i,j)<T1)
            BW1(i,j)=0;
        else
            BW1(i,j)=250;
        end
    end
end

figure;
subplot(2,2,1);imshow(pic);title('1');
subplot(2,2,2);imshow(BW1);title('2');
% imshow(BW1);