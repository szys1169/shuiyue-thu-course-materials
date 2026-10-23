x=[0:0.01:1];
u=9.444E-3+0*x;
v=2.778E-4.*x.*x.*x-1.667E-3.*x.*x-8.333E-3.*x-1.111E-5;
% plot(x,v)
% xlabel('x/m')
% ylabel('v/m')
% title('单元3横向位移')

% F=0.*x-0
% plot(x,F)
% xlabel('x/m')
% ylabel('F/N')
% title('单元3轴力')

% M=10000.*x-20000
% plot(x,M)
% xlabel('x/m')
% ylabel('M/Nm')
% title('单元3弯矩')

% V=10000+0.*x
% plot(x,V)
% xlabel('x/m')
% ylabel('V/N')
% title('单元3剪力')

% sigma=3.33e7.*x-6.67e7
% plot(x,sigma)
% xlabel('x/m')
% ylabel('σ/N/m2')
% title('单元3最大正应力')

tao=0.*x+1.67e6
plot(x,tao)
xlabel('x/m')
ylabel('τ/N/m2')
title('单元3最大剪力')