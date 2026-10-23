%四结点等参单元计算
%% 参数准备
P1=[0 5];
P2=[6 5];
P3=[20 12];
P4=[0 12];
type=1;
t=4;
if type==2
    t=1;
end
E=3e6;
miu=0.2;

%% 雅克比矩阵→刚度矩阵相关计算
[X,Y,J,det_J,B]=Jacobian_4node(P1,P2,P3,P4);
J=simplify(J)
det_J
D=BenGouJuZhen(E,miu,type)
B=simplify(B)
f=B'*D*B*det_J*t;
f=simplify(f);
K=Gauss_Integral_2d(f,4)

%% 等效结点载荷计算
q=[0;-50];
choice=3;
[Jc,r_q]=DengCan_JieDianZaiHe(choice,P3,P4,q,t)
f=[0 0 0 0 0 0 0 0]';
f=r_q+f;

%% 求解计算
delta_known=[0 0 0]';
position_du=[3 5 6 7 8];
F_known=[0 0 -2000 0 -2000]';
position_Fu=[1 2 4];

[delta,F]=fangchengqiujie(K,delta_known,position_du,F_known,position_Fu)
%高斯点位移与应力
[d1,d2,d3,d4,s1,s2,s3,s4]=Gauss_weiyi(delta,D,B)



