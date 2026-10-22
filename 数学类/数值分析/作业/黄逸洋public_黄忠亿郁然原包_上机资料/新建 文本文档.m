m = A(1,2) 
J = zeros(10,10)
n=1
x=1
y=2
while m >= 10e-5
for i=1:10
    for j=1:10
        if (i~=j)
            if (A(i,j)>m)
                m = A(i,j)
                x = i
                y = j
            end
        end
    end
end
J=givens(x,y,A)
n+n+1
A=J*A*inv(J)
end