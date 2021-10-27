#pragma once

#include <vector>
#include <random>
#include <algorithm>

using std::vector;

class GameOfLife {
private:
    struct CellState {
        bool alive = false;
        int neighboursCount = 0;

        void swapLife() {
            alive = !alive;
        }
    };

    int rowCount;
    int colCount;
    vector<vector<CellState>> buffer;
    vector<vector<CellState>> states;

    void initBoard(float fillFactor) {
        std::random_device rd;  // random generator
        std::mt19937 rng(rd());
        std::uniform_int_distribution<int> randRow(0, rowCount - 1);  // fk it's inclusive [a, b]
        std::uniform_int_distribution<int> randCol(0, colCount - 1);

        int totalCnt = rowCount * colCount * fillFactor;

        while (totalCnt > 0) {  // generate cell
            int x = randRow(rng);
            int y = randCol(rng);
            if (states[x][y].alive) continue;
            totalCnt--;
            states[x][y].swapLife();
            // Update neighbour
            updateNeighbours(x, y, states, true);
        }
    }

    void updateNeighbours(int x, int y, vector<vector<CellState>> &board, bool addNeighbour) const {
        for (int i = std::max(0, x - 1); i < std::min(rowCount, x + 2); ++i) {
            for (int j = std::max(0, y - 1); j < std::min(colCount, y + 2); ++j) {
                if (i == x && j == y) continue;

                if (addNeighbour) board[i][j].neighboursCount++;
                else board[i][j].neighboursCount--;
            }
        }
    }

public:
    GameOfLife(int rowCnt, int colCnt, float fillFactor = 0.2f) : rowCount(rowCnt), colCount(colCnt),
                                                                  states(rowCnt, vector<CellState>(colCnt)) {
        initBoard(fillFactor);
    }

    void updateBoard() {
        buffer = states;

        for (int i = 0; i < rowCount; ++i) {
            for (int j = 0; j < colCount; ++j) {
                if (states[i][j].alive && (states[i][j].neighboursCount < 2 || states[i][j].neighboursCount > 3)) {
                    buffer[i][j].swapLife();
                    updateNeighbours(i, j, buffer, false);
                    // live cell with 2, 3 neighboursCount lives to next gen
                } else if (!states[i][j].alive && states[i][j].neighboursCount == 3) {  // revive dead cell
                    buffer[i][j].swapLife();
                    updateNeighbours(i, j, buffer, true);
                }
            }
        }

        states = buffer;
    }

    void debugPrintBoard() const {
        std::cout << "Debugging board: \n";
        for (int i = 0; i < rowCount; ++i) {
            for (int j = 0; j < colCount; ++j) {
                std::cout << (states[i][j].alive ? "*" : "-") << " ";
            }
            std::cout << '\n';
        }
    }

    const vector<vector<CellState>> &getBoard() const {
        return states;
    }
};