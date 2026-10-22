function [B,t] = qrfa(A)
B=A;
t=0;
while(abs(B(10,10)-0.081014052771063)>10^(-10))
    [Q,R]=qr(B);
    B=R*Q;
    t=t+1;
end
end