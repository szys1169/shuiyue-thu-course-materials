#include<iostream>
#include<cstdio>
#include<cstdlib>

int r=0;//记录旋转

int normalmod(int a,int b)
{
    int res=a%b;
    if(res<0)res+=b;
    return res;
}

struct node
{
    int reverseflag=0;
    int size;
    int name;
    node* parent=nullptr;
    node* leftchild=nullptr;
    node* rightchild=nullptr;
};

node* null;//哨兵节点
node* root=nullptr;
int current_size=0;//当前舞者总数
node* pool = nullptr;
int pool_ptr = 0;
int pool_cap = 0;

void init()
{
    null=new node;
    null->leftchild=null->rightchild=null->parent=null;
    null->size=0;
    null->reverseflag=0;
    root=null;
}

node* newnode(int name)
{
    extern node* pool;
    extern int pool_ptr;
    extern int pool_cap;
    node* p = nullptr;
    if(pool && pool_ptr < pool_cap){
        p = &pool[pool_ptr++];
    } else {
        p = new node;
    }
    p->name = name;
    p->leftchild = p->rightchild = p->parent = null;
    p->size = 1;
    p->reverseflag = 0;
    return p;
}

//更新树规模
void pushupsize(node* x)
{
    if(x==null)return;
    x->size=x->leftchild->size+1+x->rightchild->size;
}

//下传翻转标记
void pushdownreverse(node* x)
{
    if(x==null||x->reverseflag==0)return;
    std::swap(x->leftchild,x->rightchild);
    x->leftchild->reverseflag^=1;
    x->rightchild->reverseflag^=1;
    x->reverseflag=0;
}

void lrotate(node* target)
{
    if(target==null)
        return;
    if(target->rightchild==null)
        return;
    node* newroot=target->rightchild;
    pushdownreverse(target);
    pushdownreverse(newroot);
    target->rightchild=newroot->leftchild;
    if(newroot->leftchild!=null)
        newroot->leftchild->parent=target;
    newroot->leftchild=target;
    newroot->parent=target->parent;
    target->parent=newroot;
    if(newroot->parent==null)
        root=newroot;
    else
    {
        if(newroot->parent->leftchild==target)
            newroot->parent->leftchild=newroot;
        else
            newroot->parent->rightchild=newroot;
    }
    pushupsize(target);
    pushupsize(newroot);
}

void rrotate(node* target)
{
    if(target==null)
        return;
    if(target->leftchild==null)
        return;
    node* newroot=target->leftchild; 
    pushdownreverse(target);
    pushdownreverse(newroot);
    target->leftchild=newroot->rightchild;
    if(newroot->rightchild!=null)
        newroot->rightchild->parent=target;
    newroot->rightchild=target;
    newroot->parent=target->parent;
    target->parent=newroot;
    if(newroot->parent==null)
        root=newroot;
    else
    {
        if(newroot->parent->leftchild==target)
            newroot->parent->leftchild=newroot;
        else
            newroot->parent->rightchild=newroot;
    }
    pushupsize(target);
    pushupsize(newroot);
}

void movetoroot(node* target,node* target_parent)
{
    if(target==null)
        return;
    while(target->parent!=target_parent)
    {
        node* parent=target->parent;
        node* grandparent=parent->parent;
        pushdownreverse(grandparent);
        pushdownreverse(parent);
        pushdownreverse(target);
        if(grandparent==target_parent)
        {
            if(parent->leftchild==target)
                rrotate(parent);
            else
                lrotate(parent);
        }
        else
        {
            if(grandparent->leftchild==parent&&parent->leftchild==target)
            {
                rrotate(grandparent);
                rrotate(parent);
            }
            else if(grandparent->rightchild==parent&&parent->rightchild==target)
            {
                lrotate(grandparent);
                lrotate(parent);
            }
            else if(grandparent->leftchild==parent&&parent->rightchild==target)
            {
                lrotate(parent);
                rrotate(grandparent);
            }
            else
            {
                rrotate(parent);
                lrotate(grandparent);
            }
        }
    }
}

