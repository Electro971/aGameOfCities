#include "player.h"
#include <iostream>
using namespace std;

player::player()
{
    name = "None";
}
player::player(const string& playerName) : name(playerName), score(0), troops(0) {}

void player::increaseScore(int points) {
    score += points;
}

string player::getName() const {
    return name;
}

int player::getScore() const {
    return score;
}

void player::setTroops(int numTroops) {
    if (numTroops >= 0) {
        troops = numTroops;
    }
}

string player::getColor()
{
    return color;
}

void player::setColor(string input)
{
    color = input;
}

void player::playerSummary() const {
    cout << "Player: " << name << endl;
    cout << "Score: " << score << endl;
    cout << "Troops: " << troops << endl;
    cout << "Color: " << color << endl;
}
