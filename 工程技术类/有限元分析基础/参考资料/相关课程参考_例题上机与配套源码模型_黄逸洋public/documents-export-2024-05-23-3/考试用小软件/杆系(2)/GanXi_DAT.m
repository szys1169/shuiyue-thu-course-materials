function T = GanXi_DAT(a)
%坐标变换矩阵6*6 输入角度a°
lx = cosd(a);  mx = sind(a);
T=[ lx -mx 0  0   0  0;
    mx  lx 0  0   0  0;
    0   0  1  0   0  0;
    0   0  0  lx -mx 0;
    0   0  0  mx  lx 0;
    0   0  0  0   0  1;];
    
end

