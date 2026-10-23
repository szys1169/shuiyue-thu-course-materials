function  [magnfac]=eldisp2(ex,ey,ed,plotpar,magnfac) 
 dxmax=max(max(ex')-min(ex')); dymax=max(max(ey')-min(ey')); 
 dlmax=max(dxmax,dymax); 
 edmax=max(max(abs(ed(:,[1 3])))); 
 krel=0.1; 
  
 if nargin==3  
      plotpar=[2 1 1]; magnfac=krel*dlmax/edmax; 
 elseif nargin==4 
      magnfac=krel*dlmax/edmax; 
 end  
  [s1,s2]=pltstyle(plotpar); 
  k=magnfac; 
  
   x=ex';  
   y=(ey+k*ed(:,[1 3]))'; 
   [exc,eyc]=beam2crd(ex,ey,ed,k); 
   xc=exc'; 
   yc=eyc'; 
      
    axis('equal') 
    hold on 
    plot(xc,yc,s1) 
    plot(x,y,s2) 
    hold off 
end

