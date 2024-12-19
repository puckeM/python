#include <iostream>
#include <vector>
#include <iomanip>
#include <ctime>
#include <locale.h>

using namespace std;

void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            cout << setw(5) << elem;
        }
        cout << endl;
    }
}

vector<vector<int>> removeColumns(const vector<vector<int>>& matrix, vector<int>& evenCounts) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    vector<vector<int>> result;

    evenCounts.resize(cols, 0);
    for (int j = 0; j < cols; j++) {
        for (int i = 0; i < rows; i++) {
            if (matrix[i][j] % 2 == 0) {
                evenCounts[j]++;
            }
        }
    }

    for (int i = 0; i < rows; i++) {
        vector<int> newRow;
        for (int j = 0; j < cols; j++) {
            if (evenCounts[j] <= 3) {
                newRow.push_back(matrix[i][j]);
            }
        }
        result.push_back(newRow);
    }
    return result;
}

pair<int, int> findMaxElement(const vector<vector<int>>& matrix) {
    int maxElement = INT_MIN;
    int columnIndex = -1;

    for (int j = 0; j < matrix[0].size(); j++) {
        for (int i = 0; i < matrix.size(); i++) {
            if (matrix[i][j] > maxElement) {
                maxElement = matrix[i][j];
                columnIndex = j;
            }
        }
    }
    return { columnIndex, maxElement };
}

int main() {
    srand(time(0));
    setlocale(0, "russian");

    int N, M;

    cout << "Введите количество строк (N): ";
    cin >> N;
    cout << "Введите количество столбцов (M): ";
    cin >> M;

    if (M <= N) {
        cout << "Количество столбцов (M) должно быть больше количества строк (N)!" << endl;
        return 1;
    }

    vector<vector<int>> matrix(N, vector<int>(M));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            matrix[i][j] = rand() % 50 - 25;
        }
    }

    cout << "\nИсходная матрица:\n";
    printMatrix(matrix);

    vector<int> evenCounts;
    vector<vector<int>> updatedMatrix = removeColumns(matrix, evenCounts);

    cout << "\nКоличество четных элементов в столбцах исходной матрицы:\n";
    for (int i = 0; i < evenCounts.size(); ++i) {
        cout << "Столбец " << i + 1 << ": " << evenCounts[i] << " четных элементов\n";
    }

    cout << "\nМатрица после удаления столбцов с более чем тремя четными элементами:\n";

    if (!updatedMatrix.empty() && !updatedMatrix[0].empty()) {
        pair<int, int> result = findMaxElement(updatedMatrix);
        int columnIndex = result.first;
        int maxElement = result.second;
        cout << "\nМаксимальный элемент: " << maxElement << ", находится в столбце " << columnIndex + 1 << endl;
    }
    else {
        cout << "\nПолученная матрица пуста.\n";
    }

    return 0;
}
