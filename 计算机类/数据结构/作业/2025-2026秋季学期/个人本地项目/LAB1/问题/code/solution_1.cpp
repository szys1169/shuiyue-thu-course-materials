/*#include <cstdio>

int matrix[2000][2000];

int main() {
    int n, m, q;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            scanf("%d", &matrix[i][j]);
        }
    }
    scanf("%d", &q);
    
    for (int i = 1; i <= q; ++i) {
        int sum = 0;
        int x, y, a, b;
        scanf("%d %d %d %d", &x, &y, &a, &b);
        for (int j = 0; j < a; ++j) {
            for (int k = 0; k < b; ++k) {
                sum += matrix[x + j][y + k];
            }
        }
        printf("%d\n", sum);
    }
    return 0;
}*/

#include <iostream>
#include <time.h>
#include <cstdio>

int matrix[2000][2000];

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
    scanf("%d", &q);
    printf("%d %d %d\n", n,m,q);
    for (int i = 1; i <= q; ++i) {
        long long sum = 0;
        int x, y, a, b;
        scanf("%d %d %d %d", &x, &y, &a, &b);
        for (int j = 0; j < a; ++j) {
            for (int k = 0; k < b; ++k) {
                sum += matrix[x + j][y + k];
            }
        }
        //printf("%d\n", sum);
    }
    
    end = clock();    // 记录结束时间
    
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    std::cout << "time: " << cpu_time_used << " s" << std::endl;
    
    return 0;
}