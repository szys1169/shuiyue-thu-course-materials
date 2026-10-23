%% 输入参数
theta = [3/4*pi; pi; -pi/2];
A = 5e-4;
E = 210e9;
L = 5;
kk = 2e6;
k = [A*E/L; A*E/2/L; kk];
P1=[0,0];
P2=[-5/1.414,5/1.414];
P3=[-10,0];


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

K1=Gan_GangDuJuZhen(A,E,P1,P2)
K2=Gan_GangDuJuZhen(A,E,P1,P3)
K3=TanHuang_GangDuJuZhen(2e6,P1,[0,-1])

K_big = JuZhenhebing(8, K1, contri_1, K2, contri_2, K3, contri_3, 0, 0, 0, 0)

[delta,F]=fangchengqiujie(K_big,[0;0;0;0;0;0],[1,2],[0;-50e3],[3,4,5,6,7,8])
