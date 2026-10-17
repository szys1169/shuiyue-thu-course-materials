#include<cstdio>
#include<cstdlib>
#include<iostream>

struct node
{
    int id;//编号，存储的编号减了1
    int parent;//师父
    int* children;//徒弟
    int childnumber=0;//徒弟数量
    int zhengtong=-1;//正统弟子，没有为-1
    int guide=-1;//引路人，没有为-2（便于后续编号+1调整）
    long long powersum=0;//结点战力和
    long long power=0;//战力
    int teacher=-1;//是否为正统弟子，若是则存储师父，否为-1
};

node* nodes;

//计算战力，用递归，便于按顺序计算
void powercalculate(int id)
{
    long long sum=nodes[id].power;
    for(int i=0;i<nodes[id].childnumber;i++)
    {
        powercalculate(nodes[id].children[i]);
        sum+=nodes[nodes[id].children[i]].powersum;
    }
    nodes[id].powersum=sum;
}

//计算正统弟子
void zhengtong(int id)
{
    if(nodes[id].childnumber==0)nodes[id].zhengtong=-1;
    else
    {
        int zhengtongid=-1;
        long long maxsum=-1;
        for(int i=0;i<nodes[id].childnumber;i++)
        {
            if(nodes[nodes[id].children[i]].powersum>maxsum)
            {
                maxsum=nodes[nodes[id].children[i]].powersum;
                zhengtongid=nodes[nodes[id].children[i]].id;
            }
            /*else if(nodes[nodes[id].children[i]].powersum==maxsum)
            {
                if(zhengtongid>nodes[nodes[id].children[i]].id)zhengtongid=nodes[nodes[id].children[i]].id;
            }*/
        }
        nodes[id].zhengtong=zhengtongid;
        nodes[zhengtongid].teacher=id;
    }
}

//寻找引路人
void guide(int id)
{
    int result=-2;
    int teacher=nodes[id].teacher;

    while(teacher!=-1&&teacher!=-2)
    {
        if(nodes[id].power<nodes[teacher].power)
        {
            result=teacher;
            break;
        }
        teacher=nodes[teacher].guide;
    }

    nodes[id].guide=result;

    for(int i=0;i<nodes[id].childnumber;i++)
    {
        guide(nodes[id].children[i]);
    }

}

int main()
{
    int n;
    scanf("%d",&n);
    nodes=new node[n];

    int childnum=0;
    int childid=0;
    for(int i=0;i<n;i++)
    {
        nodes[i].id=i;
        scanf("%d",&childnum);
        nodes[i].childnumber=childnum;
        nodes[i].children=new int[childnum];

        for(int j=0;j<childnum;j++)
        {
            scanf("%d",&childid);
            childid--;
            nodes[i].children[j]=childid;
            nodes[childid].parent=i;
        }
    }

    for(int i=0;i<n;i++)scanf("%lld",&nodes[i].power);

    powercalculate(0);

    for(int i=0;i<n;i++)zhengtong(i);

    guide(0);

    for(int i=0;i<n;i++)
    {
        printf("%d\n",nodes[i].guide+1);
    }
    return 0;
}
