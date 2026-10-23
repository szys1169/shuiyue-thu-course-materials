clc,clear
s=tf('s');
T1=0.002;T2=0.001;K=10;

G0=K/s/(s+1)/(2*s+1);

figure(2)
% subplot(1,2,1);
% nyquist(G0);
% % axis([-1000000,10,-1000000,1000000])
% subplot(1,2,2);
margin(G0)