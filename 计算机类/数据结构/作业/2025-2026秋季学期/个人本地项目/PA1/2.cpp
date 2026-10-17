#include<iostream>
#include<vector>
#include<algorithm>
#include<iomanip>
using namespace std;

int main()
{
    int n;                          
    cin >> n;
    //输入第一行

    vector <int> cantin(n);
    for(int k = 0; k < n; k++)
    {
        cin >> cantin[k];
    }//输入第二行

    vector<vector<int>> goal(n, vector<int>(n,0));

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < i; j++)
        {
            cin >> goal[i][j];
            goal[j][i] = goal[i][j];
        }
    }
    //输入剩下的数据并且补全二维数组

    vector<int> shunxu(n);
    for(int h = 0; h < n; h++)
    {
        shunxu[h] = h;
    }
    //把目标点的顺序放在一维数组里便于进行全排列

    int total_time = 0;
    int min_time = 0;
    int first = 0;
    int last = 0;
    vector<int> time(0);
    do
    {   
        int goals = 0;
        first = cantin[shunxu[0]];
        for(int i = 0; i < n-1; i++)
        {
            goals = goals + goal[shunxu[i]][shunxu[i+1]];
        }
        last = cantin[shunxu[n-1]];
        //分别计算所用时间
        total_time = first + goals + last;
        time.push_back(total_time);
        //比较最小时间
    }while(next_permutation(shunxu.begin(), shunxu.end()));
    //全排列计算比较时间

    min_time = time[0];
    for(int i = 0; i < time.size(); i++)
    {
        if(min_time > time[i])
        {
            min_time = time[i];
        }
    }
    cout << min_time;

    return 0;
}