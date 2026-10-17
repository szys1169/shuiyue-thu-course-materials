#include <cstdio>

const int MAXN = 1000005;

// 交换函数替代 std::swap
template<typename T>
void my_swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

// 左式堆节点
struct Node {
    int val;        // 值
    int dist;       // 零路径长度
    Node* left;     // 左子树
    Node* right;    // 右子树
    
    Node(int v) : val(v), dist(0), left(nullptr), right(nullptr) {}
};

// 左式堆
class LeftistHeap {
private:
    Node* root;
    int size;
    
    // 合并两个堆
    Node* merge(Node* a, Node* b) {
        if (a == nullptr) return b;
        if (b == nullptr) return a;
        
        // 保证a是根值较小的堆（最小堆）
        if (a->val > b->val) {
            my_swap(a, b);
        }
        
        // 递归合并右子树
        a->right = merge(a->right, b);
        
        // 维护左式堆性质：左子树的零路径长度不小于右子树
        if (a->left == nullptr || (a->right != nullptr && a->left->dist < a->right->dist)) {
            my_swap(a->left, a->right);
        }
        
        // 更新零路径长度
        if (a->right == nullptr) {
            a->dist = 0;
        } else {
            a->dist = a->right->dist + 1;
        }
        
        return a;
    }
    
public:
    LeftistHeap() : root(nullptr), size(0) {}
    
    LeftistHeap(int val) : root(new Node(val)), size(1) {}
    
    // 插入元素
    void push(int val) {
        Node* newNode = new Node(val);
        root = merge(root, newNode);
        size++;
    }
    
    // 获取堆顶
    int top() {
        if (root == nullptr) return -1;
        return root->val;
    }
    
    // 弹出堆顶
    void pop() {
        if (root == nullptr) return;
        
        Node* oldRoot = root;
        root = merge(root->left, root->right);
        delete oldRoot;
        size--;
    }
    
    // 合并另一个堆
    void merge(LeftistHeap& other) {
        root = merge(root, other.root);
        size += other.size;
        other.root = nullptr;
        other.size = 0;
    }
    
    // 获取堆大小
    int getSize() {
        return size;
    }
    
    // 清空堆
    void clear() {
        root = nullptr;
        size = 0;
    }
};

// 并查集
struct UnionFind {
    int parent[MAXN];
    int rank[MAXN];
    
    void init(int n) {
        for (int i = 1; i <= n; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }
    
    int find(int x) {
        // 路径压缩
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    bool unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        
        if (rootX == rootY) return false;
        
        // 按秩合并
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
        
        return true;
    }
};

int n, m, k, q;
int a[MAXN];
UnionFind uf;
LeftistHeap heaps[MAXN];  // 每个连通分量的堆

int main() {
    scanf("%d %d %d %d", &n, &m, &k, &q);
    
    // 读入点权
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    
    // 初始化并查集
    uf.init(n);
    
    // 初始化堆：每个点有自己的堆
    for (int i = 1; i <= n; i++) {
        heaps[i].push(a[i]);
    }
    
    // 读入初始边
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        
        int rootU = uf.find(u);
        int rootV = uf.find(v);
        
        if (rootU != rootV) {
            // 合并连通分量
            bool success = uf.unite(u, v);
            if (success) {
                int newRoot = uf.find(u);
                int oldRoot = (newRoot == rootU) ? rootV : rootU;
                
                // 合并堆
                heaps[newRoot].merge(heaps[oldRoot]);
                
                // 保持堆大小不超过k
                while (heaps[newRoot].getSize() > k) {
                    heaps[newRoot].pop();
                }
            }
        }
    }
    
    // 处理操作
    for (int i = 0; i < q; i++) {
        int op;
        scanf("%d", &op);
        
        if (op == 1) {
            // 加边操作
            int u, v;
            scanf("%d %d", &u, &v);
            
            int rootU = uf.find(u);
            int rootV = uf.find(v);
            
            if (rootU != rootV) {
                // 合并连通分量
                bool success = uf.unite(u, v);
                if (success) {
                    int newRoot = uf.find(u);
                    int oldRoot = (newRoot == rootU) ? rootV : rootU;
                    
                    // 合并堆
                    heaps[newRoot].merge(heaps[oldRoot]);
                    
                    // 保持堆大小不超过k
                    while (heaps[newRoot].getSize() > k) {
                        heaps[newRoot].pop();
                    }
                }
            }
        } else {
            // 查询操作
            int u;
            scanf("%d", &u);
            
            int root = uf.find(u);
            
            if (heaps[root].getSize() < k) {
                printf("-1\n");
            } else {
                printf("%d\n", heaps[root].top());
            }
        }
    }
    
    return 0;
}