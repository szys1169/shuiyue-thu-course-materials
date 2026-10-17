#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<random>
#include<ctime>
#include<fstream>
#include<sstream>

using namespace std;

typedef pair<string, int> DataPair;
vector<DataPair> poj_data;

void parse_poj() {
    ifstream fin("poj.txt");  
    if (!fin) { cerr << "debug"; return; }
    string line;
    while (getline(fin, line)) 
    {  
        stringstream ss(line);
        int rank, ac_count, submit_count;
        string username;
        if (ss >> rank >> username >> ac_count >> submit_count) 
        {
            poj_data.emplace_back(username, ac_count);
        }
    }
    fin.close();
}

int main()
{
    int m,n;
    cin >> n >> m;

    parse_poj();

    std::vector<int> nums(500001);
    for (int i = 0; i < 500001; ++i) 
    {
        nums[i] = 0 + i;
    }

    for (int i = 500001 - 1; i > 0; --i) 
    {
        long long rand_val = (long long)rand() * (RAND_MAX + 1LL) + rand();
        int j = static_cast<int>(rand_val % (i + 1)); 
        std::swap(nums[i], nums[j]);
    }

    nums.resize(n);

    ofstream fout("out1");

    for (int i=1; i<=n; i++) 
    {
        fout << "0 " << poj_data[nums[i]].first << " " << poj_data[nums[i]].second << "\n";
    }

    for (int i = n; i > 0; --i) 
    {
        long long rand_val = (long long)rand() * (RAND_MAX + 1LL) + rand();
        int j = static_cast<int>(rand_val % (i + 1)); 
        std::swap(nums[i], nums[j]);
    }

    nums.resize(n);

    for (int i=1; i<=m; i++) 
    {
        fout << "1 " << poj_data[nums[i]].first  << "\n";
    }

    for (int i = n; i > 0; --i) 
    {
        long long rand_val = (long long)rand() * (RAND_MAX + 1LL) + rand();
        int j = static_cast<int>(rand_val % (i + 1)); 
        std::swap(nums[i], nums[j]);
    }
    
    fout<<"2"<<endl;
    
    fout.close();
}