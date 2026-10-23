function [r]=dengxiaozaihetili(N,b,J,t)
 %b为体力向量，列向量；为形函数矩阵，J为雅克比矩阵
 f=N'*b*det(J)*t;
 r=Gauss_Integral_2d(f,4);

end