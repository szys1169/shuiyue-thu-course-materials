%% 数值分析作业：Hilbert 矩阵的迭代解法
clear; clc; close all;

%% 全局参数
tol = 1e-12;
max_k = 200;
omegas = [1.0, 1.25, 1.5];

%% === 第一部分：n = 6 时的详细数据分析===
fprintf('======================================================\n');
fprintf('  实验一：n = 6 时各方法的详细指标 + 解向量\n');
fprintf('======================================================\n');

n = 6;
H = hilb(n);
x_star = ones(n, 1);
b = H * x_star;
x0 = zeros(n, 1);

% Jacobi
[x_jac, err_jac, rho_jac] = SolveJacobi(H, b, x0, x_star, max_k);

% SOR
res_sor = cell(1,3); 
[x_s1,  err_s1,  rho_s1 ] = SolveSOR(H, b, 1.00, x0, x_star, max_k);
res_sor{1} = err_s1;
[x_s125, err_s125, rho_s125] = SolveSOR(H, b, 1.25, x0, x_star, max_k);
res_sor{2} = err_s125;
[x_s150, err_s150, rho_s150] = SolveSOR(H, b, 1.50, x0, x_star, max_k);
res_sor{3} = err_s150;

fprintf('%-12s | %-12s | %-12s | %-12s\n', ...
    'Method', 'Spectral(rho)', 'Err(k=200)', 'Converged?');
fprintf('------------------------------------------------------\n');

fprintf('%-12s | %-12.6f | %-12.4e | %s\n', ...
    'Jacobi', rho_jac, err_jac(end), 'No');
fprintf('%-12s | %-12.6f | %-12.4e | %s\n', ...
    'SOR(1.0)', rho_s1, err_s1(end), 'Yes(Slow)');
fprintf('%-12s | %-12.6f | %-12.4e | %s\n', ...
    'SOR(1.25)', rho_s125, err_s125(end), 'Yes(Slow)');
fprintf('%-12s | %-12.6f | %-12.4e | %s\n', ...
    'SOR(1.5)', rho_s150, err_s150(end), 'Yes(Slow)');

fprintf('\n迭代 200 次后的解向量（按方法排列）：\n\n');

% Jacobi 用科学计数法 1 位小数，SOR 保持常规浮点显示
for i = 1:n
    fprintf('  ( %8.1e )   ( %10.4f )   ( %10.4f )   ( %10.4f )\n', ...
        x_jac(i), x_s1(i), x_s125(i), x_s150(i));
end
fprintf('\n');


%% === 第二部分：n = 8,10,12,14 输出解向量===
fprintf('======================================================\n');
fprintf('  不同 n（8,10,12,14）迭代200步后的解向量\n');
fprintf('======================================================\n');

n_list = [8, 10, 12, 14];

for idx = 1:length(n_list)
    n = n_list(idx);
    fprintf('\n=====================  n = %d  =====================\n', n);

    H = hilb(n);
    x_star = ones(n,1);
    b = H * x_star;
    x0 = zeros(n,1);

    % Jacobi
    [x_jac, err_jac, rho_jac] = SolveJacobi(H, b, x0, x_star, max_k);

    % SOR
    [x_s1,  err_s1,  rho_s1 ] = SolveSOR(H, b, 1.00, x0, x_star, max_k);
    [x_s125, err_s125, rho_s125] = SolveSOR(H, b, 1.25, x0, x_star, max_k);
    [x_s150, err_s150, rho_s150] = SolveSOR(H, b, 1.50, x0, x_star, max_k);

    fprintf('%-12s | %-12s | %-15s | %-12s\n', ...
        'Method', 'Spectral(rho)', 'Err(k=200)', 'Converged?');
    fprintf('---------------------------------------------------------------\n');

    fprintf('%-12s | %-12.6f | %-15.4e | %s\n', ...
        'Jacobi', rho_jac, err_jac(end), 'No');
    fprintf('%-12s | %-12.6f | %-15.4e | %s\n', ...
        'SOR(1.00)', rho_s1, err_s1(end), 'Yes(Slow)');
    fprintf('%-12s | %-12.6f | %-15.4e | %s\n', ...
        'SOR(1.25)', rho_s125, err_s125(end), 'Yes(Slow)');
    fprintf('%-12s | %-12.6f | %-15.4e | %s\n', ...
        'SOR(1.50)', rho_s150, err_s150(end), 'Yes(Slow)');

    fprintf('\n迭代 200 次后的解向量（按方法排列）：\n\n');

    % Jacobi 用科学计数法，保留 1 位小数
    for i = 1:n
        fprintf('  ( %8.1e )   ( %10.4f )   ( %10.4f )   ( %10.4f )\n', ...
            x_jac(i), x_s1(i), x_s125(i), x_s150(i));
    end
end
fprintf('\n');


%% === 第三部分：绘图 (n = 6) ===
figure('Name', 'n=6 Error Curve', 'Color', 'w');
hold on;
colors = lines(3);
for i = 1:3
    semilogy(1:length(res_sor{i}), res_sor{i}, 'Color', colors(i,:), ...
        'LineWidth', 1.5, 'DisplayName', sprintf('SOR \\omega=%.2f', omegas(i)));
end
xlabel('Iterations (k)');
ylabel('Error ||x^{(k)} - x^*||_\infty');
title('n = 6 Error Convergence');
legend('Location', 'Best');
grid on;


%% === 第四部分：不同 n 下的 SOR 收敛曲线 ===
fprintf('======================================================\n');
fprintf('  实验二：不同维数 n 的迭代行为对比\n');
fprintf('======================================================\n');

figure('Name', 'Different Dimensions', 'Color', 'w', 'Position', [100, 100, 1000, 600]);

for k = 1:length(n_list)
    curr_n = n_list(k);
    H_curr = hilb(curr_n);
    b_curr = H_curr * ones(curr_n, 1);
    x0_curr = zeros(curr_n, 1);
    x_star_curr = ones(curr_n, 1);

    subplot(2, 2, k);
    hold on; box on; grid on;

    for j = 1:3
        w = omegas(j);
        [~, err_hist, ~] = SolveSOR(H_curr, b_curr, w, x0_curr, x_star_curr, 100);
        semilogy(err_hist, '.-', 'LineWidth', 1, 'MarkerSize', 8, ...
                 'DisplayName', sprintf('\\omega=%.2f', w));
    end

    title(sprintf('Dimension n = %d', curr_n));
    xlabel('Iter'); ylabel('Error ||x-x^*||');
    if k == 1, legend('Location','best'); end
end


%% === 本地函数定义 ===
function [x, err_history, rho] = SolveJacobi(A, b, x0, x_star, max_iter)
    D = diag(diag(A));
    L = -tril(A, -1);
    U = -triu(A, 1);
    B = D \ (L + U);
    rho = max(abs(eig(B)));
    f = D \ b;
    x = x0;
    err_history = zeros(max_iter, 1);
    for k = 1:max_iter
        x = B * x + f;
        err_history(k) = norm(x - x_star, inf);
    end
end

function [x, err_history, rho] = SolveSOR(A, b, w, x0, x_star, max_iter)
    D = diag(diag(A));
    L = -tril(A, -1);
    U = -triu(A, 1);
    M = D - w * L;
    N = (1 - w) * D + w * U;
    B = M \ N;
    rho = max(abs(eig(B)));
    rhs_vec = w * b;
    x = x0;
    err_history = zeros(max_iter, 1);
    for k = 1:max_iter
        x = M \ (N * x + rhs_vec);
        err_history(k) = norm(x - x_star, inf);
    end
end
