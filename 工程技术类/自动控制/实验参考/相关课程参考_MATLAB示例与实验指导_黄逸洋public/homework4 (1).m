clc,clear
s=tf('s');
T1=0.002;T2=0.001;K=50;
% G0=K*(s+1)*(0.5*s+1)/s^3/(0.1*s+1)/(0.05*s+1);
G0=K*(0.2*s+1)/s^2/(0.05*s+1)/(0.02*s+1);
% G1=K/s/s;
figure(2)
subplot(1,2,1);
nyquist(G0);
% axis([-1000000,10,-1000000,1000000])
subplot(1,2,2);
margin(G0)
% figure(3)
% subplot(1,2,1);
% nyquist(G1);
% % axis([-1000000,10,-1000000,1000000])
% subplot(1,2,2);
% margin(G1)

% G0=K*(0.5*s+1)*(s+1)/(10*s+1)/(s-1);
% figure(3)
% subplot(1,2,1);
% nyquist(G0);
% subplot(1,2,2);
% margin(G0)

% G0=20*(10*s+1)/s/(100*s+1)/(1/6*s+1)/(0.1*s+1);
% a=feedback(G0,1);
% c=stepinfo(a)
% figure(1)
% plot(b)
% figure(2)
% subplot(1,2,1);
% nyquist(G0);
% subplot(1,2,2);
% margin(G0)

% T2=0.02;T1=0.001;T3=0.0001;
% G0=1*(T2*s+1)/s/s/(T1*s+1)/(T3*s+1);
% subplot(1,2,1);
% nyquist(G0);
% axis([-10000,10,-1,1])
% subplot(1,2,2);
% margin(G0)

% syms T1 T2 T3 y w
% w=((-T1-T2+T3)/T1/T2/T3)^0.5;
% assume(w>0)
% y=1/w^2*((T2^2*w^2+1)/(T1^2*w^2+1)/(T1^3*w^2+1))^0.5;