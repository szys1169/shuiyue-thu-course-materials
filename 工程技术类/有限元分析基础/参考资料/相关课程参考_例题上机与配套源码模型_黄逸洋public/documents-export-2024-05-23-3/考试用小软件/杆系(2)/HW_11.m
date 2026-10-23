%作业2，混合单元
p1 = [0,0]; p2 = [300,0]; p3 = [600,0]; p4 = [300,200];   %四个结点的坐标
E1 = 207;  Iz = 40*40^3/12;  A1 = 1600;  h = 40; b = 40;%E1 Iz A1为梁的弹性模量，截面惯性矩，截面积,h b高宽
E2 = 69;   A2 = 78.54;                   %二力杆的弹性模量，截面积

k1 = ZTGangDu(E1,A1,Iz,300,0);            %单元1整体刚度矩阵，需要输入长度和角度

k2 = ZTGangDu(E1,A1,Iz,300,0);           %单元2整体刚度矩阵

k3 = Gan_GangDuJuZhen(A2,E2,p2,p4);       %单元3整体刚度矩阵，这里输入的是坐标

contri1 = [ 1 2 3 4 5 6 ];
contri2 = [ 4 5 6 7 8 9 ];
contri3 = [ 4 5 10 11 ];

k = JuZhenhebing(11, k1, contri1, k2, contri2, k3, contri3, 0, 0, 0, 0);   %合并刚度矩阵
disp('k=');vpa(k,4) 

delta_k = [0 0 0 0]';       %已知的位移大小
delta_uk = [3 4 5 6 7 8 9];     %未知位移对应的自由度
F_k = [0 0 0 0 0 -10 0]';     %已知的外载荷大小
F_uk = [1 2 10 11];           %未知的外载荷对应的自由度   一般来说，两个uk拼起来刚好齐了所有自由度

[delta,F] = fangchengqiujie(k, delta_k, delta_uk, F_k, F_uk);
disp('delta=');vpa(delta,4)
disp('F=');vpa(F,4)                              %求解并以四位有效数字显示

% %求解位移分布等，ctrl+T取消多行注释，ctrl+R注释
% delta_1 = [delta(1), delta(2), delta(3), delta(4), delta(5), delta(6)]';  %单元1整体位移
% delta_1 = GanXi_DAT(0)'*delta_1;    %逆变换到局部坐标系下，输入为角度
% uv = GanXi_uv(300, delta_1);
% disp('uv='); vpa(uv,4)           %系数太小说明是计算误差
% 
% F = E1*A1*diff( uv(1) );         %轴向力
% disp('F='); vpa(F,4)
% 
% M = E1*Iz*diff(uv(2),2);         %弯矩
% disp('M='); vpa(M,4)
% 
% V = diff(M);
% disp('V='); vpa(V,4)             %剪力
% 
% sigmax = M*h/2/Iz;
% disp('σmax='); vpa(sigmax,4)    %最大正应力
% 
% Qmax = 1/8*b*h^2;  %对中性轴的最大面积矩
% vmax = V*Qmax/Iz/b;
% disp('τmax='); vpa(vmax,4)    %最大切应力