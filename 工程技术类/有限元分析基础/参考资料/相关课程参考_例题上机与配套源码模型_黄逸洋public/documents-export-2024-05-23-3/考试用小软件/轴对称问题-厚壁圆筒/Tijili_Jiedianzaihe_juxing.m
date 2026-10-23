function rq =Tijili_Jiedianzaihe_juxing(br,bz,rc,zc,a,b)
x=rc;y=zc;
Ni = (1-(x-rc)/a)*(1-(y-zc)/b)/4;
Nj = (1+(x-rc)/a)*(1-(y-zc)/b)/4;
Nm = (1+(x-rc)/a)*(1+(y-zc)/b)/4;
Np = (1-(x-rc)/a)*(1+(y-zc)/b)/4;

rqi=2*pi*rc*(4*a*b)*Ni*[br bz]';
rqj=2*pi*rc*(4*a*b)*Nj*[br bz]';
rqm=2*pi*rc*(4*a*b)*Nm*[br bz]';
rqp=2*pi*rc*(4*a*b)*Np*[br bz]';

rq=[rqi(1);rqi(2);rqj(1);rqj(2);rqm(1);rqm(2);rqp(1);rqp(2);];


