function [K,T,L] = Gan_GangDuJuZhen(A,E,i,j)
%   二力杆的刚度矩阵 K = K(截面积，弹性模量，i结点坐标，j结点坐标)
%   坐标变换矩阵 T
%   杆的长度 L
%   输出为4*4矩阵
L=norm(i-j);
k=A*E/L;
lx=(j(1)-i(1))/L;
mx=(j(2)-i(2))/L;
K=k*[lx^2    lx*mx   -lx^2   -lx*mx
     lx*mx   mx^2    -lx*mx  -mx^2
     -lx^2   -lx*mx  lx^2    lx*mx
     -lx*mx  -mx^2   lx*mx   mx^2];
 T=[lx mx 0 0;0 0 lx mx];
end