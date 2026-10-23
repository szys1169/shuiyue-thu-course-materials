%第三讲求解
%% 参数准备
E=30e6;
miu=0.25;
t=1;
P1=[0;-1];
P2=[2;0];
P3=[0;1];
%% 计算单元应变矩阵[B]本构矩阵[D]
[B,A]=SanJiao_YingBianJuZhen(P1,P2,P3)
D=BenGouJuZhen(E,miu,1)

%% 给定结点位移，求单元应力，主应力，主平面矢量，主角度，Von Mises等效应力
delta=[0 0.0025 0.0012 0 0 0.0025]';
YingLi=D*B*delta
S=[YingLi(1) YingLi(3) 0;YingLi(3) YingLi(2) 0;0 0 0]
[n,sigma]=eig(S)
sigma=diag(sigma);
[a,b]=max(sigma);
theta=angle(n(1,b)+n(2,b)*i)/pi*180
sigma_e=1/sqrt(2)*sqrt((sigma(1)-sigma(2))^2+(sigma(3)-sigma(2))^2+(sigma(1)-sigma(3))^2)

%% 计算三角单元刚度矩阵
K=SanJiao_GangDuJuZhen(D,B,A,1,1)