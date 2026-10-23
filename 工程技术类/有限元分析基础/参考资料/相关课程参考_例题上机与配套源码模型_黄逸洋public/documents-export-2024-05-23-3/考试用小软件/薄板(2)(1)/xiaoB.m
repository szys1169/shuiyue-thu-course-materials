function out = xiaoB(x,y,xx,yy)
%仅用于中间传递，计算本构矩阵B，用不上
%   此处显示详细说明
out = -[ -6*x/xx^3/8*(1+y/yy)    0    xx/8*(1+y/yy)*(-2/xx^2-6*x/xx^3);
         -6*y/yy^3/8*(1+x/xx)   -yy/8*(1+x/xx)*(-2/yy^2-6*y/yy^3)    0;
         1/4*(2/xx/yy + 1/yy*(1/xx-3*x^2/xx^3) + 1/xx*(1/yy-3*y^2/yy^3))  -yy/4/xx*(1/yy-2*y/yy^2-3*y^2/yy^3)  xx/4/yy*(1/xx-2*x/xx^2-3*x^2/xx^3);]  ;
end

