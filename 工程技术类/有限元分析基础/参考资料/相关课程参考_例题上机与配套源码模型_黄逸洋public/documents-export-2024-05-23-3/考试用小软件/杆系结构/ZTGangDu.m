function k = ZTGangDu(E,A,Iz,l,a)
%整体坐标平面梁单元刚度矩阵 E A Iz l a°      E弹性模量 A截面积 Iz截面惯性矩 l梁长度 a方向角
%   此处显示详细说明
T = DAT(a);
k = T*GangDu(E,A,Iz,l)*T';
end

