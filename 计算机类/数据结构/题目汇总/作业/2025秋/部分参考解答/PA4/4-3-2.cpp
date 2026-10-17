#include<cstdio>

const int MAXN = 1000005;

template<typename T>
void my_swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

struct node
{
    int val;        // 值
    int dist;       // 零路径长度
    node* left;     // 左孩子
    node* right;    // 右孩子

    node(int v):val(v),dist(0),left(nullptr),right(nullptr){}
};

class leftheap
{
private:
    node* root;
    int size;
    
    node* merge_nodes(node* a, node* b)  
    {
        if(a == nullptr) return b;
        if(b == nullptr) return a;

        if(a->val > b->val)
        {
            my_swap(a, b);
        }

        a->right = merge_nodes(a->right, b);
        
        if (a->left == nullptr || (a->right != nullptr && a->left->dist < a->right->dist))
        {
            my_swap(a->left, a->right);
        }

        if(a->right == nullptr)
        {
            a->dist = 0;
        }
        else
        {
            a->dist = a->right->dist + 1;
        }

        return a;
    }

public:
    leftheap(): root(nullptr), size(0) {}
    
    leftheap(int val) : root(new node(val)), size(1) {}
    
    ~leftheap() 
    { 
        while(root != nullptr) {
            pop();
        }
    }

    void push(int val)
    {
        node* newnode = new node(val);
        root = merge_nodes(root, newnode);
        size++;
    }

    int top()
    {
        if(root == nullptr) return -1;  
        else return root->val;
    }

    void pop()
    {
        if(root == nullptr) return;

        node* oldRoot = root;  
        root = merge_nodes(root->left, root->right);
        delete oldRoot;  
        size--;
    }

    void merge(leftheap& other)  
    {
        root = merge_nodes(root, other.root);
        size += other.size;
        other.root = nullptr;
        other.size = 0;
    }

    int getsize()
    {
        return size;
    }
};

// 并查集
struct unionfind
{
    int parent[MAXN];
    int rank[MAXN];

    void init(int n)
    {
        for(int i = 1; i <= n; i++)
        {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    int find(int x)
    {
        if(parent[x] != x)
        {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    bool unite(int x, int y) 
    {
        int rootX = find(x);
        int rootY = find(y);

        if(rootX == rootY) return false;

        if(rank[rootX] < rank[rootY])
        {
            parent[rootX] = rootY;
        }
        else if(rank[rootX] > rank[rootY])
        {
            parent[rootY] = rootX;
        }
        else{
            parent[rootY] = rootX;
            rank[rootX]++;
        }
        return true;
    }
};

// 全局变量
int a[MAXN];
unionfind uf;
leftheap heaps[MAXN];

int main()
{
    int n, m, k, q;
    scanf("%d %d %d %d", &n, &m, &k, &q);

    // 读入点权
    for(int i = 1; i <= n; i++)  // 从1开始
    {
        scanf("%d", &a[i]);
        heaps[i].push(a[i]);
    }

    uf.init(n);

    // 处理初始边
    for(int i = 0; i < m; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);

        int rootu = uf.find(u);
        int rootv = uf.find(v);

        if(rootu != rootv)
        {
            // 先合并并查集
            bool success = uf.unite(u, v);
            if(success) {
                int newroot = uf.find(u);
                int oldroot = (newroot == rootu) ? rootv : rootu;

                // 合并堆
                heaps[newroot].merge(heaps[oldroot]);

                while(heaps[newroot].getsize() > k)
                {
                    heaps[newroot].pop();
                }
            }
        }
    }

    // 处理操作
    for(int i = 0; i < q; i++)
    {
        int op;
        scanf("%d", &op);

        if(op == 1)  // 加边操作
        {
            int u, v;
            scanf("%d %d", &u, &v);

            int rootu = uf.find(u);
            int rootv = uf.find(v);

            if(rootu != rootv)
            {
                bool success = uf.unite(u, v);
                if(success) {
                    int newroot = uf.find(u);
                    int oldroot = (newroot == rootu) ? rootv : rootu;

                    heaps[newroot].merge(heaps[oldroot]);

                    while(heaps[newroot].getsize() > k)
                    {
                        heaps[newroot].pop();
                    }
                }
            }
        }
        else if(op == 2)  // 查询操作
        {
            int u;
            scanf("%d", &u);

            int rootu = uf.find(u);

            if(heaps[rootu].getsize() < k)  
            {
                printf("-1\n");
            }
            else
            {
                printf("%d\n", heaps[rootu].top());
            }
        }
    }
    
    return 0;
}