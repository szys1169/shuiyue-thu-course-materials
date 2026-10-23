function [ I_cap ] = Gauss_Integral_1d(f, n)
% 一维高斯积分
% 输入: f-被积函数或矩阵; n-积分点数(1~5) f必须是关于xi,eta的函数，因此输入时务必注意
% 输出: I_cap-被积函数结果
I_cap = 0;
if n == 1
    point = 0;
    xi=point;
    I_cap = 2*eval(f);
    
elseif n == 2
    point = [-0.577350269189626;0.577350269189626];
    H = [1;1];
    for i=1:2
        xi=point(i);
        I_cap = I_cap+H(i)*eval(f);
    end
    
elseif n == 3
    point = [-0.774596669241483;0;0.774596669241483];
    H = [0.555555555555556;0.888888888888889;0.555555555555556];
    for i=1:3
        xi=point(i);
        I_cap = I_cap+H(i)*eval(f);
    end
    
elseif n == 4
    point = [-0.861136, -0.339981, 0.339981, 0.861136];
    H = [0.347855, 0.652145, 0.652145, 0.347855];
    for i =1:length(point)
        xi = point(i);
        I_cap = I_cap + H(i) * eval(f);
    end
    
elseif n == 5
    point = [-0.9061798, -0.5384693, 0, 0.5384693, 0.9061798];
    H = [0.2369269, 0.4786286, 0.5688889, 0.4786286, 0.2369269];
    for i =1:length(point)
        xi = point(i);
        I_cap = I_cap + H(i) * eval(f);
    end
end


end

