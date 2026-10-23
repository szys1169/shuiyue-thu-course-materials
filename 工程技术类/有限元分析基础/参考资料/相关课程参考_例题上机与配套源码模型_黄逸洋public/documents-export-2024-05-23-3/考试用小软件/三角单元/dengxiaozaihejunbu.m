function [r]=dengxiaozaihejunbu(qn,qt,i,j,t)
  L=sqrt((i(1)-j(1))^2+(i(2)-j(2))^2);
  nx=(j(2)-i(2))/L;
  ny=-(j(1)-i(1))/L;
  q=[nx,-ny;ny,nx]*[qn;qt];
  qx=q(1);
  qy=q(2);
  r=0.5*t*L*q;  
  disp('注意正方向')
end