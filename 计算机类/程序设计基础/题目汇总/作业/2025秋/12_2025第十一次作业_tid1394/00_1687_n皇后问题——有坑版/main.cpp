#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n;
int answer = 0;
vector<vector<int>> board;
vector<bool> usedColumn;
vector<bool> usedDiagonal1;
vector<bool> usedDiagonal2;

void search(int row, int count) {
    if (row == n) {
        answer = max(answer, count);
        return;
    }

    for (int column = 0; column < n; ++column) {
        int diagonal1 = row - column + n - 1;
        int diagonal2 = row + column;
        if (board[row][column] == 0
            || usedColumn[column]
            || usedDiagonal1[diagonal1]
            || usedDiagonal2[diagonal2]) {
            continue;
        }

        usedColumn[column] = true;
        usedDiagonal1[diagonal1] = true;
        usedDiagonal2[diagonal2] = true;
        search(row + 1, count + 1);
        usedColumn[column] = false;
        usedDiagonal1[diagonal1] = false;
        usedDiagonal2[diagonal2] = false;
    }
}

int main() {
    cin >> n;
    board.assign(n, vector<int>(n));
    for (auto& row : board) {
        for (int& cell : row) {
            cin >> cell;
        }
    }

    usedColumn.assign(n, false);
    usedDiagonal1.assign(2 * n - 1, false);
    usedDiagonal2.assign(2 * n - 1, false);
    search(0, 0);

    cout << answer << '\n';
    return 0;
}
