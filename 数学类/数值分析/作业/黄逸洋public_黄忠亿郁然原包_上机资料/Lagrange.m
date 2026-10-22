X = input('请输入横坐标向量X:\nX=');  % 获取用户输入的横坐标向量
Y = input('请输入纵坐标向量Y:\nY=');  % 获取用户输入的纵坐标向量
m = length(X);  % 获取节点个数
L = ones(m, m);  % 初始化基函数系数矩阵
for k = 1 : m  % 循环计算每个基函数的系数
    V = 1;  % 初始化基函数的临时变量
    for i = 1 : m
        if k ~= i  % 排除当前节点时的计算
            V = conv(V, poly(X(i))) / (X(k) - X(i));  % 在当前节点处计算基函数的系数
        end
    end
    L(k, :) = V;  % 将基函数的系数存储到矩阵中
end
l = sym(zeros(m, 1));  % 初始化基函数数组
for k = 1 : m  % 遍历基函数系数矩阵
    l(k) = poly2sym(L(k, :));  % 将基函数系数转化为符号表达式
end
fprintf('基函数为：\n');
for k = 1 : m  % 输出每个基函数的表达式
    fprintf('q%d(x)=%s\n', k, char(l(k)));
end
P = sym(0);  % 初始化拉格朗日多项式
for k = 1 : m  % 计算拉格朗日多项式的表达式
    P = P + Y(k) * l(k);
end
fprintf('拉格朗日多项式为：\nP(x)=%s\n', char(P));  % 输出拉格朗日多项式的表达式