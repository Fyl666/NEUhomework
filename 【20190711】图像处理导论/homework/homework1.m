clear;
pic = imread('t3.jpg');
pic1 = rgb2gray(pic);
pic21 = imnoise(pic1,'gaussian',0.01,0);
%目前保持平滑性，仅增加1%扰动，第四个参数不为0则不考虑平滑
pic22 = imnoise(pic21,'salt & pepper',0.08);
%第三个参数范围[0,1]，越大噪声越大
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%均值滤波的实现，也可以使用自带函数filter2(fspecial('average',n);,g)/255; 
%详见：http://www.voidcn.com/article/p-szxnlgkm-gh.html
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
n = 3; %模板大小
template = ones(n);
[height, width] = size(pic22);
x1 = double(pic22);
x2 = x1;
for i = 1:height-n+1
    for j = 1:width-n+1
        c = x1(i:i+n-1,j:j+n-1).*template;
        s = sum(sum(c));
        x2(i+(n-1)/2,j+(n-1)/2) = s/(n*n);
    end
end
pic23 = uint8(x2);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%中值滤波的实现，也可以使用自带函数medfilt2(g,[n2 n2]);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
[height, width] = size(pic23);
x3 = double(pic23);
x4 = x3;
for i = 1:height-n+1
    for j = 1:width-n+1
        c = x1(i:i+n-1,j:j+n-1);
        e = c(1,:);
        for k = 2:n
            e = [e, c(k, :)];
        end
        tmp = median(e);
        x4(i+(n-1)/2,j+(n-1)/2) = tmp;
    end
end
pic24 = uint8(x4);


figure;
subplot(2,2,1);imshow(pic21);title('1.高斯噪声(基于原图):'); 
subplot(2,2,2);imshow(pic22);title('2.椒盐噪声(基于图1):');
subplot(2,2,3);imshow(pic23);title('3.均值滤波(基于图2):');
subplot(2,2,4);imshow(pic24);title('4.中值滤波(基于图3):');

