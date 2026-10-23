function D=calD(E,u,s)
if s=='应力'
    D=E/(1-u*u)*[1 u 0;u 1 0;0 0 (1-u)/2];%平面应力
elseif s=='应变' 
  D=E/(1+u)/(1-2*u)*[1-u u 0; u 1-u 0;0 0 (1-2*u)/2];
else 
  D=NAN;
end
%D=E/(1+u)/(1-2*u)*[1-u u 0; u 1-u 0;0 0 (1-2*u)/2];