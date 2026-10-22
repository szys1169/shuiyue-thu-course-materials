%% 数值分析作业：Poisson 方程边值问题

clear; clc; close all;

%% === 实验设置 ===
N_values = [5, 10, 20];
tol = 1e-6;          % 收敛判定：残差或步长误差 < 1e-6
max_it = 2000;       % 最大迭代步数

% 定义要对比的方法
method_list = {
    'SOR_1.0',  1.0; 
    'SOR_1.25', 1.25; 
    'SOR_1.5',  1.5; 
    'CG',       0; 
    'PCG',      0
};

fprintf('================================================================\n');
fprintf('%-6s | %-12s | %-10s | %-12s | %-10s\n', 'N', 'Method', 'Iters', 'Final Error', 'Time(s)');
fprintf('----------------------------------------------------------------\n');

%% === 主循环：针对不同的 N ===
for i = 1:length(N_values)
    N = N_values(i);
    h = 1 / (N + 1);
    n_sq = N * N;
    
    % 1. 组装系数矩阵 A (使用 Kronecker 积，更高效且专业)
    e = ones(N, 1);
    T = spdiags([-e, 2*e, -e], -1:1, N, N); % 1D Laplace算子
    I = speye(N);
    A = kron(I, T) + kron(T, I);            % 2D Poisson 矩阵 (4, -1 pattern)
    
    % 2. 组装右端项 b
    % 网格生成 (reshape 需要对应自然排序)
    [x, y] = meshgrid((1:N)*h, (1:N)*h); 
    % 为了配合 kron(I,T)，我们需要先按 x 遍历再按 y 遍历，或者直接转置
    % 这里 A 的结构对应 u = [u_11, u_21 ... u_N1, u_12 ...]' (列优先/x优先)
    % meshgrid 默认 x 为列变化，y 为行变化。转置一下比较稳妥。
    x = x'; y = y';
    
    F = 2 * pi^2 * sin(pi * x) .* sin(pi * y);
    b = h^2 * reshape(F, n_sq, 1);
    
    % 真实解 (用于计算最终真实误差，而非停机准则)
    u_exact = reshape(sin(pi * x) .* sin(pi * y), n_sq, 1);
    
    % 绘图准备
    fig = figure('Visible', 'off'); % 后台绘图
    hold on; grid on; box on;
    set(gca, 'YScale', 'log');
    
    % 3. 运行各算法
    for m = 1:size(method_list, 1)
        m_name = method_list{m, 1};
        w_param = method_list{m, 2};
        
        tic; % 计时开始
        if contains(m_name, 'SOR')
            [u, res_hist, k] = RunSOR(A, b, w_param, tol, max_it);
            disp_name = sprintf('SOR(\\omega=%.2f)', w_param);
        elseif strcmp(m_name, 'CG')
            [u, res_hist, k] = RunCG(A, b, tol, max_it);
            disp_name = 'CG';
        elseif strcmp(m_name, 'PCG')
            [u, res_hist, k] = RunPCG(A, b, tol, max_it);
            disp_name = 'PCG (IC)';
        end
        t_cost = toc; % 计时结束
        
        final_err = norm(u - u_exact, inf);
        fprintf('%-6d | %-12s | %-10d | %-12.4e | %-10.4f\n', N, m_name, k, final_err, t_cost);
        
        % 绘制收敛曲线
        plot(res_hist, 'LineWidth', 1.5, 'DisplayName', disp_name);
    end
    
    % 图像修饰
    yline(tol, '--r', 'Tolerance');
    title(sprintf('Convergence for N = %d', N));
    xlabel('Iterations');
    ylabel('Step Error ||x_{k+1} - x_k||_\infty');
    legend('Location', 'best');
    
    % 保存或显示
    print(fig, sprintf('Poisson_Result_N%d', N), '-dpng', '-r150');
    set(fig, 'Visible', 'on'); 
end
fprintf('----------------------------------------------------------------\n');
fprintf('运行完成。图片已保存为 Poisson_Result_Nx.png\n');

%% === 本地求解器函数 ===

% 1. SOR 求解器
function [x, step_err_hist, iter] = RunSOR(A, b, w, tol, max_iter)
    D = diag(diag(A));
    L = -tril(A, -1); 
    
    % 为了利用稀疏性，我们不显式构建 U，而是利用 A = D - L - U -> U = D - L - A
    % RHS = (1-w)D + w(D - L - A) = D - wL - wA = M - wA
    % 于是方程变为: M * x_new = (M - wA) * x + w*b
    % => M (x_new - x) = w * (b - A*x)
    % => x_new = x + w * M \ (b - A*x)
    
    x = zeros(size(b));
    M = sparse(D - w * L); % 保持稀疏
    step_err_hist = [];
    
    for iter = 1:max_iter
        r = b - A * x;            % 残差
        delta = M \ (w * r);      % 求解修正量
        x = x + delta;
        
        err = norm(delta, inf);   % 步长误差
        step_err_hist(end+1) = err;
        
        if err < tol
            return;
        end
    end
end

% 2. CG 求解器
function [x, err_hist, iter] = RunCG(A, b, tol, max_iter)
    x = zeros(size(b));
    r = b - A * x;
    p = r;
    rsold = r' * r;
    err_hist = [];
    
    for iter = 1:max_iter
        Ap = A * p;
        alpha = rsold / (p' * Ap);
        x_new = x + alpha * p;
        
        % 计算步长误差用于画图
        err = norm(x_new - x, inf);
        err_hist(end+1) = err;
        
        if err < tol
            x = x_new;
            return;
        end
        
        x = x_new;
        r = r - alpha * Ap;
        rsnew = r' * r;
        p = r + (rsnew / rsold) * p;
        rsold = rsnew;
    end
end

% 3. 预处理 CG (PCG) 求解器
function [x, err_hist, iter] = RunPCG(A, b, tol, max_iter)
    % 构造不完全 Cholesky 分解作为预处理子 M = L*L'
    % 'michol' (Modified Incomplete Cholesky) 通常对 Poisson 问题更优
    try
        L_ichol = ichol(A, struct('type','ict','droptol',1e-3));
    catch
        % 如果矩阵不是严格正定可能失败，回退到对角预处理
        L_ichol = diag(sqrt(diag(A))); 
    end
    
    x = zeros(size(b));
    r = b - A * x;
    z = L_ichol' \ (L_ichol \ r); % 求解 Mz = r
    p = z;
    rz_old = z' * r;
    
    err_hist = [];
    
    for iter = 1:max_iter
        Ap = A * p;
        alpha = rz_old / (p' * Ap);
        x_new = x + alpha * p;
        
        err = norm(x_new - x, inf);
        err_hist(end+1) = err;
        
        if err < tol
            x = x_new;
            return;
        end
        
        x = x_new;
        r = r - alpha * Ap;
        z = L_ichol' \ (L_ichol \ r); % 预处理步骤
        
        rz_new = z' * r;
        beta = rz_new / rz_old;
        p = z + beta * p;
        rz_old = rz_new;
    end
end