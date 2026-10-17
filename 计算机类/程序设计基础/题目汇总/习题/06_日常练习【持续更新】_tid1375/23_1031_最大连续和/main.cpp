#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<long long> numbers;
    long long value;
    while (cin >> value) {
        numbers.push_back(value);
    }

    long long current = 0;
    long long answer = 0;
    for (long long number : numbers) {
        current = max(0LL, current + number);
        answer = max(answer, current);
    }

    cout << answer << '\n';
    return 0;
}
