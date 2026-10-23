%第四讲求解
%% 参数准备
A=2;
E=30e6;
L=60;
alpha=30;
P1=[0;0];
P2=L*[cos(alpha*pi/180);sin(alpha*pi/180)];

%% 计算二力杆单元刚度方程[K]
[K,T,L]=Gan_GangDuJuZhen(A,E,P1,P2)

%% 给定单元结点位移，计算轴向位移、应变、应力和轴向力
delta=[0.1 0 0.2 0.3]';
d=T*delta
epsilon=1/L*[-1 1]*d
sigma=E*epsilon
f=A*sigma
