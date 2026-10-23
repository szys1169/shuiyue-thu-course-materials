function t = GanXi_t(a)
%坐标变换矩阵3*3 输入角度a°
lx = cosd(a);  mx = sind(a);
t=[ lx -mx 0;
    mx  lx 0;
    0   0  1;];
end

