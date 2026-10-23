function rb =Tijili_Jiedianzaihe_sanjiaoxing(br,bz,P1,P2,P3)
A1=(P1+P2+P3)/3;
rc=A1(1);zc=A1(2);
A=1/2*det([1 P1(1) P1(2);
            1 P2(1) P2(2);
            1 P3(1) P3(2)]);
rb=2*pi/3*rc*A*[br bz br bz br bz]';

