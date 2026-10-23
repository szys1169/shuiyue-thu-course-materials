%极坐标
clc
clear
global K 
global zuobiao
K=zeros(8,8);
zuobiao=[0 0; 0 3; 5 -3;5 3];
jisuan(1,3);
jisuan(1,4);
jisuan(1,2);
jisuan(3,4);
jisuan(2,4);
% K=7e4*K;
K0=K;
delzy(3);
delzy(3);
R=[0 0 20 0 0 0];
a=30/180*pi;
c=[sin(a) cos(a) 0 0 0 0];
q=0;
%Lagrange
D1=[R q]/[K c';c 0]
%Penalty Function
u=abs(max(max(K)))*1e5;
D2=R/(K+u*(c'*c))
F=K0*[D2(1:2) 0 0 D2(3:6)]';
F'
global delta
delta=reshape([D2(1:2) 0 0 D2(3:6)],2,4);
hjisuan(1,3);
hjisuan(1,4);
hjisuan(1,2);
hjisuan(3,4);
hjisuan(2,4);
function [] = jisuan(i,j)
global K 
global zuobiao
E=70;
A=1e3;
lx=zuobiao(j,1)-zuobiao(i,1);
mx=zuobiao(j,2)-zuobiao(i,2);
L=sqrt(lx*lx+mx*mx);
mx=mx/L;
lx=lx/L;
T=[lx mx 0 0; 0 0 lx mx];
k=A*E/L*T'*[1 -1;-1 1]*T;
% k=1/L*[lx*lx lx*mx -lx*lx -lx*mx;lx*mx mx*mx -lx*mx -mx*mx;-lx*lx -lx*mx lx*lx lx*mx;-lx*mx -mx*mx lx*mx mx*mx]
a=[2*i-1 2*i 2*j-1 2*j];
for ii=1:4
    for jj=1:4        
        K(a(ii),a(jj))=K(a(ii),a(jj))+k(ii,jj);
    end
end
end
function [] = hjisuan(i,j)
E=70;
A=1e3;
global K 
global zuobiao
lx=zuobiao(j,1)-zuobiao(i,1);
mx=zuobiao(j,2)-zuobiao(i,2);
L=sqrt(lx*lx+mx*mx);
mx=mx/L;
lx=lx/L;
%k=1/L*[lx*lx lx*mx -lx*lx -lx*mx;lx*mx mx*mx -lx*mx -mx*mx;-lx*lx -lx*mx lx*lx lx*mx;-lx*mx -mx*mx lx*mx mx*mx]
T=[lx mx 0 0; 0 0 lx mx];
global delta
D=[delta(:,i)' delta(:,j)']';
d=T*D;%单元内位移
k=A*E/L*T'*[1 -1;-1 1]*T
epsilon=1/L*[-1 1]*T*D;%应变
sigma=E*epsilon;%应力
f=A*sigma%单元轴向力
end
function [] = delzy(i)
global K 
K(i,:)=[];
K(:,i)=[];
end
