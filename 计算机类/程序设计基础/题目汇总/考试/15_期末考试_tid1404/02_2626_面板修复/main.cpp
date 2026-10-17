#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int height, width;
    cin >> height >> width;
    vector<string> panel(height);
    for (string& row : panel) {
        cin >> row;
    }

    const int infinity = 1e9;
    vector<vector<int>> dp(height, vector<int>(width, infinity));
    dp[0][0] = 0;

    for (int row = 0; row < height; ++row) {
        for (int column = 0; column < width; ++column) {
            if (row == 0 && column == 0) {
                continue;
            }

            int previous = infinity;
            if (row > 0) {
                previous = min(previous, dp[row - 1][column]);
            }
            if (column > 0) {
                previous = min(previous, dp[row][column - 1]);
            }
            dp[row][column] = previous + (panel[row][column] == '#' ? 1 : 0);
        }
    }

    cout << dp[height - 1][width - 1] << '\n';
    return 0;
}
