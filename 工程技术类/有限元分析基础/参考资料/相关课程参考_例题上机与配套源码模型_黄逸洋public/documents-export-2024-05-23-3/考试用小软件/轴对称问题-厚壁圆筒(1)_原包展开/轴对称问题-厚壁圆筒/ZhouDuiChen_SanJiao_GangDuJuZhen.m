function [K, D, B]= ZhouDuiChen_SanJiao_GangDuJuZhen(P1,P2,P3,E,mu)
%轴对称三角单元刚度矩阵 K = K(本构矩阵，应变矩阵，面积，类型，厚度)

[ri1,zi1]=deal(P1(1),P1(2));
[rj1,zj1]=deal(P2(1),P2(2));
[rm1,zm1]=deal(P3(1),P3(2));
rc1=(ri1+rj1+rm1)/3;zc1=(zi1+zj1+zm1)/3;
bi1=zj1-zm1;bj1=zm1-zi1;bm1=zi1-zj1;
ci1=-(rj1-rm1);cj1=-(rm1-ri1);cm1=-(ri1-rj1);
ai1=rj1*zm1-rm1*zj1;aj1=rm1*zi1-ri1*zm1;am1=ri1*zj1-rj1*zi1;
A1=(ai1+aj1+am1)/2;
[B1]=1/2/A1*[bi1 0 bj1 0 bm1 0;
              0 ci1 0 cj1 0 cm1;
              2*A1/3/rc1 0 2*A1/3/rc1 0 2*A1/3/rc1 0;
              ci1 bi1 cj1 bj1 cm1 bm1];
          B=B1;
[D1]=E/(1-2*mu)/(1+mu)*[1-mu mu mu 0;
                        mu 1-mu mu 0;
                        mu mu 1-mu 0;
                        0 0 0 (1-2*mu)/2];
             D=D1;       
K=2*pi*rc1*B1'*D1*B1*A1;