function Interpolation_Homework()
    % 主程序：依次执行 Problem 1 和 Problem 2 的所有任务
    % 设置绘图保存文件夹（可选，默认当前目录）
    close all; clc;
    
    % ================= PROBLEM 1: Runge Function =================
    disp('Processing Problem 1: Runge Function...');
    run_problem(1);
    
    % ================= PROBLEM 2: Piecewise Function =================
    disp('Processing Problem 2: Piecewise Function...');
    run_problem(2);
    
    disp('All tasks completed. Images saved.');
end

function run_problem(probNum)
    % N 取值列表
    N_list = [10, 20, 40];
    
    for N = N_list
        % --- Task 1: Newton Interpolation (Equidistant) ---
        [x_nodes, y_nodes, x_plot, y_true] = get_data(probNum, N, 'equidistant');
        y_est = newton_interp(x_nodes, y_nodes, x_plot);
        do_plot(x_plot, y_true, y_est, x_nodes, y_nodes, ...
            sprintf('Prob%d_Newton_N%d', probNum, N), ...
            sprintf('Newton Interpolation (N=%d)', N));

        % --- Task 2: Lagrange Interpolation (Chebyshev Nodes) ---
        [x_nodes, y_nodes, x_plot, y_true] = get_data(probNum, N, 'chebyshev');
        y_est = lagrange_interp(x_nodes, y_nodes, x_plot);
        do_plot(x_plot, y_true, y_est, x_nodes, y_nodes, ...
            sprintf('Prob%d_Lagrange_N%d', probNum, N), ...
            sprintf('Lagrange (Chebyshev) (N=%d)', N));

        % --- Task 3: Linear Interpolation (Equidistant) ---
        [x_nodes, y_nodes, x_plot, y_true] = get_data(probNum, N, 'equidistant');
        % MATLAB自带的 interp1 默认就是分段线性
        y_est = interp1(x_nodes, y_nodes, x_plot, 'linear'); 
        do_plot(x_plot, y_true, y_est, x_nodes, y_nodes, ...
            sprintf('Prob%d_Linear_N%d', probNum, N), ...
            sprintf('Piecewise Linear (N=%d)', N));

        % --- Task 4: Cubic Spline (Natural & Clamped) ---
        % 重新获取等距节点
        [x_nodes, y_nodes, x_plot, y_true] = get_data(probNum, N, 'equidistant');
        
        % 4a. Natural (Variational)
        pp_nat = csape(x_nodes, y_nodes, 'variational');
        y_est_nat = ppval(pp_nat, x_plot);
        do_plot(x_plot, y_true, y_est_nat, x_nodes, y_nodes, ...
            sprintf('Prob%d_Spline_Natural_N%d', probNum, N), ...
            sprintf('Natural Cubic Spline (N=%d)', N));
            
        % 4b. Clamped (Fixed derivatives)
        % 计算端点导数 (Boundary Conditions)
        if probNum == 1
            % Runge函数导数: f'(x) = -50x / (1+25x^2)^2
            dy_left = -50*(-1) / (1+25*(-1)^2)^2;
            dy_right = -50*(1) / (1+25*(1)^2)^2;
        else
            % 分段函数导数: f'(-1) = pi*cos(-pi) = -pi; f'(1) = 0
            dy_left = -pi; 
            dy_right = 0;
        end
        
        % csape 使用 [1, 1] 标记来指定给定的端点一阶导数
        pp_clamp = csape(x_nodes, [dy_left, y_nodes, dy_right], [1, 1]);
        y_est_clamp = ppval(pp_clamp, x_plot);
        do_plot(x_plot, y_true, y_est_clamp, x_nodes, y_nodes, ...
            sprintf('Prob%d_Spline_Clamped_N%d', probNum, N), ...
            sprintf('Clamped Cubic Spline (N=%d)', N));
    end
end

% ================= 数学核心算法 =================

function y_eval = newton_interp(x, y, x_query)
    % 使用差商表实现牛顿插值 (避免使用符号运算，提高效率)
    n = length(x);
    D = zeros(n, n);
    D(:,1) = y(:);
    
    % 计算差商表
    for j = 2:n
        for i = 1:n-j+1
            D(i,j) = (D(i+1,j-1) - D(i,j-1)) / (x(i+j-1) - x(i));
        end
    end
    
    % Horner算法求值
    coeff = D(1,:); % 差商系数
    y_eval = coeff(n) * ones(size(x_query));
    for k = n-1:-1:1
        y_eval = y_eval .* (x_query - x(k)) + coeff(k);
    end
end

function y_eval = lagrange_interp(x, y, x_query)
    % 拉格朗日插值
    n = length(x);
    m = length(x_query);
    y_eval = zeros(1, m);
    
    for k = 1:m
        xx = x_query(k);
        L_sum = 0;
        for i = 1:n
            % 计算基函数 Li(x)
            Li = 1;
            for j = 1:n
                if i ~= j
                    Li = Li * (xx - x(j)) / (x(i) - x(j));
                end
            end
            L_sum = L_sum + y(i) * Li;
        end
        y_eval(k) = L_sum;
    end
end

% ================= 数据生成与辅助函数 =================

function [x_nodes, y_nodes, x_plot, y_true] = get_data(probNum, N, nodeType)
    % 生成节点和用于绘图的密集点
    if strcmp(nodeType, 'equidistant')
        x_nodes = linspace(-1, 1, N+1); % 等距节点
    else
        % Chebyshev 节点 (注意索引从0开始的公式转换)
        i = 0:N;
        x_nodes = cos((2*i + 1) * pi / (2*N + 2));
    end
    
    % 绘图用的密集网格
    x_plot = linspace(-1, 1, 1000);
    
    % 计算函数值
    if probNum == 1
        y_nodes = runge_func(x_nodes);
        y_true = runge_func(x_plot);
    else
        y_nodes = piecewise_func_vec(x_nodes);
        y_true = piecewise_func_vec(x_plot);
    end
end

function y = runge_func(x)
    y = 1 ./ (1 + 25 * x.^2);
end

function y = piecewise_func_vec(x)
    % 向量化的分段函数
    y = zeros(size(x));
    for i = 1:length(x)
        xi = x(i);
        if xi >= -1 && xi < 0
            y(i) = sin(pi * xi);
        elseif xi >= 0 && xi < 0.5
            y(i) = cos(pi * xi);
        else
            y(i) = 0;
        end
    end
end

function do_plot(x_plot, y_true, y_est, x_nodes, y_nodes, filename, plot_title)
    % 统一绘图函数，保证风格一致且美观
    h = figure('Visible', 'off'); % 不弹窗，直接后台绘图
    
    % 绘制原函数曲线
    plot(x_plot, y_true, 'k-', 'LineWidth', 1.5, 'DisplayName', 'Original F(x)');
    hold on;
    
    % 绘制插值曲线
    plot(x_plot, y_est, 'b--', 'LineWidth', 1.2, 'DisplayName', 'Interpolation');
    
    % 绘制样本点
    scatter(x_nodes, y_nodes, 40, 'r', 'filled', 'DisplayName', 'Nodes');
    
    % 图表装饰
    title(plot_title, 'Interpreter', 'none', 'FontSize', 12);
    xlabel('x'); ylabel('y');
    legend('show', 'Location', 'best');
    grid on; grid minor;
    box on;
    ylim([-1.2, 1.2]); % 统一Y轴范围便于观察Runge现象
    
    % 保存
    % print(h, filename, '-dpng', '-r300'); % 原版用 print
    saveas(h, [filename, '.png']); % 改用 saveas，更通用
    close(h);
end