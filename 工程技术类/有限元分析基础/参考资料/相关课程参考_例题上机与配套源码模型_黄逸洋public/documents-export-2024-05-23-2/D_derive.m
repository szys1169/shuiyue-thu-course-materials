function D_derive(E,u)
D=E*[1,u,0;u,1,0;0,0,(1-u)/2]/(1-u*u)
end