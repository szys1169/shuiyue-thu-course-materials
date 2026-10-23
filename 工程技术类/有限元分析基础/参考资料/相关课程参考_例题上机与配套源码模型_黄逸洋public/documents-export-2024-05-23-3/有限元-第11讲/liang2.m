clc
clear
global K 
global zuobiao
K=zeros(9,9);
p=1e4;
zuobiao=[0 0; 0.3 0;0.6 0];
jisuan(1,2,0.3);
jisuan(2,3,0.3);
K0=K;
delzy(5);
delzy(2);
delzy(1);
F=[0 0 0 0 -1e4 0]+7.381e-4*[K0(5,3) K0(5,4) K0(5,6) K0(5,7) K0(5,8) K0(5,9)];
die=K\F';
die=[0 0 die(1:2)' -7.381e-4 die(3:6)'];
global dudie
dudie=reshape(die,3,3);
disp("单元1")
zhouweiyi(1,2,0.3);
disp("单元2")
zhouweiyi(2,3,0.3);
function []=zhouweiyi(i,j,l)
E=207e9;
A=40*40e-6;
Iz=(40e-3)^4/12;
b=40e-3;
h=40e-3;
global dudie
die=[dudie(:,i)' dudie(:,j)'];
die=hjisuan(i,j,l,die);
syms x 
y=-h/2;
%uj=zuobiao(j,1);ui=zuobiao(i,1);
Niu=1-x/l;
Nju=x/l;
Niv=1-3*x*x/l/l+2*x*x*x/l/l/l;
Nis=x-2*x*x/l+x*x*x/l/l;
Njv=3*x*x/l/l-2*x*x*x/l/l/l;
Njs=-x*x/l+x*x*x/l/l;
N=[Niu 0 0 Nju 0 0; 0 Niv Nis 0 Njv Njs];
uv=N*die';
disp("轴向位移")
u=vpa(uv(1),4)
disp("横向位移(挠度)")
v=vpa(uv(2),4)
F=E*A*diff(u,x);
disp("轴向力")
F=vpa(F,4)
disp("弯矩")
M=E*Iz*diff(diff(v,x),x);
M=vpa(M,4)
disp("剪力")
V=vpa(diff(M,x),4)
B=[-1/l -y*(-6/l/l+12/l/l/l*x) -y*(-4/l+6/l/l*x) 1/l -y*(-6/l/l-12/l/l/l*x) -y*(-2/l+6/l/l*x)];
% epsion=vpa(B*die',4);
epsion=diff(u,x)-y*diff(diff(v,x),x);
tau=V*A/2*h/4/Iz/b;
disp("最大剪应力")
tau=vpa(tau,4)
disp("最大正应力")
sigam=vpa(E*epsion,4)
% sigam=vpa(M*h/2*Iz,4)
end
function [] = jisuan(i,j,l)
E=207e9;
A=40*40e-6;
Iz=(40e-3)^4/12;
kii=[E*A/l 0 0; 0 12*E*Iz/l^3 6*E*Iz/l^2;0 6*E*Iz/l^2 4*E*Iz/l];
kij=[-E*A/l 0 0; 0 -12*E*Iz/l^3 6*E*Iz/l^2;0 -6*E*Iz/l^2 2*E*Iz/l];
kji=[-E*A/l 0 0; 0 -12*E*Iz/l^3 -6*E*Iz/l^2;0 6*E*Iz/l^2 2*E*Iz/l];
kjj=[E*A/l 0 0; 0 12*E*Iz/l^3 -6*E*Iz/l^2;0 -6*E*Iz/l^2 4*E*Iz/l];
k=[kii kij; kji kjj];
global K 
global zuobiao

lx=zuobiao(j,1)-zuobiao(i,1);
mx=zuobiao(j,2)-zuobiao(i,2);
L=sqrt(lx*lx+mx*mx);
mx=mx/L;
lx=lx/L;
t=[lx -mx 0;mx lx 0; 0 0 1];
o=zeros(3,3);
T=[t o;o t];
k=T*k*T';
a=[3*i-2 3*i-1 3*i 3*j-2 3*j-1 3*j];
for ii=1:6
    for jj=1:6        
        K(a(ii),a(jj))=K(a(ii),a(jj))+k(ii,jj);
    end
end
end
function [] = delzy(i)
global K 
K(i,:)=[];
K(:,i)=[];
end
function die1 = hjisuan(i,j,l,die)
global zuobiao
lx=zuobiao(j,1)-zuobiao(i,1);
mx=zuobiao(j,2)-zuobiao(i,2);
L=sqrt(lx*lx+mx*mx);
mx=mx/L;
lx=lx/L;
t=[lx -mx 0;mx lx 0; 0 0 1];
o=zeros(3,3);
T=[t o;o t];
die1=inv(T)*die';
die1=die1';
end

