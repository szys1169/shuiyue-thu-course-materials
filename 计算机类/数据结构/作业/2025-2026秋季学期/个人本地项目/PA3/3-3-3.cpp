#include<cstdlib>
#include<cstdio>

int d,n;
int point[100005][5];
int index[100005];
int current_dim=0;

struct node
{
    int splitdim;
    int splitval;
    node* left=nullptr;
    node* right=nullptr;
    bool isleaf=1;
    int start;
    int count;
};

node* newnode()
{
    node* p=new node;
    return p;
}

int compare(const void* a,const void* b)
{
    int idx_a=*(const int*)a;
    int idx_b=*(const int*)b;
    int val_a=point[idx_a][current_dim];
    int val_b=point[idx_b][current_dim];
    return val_a-val_b;
}

node* build(node* node,int left,int right,int dim)
{
    node->splitdim=dim;

    if(right-left+1<=20)
    {
        node->isleaf=1;
        node->start=left;
        node->count=right-left+1;
        return node;
    }
    
    node->isleaf=0;

    current_dim=dim;
    qsort(index + left, right - left + 1, sizeof(index[0]), compare);

    int mid=(left+right)/2;
    node->splitval=point[index[mid]][dim];

    node->left=newnode();
    build(node->left,left,mid, (dim + 1) % d);

    node->right=newnode();
    build(node->right,mid+1,right, (dim + 1) % d);

    return node;
}

void query(node* node,const int* x,long long& min_dist)
{
    if(node->isleaf)
    {
        for(int i=0;i<node->count;i++)
        {
            int p_idx=index[node->start+i];
            long long dist=0;
            for(int j=0;j<d;j++)
            {
                long long diff=x[j]-point[p_idx][j];
                dist+=diff*diff;
                if(dist>=min_dist)break;
            }
            if(dist<min_dist)
            {
                min_dist=dist;
            }
        }
        return;
    }

    if(x[node->splitdim]<=node->splitval)
    {
        query(node->left,x,min_dist);
        long long diff=x[node->splitdim]-node->splitval;
        long long dist_to_plane=diff*diff;
        if(dist_to_plane<min_dist)
        {
            query(node->right,x,min_dist);
        }
    }
    else
    {
        query(node->right,x,min_dist);
        long long diff=x[node->splitdim]-node->splitval;
        long long dist_to_plane=diff*diff;
        if(dist_to_plane<min_dist)
        {
            query(node->left,x,min_dist);
        }
    }
    
}

int main()
{
    scanf("%d%d",&d,&n);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<d;j++)
        {
            scanf("%d",&point[i][j]);
        }
        index[i]=i;
    }

    node* root=newnode();
    build(root,0,n-1,0);

    int q;
    scanf("%d",&q);
    for(int i=0; i < q; i++)
    {
        int x[5];
        for(int j=0;j<d;j++)
        {
            scanf("%d",&x[j]);
        }
        long long min_dist=1e18;
        query(root,x,min_dist);
        printf("%lld\n",min_dist);
    }

    return 0;

}