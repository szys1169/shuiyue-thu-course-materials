function [a] = newton(b)
a = b - (b^3+2*b^2+10*b-20)/(3*b^2+4*b+10)
end
for j = 2:100
x(j,1)=newton(x(j-1,1))
end