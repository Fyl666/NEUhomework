clear;
img = imread('大作业.png');
%题目1：转为灰度图，后续imhist输出直方图
img1 = rgb2gray(img);
%题目2：均衡化处理
img2 = histeq(img1);
%输出题目1和2的结果
figure;
subplot(2,2,1);imshow(img1,[]);title('T1:处理前：');
subplot(2,2,2);imhist(img1);title('T1:灰度直方图：');
subplot(2,2,3);imshow(img2,[]);title('T2:均衡化后图像：');
subplot(2,2,4);imhist(img2);title('T2:均衡化后直方图：');

%题目3：
%灰度图像二值化
img3 = im2bw(img1);
%图像填充，身体内部为1，外部为0
img4 = imfill(img3,'holes');
%图像二次分割，以“身体-外界”和“肺部-身体”为两个界限
[width, height] = size(img4);
for i=1:width
    for j=1:height
        if(img4(i,j)==1)
            if(img3(i,j)==0)
                img7(i,j)=img1(i,j);
                img5(i,j)=255;
                img6(i,j)=255;
            else
                img5(i,j)=img1(i,j);
                img6(i,j)=255;
                img7(i,j)=255;
            end
        else
            img6(i,j)=img1(i,j);
            img5(i,j)=255;
            img7(i,j)=255;
        end
    end
end
figure;
subplot(221);imshow(img3,[]);title('T3:三部分：');
subplot(222);imshow(img4,[]);title('T3:背景：');
subplot(223);imshow(img7,[]);title('T3:肺实质：');
subplot(224);imshow(img5,[]);title('T3:其他组织：');

%题目4：
%去掉肺部中的白色小点儿
se = strel('disk',6);
img8 = imerode(img7,se);
%膨胀图像
img9 = imerode(img8,se);
se = strel('disk',7);
img10 = imdilate(img9,se);
%腐蚀图像
img11 = imdilate(img10,se);
%粘连图像
[height, width] = size(img7);
for i=1:height
    for j=1:width
        if((i>(height/2-40)&&i<(height/2+40))&&(j>(width/2-40)&&j<(width/2+40)))
            m(i,j)=img7(i,j);
        else
            m(i,j)=img11(i,j);
        end
    end
end
image = edge(m,'log',4);
se = strel('disk',1);
img11 = imdilate(image,se);
figure;
imshow(img11,[]);title('T4:肺部：');
imwrite(img11,'resultT4.jpg');

%题目5：压缩图像
I = img11;
I = im2double(I); % 数据类型转换
T = dctmtx(8); % 计算二维离散DCT矩阵
dct = @(x)T * x * T'; % 设置函数句柄
B = blkproc(I,[8 8],dct); % 图像块处理
mask = [1 1 1 1 0 0 0 0 % 掩膜
1 1 1 0 0 0 0 0
1 1 0 0 0 0 0 0
1 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0];
B2 = blkproc(B,[8 8],@(x)mask.* x); % 图像块处理
invdct = @(x)T' * x * T; % 设置函数句柄
I2 = blkproc(B2,[8 8],invdct); % 图像块处理
figure, imshow(I2),title('T5:压缩后（压缩比：72.20%）'); % 显示原始图像和压缩重构图像
imwrite(I2,'resultT5.jpg');