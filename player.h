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

        // Function to increase the player's score
        void increaseScore(int points);

        // Function to get the player's name
        string getName() const;

        // Function to get the player's score
        int getScore() const;

        // Function to set the number of troops for the player
        void setTroops(int numTroops);

        void playerSummary() const;

        string getColor();

        void setColor(string);

    private:
        string name; // Player's name
        int score; // Player's score
        int troops; // Number of troops the player has
        string color = "white";
};