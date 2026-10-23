function [Edof]=caldof(Enode,ndof)
 Nele=size(Enode,1); 
 Esize=size(Enode,2)-1; 
 Edof=zeros(Nele,2*Esize+1);
 for i=1:Nele 
     Edof(i,1)=i; 
     for j=1:Esize 
         Edof(i,2*j)=2*(Enode(i,j+1)-1)+1; 
         Edof(i,2*j+1)=2*(Enode(i,j+1)-1)+2; 
     end 
 end
end