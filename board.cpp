#include "board.h"
#include "player.h"
#include <iostream>
#include <random>
#include <osmanip/manipulators/colsty.hpp>
#include <algorithm>

using namespace std;
using namespace osm;

// Helper function to generate a three-letter ID from an integer
inline string generateId(int n) {
    string id(3, 'A');
    id[0] += (n / (26 * 26)) % 26;
    id[1] += (n / 26) % 26;
    id[2] += n % 26;
    return id;
}

board::board(void)
{
    //empty board;
}

board::board(int rows, int cols) : rows(rows), cols(cols), grid(rows, vector<territory>(cols)) {
    int id = 0;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            grid[r][c].setId(generateId(id++));
            grid[r][c].setName("T" + grid[r][c].getId());
        }
    }
}

void board::initializeGameState(vector<player>& playerList) {
    vector<pair<int, int>> positions;
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < cols; ++c)
            positions.emplace_back(r, c);

    random_device rd;
    mt19937 g(rd());
    shuffle(positions.begin(), positions.end(), g);

    int numPlayers = playerList.size();
    for (size_t i = 0; i < positions.size(); ++i) {
        int playerIndex = i % numPlayers;
        int r = positions[i].first;
        int c = positions[i].second;
        grid[r][c].setOwner(playerList[playerIndex]);
        int troops = rand() % 5 + 1;
        grid[r][c].setTroops(troops);
        grid[r][c].getOwner().setTroops(grid[r][c].getOwner().getTroops()+troops);
    }
}

void board::printBoard() const {
    const int cellWidth = 9;
    const int cellHeight = 3; // 1 for border, 1 for content, 1 for border

    for (int r = 0; r < rows; ++r) {
        // Print top border for each cell in the row
        for (int c = 0; c < cols; ++c) {
            cout << "+" << string(cellWidth - 2, '-') << "+ ";
        }
        cout << "\n";
        // Print content line for each cell in the row
        for (int c = 0; c < cols; ++c) {
            const territory& t = grid[r][c];
            cout << "|";
            cout << feat(col, t.getOwner().getColor());
            // Format: [ID] [Troops], padded to fit cell
            string content = t.getId() + " " + to_string(t.getTroops());
            int pad = cellWidth - 2 - content.length();
            int padLeft = pad / 2;
            int padRight = pad - padLeft;
            cout << string(padLeft, ' ') << content << string(padRight, ' ');
            cout << feat(rst, "all");
            cout << "| ";
        }
        cout << "\n";
        // Print bottom border for each cell in the row
        for (int c = 0; c < cols; ++c) {
            cout << "+" << string(cellWidth - 2, '-') << "+ ";
        }
        cout << "\n";
    }
}

void board::selectTerritory(int row, int col) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        cout << "Invalid territory selection." << endl;
        return;
    }
    grid[row][col].printTerritory();
}

void board::selectTerritoryById(const string& tid) {
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (grid[r][c].getId() == tid) {
                cout << "Selected Territory: ";
                grid[r][c].printTerritory();
                return;
            }
        }
    }
    cout << "No territory with ID: " << tid << endl;
}

void board::renameGrid(vector<string> newNames, vector<string> newIds) {
    if (newNames.size() != rows * cols || newIds.size() != rows * cols) {
        cout << "Error: New names or IDs size does not match the grid size." << endl;
        return;
    }
    int index = 0;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            grid[r][c].setName(newNames[index]);
            grid[r][c].setId(newIds[index]);
            index++;
        }
    }
}

int board::getRows() const { return rows; }
int board::getCols() const { return cols; }

vector<territory>& board::operator[](int row) {
    return grid[row];
}
const vector<territory>& board::operator[](int row) const {
    return grid[row];
}
