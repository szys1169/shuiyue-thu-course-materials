#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> numbers(n);
    for (int& number : numbers) {
        cin >> number;
    }

    int maximum = *max_element(numbers.begin(), numbers.end());
    for (int place = 1; maximum / place > 0; place *= 10) {
        vector<vector<int>> buckets(10);
        for (int number : numbers) {
            buckets[(number / place) % 10].push_back(number);
        }

        int index = 0;
        for (auto& bucket : buckets) {
            while (!bucket.empty()) {
                numbers[index++] = bucket.back();
                bucket.pop_back();
            }
        }

        for (int i = 0; i < n; ++i) {
            if (i > 0) {
                cout << ' ';
            }
            cout << numbers[i];
        }
        cout << '\n';
    }
    return 0;
}
