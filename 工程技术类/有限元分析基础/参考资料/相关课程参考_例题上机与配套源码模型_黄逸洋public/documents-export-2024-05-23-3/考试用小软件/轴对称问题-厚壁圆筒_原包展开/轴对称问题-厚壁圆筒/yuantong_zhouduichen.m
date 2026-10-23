%% 习题8-2
%轴对称单元+两个单元求解
%薄壁圆筒，厚壁圆筒承受2000 psi 的内压，圆筒内半径为10 in，外半径为15 in。约束圆筒的轴向（Z 向）位移
%% 参数输入
%输入坐标参数,
[ri,zi]=deal(10,0);
[rj,zj]=deal(15,0);
[rm,zm]=deal(15,1);
[rp,zp]=deal(10,1);
%输入材料参数
E=2.8e6;mu=0.3;
%单元1贡献自由度为
F1=[1,2,3,4,5,6];
%单元2贡献自由度为
F2=[1,2,5,6,7,8];
%% 刚度矩阵求解
%单元1刚度矩阵
[ri1,zi1]=deal(ri,zi);
[rj1,zj1]=deal(rj,zj);
[rm1,zm1]=deal(rm,zm);
rc1=(ri1+rj1+rm1)/3;zc1=(zi1+zj1+zm1)/3;
bi1=zj1-zm1;bj1=zm1-zi1;bm1=zi1-zj1;
ci1=-(rj1-rm1);cj1=-(rm1-ri1);cm1=-(ri1-rj1);
ai1=rj1*zm1-rm1*zj1;aj1=rm1*zi1-ri1*zm1;am1=ri1*zj1-rj1*zi1;
A1=(ai1+aj1+am1)/2;
[B1]=1/2/A1*[bi1 0 bj1 0 bm1 0;
              0 ci1 0 cj1 0 cm1;
              2*A1/3/rc1 0 2*A1/3/rc1 0 2*A1/3/rc1 0;
              ci1 bi1 cj1 bj1 cm1 bm1];
[D1]=E/(1-2*mu)/(1+mu)*[1-mu mu mu 0;
                        mu 1-mu mu 0;
                        mu mu 1-mu 0;
                        0 0 0 (1-2*mu)/2];
%单元1刚度矩阵，贡献自由度（1,2,3,4,5,6）
K1=2*pi*rc1*B1'*D1*B1*A1;
disp('单元1刚度矩阵如下，贡献自由度为（1,2,3,4,5,6）')
disp(K1);

%单元2刚度矩阵
[ri2,zi2]=deal(ri,zi);
[rj2,zj2]=deal(rm,zm);
[rm2,zm2]=deal(rp,zp);
rc2=(ri2+rj2+rm2)/3;zc2=(zi2+zj2+zm2)/3;
bi2=zj2-zm2;bj2=zm2-zi2;bm2=zi2-zj2;
ci2=-(rj2-rm2);cj2=-(rm2-ri2);cm2=-(ri2-rj2);
ai2=rj2*zm2-rm2*zj2;aj2=rm2*zi2-ri2*zm2;am2=ri2*zj2-rj2*zi2;
A2=(ai2+aj2+am2)/2;
[B2]=1/2/A2*[bi2 0 bj2 0 bm2 0;
             0 ci2 0 cj2 0 cm2;
             2*A2/3/rc2 0 2*A2/3/rc2 0 2*A2/3/rc2 0;
             ci2 bi2 cj2 bj2 cm2 bm2];
[D2]=E/(1-2*mu)/(1+mu)*[1-mu mu mu 0;
                        mu 1-mu mu 0;
                        mu mu 1-mu 0;
                        0 0 0 (1-2*mu)/2];
K2=2*pi*rc2*B2'*D2*B2*A2;
disp('单元2刚度矩阵如下，贡献自由度为（1,2,5,6,7,8）')
disp(K2);

K=zeros(8,8);
for i=1:6
    for j=1:6
        K(F1(i),F1(j))=K(F1(i),F1(j))+K1(i,j);
    end 
end 
for i=1:6
    for j=1:6
        K(F2(i),F2(j))=K(F2(i),F2(j))+K2(i,j);
    end 
end 
disp('叠加得整体刚度矩阵如下')
disp(K);

%% 等效结点载荷
rq=dengxiaojiedian(1,rm2,zm2,ri2,zi2,-2000,0);
%注意：
%其中第一个数字为1，表示力作用在边界面m-i上；第一个数字为2，表示力作用在边界面i-j上；第一个数字为3，表示力作用在边界面j-m上；

disp('等效结点载荷为')
disp(rq);

%% 降阶方程
%注意，此处要根据上面得到的等效结点载荷来改变F3的值
K_d=zeros(4,4);
F3=[1 3 5 7];
for i=1:4
    for j=1:4
        K_d(i,j)=K(F3(i),F3(j));
    end 
end 
b=2*1e4*pi*[1;0;0;1];
r=K_d\b;

delta=[r(1);0;r(2);0;r(3);0;r(4);0];
delta1=[r(1);0;r(2);0;r(3);0];
delta2=[r(1);0;r(3);0;r(4);0];
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