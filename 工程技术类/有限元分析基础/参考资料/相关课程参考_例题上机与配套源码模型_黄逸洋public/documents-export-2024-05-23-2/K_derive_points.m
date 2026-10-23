function K_derive_points(x1,y1,x2,y2,A,E,L,u1,v1,u2,v2)
length=sqrt((x2-x1)^2+(y2-y1)^2)
l=(x2-x1)/length
m=(y2-y1)/length
K=A*E/L*[l*l,l*m,-l*l,-l*m;l*m,m*m,-l*m,-m*m;-l*l,-l*m,l*l,l*m;-l*m,-m*m,l*m,m*m]
D=[l,m,0,0;0,0,l,m;]*[u1;v1;u2;v2]
Ei=1/L*[-l,-m,l,m]*[u1;v1;u2;v2]
Sigma=Ei*E
f=A*Sigma
end