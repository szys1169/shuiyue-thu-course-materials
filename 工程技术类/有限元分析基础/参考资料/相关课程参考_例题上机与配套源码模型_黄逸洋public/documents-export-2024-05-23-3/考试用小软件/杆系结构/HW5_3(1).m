%% 输入参数
theta = [3/4*pi; pi; -pi/2];
A = 5e-4;
E = 210e9;
L = 5;
kk = 2e6;
k = [A*E/L; A*E/2/L; kk];

%% 节点数
n = 4;
%%
lx = cos(theta);
mx = sin(theta);

%% 前面系数也可以是K
% K = A*E/L * [lx^2, lx*mx, -lx^2, -lx*mx;
%              lx*mx, mx^2, -lx*mx, -mx^2;
%              -lx^2, -lx*mx, lx^2, lx*mx;
%              -lx*mx, -mx^2, lx*mx, mx^2];

contri_1 = [1,2,3,4];
contri_2 = [1,2,5,6];
contri_3 = [1,2,7,8];
i = 1;
K1 = k(i) * [lx(i)^2, lx(i)*mx(i), -lx(i)^2, -lx(i)*mx(i);
             lx(i)*mx(i), mx(i)^2, -lx(i)*mx(i), -mx(i)^2;
             -lx(i)^2, -lx(i)*mx(i), lx(i)^2, lx(i)*mx(i);
             -lx(i)*mx(i), -mx(i)^2, lx(i)*mx(i), mx(i)^2];
i = 2;
K2 = k(i) * [lx(i)^2, lx(i)*mx(i), -lx(i)^2, -lx(i)*mx(i);
             lx(i)*mx(i), mx(i)^2, -lx(i)*mx(i), -mx(i)^2;
             -lx(i)^2, -lx(i)*mx(i), lx(i)^2, lx(i)*mx(i);
             -lx(i)*mx(i), -mx(i)^2, lx(i)*mx(i), mx(i)^2];
i = 3;
K3 = k(i) * [lx(i)^2, lx(i)*mx(i), -lx(i)^2, -lx(i)*mx(i);
             lx(i)*mx(i), mx(i)^2, -lx(i)*mx(i), -mx(i)^2;
             -lx(i)^2, -lx(i)*mx(i), lx(i)^2, lx(i)*mx(i);
             -lx(i)*mx(i), -mx(i)^2, lx(i)*mx(i), mx(i)^2];
         
K_big = JuZhenhebing_modified(8, K1, contri_1, K2, contri_2, K3, contri_3, 0, 0, 0, 0)

