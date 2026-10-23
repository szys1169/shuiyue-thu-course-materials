function [L,X]=eigen(K,M,b)
  [nd,nd]=size(K); 
  fdof=[1:nd]'; 
 
  if nargin==3 
    pdof=b(:); 
    fdof(pdof)=[];  
    if nargout==2 
      [X1,D]=eig(K(fdof,fdof),M(fdof,fdof)); 
      [nfdof,nfdof]=size(X1); 
      for j=1:nfdof 
        mnorm=sqrt(X1(:,j)'*M(fdof,fdof)*X1(:,j)); 
        X1(:,j)=X1(:,j)/mnorm; 
      end 
      d=diag(D); 
      [L,i]=sort(d); 
      X2=X1(:,i); 
      X=zeros(nd,nfdof); 
      X(fdof,:)=X2; 
    else 
      d=eig(K(fdof,fdof),M(fdof,fdof)); 
      L=sort(d); 
    end 
  else 
    if nargout==2 
      [X1,D]=eig(K,M); 
      for j=1:nd 
        mnorm=sqrt(X1(:,j)'*M*X1(:,j)); 
        X1(:,j)=X1(:,j)/mnorm; 
      end 
      d=diag(D); 
      [L,i]=sort(d); 
      X=X1(:,i); 
    else 
      d=eig(K,M); 
      L=sort(d); 
    end 
  end
end