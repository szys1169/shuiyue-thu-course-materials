function [K]=assem(edof,K,Ke)
    [nie,n]=size(edof); 
    t=edof(:,2:n); 
    for i = 1:nie 
      K(t(i,:),t(i,:)) = K(t(i,:),t(i,:))+Ke; 
    end 
end