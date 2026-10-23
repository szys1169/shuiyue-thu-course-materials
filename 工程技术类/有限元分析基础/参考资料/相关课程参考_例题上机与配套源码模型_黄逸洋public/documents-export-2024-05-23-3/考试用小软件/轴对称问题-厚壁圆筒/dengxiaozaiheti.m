function [r_b]=dengxiaozaiheti(b,rc,A,n)

a=2*pi*rc*A*b(1)/3;
d=2*pi*rc*A*b(2)/3;
r_b=zeros(n,1);

for i=1:n
 if mod(i,2)==0
    r_b(i)=d;
 else
    r_b(i)=a;
 end

end