node* find(int index)
{
    node* cur=root;
    pushdownreverse(cur);
    while(true)
    {
        if(cur->leftchild->size>=index)
        {
            cur=cur->leftchild;
        }
        else if(cur->leftchild->size+1==index)
        {
            return cur;
        }
        else
        {
            index=index-(cur->leftchild->size+1);
            cur=cur->rightchild;
        }
        pushdownreverse(cur);
    }
}

void split(int index,node*& left,node*& right)
{
    if (index <= 0)
    {
        left = null;
        right = root;
        if (right != null) right->parent = null;
        return;
    }
    if (index >= current_size)
    {
        left = root;
        if (left != null) left->parent = null;
        right = null;
        return;
    }
    node* kth=find(index);
    movetoroot(kth,null);
    left=kth;
    right=kth->rightchild;
    right->parent=null;
    left->rightchild=null;
    pushupsize(left);
}

node* merge(node* left,node* right)
{
    if(left==null)return right;
    if(right==null)return left;
    root = left;
    node* last = find(left->size);
    movetoroot(last,null);
    last->rightchild=right;
    right->parent=last;
    pushupsize(last);
    return last;
}

void insert(int index,int name)
{
    node* new_node=newnode(name);
    node* left=null;
    node* right=null;
    split(index,left,right);
    root=merge(merge(left,new_node),right);
    current_size++;
}

void swapname(int x,int y)
{
    if(x==y)return;
    node* nx=find(x+1);
    movetoroot(nx,null);
    node* ny=find(y+1);
    movetoroot(ny,null);
    std::swap(nx->name,ny->name);
}

void reverse(int x,int y)
{
    if(x==y)return;
    //if(x==y-1)swapname(x,y);
    node* left=null;
    node* mid=null;
    node* right=null;
    node* n=null;
    if(x<y)
    {
        split(y+1,mid,right);
        root = mid;
        split(x,left,mid);
        mid->reverseflag^=1;
        root=merge(merge(left,mid),right);   
    }
    else
    {
        split(x, left, right);
        split(y+1, left, mid);
        n = merge(right,left);
        n->reverseflag ^= 1;
        root=merge(n,mid);
        r=normalmod(r + x , current_size);//通过操作旋转量r，节省split和merge的操作次数
    }
}

void traversepreorder(node* x,int* ans,int& index)
{
    if(x==null)return;
    pushdownreverse(x);
    traversepreorder(x->leftchild,ans,index);
    ans[index++]=x->name;
    traversepreorder(x->rightchild,ans,index);
}

void printpre()
{
    int N = current_size;
    if (N == 0) {
        std::cout << '\n';
        return;
    }
    int* ans = new int[N];
    int index = 0;
    traversepreorder(root, ans, index);

    int first = normalmod(N - r, N);
    for (int i = 0; i < N; i++) {
        if(i) std::cout << ' ';
        std::cout << ans[(first + i) % N];
    }
    std::cout << '\n';
    delete[] ans;
}

int main()
{
    int N,M;
    scanf("%d%d",&N,&M);

    char op;//选择
    int x,y;
    init();
    if (N > 0) {
        pool = new node[N];
        pool_ptr = 0;
        pool_cap = N;
    }
    for(int i=1;i<=M;i++)
    {
        scanf(" %c",&op);
        if(op=='I')//插入新的节点
        {
            scanf("%d%d",&x,&y);
            if(current_size!=0)y=y - r;
            if(y<-1)
            {
                y+=current_size;
                r=normalmod(r+1,current_size+1);
            }
            else if(y==-1)
            {
                y+=current_size;
                r=normalmod(r+1,current_size+1);
            }
            insert(y,x);
        }
        else if(op == 'S') // 交换两个节点的名字
        {
            scanf("%d%d",&x,&y);
            if(x==y)continue;
            if(current_size == 0) continue;
            x = normalmod(x - r, current_size);
            y = normalmod(y - r, current_size);
            swapname(x, y);
        }
        else if(op=='R')//旋转
        {
            scanf("%d",&x);
            r = normalmod(r + x, current_size);
        }
        else if(op=='F')//翻转
        {
            scanf("%d%d",&x,&y);
            x=normalmod(x - r, current_size);
            y=normalmod(y - r, current_size);
            reverse(x,y);
        }
    }
    printpre();
    return 0;
}