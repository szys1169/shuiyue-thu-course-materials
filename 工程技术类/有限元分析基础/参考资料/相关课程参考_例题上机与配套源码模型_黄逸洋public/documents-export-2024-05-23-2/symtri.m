function symtri(ri,zi,rj,zj,rm,zm,E,u,A)
% 轴对称三角形单元
D=E/(1+u)/(1-2*u)*[1-u,u,u,0;u,1-u,u,0;u,u,1-u,0;0,0,0,0.5-u;];
bi=zj-zm;
bj=zm-zi;
bm=zi-zj;
ci=rm-rj;
cj=ri-rm;
cm=rj-ri;
ai=rj*zm-rm*zj;
aj=rm*zi-ri*zm;
am=ri*zj-rj*zi;
rc=(ri+rj+rm)/3;
fai=2*A/3/rc;
fi=(ai+12.5*bi+0.5*zi)/12.5;
fj=(aj+12.5*bj+0.5*zj)/12.5;
fm=(am+12.5*bm+0.5*zm)/12.5;
B=[bi,0,bj,0,bm,0;0,ci,0,cj,0,cm;fai,0,fai,0,fai,0;ci,bi,cj,bj,cm,bm;]/2/A;
K=2*pi*rc*B'*D*B*A;
Ks=[K(1,1),K(1,3),K(1,5);K(3,1),K(3,3),K(3,5);K(5,1),K(5,3),K(5,5)];
Kss=inv(Ks)
F=[20000*pi;0;20000*pi];
delta=Kss*F;
delta_full=[delta(1);0;delta(2);0;delta(3);0;];
Bf=[bi,0,bj,0,bm,0;0,ci,0,cj,0,cm;fi,0,fj,0,fm,0;ci,bi,cj,bj,cm,bm;]/2/A;
sigma=D*Bf*delta_full;
end