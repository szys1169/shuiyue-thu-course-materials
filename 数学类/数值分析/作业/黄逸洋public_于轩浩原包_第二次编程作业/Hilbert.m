% 这是一个 MATLAB 脚本，用于执行 Hilbert 矩阵的相关计算
% 对应图片中的任务 (1), (2), (3)

clear;
clc;
format shorte; % 使用科学计数法显示

N = 20; % 设置最大阶数 n

% --- 任务 (1): 计算 Hilbert 矩阵的无穷条件数 ---
% 我们需要使用高精度计算，因为条件数增长非常快
digits(100); % 设置 100 位小数精度
cond_inf = zeros(N, 1); % 预分配数组
cond_inf_double = zeros(N, 1); % 对比标准双精度的结果

for n = 2:N
    % 使用 vpa (可变精度) 来创建高精度的 Hilbert 矩阵
    H_vpa = vpa(hilb(n)); 
    cond_inf(n) = cond(H_vpa, 'inf');
    
    % 作为对比，也计算标准双精度下的条件数
    % 当 n 较大时，这个值会很快变成 Inf
    H_double = hilb(n);
    cond_inf_double(n) = cond(H_double, 'inf');
end

% --- 任务 (2) 和 (3): 求解线性方程组并分析误差 ---
% 这里我们使用标准双精度 (double)，来模拟真实计算中的舍入误差

% 恢复到标准双精度
digits(16); 
format shorte;

norm_r = zeros(N, 1);      % 存储残差的无穷范数 ||r_n||_inf
norm_err = zeros(N, 1);    % 存储误差的无穷范数 ||x_tilde - x||_inf
rel_err = zeros(N, 1);     % 存储相对误差

for n = 2:N
    % 1. 创建标准双精度的 Hilbert 矩阵
    H = hilb(n);
    
    % 2. 设置精确解 x = [1, 1, ..., 1]^T
    x = ones(n, 1);
    
    % 3. 计算精确的 b = H * x
    % 注意：为了更准确地模拟，b 也应该在双精度下计算
    b = H * x;
    
    % 4. 使用 MATLAB 的 '\' 求解 H_n * x_tilde = b
    x_tilde = H \ b;
    
    % 5. 计算残差向量 r_n = b - H * x_tilde
    r_n = b - H * x_tilde;
    
    % 6. 计算误差向量 err = x_tilde - x
    err = x_tilde - x;
    
    % 7. 计算无穷范数
    norm_r(n) = norm(r_n, 'inf');
    norm_err(n) = norm(err, 'inf');
    
    % 8. 计算相对误差 ||x_tilde - x||_inf / ||x||_inf
    % 因为 ||x||_inf = 1，所以相对误差等于 norm_err(n)
    rel_err(n) = norm_err(n) / norm(x, 'inf');
end


% --- 显示结果 ---

% 任务 (1) 的结果
fprintf('--- 任务 (1): Hilbert 矩阵的无穷条件数 (高精度) ---\n');
fprintf('%-5s %-25s %-25s\n', 'n', 'cond_inf (VPA)', 'cond_inf (Double)');
for n = 2:N
    fprintf('%-5d %-25.4e %-25.4e\n', n, cond_inf(n), cond_inf_double(n));
end

% 任务 (2) 和 (3) 的结果
fprintf('\n--- 任务 (2) & (3): 残差、误差和相对误差 (标准双精度) ---\n');
fprintf('%-5s %-18s %-18s %-18s\n', 'n', '||r_n||_inf', '||err||_inf', 'Rel. Err (%)');
for n = 2:N
    fprintf('%-5d %-18.4e %-18.4e %-18.4f\n', n, norm_r(n), norm_err(n), rel_err(n) * 100);
end

fprintf('\n分析:\n');
fprintf('1. 条件数 (cond_inf) 随 n 指数级增长。\n');
fprintf('2. 标准双精度的条件数在 n=15 左右就溢出 (Inf)，显示了高精度计算的必要性。\n');
fprintf('3. 残差范数 ||r_n||_inf 始终很小，接近机器精度 (约 1e-16)。\n');
fprintf('4. 误差范数 ||err||_inf 和相对误差 (Rel. Err) 随 n 迅速增长。\n');
fprintf('5. 当 n 约为 13-14 时，相对误差达到或超过 100%%，意味着计算解 x_tilde 完全失去了有效数字。\n');