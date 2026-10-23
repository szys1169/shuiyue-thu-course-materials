function [x,y,J,det_J,B]=Jacobian_4WYN(x1,y1,x2,y2,x3,y3,x4,y4)
%   4结点等参单元[位移模式x,y,雅克比矩阵,其行列式,应变矩阵]
%   输入为4个结点坐标，逆时针选取
syms xi eta;
P1=[x1,y1];
P2=[x2,y2];
P3=[x3,y3];
P4=[x4,y4];
N1=0.25*(1-xi)*(1-eta);
N2=0.25*(1+xi)*(1-eta);
N3=0.25*(1+xi)*(1+eta);
N4=0.25*(1-xi)*(1+eta);
% N=[N1 0 N2 0 N3 0 N4 0;0 N1 0 N2 0 N3 0 N4];
x=simplify( N1*P1(1)+N2*P2(1)+N3*P3(1)+N4*P4(1) );
y=simplify( N1*P1(2)+N2*P2(2)+N3*P3(2)+N4*P4(2) );

N1_xi = diff(N1, xi);
N1_eta = diff(N1, eta);
N2_xi = diff(N2, xi);
N2_eta = diff(N2, eta);
N3_xi = diff(N3, xi);
N3_eta = diff(N3, eta);
N4_xi = diff(N4, xi);
N4_eta = diff(N4, eta);
N_=[N1_xi  0 N2_xi  0 N3_xi  0 N4_xi  0
    N1_eta 0 N2_eta 0 N3_eta 0 N4_eta 0
    0 N1_xi  0 N2_xi  0 N3_xi  0 N4_xi
    0 N1_eta 0 N2_eta 0 N3_eta 0 N4_eta];

J11=diff(x,xi);
J12=diff(y,xi);
J21=diff(x,eta);
J22=diff(y,eta);

J=[J11 J12;J21 J22];
det_J=J11*J22-J12*J21;
J_=1/det_J*[J22 -J12;-J21 J11];
A=[1 0 0 0;0 0 0 1;0 1 1 0];
C=[J_ zeros(2,2);zeros(2,2) J_];
B=A*C*N_;

end