function equal_point_force(qn,qt,x1,y1,x2,y2,t)
Lm=sqrt((x1-x2)^2+(y1-y2)^2)
nx=(y2-y1)/Lm
ny=-(x2-x1)/Lm
Qxy=[nx,-ny;ny,nx]*[qn;qt]
qx=Qxy(1,1)
qy=Qxy(2,1)
rq=t*Lm/2*[qx;qy;0;0;qx;qy]
end