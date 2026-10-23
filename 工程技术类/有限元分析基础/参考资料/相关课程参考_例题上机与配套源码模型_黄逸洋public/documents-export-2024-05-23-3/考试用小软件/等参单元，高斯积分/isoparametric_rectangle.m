function [ B, J ] = isoparametric_rectangle(x1,y1, x2,y2, x3,y3, x4,y4)
% 输入：子单元中4个点坐标; D-本构矩阵
% 输出：B-应变矩阵; J-雅克比矩阵
syms xi eta
N1 = (1-xi)*(1-eta)/4;
N2 = (1+xi)*(1-eta)/4;
N3 = (1+xi)*(1+eta)/4;
N4 = (1-xi)*(1+eta)/4;

N1_xi = diff(N1, xi);
N1_eta = diff(N1, eta);
N2_xi = diff(N2, xi);
N2_eta = diff(N2, eta);
N3_xi = diff(N3, xi);
N3_eta = diff(N3, eta);
N4_xi = diff(N4, xi);
N4_eta = diff(N4, eta);

front = [1 0 0 0; 0 0 0 1; 0 1 1 0];

J11 = N1_xi*x1 + N2_xi*x2 + N3_xi*x3 + N4_xi*x4;
J12 = N1_xi*y1 + N2_xi*y2 + N3_xi*y3 + N4_xi*y4;
J21 = N1_eta*x1 + N2_eta*x2 + N3_eta*x3 + N4_eta*x4;
J22 = N1_eta*y1 + N2_eta*y2 + N3_eta*y3 + N4_eta*y4;

J = simplify([J11 J12; J21 J22]);
J_cap = inv(J);
JJ = simplify([J_cap, zeros(2,2); zeros(2,2), J_cap]);
N = [N1_xi, 0, N2_xi, 0, N3_xi, 0, N4_xi, 0;
     N1_eta, 0, N2_eta, 0, N3_eta, 0, N4_eta, 0;
     0, N1_xi, 0, N2_xi, 0, N3_xi, 0, N4_xi;
     0, N1_eta, 0, N2_eta, 0, N3_eta, 0, N4_eta];

B = simplify(front * JJ * N);

end

