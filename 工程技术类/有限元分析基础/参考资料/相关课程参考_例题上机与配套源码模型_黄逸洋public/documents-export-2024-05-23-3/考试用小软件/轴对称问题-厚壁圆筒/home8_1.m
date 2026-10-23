syms g gamma omega a
rc=4.5*a;zc=0.5*a;
b=1/g*[gamma*omega^2*rc -gamma*g]';
rb1 =Tijili_Jiedianzaihe_juxing(b(1),b(2),rc,zc,a/2,a/2)

%Èý½ÇÐÎ
P1=[4*a,0];
P2=[5*a,0];
P3=[4*a,a];
A1=(P1+P2+P3)/3;
rc=A1(1);zc=A1(2);
br=1/g*gamma*omega^2*rc;
bz=-gamma;
rb2 =Tijili_Jiedianzaihe_sanjiaoxing(br,bz,P1,P2,P3)

