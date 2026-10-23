function [Fangxiang,Yingli] = TeZheng_2D(x,y,xy)
%用于求解应力特征值，主应力和主方向. 输入为σx，σy，τxy
%   此处显示详细说明

S=[ x  xy 0;
    xy y  0;
    0  0  0;];
[Fangxiang,Yingli]=eig(S)
disp('记得自己排个序，方向是列向量');
end

