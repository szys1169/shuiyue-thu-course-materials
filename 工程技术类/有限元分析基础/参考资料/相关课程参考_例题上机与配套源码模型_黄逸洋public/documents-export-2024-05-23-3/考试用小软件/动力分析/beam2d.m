function [Ke,Me]=beam2d(ex,ey,ep)
   b=[ ex(2)-ex(1); ey(2)-ey(1) ]; 
   L=sqrt(b'*b); 
    
   E=ep(1);
   A=ep(2);
   I=ep(3);
   m=ep(4); 

   Ke=E*I/L^3*[  12   6*L    -12   6*L; 
                  6*L  4*L^2  -6*L  2*L^2; 
                  -12  -6*L   12    -6*L; 
                  6*L  2*L^2  -6*L  4*L^2]; 
 
   Me=m*L/420*[ 156   22*L   54    -13*L ; 
                 22*L  4*L^2  13*L  -3*L^2 ; 
                 54    13*L   156   -22*L ; 
                 -13*L -3*L^2 -22*L 4*L^2]; 
end

