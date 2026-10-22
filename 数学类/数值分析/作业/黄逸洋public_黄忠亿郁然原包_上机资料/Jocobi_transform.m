function [B,t,k]=Jocobi_transform(A)
flag=1;
delta=0.1;
t=0;
k=0;
while(flag)
    B=A;
    n=10;
    for i=1:n
        for j=i+1:n
            B=A;
            if(abs(B(i,j))>delta)
                if(B(i,i)==B(j,j))
                    sita=pi/4;
                else
                    sita=1/2*atan(2*A(i,j)/(B(j,j)-B(i,i)));
                end
                c=cos(sita);s=sin(sita);
                A([i,j],:)=[c,-s;s,c]*B([i,j],:);
                A(:,[i,j])=B(:,[i,j])*[c,s;-s,c];
                A([i,j],[i,j])=[c,-s;s,c]*B([i,j],[i,j])*[c,s;-s,c];
                k=k+1;
            end
        end
    end
    t=t+1;
    delta=delta/10;
    if (delta<10^(-5))
        flag=0;
    end
end
