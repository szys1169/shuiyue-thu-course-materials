function D=BenGouJuZhen(E,miu,type)
%本构矩阵D=D(弹性模量，泊松比，类型)
%类型=1=平面应  力
%类型=2=平面应  变

if type==1
    D=E/(1-miu^2)*[1 miu 0;miu 1 0;0 0 (1-miu)/2];
elseif type==2
    D=E/(1+miu)/(1-2*miu)*[1-miu miu 0;miu 1-miu 0;0 0 0.5-miu];
end
end