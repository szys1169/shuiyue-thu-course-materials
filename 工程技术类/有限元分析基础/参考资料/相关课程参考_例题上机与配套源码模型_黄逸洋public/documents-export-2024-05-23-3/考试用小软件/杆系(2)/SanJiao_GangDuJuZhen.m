function K = SanJiao_GangDuJuZhen(D,B,A,type,t)
%三节点三角单元刚度矩阵 K = K(本构矩阵，应变矩阵，面积，类型，厚度)
%类型=1=平面应  力
%类型=2=平面应  变

if type==1
    K=B'*D*B*t*A;
elseif type==2
    K=B'*D*B*A;
end