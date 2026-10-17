#include<iostream>
#include<cstdio>
#include<cstdlib>

struct node
{
    long long left,right;
    long long reversesum=0;
    long long reverselazy=0;
    node* parent=nullptr;
    node* leftchild=nullptr;
    node* rightchild=nullptr;

    node(long long l,long long r)
    {
        left=l;
        right=r;
        reversesum=0;
        reverselazy=0;
        parent=leftchild=rightchild=nullptr;
    }
};
node* root=nullptr;

node* newnode(long long l,long long r)
{
    node* p=new node(l,r);
    return p;
}

void init(long long n)
{
    root=new node(1,n);
}

void pushdownreverse(node* x)//下传标记
{
    if(x==nullptr||x->reverselazy==0)return;
    if(x->leftchild!=nullptr)
    {
        x->leftchild->reversesum+=x->reverselazy*(x->leftchild->right-x->leftchild->left+1);
        x->leftchild->reverselazy+=x->reverselazy;
        x->rightchild->reversesum+=x->reverselazy*(x->rightchild->right-x->rightchild->left+1);
        x->rightchild->reverselazy+=x->reverselazy;
        x->reverselazy=0;
    }
}
void split(node* node,long long pos)//分裂
{
    if(node==nullptr)return ;
    if(pos<=node->left||pos>node->right)return;
    if(node->leftchild==nullptr&&node->rightchild==nullptr)
    {
        node->leftchild=newnode(node->left,pos-1);
        node->rightchild=newnode(pos,node->right);
        node->leftchild->parent=node;
        node->rightchild->parent=node;
        pushdownreverse(node);
        return;
    }
}
void reverse(node* node,long long a,long long b)//区间
{
    pushdownreverse(node);
    if(node->left>b||node->right<a)return;
    else if(node->left>=a&&node->right<=b)//区间覆盖节点范围直接增加
    {
        node->reversesum+=(node->right-node->left+1);
        node->reverselazy+=1;
        return;
    }
    else if(node->leftchild!=nullptr||node->rightchild!=nullptr)//有子节点则继续向下递归
    {
        node->reversesum+=(std::min(b,node->right)-std::max(a,node->left)+1);
        reverse(node->leftchild,a,b);
        reverse(node->rightchild,a,b);
    }
    else if(node->left<a)//没有子节点则分裂
    {
        split(node,a);
        reverse(node,a,b);
    }
    else if(node->right>b)
    {
        split(node,b+1);
        reverse(node,a,b);
    }
}
long long query(node* node,long long a,long long b)//查询
{
    pushdownreverse(node);
    if(node->left>b||node->right<a)return 0;
    else if(node->left>=a&&node->right<=b)//区间覆盖节点范围直接加上节点大小
    {
        return node->reversesum;
    }
    else if(node->leftchild==nullptr&&node->rightchild==nullptr)//没有子节点则代表该区间上均匀分布
    {
        return (std::min(b,node->right)-std::max(a,node->left)+1)*node->reversesum/(node->right-node->left+1);
    }
    else //有子节点则继续向下查询
    {
        return query(node->leftchild,a,b)+query(node->rightchild,a,b);
    }
}
int main()
{
    long long n;
    int m;
    scanf("%lld%d",&n,&m);
    init(n);
    for(int i=0;i<m;i++)
    {
        char c;
        long long a,b;
        scanf(" %c%lld%lld",&c,&a,&b);
        if(c=='H')
        {
            reverse(root,a,b);
        }
        else if(c=='Q')
        {
            printf("%lld\n", query(root,a,b));
        }
    }
}