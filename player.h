#pragma once
#include <string>
#include <vector>
using namespace std;

class player
{
    public:
        // Constructor to initialize player with a name
        player();
        player(const string& playerName);

        // Function to get the player's name
        string getName() const;

        // Function to set the number of troops for the player
        void setTroops(int numTroops);
        int getTroops();

        void playerSummary() const;

        string getColor();

        void setColor(string);

        bool operator==(const player& other) const;
        bool operator!=(const player& other) const;

    private:
        string name; // Player's name
        int troops; // Number of troops the player has
        string color = "white";
};