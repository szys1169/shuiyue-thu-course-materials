function K = TanHuang_GangDuJuZhen(k,i,j)
%   弹簧的刚度矩阵 K = K(弹簧刚度，i结点坐标，j结点坐标)
%   输出为4*4矩阵
L=norm(i-j);
lx=(i(2)-i(1))/L;
mx=(j(2)-j(1))/L;
K=k*[lx^2    lx*mx   -lx^2   -lx*mx
     lx*mx   mx^2    -lx*mx  -mx^2
     -lx^2   -lx*mx  lx^2    lx*mx
     -lx*mx  -mx^2   lx*mx   mx^2];
end