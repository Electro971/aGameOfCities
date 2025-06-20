#pragma once
#include <vector>
#include <osmanip/manipulators/colsty.hpp>
#include "territory.h"
#include "player.h"
using namespace std;
using namespace osm;

// Helper function to generate a three-letter ID from an integer
inline string generateId(int);

class board {
public:
    board();
    board(int rows, int cols);
    void initializeGameState(vector<player>& playerList);
    void printBoard() const;
    void selectTerritory(int row, int col);
    void selectTerritoryById(const string& tid);
    void renameGrid(vector<string> newNames, vector<string> newIds);
    int getRows() const;
    int getCols() const;
    vector<territory>& operator[](int row);
    const vector<territory>& operator[](int row) const;

private:
    int rows, cols;
    vector<vector<territory>> grid;
};