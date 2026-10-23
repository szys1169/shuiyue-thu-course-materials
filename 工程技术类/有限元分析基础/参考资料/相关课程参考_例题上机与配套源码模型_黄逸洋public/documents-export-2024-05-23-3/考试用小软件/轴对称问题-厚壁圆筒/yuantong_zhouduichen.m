%% 习题8-2
%轴对称单元+两个单元求解
%薄壁圆筒，厚壁圆筒承受2000 psi 的内压，圆筒内半径为10 in，外半径为15 in。约束圆筒的轴向（Z 向）位移
%% 参数输入
%输入坐标参数,
P1=[10,0];
P2=[15,0];
P3=[15,1];
P4=[10,1];
%输入材料参数
E=2.8e6;mu=0.3;
%单元1贡献自由度为
F1=[1,2,3,4,5,6];
%单元2贡献自由度为
F2=[1,2,5,6,7,8];
%% 刚度矩阵求解
%单元1刚度矩阵
[K1,D1,B1]=ZhouDuiChen_SanJiao_GangDuJuZhen(P1,P2,P3,E,mu);

%单元1刚度矩阵，贡献自由度（1,2,3,4,5,6）

disp('单元1刚度矩阵如下，贡献自由度为（1,2,3,4,5,6）')
disp(K1);

%单元2刚度矩阵
[K2,D2,B2]=ZhouDuiChen_SanJiao_GangDuJuZhen(P1,P3,P4,E,mu);
disp('单元2刚度矩阵如下，贡献自由度为（1,2,5,6,7,8）')
disp(K2);

K=JuZhenHeBing(8,K1,F1,K2,F2,0,0,0,0,0,0)


%% 等效结点载荷
rq=dengxiaojiedian(1,P4(1),P4(2),P1(1),P1(2),-2000,0);
%注意：
%其中第一个数字为1，表示力作用在边界面m-i上；第一个数字为2，表示力作用在边界面i-j上；第一个数字为3，表示力作用在边界面j-m上；

disp('等效结点载荷为')
disp(rq);

%% 降阶方程
%注意，此处要根据上面得到的等效结点载荷来改变F3的值
delta_known=[0;0;0;0];
position_du=[1 3 5 7];
F_known=2e4*pi*[1;0;0;1];
position_Fu=[2 4 6 8];
[delta,F]=FangChengQiuJie(K,delta_known,position_du,F_known,position_Fu)
%K为总刚度矩阵，delta_known为已知的位移条件（为列向量），position_du为未知的位移在位移向量中的位置，为一个行向量；
  %F_known为一个列向量，表示已知的载荷条件，position_Fu为位置的载荷在力向量中所在的行数，为一个行向量


delta1=[delta(F1(1));delta(F1(2));delta(F1(3));delta(F1(4));delta(F1(5));delta(F1(6));];
delta2=[delta(F2(1));delta(F2(2));delta(F2(3));delta(F2(4));delta(F2(5));delta(F2(6));];
sigma1=D1*B1*delta1;
sigma2=D2*B2*delta2;
sigmac=(sigma1+sigma2)/2;

disp('结点位移delta为')
disp(delta);
disp('三角形单元1形心应力为')
disp(sigma1);
disp('三角形单元2形心应力为')
disp(sigma2);
disp('整体单元形心应力为')
disp(sigmac);