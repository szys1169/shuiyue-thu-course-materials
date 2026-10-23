function K_derive(theta,A,E,L,u1,v1,u2,v2)
l=cos(theta)
m=sin(theta)
K=A*E/L*[l*l,l*m,-l*l,-l*m;l*m,m*m,-l*m,-m*m;-l*l,-l*m,l*l,l*m;-l*m,-m*m,l*m,m*m]
D=[l,m,0,0;0,0,l,m;]*[u1;v1;u2;v2]
Ei=1/L*[-l,-m,l,m]*[u1;v1;u2;v2]
Sigma=Ei*E
f=A*Sigma
end