function k = GangDu(E,A,Iz,l)
%  局部坐标平面梁单元刚度矩阵 E A Iz l        E弹性模量 A截面积 Iz截面惯性矩 l梁长度
a = E*A/l;
b = E*Iz/l;

k=[ a  0         0    -a  0         0;
    0  12*b/l^2  6*b/l 0 -12*b/l^2  6*b/l;
    0  6*b/l     4*b   0 -6*b/l     2*b;
   -a  0         0     a  0         0;
    0 -12*b/l^2 -6*b/l 0  12*b/l^2 -6*b/l;
    0  6*b/l     2*b   0 -6*b/l     4*b;];

end

