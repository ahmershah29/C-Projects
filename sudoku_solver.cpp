#include <iostream>
#include <vector>

#define UNASSIGNED 0
#define N 9

class SudokuSolver {
public:
    bool solveSudoku(int grid[N][N]) {
        int row, col;
        if (!findUnassignedLocation(grid, row, col))
            return true; // success!

        for (int num = 1; num <= 9; num++) {
            if (isSafe(grid, row, col, num)) {
                grid[row][col] = num;
                if (solveSudoku(grid))
                    return true;
                grid[row][col] = UNASSIGNED;
            }
        }
        return false; // triggers backtracking
    }

    void printGrid(int grid[N][N]) {
        for (int row = 0; row < N; row++) {
            for (int col = 0; col < N; col++)
                std::cout << grid[row][col] << " ";
            std::cout << std::endl;
        }
    }

    void inputGrid(int grid[N][N]) {
        std::cout << "Enter the Sudoku puzzle (use 0 for empty cells):" << std::endl;
        for (int row = 0; row < N; row++) {
            for (int col = 0; col < N; col++) {
                std::cin >> grid[row][col];
            }
        }
    }

    void clearGrid(int grid[N][N]) {
        for (int row = 0; row < N; row++) {
            for (int col = 0; col < N; col++) {
                grid[row][col] = UNASSIGNED;
            }
        }
    }

    bool validateGrid(int grid[N][N]) {
        for (int row = 0; row < N; row++) {
            for (int col = 0; col < N; col++) {
                if (grid[row][col] != UNASSIGNED) {
                    int num = grid[row][col];
                    grid[row][col] = UNASSIGNED;
                    if (!isSafe(grid, row, col, num)) {
                        grid[row][col] = num;
                        return false;
                    }
                    grid[row][col] = num;
                }
            }
        }
        return true;
    }

private:
    bool findUnassignedLocation(int grid[N][N], int &row, int &col) {
        for (row = 0; row < N; row++)
            for (col = 0; col < N; col++)
                if (grid[row][col] == UNASSIGNED)
                    return true;
        return false;
    }

    bool usedInRow(int grid[N][N], int row, int num) {
        for (int col = 0; col < N; col++)
            if (grid[row][col] == num)
                return true;
        return false;
    }

    bool usedInCol(int grid[N][N], int col, int num) {
        for (int row = 0; row < N; row++)
            if (grid[row][col] == num)
                return true;
        return false;
    }

    bool usedInBox(int grid[N][N], int boxStartRow, int boxStartCol, int num) {
        for (int row = 0; row < 3; row++)
            for (int col = 0; col < 3; col++)
                if (grid[row + boxStartRow][col + boxStartCol] == num)
                    return true;
        return false;
    }

    bool isSafe(int grid[N][N], int row, int col, int num) {
        return !usedInRow(grid, row, num) &&
               !usedInCol(grid, col, num) &&
               !usedInBox(grid, row - row % 3, col - col % 3, num) &&
               grid[row][col] == UNASSIGNED;
    }
};

void displayMenu() {
    std::cout << "Sudoku Solver Menu:" << std::endl;
    std::cout << "1. Input Sudoku Puzzle" << std::endl;
    std::cout << "2. Solve Sudoku Puzzle" << std::endl;
    std::cout << "3. Print Sudoku Puzzle" << std::endl;
    std::cout << "4. Clear Sudoku Puzzle" << std::endl;
    std::cout << "5. Validate Sudoku Puzzle" << std::endl;
    std::cout << "6. Exit" << std::endl;
}

void loadPredefinedPuzzle(int grid[N][N], int difficulty) {
    int easyPuzzle[N][N] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    int mediumPuzzle[N][N] = {
        {0, 0, 0, 6, 0, 0, 4, 0, 0},
        {7, 0, 0, 0, 0, 3, 6, 0, 0},
        {0, 0, 0, 0, 9, 1, 0, 8, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 5, 0, 1, 8, 0, 0, 0, 3},
        {0, 0, 0, 3, 0, 6, 0, 4, 5},
        {0, 4, 0, 2, 0, 0, 0, 6, 0},
        {9, 0, 3, 0, 0, 0, 0, 0, 0},
        {0, 2, 0, 0, 0, 0, 1, 0, 0}
    };

    int hardPuzzle[N][N] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 3, 0, 8, 5},
        {0, 0, 1, 0, 2, 0, 0, 0, 0},
        {0, 0, 0, 5, 0, 7, 0, 0, 0},
        {0, 0, 4, 0, 0, 0, 1, 0, 0},
        {0, 9, 0, 0, 0, 0, 0, 0, 0},
        {5, 0, 0, 0, 0, 0, 0, 7, 3},
        {0, 0, 2, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 4, 0, 0, 0, 9}
    };

    switch (difficulty) {
        case 1:
            std::copy(&easyPuzzle[0][0], &easyPuzzle[0][0] + N * N, &grid[0][0]);
            break;
        case 2:
            std::copy(&mediumPuzzle[0][0], &mediumPuzzle[0][0] + N * N, &grid[0][0]);
            break;
        case 3:
            std::copy(&hardPuzzle[0][0], &hardPuzzle[0][0] + N * N, &grid[0][0]);
            break;
        default:
            std::cerr << "Invalid difficulty level. Loading easy puzzle." << std::endl;
            std::copy(&easyPuzzle[0][0], &easyPuzzle[0][0] + N * N, &grid[0][0]);
            break;
    }
}

int main() {
    int grid[N][N] = {0};
    SudokuSolver solver;
    int choice, difficulty;

    while (true) {
        displayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Select difficulty level (1: Easy, 2: Medium, 3: Hard): ";
                std::cin >> difficulty;
                loadPredefinedPuzzle(grid, difficulty);
                break;
            case 2:
                if (solver.solveSudoku(grid)) {
                    std::cout << "Sudoku puzzle solved successfully!" << std::endl;
                } else {
                    std::cout << "No solution exists for the given Sudoku puzzle." << std::endl;
                }
                break;
            case 3:
                solver.printGrid(grid);
                break;
            case 4:
                solver.clearGrid(grid);
                std::cout << "Sudoku puzzle cleared." << std::endl;
                break;
            case 5:
                if (solver.validateGrid(grid)) {
                    std::cout << "Sudoku puzzle is valid." << std::endl;
                } else {
                    std::cout << "Sudoku puzzle is invalid." << std::endl;
                }
                break;
            case 6:
                std::cout << "Exiting..." << std::endl;
                return 0;
            default:
                std::cerr << "Invalid choice. Please try again." << std::endl;
        }
    }

    return 0;
}