function out = Ban_GangDu(E,v,t,Pi,Pj,Pm,Pp)
%E弹性模量,v=μ泊松比,t厚度, Pi,Pj,Pm,Pp 1*2坐标，i必须为左下角，逆时针
%   此处显示详细说明
syms x y;
D=E/(1-v^2)*[ 1 v 0;
              v 1 0
              0 0 (1-v)/2;];
K = t^3/12*Ban_B(x,y,Pi,Pj,Pm,Pp)'*D*Ban_B(x,y,Pi,Pj,Pm,Pp);
K1=int(K,'x',Pi(1),Pm(1));
out=int(K1,'y',Pi(2),Pm(2));
end

