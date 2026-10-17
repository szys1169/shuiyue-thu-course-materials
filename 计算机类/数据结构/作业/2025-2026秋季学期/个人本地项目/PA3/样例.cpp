#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

const int MAX_N = 100005;
const int MAX_D = 5;
const int MAX_KD_NODES = 200005;
const int LEAF_SIZE = 32;
// 自定义无穷大（大于最大可能距离平方：5*(1e7)^2=5e14）
const long long INF = 1000000000000000000LL;

int d, n;
int pts[MAX_N][MAX_D];
int idx[MAX_N];
// 用于qsort比较函数的全局临时变量（传递当前划分维度）
int current_dim;

struct KDNode {
    int split_dim;
    int split_val;
    int left, right;
    bool is_leaf;
    int start, count;
} kd_nodes[MAX_KD_NODES];

int next_node;

// qsort比较函数：按current_dim维度升序排序索引
int cmp(const void* a, const void* b) {
    int idx1 = *(const int*)a;
    int idx2 = *(const int*)b;
    int val1 = pts[idx1][current_dim];
    int val2 = pts[idx2][current_dim];
    return val1 - val2;
}

int build(int node, int l, int r, int dim) {
    kd_nodes[node].split_dim = dim;
    kd_nodes[node].is_leaf = false;

    if (r - l + 1 <= LEAF_SIZE) {
        kd_nodes[node].is_leaf = true;
        kd_nodes[node].start = l;
        kd_nodes[node].count = r - l + 1;
        return node;
    }

    // 使用qsort替代sort，设置当前划分维度
    current_dim = dim;
    qsort(idx + l, r - l + 1, sizeof(int), cmp);

    int mid = (l + r) / 2;
    int mid_val = pts[idx[mid]][dim];
    kd_nodes[node].split_val = mid_val;

    int left_node = next_node++;
    kd_nodes[node].left = left_node;
    build(left_node, l, mid, (dim + 1) % d);

    int right_node = next_node++;
    kd_nodes[node].right = right_node;
    build(right_node, mid + 1, r, (dim + 1) % d);

    return node;
}

void query(int node, const int* x, long long& min_dist) {
    KDNode& curr = kd_nodes[node];

    if (curr.is_leaf) {
        for (int i = 0; i < curr.count; ++i) {
            int p_idx = idx[curr.start + i];
            long long dist = 0;
            for (int j = 0; j < d; ++j) {
                long long diff = x[j] - pts[p_idx][j];
                dist += diff * diff;
                if (dist >= min_dist) break; // 提前剪枝
            }
            if (dist < min_dist) {
                min_dist = dist;
            }
        }
        return;
    }

    int dim = curr.split_dim;
    int val = x[dim];
    int split_val = curr.split_val;
    long long diff = val - split_val;
    long long dist_to_plane = diff * diff;

    // 优先查询同侧子树
    if (val <= split_val) {
        query(curr.left, x, min_dist);
        // 剪枝判断：是否需要查询另一侧
        if (dist_to_plane < min_dist) {
            query(curr.right, x, min_dist);
        }
    } else {
        query(curr.right, x, min_dist);
        if (dist_to_plane < min_dist) {
            query(curr.left, x, min_dist);
        }
    }
}

int main() {
    scanf("%d%d", &d, &n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < d; ++j) {
            scanf("%d", &pts[i][j]);
        }
        idx[i] = i;
    }

    next_node = 1;
    build(0, 0, n - 1, 0);

    int q;
    scanf("%d", &q);
    while (q--) {
        int x[MAX_D];
        for (int j = 0; j < d; ++j) {
            scanf("%d", &x[j]);
        }
        long long min_dist = INF;
        query(0, x, min_dist);
        printf("%lld\n", min_dist);
    }

    return 0;
}