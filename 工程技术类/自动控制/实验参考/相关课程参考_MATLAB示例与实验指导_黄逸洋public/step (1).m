clc,clear
% %%
% G=tf([16],[1 1 16]);
% figure(1)
% step(G)
% G1=tf([16],[1 4.2 16]);
% figure(2)
% 
% num=[16];
% den=[1 1 16];
% t=0:0.1:10; u=t;
% z=lsim(num,den,u,t);
%  plot(t,z);hold on;
%  m=-z'+u;
%  plot(t,m)
%%
%%

figure(1)

G1=tf([16],[1 4.2 16]);step(G1)
figure(2)

num=[16];
den=[1 4.2 16];
t=0:0.1:10; u=t;
z=lsim(num,den,u,t);
 plot(t,z);hold on;
 m=-z'+u;
 plot(t,m)