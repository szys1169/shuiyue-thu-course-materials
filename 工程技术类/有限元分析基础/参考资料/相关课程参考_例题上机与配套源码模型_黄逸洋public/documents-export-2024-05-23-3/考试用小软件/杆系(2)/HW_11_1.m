p1 = [0,0]; p2 = [1,0]; p3 = [2,0]; p4 = [2,-2];   %四个结点的坐标

E1 = 200e9;  Iz = 3e-5;  A1 = 9e-3;  h =0.2; b =0.045;%E1 Iz A1为梁的弹性模量，截面惯性矩，截面积,h b高宽

k1 = ZTGangDu(E1,A1,Iz,1,0);            %单元1整体刚度矩阵，需要输入长度和角度

k2 = ZTGangDu(E1,A1,Iz,1,0);           %单元2整体刚度矩阵

k3 = ZTGangDu(E1,A1,Iz,2,-90);       %单元3整体刚度矩阵，这里输入的是坐标

contri1 = [ 1 2 3 4 5 6 ];
contri2 = [ 4 5 6 7 8 9 ];
contri3 = [ 7,8,9,10,11,12 ];

k = JuZhenhebing(12, k1, contri1, k2, contri2, k3, contri3, 0, 0, 0, 0);

disp('k=');vpa(k,4) 

delta_k=[0 0 0]';
F_k=[4 5 6 7 8 9 10 11 12];
F=[0 -2e4 0 0 0 0 -1e4 0 0]';
F_uk=[1 2 3];

[delta,F] = fangchengqiujie(k, delta_k,F_k, F, F_uk);
disp('delta=');vpa(delta,4)
disp('F=');vpa(F,4)

delta_1 = [delta(1), delta(2), delta(3), delta(4), delta(5), delta(6)]';  %单元1整体位移
delta_1 = GanXi_DAT(0)'*delta_1;    %逆变换到局部坐标系下，输入为角度
uv = GanXi_uv(1, delta_1);
disp('uv='); vpa(uv,4)           %系数太小说明是计算误差

F = E1*A1*diff( uv(1) );         %轴向力
disp('F='); vpa(F,4)

M = E1*Iz*diff(uv(2),2);         %弯矩
disp('M='); vpa(M,4)

V = diff(M);
disp('V='); vpa(V,4)             %剪力

sigmax = M*h/2/Iz;
disp('σmax='); vpa(sigmax,4)    %最大正应力

Qmax = 1/8*b*h^2;  %对中性轴的最大面积矩
vmax = V*Qmax/Iz/b;
disp('τmax='); vpa(vmax,4)    %最大切应力
