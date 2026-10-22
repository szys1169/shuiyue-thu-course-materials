clear; clc; close all;
format long g;

%% 1. Wilkinson 多项式

fprintf('--- 1. Wilkinson 多项式 ---\n');

% (1) 生成系数
r_original = (1:20)'; 
a = poly(r_original);
fprintf('Wilkinson 多项式的系数已生成。\n');
fprintf('a(1) (x^20的系数): %f\n', a(1));
fprintf('a(2) (x^19的系数): %f\n', a(2));
fprintf('a(21) (x^0的系数): %e\n', a(21));
fprintf('\n');

% (2) 扰动系数并观察根
epsilons = [1e-10, 1e-6, 1e-3];
rng(0);

% 创建一个新的画布用于子图
figure('Name', 'Wilkinson 多项式根扰动分析');
sgtitle('Wilkinson 多项式根扰动分析 (原始根为 1, ..., 20)', 'FontSize', 14);

% 存储每个 epsilon 下的绝对误差
all_errors = zeros(length(epsilons), length(r_original));

for i = 1:length(epsilons)
    eps = epsilons(i);
    
    % 生成扰动
    r_k = randn(1, 20);
    a_perturbed = a;
    perturbation = (1 + eps * r_k);
    a_perturbed(1:20) = a(1:20) .* perturbation;
    
    % 计算新根
    r_perturbed = roots(a_perturbed);
    
    % --- 绘制根分布子图 ---
    subplot(2, 2, i);
    plot(real(r_perturbed), imag(r_perturbed), 'bx', 'MarkerSize', 8, 'LineWidth', 1);
    hold on;
    plot(r_original, zeros(size(r_original)), 'ro', 'MarkerSize', 6, 'LineWidth', 1.5);
    hold off;
    
    grid on;
    axis equal;
    xlabel('实部 (Real Part)');
    ylabel('虚部 (Imaginary Part)');
    title(sprintf('根分布 (\\epsilon = %.0e)', eps));
    if i == 1
        legend('扰动后的根', '原始根', 'Location', 'northwest');
    end
    

    r_perturbed_sorted = sort(r_perturbed, 'ComparisonMethod', 'real');
    all_errors(i, :) = abs(r_perturbed_sorted - r_original);
end

% --- 绘制对比图 ---
subplot(2, 2, 4);
semilogy(r_original, all_errors(1, :), 'r-o', 'LineWidth', 1.5, 'DisplayName', sprintf('\\epsilon = %.0e', epsilons(1)));
hold on;
semilogy(r_original, all_errors(2, :), 'g-s', 'LineWidth', 1.5, 'DisplayName', sprintf('\\epsilon = %.0e', epsilons(2)));
semilogy(r_original, all_errors(3, :), 'b-^', 'LineWidth', 1.5, 'DisplayName', sprintf('\\epsilon = %.0e', epsilons(3)));
hold off;

grid on;
xlabel('原始根 (i)');
ylabel('绝对误差 |r_{new} - i| (对数尺度)');
title('根的绝对误差对比');
legend('show', 'Location', 'northwest');
xticks(1:2:20);
xlim([0, 21]);


saveas(gcf, 'wilkinson_roots_combined.png');
fprintf('已生成合并的根分布与对比图 (wilkinson_roots_combined.png)。\n\n');


%% 2. 避免相近数相减

fprintf('--- 2. 避免相近数相减的数值计算 ---\n');

% 生成 x 值
x = 10.^-(1:14)';

% (a) (1 - sec(x)) / tan(x)^2
fprintf('--- (a) f(x) = (1 - sec(x)) / tan(x)^2 ---\n');
f_a = (1 - sec(x)) ./ (tan(x).^2);
g_a = -cos(x) ./ (1 + cos(x));

% (b) (1 - (1-x)^3) / x
fprintf('--- (b) f(x) = (1 - (1-x)^3) / x ---\n');
f_b = (1 - (1 - x).^3) ./ x;
g_b = 3 - 3*x + x.^2; 

% 创建并显示结果表格
fprintf('创建表格...\n\n');

% 表格 (a)
T_a = table(x, f_a, g_a);
T_a.Properties.VariableNames = {'x', 'f_a (原始)', 'g_a (稳定)'};
disp('--- 结果 (a) ---');
disp(T_a);

% 表格 (b)
T_b = table(x, f_b, g_b);
T_b.Properties.VariableNames = {'x', 'f_b (原始)', 'g_b (稳定)'};
disp('--- 结果 (b) ---');
disp(T_b);

fprintf('--- 计算完成 ---\n');