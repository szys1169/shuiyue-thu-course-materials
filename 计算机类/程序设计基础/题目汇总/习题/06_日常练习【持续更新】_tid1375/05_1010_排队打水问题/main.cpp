#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, r;
    cin >> n >> r;

    vector<int> times(n);
    for (int& time : times) {
        cin >> time;
    }
    sort(times.begin(), times.end());

    long long elapsed = 0;
    long long total = 0;
    for (int time : times) {
        elapsed += time;
        total += elapsed;
    }

    cout << total << '\n';
    return 0;
}
