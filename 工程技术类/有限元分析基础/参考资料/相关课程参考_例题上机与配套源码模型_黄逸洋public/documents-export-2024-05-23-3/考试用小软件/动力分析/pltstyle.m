function [s1,s2]=pltstyle(plotpar)
 if plotpar(1)==1 ; s1='-'; 
 elseif plotpar(1)==2 ; s1=':';
 elseif plotpar(1)==3 ; s1='-.';
 else
     error('??? Error in variable plotpar(1)!');
 end 
  
 if plotpar(2)==1 ; s1=[s1,'k']; 
 elseif plotpar(2)==2 ; s1=[s1,'b'];
 elseif plotpar(2)==3 ; s1=[s1,'m'];
 elseif plotpar(2)==4 ; s1=[s1,'r'];
 else
     error('??? Error in variable plotpar(2)!');
 end 
 
 if plotpar(3)==1 ; s2='ko'; 
 elseif plotpar(3)==2 ; s2='k*';
 elseif plotpar(3)==3 ; s2='ks';
 else
     error('??? Error in variable plotpar(3)!');
 end

end

