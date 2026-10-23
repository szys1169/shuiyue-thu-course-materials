function eldraw2(ex,ey,plotpar,elnum)
 a=size(ex); 
 nel=a(1);nen=a(2); 
 if nargin==2  
      plotpar=[1 1 1];  
 end 
 [s1,s2]=pltstyle(plotpar); 
 x0=sum(ex')/nen;
 y0=sum(ey')/nen; 
 x=ex'; 
 y=ey';   
 xc=x ;
 yc=y;  
 axis('equal') 
 hold on 
 plot(xc,yc,s1)  
 plot(x,y,s2) 
 if nargin==4 
    for i=1:nel 
        h=text(x0(i),y0(i),int2str(elnum(i))); 
        set(h,'fontsize',8); 
    end 
 end 
 xlabel('x'); ylabel('y'); 
 hold off 
end

