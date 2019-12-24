clear;
pic = imread('大作业.png');
pic1 = rgb2gray(pic);
pic2 = histeq(pic1);    %直方图均衡化

pic3 = im2bw(pic1);     %二值化，身体外与肺部为0黑，肉体骨骼为1白
%pic3 = medfilt2(h);                       %对椒盐躁声中值滤波
pic4 = imfill(pic3,'holes');   %填充黑点，分为身体内部1白和身体外部0黑
[width, height] = size(pic4);   %图像分割，0为黑
for i=1:width
    for j=1:height
        if(pic4(i,j)==1)            %二值白色部分,以身体为边界的内部
            if(pic3(i,j)==0)        %
                pic7(i,j)=pic1(i,j);
                pic5(i,j)=255;
                pic6(i,j)=255;
            else
                pic5(i,j)=pic1(i,j);    %
                pic6(i,j)=255;          %外部环境
                pic7(i,j)=255;
            end
        else
            pic6(i,j)=pic1(i,j);
            pic5(i,j)=255;
            pic7(i,j)=255;
        end
    end
end

se = strel('disk',6);
pic8 = imerode(pic7,se);%
pic9 = imerode(pic8,se);%
se = strel('disk',7);
pic10 = imdilate(pic9,se);%
pic11 = imdilate(pic10,se);%

%中间部分效果不好，保持原图
[height, width] = size(pic7);
for i=1:height
    for j=1:width
        if((i>(height/2-40)&&i<(height/2+40))&&(j>(width/2-40)&&j<(width/2+40)))
            m(i,j)=pic7(i,j);
        else
            m(i,j)=pic11(i,j);
        end
    end
end

figure;
subplot(2,2,1);imshow(pic1,[]);title('处理前：');
subplot(2,2,2);imhist(pic1);title('灰度直方图：');
subplot(2,2,3);imshow(pic2,[]);title('直方图均衡化：');
subplot(2,2,4);imhist(pic2);title('直方图均衡化后的图像：');

figure;
subplot(221);imshow(pic4,[]);title('身体外部与内部分界：');
subplot(222);imshow(pic3,[]);title('身体外部、内部、肺部三部分：');
subplot(223);imshow(pic5,[]);title('肉体：');
subplot(224);imshow(pic7,[]);title('肺部：');

figure;
subplot(221);imshow(pic7,[]);title('肺部：');
subplot(222);imshow(pic9,[]);title('第一步：膨胀图像');
subplot(223);imshow(pic11,[]);title('第二步：再腐蚀图像');
subplot(224);imshow(m,[]);title('中间部分“粘连”，保持原样');

image = edge(m,'log',4);
se = strel('disk',1);
pic11 = imdilate(image,se);%膨胀.边界线更清晰
% figure;
% imshow(pic11,[]);
[height, width, floor] = size(pic);
for i=1:height
    for j=1:width
        if(pic11(i,j)==1)
            picc(i,j,1)=255;
            picc(i,j,2)=0;
            picc(i,j,3)=0;
        else
            for k=1:floor
                picc(i,j,k)=pic(i,j,k);
            end
        end
    end
end
figure;
imshow(picc,[]);title('肺部：');

