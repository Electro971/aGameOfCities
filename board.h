#pragma once
#include <vector>
#include <osmanip/manipulators/colsty.hpp>
#include "territory.h"
#include "player.h"
#include <utility>
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
    bool selectTerritory(int row, int col);
    bool selectTerritoryById(const string& tid);
    void renameGrid(vector<string> newNames, vector<string> newIds);
    int getRows() const;
    int getCols() const;
    vector<territory>& operator[](int row);
    const vector<territory>& operator[](int row) const;
    bool doesBorder(string one, string two);
    territory* getTerritoryById(const string& id);

private:
    int rows, cols;
    vector<vector<territory>> grid;
    vector<vector<bool>> adjacencyMatrix;
};