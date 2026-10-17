#include<iostream>
#include<cstdlib>
#include<cstdio>

//常量
const int MOD=1000000007;
const long long max=1e18;

//堆
struct heapnode
{
    long long timesum;
    int idx;
};
heapnode heap[100001];

int heapsize;

//向上调整
void heapup(int pos)
{
    while(pos>0)
    {
        int parent=(pos-1)/2;
        if(heap[pos].timesum<heap[parent].timesum)
        {
            heapnode tmp = heap[pos];
            heap[pos] = heap[parent];
            heap[parent] = tmp;
            pos = parent;
        }
        else 
        {
            break;
        }
    }
}

//向下调整
void heapdown(int pos)
{
    while(1)
    {
        int left = 2 * pos + 1;
        int right = 2 * pos + 2;
        int min_pos = pos;
        if (left < heapsize && heap[left].timesum<heap[min_pos].timesum)
        {
            min_pos = left;
        }
        if (right < heapsize && heap[right].timesum<heap[min_pos].timesum)
        {
            min_pos = right;
        }
        if (min_pos != pos) 
        {
            heapnode tmp = heap[pos];
            heap[pos] = heap[min_pos];
            heap[min_pos] = tmp;
            pos = min_pos;
        } 
        else 
        {
            break;
        }
    }
}

//插入元素
void heappush(long long timesum,int idx)
{
    heap[heapsize].timesum=timesum;
    heap[heapsize].idx=idx;
    heapup(heapsize);
    heapsize++;
}

//弹出
void heappop()
{
    if(heapsize==0)return;
    heapsize--;
    heap[0]=heap[heapsize];
    heapdown(0);
}

struct node
{
    int time=0;//单个节点时间
    int nextnodesize=0;//连接点个数
    int* nextnode=NULL;//连接的点
    long long count=0;//最小时间的方案数
    long long mintime=max;//最小时间
};
node nodes[100001];

//添加节点
void addconnect(int u,int v)
{
    nodes[u].nextnodesize++;
    int* newnextnode=new int[nodes[u].nextnodesize];
    for(int i=0;i<nodes[u].nextnodesize-1;i++)
    {
        newnextnode[i]=nodes[u].nextnode[i];
    }
    newnextnode[nodes[u].nextnodesize-1]=v;
    nodes[u].nextnode=newnextnode;
}

void play()
{
    while(heapsize!=0)
    {
        heapnode top=heap[0];
        heappop();
        long long currenttime=top.timesum;
        int idx=top.idx;

        if(currenttime>nodes[idx].mintime)
        {
            continue;
        }

        for(int i=0;i<nodes[idx].nextnodesize;i++)
        {
            int nextnode=nodes[idx].nextnode[i];
            long long newtimesum = nodes[idx].mintime + nodes[nextnode].time;

            if(newtimesum < nodes[nextnode].mintime)
            {
                nodes[nextnode].mintime=newtimesum;
                nodes[nextnode].count = nodes[idx].count;
                heappush(newtimesum, nextnode);
            }
            else if(newtimesum==nodes[nextnode].mintime)
            {
                nodes[nextnode].count=(nodes[nextnode].count + nodes[idx].count) % MOD;
            }
        }
    }
}

int main()
{

    int N,M;
    scanf("%d%d",&N,&M);

    for(int i=1;i<=N;i++)
    {
        scanf("%d",&nodes[i].time);
    }

    for(int i=1;i<=M;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        addconnect(u,v);
        addconnect(v,u);
    }

    heapsize=0;
    nodes[1].mintime=nodes[1].time;
    nodes[1].count = 1;
    heappush(nodes[1].mintime, 1);

    play();

    printf("%lld\n", nodes[N].mintime);
    printf("%lld\n", nodes[N].count % MOD);

    return 0;
}