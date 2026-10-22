clear;
clc;
format shorte; % 使用科学计数法显示

N = 20; % 设置最大阶数 n

% --- 任务 (1) HILBERT 矩阵的无穷条件数 ---
digits(100); % 设置 100 位小数精度
cond_inf = zeros(N, 1); 
cond_inf_double = zeros(N, 1); 
n_range = (2:N)'; % n 的范围

for n = 2:N
    H_vpa = vpa(hilb(n)); 
    cond_inf(n) = cond(H_vpa, 'inf');
    
    H_double = hilb(n);
    cond_inf_double(n) = cond(H_double, 'inf');
end

% --- 任务 (2) 和 (3): 求解线性方程组并分析误差 ---
digits(16); 
format shorte;

norm_r = zeros(N, 1);      % 存储残差的无穷范数
norm_err = zeros(N, 1);    % 存储误差的无穷范数
rel_err = zeros(N, 1);     % 存储相对误差

for n = 2:N
    H = hilb(n);
    x = ones(n, 1);
    b = H * x;
    x_tilde = H \ b;
    r_n = b - H * x_tilde;
    err = x_tilde - x;
    
    norm_r(n) = norm(r_n, 'inf');
    norm_err(n) = norm(err, 'inf');
    rel_err(n) = norm_err(n) / norm(x, 'inf');
end

% --- 绘图部分 ---

% 图 1: 条件数 vs n (对数-线性图)
figure(1);
semilogy(n_range, cond_inf(2:N), 'b-o', 'LineWidth', 1.5, 'MarkerFaceColor', 'b');
hold on;
semilogy(n_range, cond_inf_double(2:N), 'r--s', 'LineWidth', 1);
hold off;
grid on;
title('Condition Number of Hilbert Matrix H_n');
xlabel('Matrix Order (n)');
ylabel('Condition Number (log scale)');
legend('cond_{\infty} (VPA, 100 digits)', 'cond_{\infty} (Double Precision)', 'Location', 'NorthWest');
% 保存图像
saveas(gcf, 'cond_plot.png');

% 图 2: 相对误差和残差 vs n (对数-线性图)
figure(2);
semilogy(n_range, rel_err(2:N), 'r-x', 'LineWidth', 1.5, 'MarkerSize', 8);
hold on;
semilogy(n_range, norm_r(2:N), 'b-d', 'LineWidth', 1.5, 'MarkerSize', 6);
% 100% 误差 (相对误差 = 1) 的参考线
semilogy(n_range, ones(size(n_range)), 'k--', 'LineWidth', 1); 
hold off;
grid on;
title('Error and Residual for H_n * x = b');
xlabel('Matrix Order (n)');
ylabel('Norm (log scale)');
legend('Relative Error ||x_{tilde} - x||_{\infty} / ||x||_{\infty}', ...
       'Residual Norm ||r_n||_{\infty}', ...
       '100% Relative Error (Error = 1.0)', ...
       'Location', 'NorthWest');
ylim([1e-18, 1e4]); % 调整 Y 轴范围以更好地显示
% 保存图像
saveas(gcf, 'error_plot.png');

fprintf('图像已保存为 cond_plot.png 和 error_plot.png\n');