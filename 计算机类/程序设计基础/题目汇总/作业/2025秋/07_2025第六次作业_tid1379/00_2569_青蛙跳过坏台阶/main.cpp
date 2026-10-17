#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> bad(m);
    for (int& step : bad) {
        cin >> step;
    }

    vector<long long> dp(n + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= n; ++i) {
        dp[i] += dp[i - 1];
        if (i >= 2) {
            dp[i] += dp[i - 2];
        }
    }

    vector<bool> isBad(n + 1, false);
    for (int step : bad) {
        if (step >= 0 && step <= n) {
            isBad[step] = true;
        }
    }

    cout << dp[n] << '\n';
    return 0;
}
