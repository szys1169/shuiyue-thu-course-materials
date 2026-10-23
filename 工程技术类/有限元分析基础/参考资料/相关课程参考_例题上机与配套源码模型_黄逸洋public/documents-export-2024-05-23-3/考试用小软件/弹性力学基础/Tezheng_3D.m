function [Fangxiang,Yingli,tn,sigma_n,tao_n] = Tezheng_3D(x,y,xy,z,xz,yz,kx,ky,kz)
%用于求解应力特征值，主应力和主方向. 输入为σx，σy，τxy
%   此处显示详细说明

S=[ x  xy xz;
    xy y  yz;
    xz  yz  z;];
L=sqrt(kx*kx+ky*ky+kz*kz);
n=[kx/L;ky/L;kz/L];
tn=S*n;
sigma_n=n'*tn;
tao_n=sqrt(tn'*tn-sigma_n*sigma_n);

[Fangxiang,Yingli]=eig(S);
disp('记得自己排个序，方向是列向量');
end

