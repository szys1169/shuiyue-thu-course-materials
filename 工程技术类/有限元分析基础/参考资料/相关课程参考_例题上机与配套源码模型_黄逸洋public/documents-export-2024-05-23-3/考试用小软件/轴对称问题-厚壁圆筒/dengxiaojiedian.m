function [rq]=dengxiaojiedian(choice,r1,z1,r2,z2,qn,qt)
if choice==1 %m-i边界上
    Lmi=((z1-z2)^2+(r1-r2)^2)^0.5;
    nr=(z2-z1)/Lmi;nz=-(r2-r1)/Lmi;
    A=[nr -nz;
        nz nr;]*[qn;qt];
    [qr,qz]=deal(A(1),A(2));
    rq=pi/3*[qr*(r1+2*r2);
             qz*(r1+2*r2);
             0;
             0;
             qr*(2*r1+r2);
             qz*(2*r1+r2)];
end

if choice==2 %i-j边界上
    Lmi=((z1-z2)^2+(r1-r2)^2)^0.5;
    nr=(z2-z1)/Lmi;nz=-(r2-r1)/Lmi;
    A=[nr -nz;
        nz nr;]*[qn;qt];
    [qr,qz]=deal(A(1),A(2));
    rq=pi/3*[qr*(2*r1+r2);
             qz*(2*r1+r2);
             qr*(r1+2*r2);
             qz*(r1+2*r2);
             0;
             0];
end


if choice==3 %j-m边界上
    Lmi=((z1-z2)^2+(r1-r2)^2)^0.5;
    nr=(z2-z1)/Lmi;nz=-(r2-r1)/Lmi;
    A=[nr -nz;
        nz nr;]*[qn;qt];
    [qr,qz]=deal(A(1),A(2));
    rq=pi/3*[0;
             0;
             qr*(2*r1+r2);
             qz*(2*r1+r2);
             qr*(r1+2*r2);
             qz*(r1+2*r2)];
end