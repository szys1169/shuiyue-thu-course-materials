#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> height(n);
    for (int& value : height) {
        cin >> value;
    }

    int m;
    cin >> m;
    vector<int> required(m);
    for (int& index : required) {
        cin >> index;
    }

    vector<int> dp(n, 1);
    int longest = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (height[j] <= height[i]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        longest = max(longest, dp[i]);
    }

    // 我先求普通最长序列，再用必选数量修正答案。
    cout << max(longest, m) << '\n';
    return 0;
}
