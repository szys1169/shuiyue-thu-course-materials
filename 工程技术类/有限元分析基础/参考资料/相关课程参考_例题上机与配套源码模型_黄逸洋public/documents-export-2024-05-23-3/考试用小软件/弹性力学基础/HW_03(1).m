%第三讲求解
%% 参数准备
E=1e7;
miu=0.25;
t=10;
type=2;%1=应力单元，2=应变单元
P1=[2;2];
P2=[4;2];
P3=[4;4];
%% 计算单元应变矩阵[B]本构矩阵[D]
[B,A]=SanJiao_YingBianJuZhen(P1,P2,P3)
D=BenGouJuZhen(E,miu,type)

%% 给定结点位移，求单元应力，主应力，主平面矢量，主角度，Von Mises等效应力
delta=[0.001 0.005 0.001 0.0025 0 0]';
YingLi=D*B*delta
if type==1
    S=[YingLi(1) YingLi(3) 0;YingLi(3) YingLi(2) 0;0 0 0]
else
    S=[YingLi(1) YingLi(3) 0;YingLi(3) YingLi(2) 0;0 0 miu*(YingLi(1)+YingLi(2))]
end
[n,sigma]=eig(S)
sigma=diag(sigma);
[a,b]=max(sigma);
if angle(n(1,b)+n(2,b)*i)<0
    theta=angle(n(1,b)+n(2,b)*i)/pi*180+180
else
    theta=angle(n(1,b)+n(2,b)*i)/pi*180
end
sigma_e=1/sqrt(2)*sqrt((sigma(1)-sigma(2))^2+(sigma(3)-sigma(2))^2+(sigma(1)-sigma(3))^2)

%% 计算三角单元刚度矩阵
K=SanJiao_GangDuJuZhen(D,B,A,type,t)