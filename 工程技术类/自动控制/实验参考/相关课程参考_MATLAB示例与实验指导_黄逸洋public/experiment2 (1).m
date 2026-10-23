clc,clear
s=tf('s');
G0=100/s/(0.1*s+1)/(0.01*s+1);
G2=(0.044*s+1)/(0.0044*s+1);
G3=(0.5*s+1)/(10*s+1);
G4=(0.47*s+1)*1*(0.23*s+1)/(5.17*s+1)/(0.011*s+1);
%第一问
figure(1)
margin(G0)
%第二问
figure(2)
margin(G2)
figure(3)
margin(G0*G2)
% 第三问
figure(4)
margin(G3)
figure(5)
margin(G0*G3)
% 第四问
figure(6)
margin(G4)
figure(7)
margin(G0*G4)