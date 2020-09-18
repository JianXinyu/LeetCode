//
// Created by jianx on 9/18/2020.
//

#include "dp.h"
// T:O(n^2) S:O(n^2)
NumMatrix::NumMatrix(const vector<vector<int>>& matrix) {
    sums_.clear();

    if (matrix.empty()) return;

    int m = matrix.size();
    int n = matrix[0].size();

    // sums_[i][j] = sum(matrix[0][0] ~ matrix[i-1][j-1])
    sums_ = vector<vector<int>>(m + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j)
            sums_[i][j] = matrix[i - 1][j - 1]
                          + sums_[i - 1][j]
                          + sums_[i][j - 1]
                          - sums_[i - 1][j - 1];
}

int NumMatrix::sumRegion(int row1, int col1, int row2, int col2) {
    return sums_[row2 + 1][col2 + 1]
           - sums_[row2 + 1][col1]
           - sums_[row1][col2 + 1]
           + sums_[row1][col1];
}