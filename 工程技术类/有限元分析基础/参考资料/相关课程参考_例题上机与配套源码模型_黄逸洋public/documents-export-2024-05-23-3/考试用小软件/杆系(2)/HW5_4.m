%% 点坐标，系统参数
P1 = [0, 0];
P2 = [20, 0];
P3 = [20, 10];
P4 = [0, 10];

t = 1;
E = 30e6;
mu = 0.3;

%% 求解各单元刚度
num_nodes = 4;
dim_matrix = 8;
contri_1 = [1,2,3,4,5,6];
contri_2 = [1,2,5,6,7,8];

D = BenGouJuZhen(E, mu, 1);
[B1, A1] = SanJiao_YingBianJuZhen(P1, P2, P3);
[B2, A2] = SanJiao_YingBianJuZhen(P1, P3, P4);

K1 = SanJiao_GangDuJuZhen(D, B1, A1, 1, t)
K2 = SanJiao_GangDuJuZhen(D, B2, A2, 1, t)

%% 单元组集
K_big = JuZhenhebing(dim_matrix, K1, contri_1, K2, contri_2, 0, 0, 0, 0, 0, 0)


