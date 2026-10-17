#include<iostream>
#include<vector>
#include<algorithm>
#include<map>

using namespace std;

int main()
{
    int n;
    scanf("%d",&n);
    vector<pair<pair<int,int>,int>> data;
    for(int i=0;i<n;i++)
    {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        if(c>0)data.emplace_back(make_pair(a,b),c);
    }

    sort(data.begin(),data.end());
    vector<pair<int,long long>> data2;
    for(int i=1;i<data.size();i++)
    {
        if(data[i].first==data[i-1].first)
        {
            data[i].second+=data[i-1].second;
        }
        else
        {
            data2.emplace_back(data[i-1].first.second,data[i-1].second);
        }
    }
    data2.emplace_back(data[data.size()-1].first.second,data[data.size()-1].second);

    map<int,long long> dp;
    for(auto it:data2)
    {
        if(!dp.empty())
        {
            auto it2=dp.upper_bound(it.first);
            if(it2!=dp.begin())it.second+=(--it2)->second;
            if(it2->first<it.first)++it2;
            while(it2!=dp.end()&&it2->second<= it.second)dp.erase(it2++);
        }
        dp[it.first]=it.second;
    }
    printf("%lld\n",dp.rbegin()->second);
    return 0;
}