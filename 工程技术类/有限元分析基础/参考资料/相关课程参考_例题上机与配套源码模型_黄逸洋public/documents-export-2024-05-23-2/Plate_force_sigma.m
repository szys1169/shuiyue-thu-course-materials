function Plate_force_sigma(x1,y1,x2,y2,x3,y3,E,u,t,A,U)

b1=y2-y3,b2=y3-y1,b3=y1-y2
c1=-x2+x3,c2=-x3+x1,c3=-x1+x2
B=[b1,0,b2,0,b3,0;0,c1,0,c2,0,c3;c1,b1,c2,b2,c3,b3]*1/A/2
D=E/(1-u*u)*[1,u,0;u,1,0;0,0,(1-u)/2]
K=B'*D*B*t*A
sigma=D*B*U

end