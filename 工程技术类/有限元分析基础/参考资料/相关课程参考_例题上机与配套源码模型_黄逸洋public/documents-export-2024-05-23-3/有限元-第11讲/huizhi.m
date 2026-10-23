function [] = huizhi(f,l,s)
X=0:0.01:l;
for i=1:size(X,2)
    x=X(i);
    sq(i)=subs(f);
end
 figure
 plot(X,sq)
title(s)