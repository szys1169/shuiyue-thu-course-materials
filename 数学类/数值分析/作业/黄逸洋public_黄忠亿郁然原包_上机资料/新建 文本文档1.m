X=zeros(1,11)
Y=zeros(1,11)
for i=0:10
X(i+1)=-1+2*i/10
Y(i+1)=1/(1+25*x(i+1)^2)
end

m = 10; 
L = ones(m, m);  
for k = 1 : m  
    V = 1;  
    for i = 1 : m
        if k ~= i  
            V = conv(V, poly(X(i))) / (X(k) - X(i));  
        end
    end
    L(k, :) = V;  
end
l = sym(zeros(m, 1));  
for k = 1 : m  
    l(k) = poly2sym(L(k, :));  
end
P = sym(0);  
for k = 1 : m  
    P = P + Y(k) * l(k);
end
fprintf('拉格朗日多项式为：\nP(x)=%s\n', char(P)); 