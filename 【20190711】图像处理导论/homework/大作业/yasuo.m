img = imread('大作业.png');
%题目1：转为灰度图，后续imhist输出直方图
I = rgb2gray(img); %输入灰度图像
I = im2double(I);
D = dctmtx(8);
C = blkproc(I,[8,8],'P1*x*P2',D,D');  %D'为D的转置
mask1=[1 1 1 1 1 0 0 0
1 1 1 1 0 0 0 0
1 1 1 0 0 0 0 0
1 1 0 0 0 0 0 0
1 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0];
mask2=[1 1 1 1 0 0 0 0
1 1 1 0 0 0 0 0
1 1 0 0 0 0 0 0
1 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0];
mask3=[1 1 0 0 0 0 0 0
1 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0];
 
X = blkproc(C,[8,8],'P1.*x',mask1);  %保留15个系数
I1  = blkproc(X,[8,8],'P1*x*P2',D',D);    %重构图像
X2 = blkproc(C,[8,8],'P1.*x',mask2);  %保留10个系数
I2  = blkproc(X2,[8,8],'P1*x*P2',D',D);    %重构图像
X3 = blkproc(C,[8,8],'P1.*x',mask3);   %保留3个系数
I3  = blkproc(X3,[8,8],'P1*x*P2',D',D);    %重构图像
subplot(2,2,1);imshow(I);
subplot(2,2,2);imshow(I1);
subplot(2,2,3);imshow(I2);
subplot(2,2,4);imshow(I3);