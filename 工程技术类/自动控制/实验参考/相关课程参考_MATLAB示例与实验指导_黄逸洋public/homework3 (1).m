clc,clear
%% 6.2
syms y s
y=simplify(s*(s+4)*(s+8)*(s^2+2*s+5))
syms K
a=[1 4];b=[1 0];c=[1 8];d=[1 2 5];
e=conv(a,conv(b,conv(c,d)));
e1=conv(polyder(e),[1 2])-e;
polyval(e,-6.4776)
% f=poly2str(e,'s');
 G=tf([1 2],e);
 Gc=feedback(G,1);
 num=[1 2];
 den=e;
 rlocus(num,den)
 
%% P460
% num=[1 3 3.25];
% den=conv([1 0 0],conv([1 0.5],conv([1 8],[1 10])));
% rlocus(num,den)
%% 6.5
% num=conv([1 2],[1 3]);
% den=conv([1 0],[1 1]);
% rlocus(num,den)
% axis equal
%% 6.8
% num=[1];
% for a=1:10
%     den=conv([1 0],conv([1 10^a],[1 1]));
%     rlocus(num,den);hold on
%     scatter(10^a,3^0.5*10^a);
% end
%%
% num=[1];
% a=1000000000000000000000;
%  den=conv([1 0],conv([1 a],[1 1]));
%     rlocus(num,den);
%% ¿Î¼þ
% num=[1];
% den=[1 1 0];
% rlocus(num,den)
%% 6.11
% num=[-3 1];
% den=[3 1 0];
% rlocus(num,den)
% axis equal