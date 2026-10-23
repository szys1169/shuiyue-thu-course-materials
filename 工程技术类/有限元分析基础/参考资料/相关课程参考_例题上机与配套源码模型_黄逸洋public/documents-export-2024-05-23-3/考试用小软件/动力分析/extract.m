function [ed]=extract(edof,a)
    [nie,n]=size(edof); 

    t=edof(:,2:n); 

    for i = 1:nie 
        ed(i,1:(n-1))=a(t(i,:))'; 
    end 

end

