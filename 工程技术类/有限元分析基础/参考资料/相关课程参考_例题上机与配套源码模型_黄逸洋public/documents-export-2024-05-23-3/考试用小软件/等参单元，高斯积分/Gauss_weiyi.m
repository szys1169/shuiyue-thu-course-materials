function [d1,d2,d3,d4,s1,s2,s3,s4]=Gauss_weiyi(delta,D,B)

syms xi eta;

N1=0.25*(1-xi)*(1-eta);
N2=0.25*(1+xi)*(1-eta);
N3=0.25*(1+xi)*(1+eta);
N4=0.25*(1-xi)*(1+eta);

point_x = [-0.57735 -0.57735 0.57735 0.57735];
point_y = [-0.57735 0.57735 -0.57735 0.57735];
d=zeros(2,4);
s=zeros(3,4);
for i=1:4
    xi=point_x(i);
    eta=point_y(i);
    u=eval(N1)*delta(1)+eval(N2)*delta(3)+eval(N3)*delta(5)+eval(N4)*delta(7);
    v=eval(N1)*delta(2)+eval(N2)*delta(4)+eval(N3)*delta(6)+eval(N4)*delta(8);
    d(:,i)=[u;v];
    s(:,i)=D*eval(B)*delta;
end
d1=d(:,1);
d2=d(:,2);
d3=d(:,3);
d4=d(:,4);
s1=s(:,1);
s2=s(:,2);
s3=s(:,3);
s4=s(:,4);
end