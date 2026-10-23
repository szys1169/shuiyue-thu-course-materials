p1 = [0,5]; p2 = [6,5]; p3 = [20,12]; p4 = [0,12];   %四节点坐标
t = 4;  E = 3e6;  miu = 0.2; q = [0 -50]';    % 厚度  弹性模量  泊松比  均布力

[x,y,J,det_J,B] = Jacobian_4node(p1,p2,p3,p4);
D = BenGouJuZhen(E,miu,1);
f = B'*D*B*t*det_J;    %被积函数
disp('刚度矩阵k = ')
k = Gauss_Integral_2d(f,4)         %2维4节点高斯积分，计算刚度矩阵

[Jc,r_q] = DengCan_JieDianZaiHe(3,p3,p4,q,4)    %计算等效节点载荷

%根据计算得到的载荷调整参数求解
delta_k = [0 0 0]';       %已知的位移大小
delta_uk = [3 5 6 7 8];     %未知位移对应的自由度
F_k = [0 0 -2000 0 -2000]';     %已知的外载荷大小
F_uk = [1 2 4];           %未知的外载荷对应的自由度   一般来说，两个uk拼起来刚好齐了所有自由度

[delta,F] = fangchengqiujie(k, delta_k, delta_uk, F_k, F_uk);
disp('位移delta=');vpa(delta,4)
disp('外载荷F=');vpa(F,4)                              %求解并以四位有效数字显示

%高斯点位移与应力
[d1,d2,d3,d4,s1,s2,s3,s4]=Gauss_weiyi(delta,D,B)

