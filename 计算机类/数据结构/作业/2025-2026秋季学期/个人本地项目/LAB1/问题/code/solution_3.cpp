#include <cstdio>

int matrix[2000][2000];
int rowsum[2000][2000];
long long matrixsum[2000][2000];

int main() {
    int n, m, q;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            scanf("%d", &matrix[i][j]);
        }
    }

    for (int i = 1; i <= n; ++i) {
        rowsum[i][0] = 0;
        for (int j = 1; j <= m; ++j) {
            rowsum[i][j] = rowsum[i][j - 1] + matrix[i][j];
        }
    }

    for (int i = 0; i <= m; ++i) {
        matrixsum[0][i] = 0;
    }
    for (int i = 1; i <= n; ++i) {
        matrixsum[i][0] = 0;
        for (int j = 1; j <= m; ++j) {
            matrixsum[i][j] = matrixsum[i-1][j] + rowsum[i][j];
        }
    }

    scanf("%d", &q);
    long long sum = 0;
    for (int i = 1; i <= q; ++i) {
        sum = 0;
        int x, y, a, b;
        scanf("%d %d %d %d", &x, &y, &a, &b);
        sum = matrixsum[x+a-1][y + b - 1] - matrixsum[x + a -1][y - 1]-matrixsum[x - 1][y + b - 1]+matrixsum[x-1][y-1];
        printf("%lld\n", sum);
    }
    return 0;
}

/*
#include <iostream>
#include <time.h>
#include <cstdio>

int matrix[2000][2000];
int rowsum[2000][2000];
long long matrixsum[2000][2000];

int main() {
    clock_t start, end;
    double cpu_time_used;

    start = clock();  // 记录开始时间
    
    int n, m, q;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            scanf("%d", &matrix[i][j]);
        }
    }

    for (int i = 1; i <= n; ++i) {
        rowsum[i][0] = 0;
        for (int j = 1; j <= m; ++j) {
            rowsum[i][j] = rowsum[i][j - 1] + matrix[i][j];
        }
    }

    for (int i = 0; i <= m; ++i) {
        matrixsum[0][i] = 0;
    }
    for (int i = 1; i <= n; ++i) {
        matrixsum[i][0] = 0;
        for (int j = 1; j <= m; ++j) {
            matrixsum[i][j] = matrixsum[i-1][j] + rowsum[i][j];
        }
    }

    scanf("%d", &q);
    printf("%d %d %d\n", n,m,q);
    long long sum = 0;
    for (int i = 1; i <= q; ++i) {
        sum = 0;
        int x, y, a, b;
        scanf("%d %d %d %d", &x, &y, &a, &b);
        sum = matrixsum[x+a-1][y + b - 1] - matrixsum[x + a -1][y - 1]-matrixsum[x - 1][y + b - 1]+matrixsum[x-1][y-1];
        //printf("%lld\n", sum);
    }
    
    end = clock();    // 记录结束时间
    
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    std::cout << "time: " << cpu_time_used << " s" << std::endl;
    
    return 0;
}*/