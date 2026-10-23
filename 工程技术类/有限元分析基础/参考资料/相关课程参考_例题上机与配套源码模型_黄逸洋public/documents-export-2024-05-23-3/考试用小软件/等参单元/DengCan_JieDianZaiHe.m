function [Jc,r_q]=DengCan_JieDianZaiHe(choice,P1,P2,q,t)
%   4结点等参单元[雅克比，面力]
%   输入为choice哪一条边，2个结点坐标，逆时针选取，二维列向量均布载荷q，厚度t
syms xi;
if choice==1
    Nc=[(1-xi)/2 0 (1+xi)/2 0 0 0 0 0
        0 (1-xi)/2 0 (1+xi)/2 0 0 0 0];
elseif choice==2
    Nc=[0 0 (1-xi)/2 0 (1+xi)/2 0 0 0
        0 0 0 (1-xi)/2 0 (1+xi)/2 0 0];
elseif choice==3
    Nc=[0 0 0 0 (1-xi)/2 0 (1+xi)/2 0
        0 0 0 0 0 (1-xi)/2 0 (1+xi)/2];
elseif choice==4
    Nc=[(1+xi)/2 0 0 0 0 0 (1-xi)/2 0
        0 (1+xi)/2 0 0 0 0 0 (1-xi)/2];
end
x_a=(P2(1)-P1(1))/2;
y_a=(P2(2)-P1(2))/2;
Jc=sqrt(x_a^2+y_a^2);
% nx=y_a/Jc;
% ny=-x_a/Jc;
r_q=t*Gauss_Integral_1d(Nc'*q*Jc,3);

end