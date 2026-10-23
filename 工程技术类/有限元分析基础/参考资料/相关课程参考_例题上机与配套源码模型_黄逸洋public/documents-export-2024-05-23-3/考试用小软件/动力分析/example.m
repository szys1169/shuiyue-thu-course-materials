%»®·ÖÍø¸ñ
Enode=[1 1 2;2 2 3;3 3 4;4 4 5;5 5 6;6 6 7;];
ndof=2;
Edof=caldof(Enode,ndof);
E=210e9;
rho=7800;
b=0.02;
h=0.1;
A=b*h;
I=b*h^3/12;
ex=3*[0 1/6;1/6 2/6;2/6 3/6;3/6 4/6;4/6 5/6;5/6 6/6];
ey=zeros(6,2);

K=zeros(14);     
M=zeros(14);
ep=[E A I rho*A];

for i=1:6 
  [k,m]=beam2d(ex(i,:),ey(i,:),ep); 
  K=assem(Edof(i,:),K,k);
  M=assem(Edof(i,:),M,m);   
end

clf;     
eldraw2(ex,ey,[1 2 2],Edof); 
grid;    
title('2-D Frame Structure') 

b=[1 2]'; 
[La,Egv]=eigen(K,M,b); 
Cfreq=sqrt(La); 
Freq=Cfreq/(2*pi); 

figure(1), clf, axis('equal'), hold on, axis off 
magnfac=1; 
title('The first six eigenmodes (Hz)' ) 
for i=1:3; 
  Edb=extract(Edof,Egv(:,i)); 
  ext=ex+(i-1)*4;                eldraw2(ext,ey,[2 3 1]);  
  eldisp2(ext,ey,Edb,[1 2 2],magnfac); 
  FreqText=num2str(Freq(i));     text(4*(i-1)+1.25,1.0,FreqText); 
end; 
eyt=ey-4;  
for i=4:6; 
  Edb=extract(Edof,Egv(:,i)); 
  ext=ex+(i-4)*4;                eldraw2(ext,eyt,[2 3 1]);  
  eldisp2(ext,eyt,Edb,[1 2 2],magnfac); 
  FreqText=num2str(Freq(i));     text(4*(i-4)+1.25,-3.0,FreqText); 
end



