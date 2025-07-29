#include "board.h"
#include "player.h"
#include <iostream>
#include <random>
#include <osmanip/manipulators/colsty.hpp>
#include <algorithm>

using namespace std;
using namespace osm;

// Helper function to generate a three-letter ID from an integer
inline string generateId(int n)
{
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
    // Build adjacency matrix
    int n = rows * cols;
    adjacencyMatrix = vector<vector<bool>>(n, vector<bool>(n, false));
    const int dr[] = {-1, 1, 0, 0};
    const int dc[] = {0, 0, -1, 1};
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            int idx = r * cols + c;
            for (int d = 0; d < 4; ++d) {
                int nr = r + dr[d];
                int nc = c + dc[d];
                if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
                    int nidx = nr * cols + nc;
                    adjacencyMatrix[idx][nidx] = true;
                }
            }
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
    for (int r = 0; r < rows; ++r) {
        // Content line for each cell
        for (int c = 0; c < cols; ++c) {
            const territory& t = grid[r][c];
            // No left border
            cout << feat(col, t.getOwner().getColor());
            string content = t.getId() + " " + to_string(t.getTroops());
            int pad = cellWidth - content.length();
            int padLeft = pad / 2;
            int padRight = pad - padLeft;
            cout << string(padLeft, ' ') << content << string(padRight, ' ');
            cout << feat(rst, "all");
            // Horizontal connection to the right (centered between cells)
            if (c < cols - 1) {
                int idx = r * cols + c;
                int rightIdx = r * cols + (c + 1);
                if (adjacencyMatrix[idx][rightIdx]) {
                    cout << '-';
                } else {
                    cout << ' ';
                }
            }
        }
        cout << "\n";
        // Vertical connections to the row below
        if (r < rows - 1) {
            for (int c = 0; c < cols; ++c) {
                int idx = r * cols + c;
                int belowIdx = (r + 1) * cols + c;
                if (adjacencyMatrix[idx][belowIdx]) {
                    cout << string((cellWidth) / 2, ' ') << "|" << string(cellWidth - (cellWidth) / 2 - 1, ' ');
                } else {
                    cout << string(cellWidth, ' ');
                }
                // Space between cells
                if (c < cols - 1) {
                    cout << " ";
                }
            }
            cout<<endl;
        }
    }
    cout<<endl;
}

bool board::selectTerritory(int row, int col) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        cout << "Invalid territory selection." << endl;
        return false;
    }
    grid[row][col].printTerritory();
    return true;
}

bool board::selectTerritoryById(const string& tid) {
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (grid[r][c].getId() == tid) {
                cout << "Selected Territory: ";
                grid[r][c].printTerritory();
                return true;
            }
        }
    }
    cout << "No territory with ID: " << tid << endl;
    return false;
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

bool board::doesBorder(string one, string two) {
    int idxOne = -1, idxTwo = -1;
    // Find indices for the given IDs
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (grid[r][c].getId() == one) idxOne = r * cols + c;
            if (grid[r][c].getId() == two) idxTwo = r * cols + c;
        }
    }
    if (idxOne == -1 || idxTwo == -1) return false;
    return adjacencyMatrix[idxOne][idxTwo];
}

territory* board::getTerritoryById(const string& id) {
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (grid[r][c].getId() == id) {
                return &grid[r][c];
            }
        }
    }
    return nullptr;
}
vector<territory>& board::operator[](int row) {
    return grid[row];
}
const vector<territory>& board::operator[](int row) const {
    return grid[row];
}