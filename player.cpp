#include "player.h"
#include <iostream>
#include <osmanip/manipulators/colsty.hpp>
using namespace std;

player::player()
{
    name = "None";
}
player::player(const string& playerName) : name(playerName), troops(0) {}

string player::getName() const {
    return name;
}

int player::getTroops()
{
    return troops;
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
    cout<<osm::feat(osm::col, color);
    cout << "Player: " << name << endl;
    cout << "Troops: " << troops << endl;
    cout<<osm::feat(osm::rst, "all");
}
