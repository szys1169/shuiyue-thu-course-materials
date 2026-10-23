function u = uv(l,delta)
% 计算轴向和横向的位移，输出列向量[u，v]       l 单元长度,delta=δ 局部坐标下的位移向量6*1
% 
syms x;
u=N(x,l)*delta;
end

