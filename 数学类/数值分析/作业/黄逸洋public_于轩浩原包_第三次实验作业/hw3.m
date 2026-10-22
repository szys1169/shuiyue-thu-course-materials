function qr_analysis()
    format shortG
    
    % 定义 epsilon 列表
    eps_list = [1e-4, 1e-8, 1e-12, 1e-16];
    
    for k = 1:length(eps_list)
        e = eps_list(k);
        
        % 构造矩阵 A
        A = [1, 1, 1, 1;
             e, 0, 0, 0;
             0, e, 0, 0;
             0, 0, e, 0;
             0, 0, 0, e];
             
        fprintf('\n############################################################\n');
        fprintf('计算情况: Epsilon = %g\n', e);
        fprintf('############################################################\n');
        
        % 1. 经典 Gram-Schmidt (CGS)
        fprintf('\n------------ [1] Classical Gram-Schmidt (CGS) ------------\n');
        [Q, R] = gs(A);
        disp('Q matrix:'); disp(Q);
        disp('R matrix:'); disp(R);
        disp('Check Orthogonality (Q''*Q):'); disp(Q'*Q);
        disp('Check Factorization (Q*R):'); disp(Q*R);
        
        % 2. 改进 Gram-Schmidt (MGS)
        fprintf('\n------------ [2] Modified Gram-Schmidt (MGS) -------------\n');
        [Q, R] = mgs(A);
        disp('Q matrix:'); disp(Q);
        disp('R matrix:'); disp(R);
        disp('Check Orthogonality (Q''*Q):'); disp(Q'*Q);
        disp('Check Factorization (Q*R):'); disp(Q*R);
        
        % 3. Householder
        fprintf('\n------------ [3] Householder Transformation --------------\n');
        [Q, R] = householder(A);
        disp('Q matrix:'); disp(Q);
        disp('R matrix:'); disp(R);
        disp('Check Orthogonality (Q''*Q):'); disp(Q'*Q);
        disp('Check Factorization (Q*R):'); disp(Q*R);
        
        % 4. Givens
        fprintf('\n------------ [4] Givens Rotation -------------------------\n');
        [Q, R] = givens(A);
        disp('Q matrix:'); disp(Q);
        disp('R matrix:'); disp(R);
        disp('Check Orthogonality (Q''*Q):'); disp(Q'*Q);
        disp('Check Factorization (Q*R):'); disp(Q*R);
    end
end

% -------------------------
% 子函数定义
% -------------------------

function [q, r] = gs(A)
    [m, n] = size(A);
    q = zeros(m, n);
    r = zeros(n, n);
    for j = 1:n
        v = A(:,j);
        for i = 1:j-1
            r(i,j) = A(:,j)'*q(:,i); % CGS: 投影到初始 A(:,j)
            v = v - r(i,j)*q(:,i);
        end
        r(j,j) = norm(v,2);
        q(:,j) = v / r(j,j);
    end
end

function [q, r] = mgs(A)
    [m, n] = size(A);
    q = zeros(m, n);
    r = zeros(n, n);
    for i = 1:n
        r(i,i) = norm(A(:,i), 2);
        q(:,i) = A(:,i) / r(i,i);
        for j = i+1:n
            r(i,j) = A(:,j)'*q(:,i);     % MGS: 使用更新后的 q
            A(:,j) = A(:,j) - r(i,j)*q(:,i);
        end
    end
end

function [q, r] = householder(A)
    [n, m] = size(A); 
    r = A;
    q = eye(n, n);
    for i = 1:m
        x = r(i:n,i);
        nx = norm(x,2);
        % 避免相消误差的符号选择
        k = -sign(x(1)) * nx;
        % 如果 x(1) 为 0，sign 返回 0，需修正
        if x(1) == 0; k = -nx; end 
        
        beta = nx * (nx + abs(x(1)));
        if beta == 0
            continue; 
        end
        x(1) = x(1) - k;
        
        % 构造 H 矩阵并更新
        H_sub = eye(length(x)) - (x*x') / beta;
        H = eye(n, n);
        H(i:n,i:n) = H_sub;
        
        r = H*r;
        q = q*H;
    end
    
    % 调整维度为 Thin QR (m*n)
    q = q(:, 1:m);
    r = r(1:m, :);
    
    % 调整对角线符号以保证 R 对角元非负
    d = eye(m, m);
    d(1:m,1:m) = diag(sign(diag(r)));
    q = q*d;
    r = d*r;
end

function [q, r] = givens(A)
    [n, m] = size(A);
    r = A;
    q = eye(n, n);
    for i = 1:m
        for j = n:-1:i+1
            if r(j,i) ~= 0
                % 计算 Givens 参数
                if abs(r(j,i)) >= abs(r(i,i))
                    t = r(i,i) / r(j,i);
                    s = 1 / sqrt(1 + t^2);
                    c = s * t;
                else
                    t = r(j,i) / r(i,i);
                    c = 1 / sqrt(1 + t^2);
                    s = c * t;
                end
                
                % 构造旋转矩阵 P
                P = eye(n, n);
                P(i,i) = c;  P(i,j) = s;
                P(j,i) = -s; P(j,j) = c;
                
                r = P*r;
                q = q*P'; % 注意：如果是右乘旋转矩阵，这里应该是 P' 或者 P的定义转置
            end
        end
    end
    
    % 调整维度为 Thin QR
    q = q(:, 1:m);
    r = r(1:m, :);
    
    % 调整符号
    d = eye(m, m);
    d(1:m,1:m) = diag(sign(diag(r)));
    q = q*d;
    r = d*r;
end