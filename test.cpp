#include <vector>
#include <iostream>

using namespace std;

int main() {
    // Cria uma matriz 3x3
    vector<vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    // Remove a segunda coluna
    int colToRemove = 1;
    vector<vector<int>> newMatrix;
    for (auto &row : matrix) {
        vector<int> newRow;
        for (int i = 0; i < row.size(); i++) {
            if (i != colToRemove) {
                newRow.push_back(row[i]);
            }
        }
        newMatrix.push_back(newRow);
    }

    // Imprime a nova matriz
    for (auto &row : newMatrix) {
        for (int &num : row) {
            cout << num << ' ';
        }
        cout << '\n';
    }

    return 0;
}