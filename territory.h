#pragma once
#include <string>
#include "player.h"
#include <iostream>
using namespace std;

class territory
{
    public:
        territory();
        territory(const string& id, const string& name);
        territory(const territory& other);
        territory& operator=(const territory& other);

        void printTerritory() const;
        void setId(const string& newId);
        void setName(const string& newName);
        string getId() const;
        string getName() const;
        int getTroops() const;
        player& getOwner() const;
        void setOwner(player& newOwner);
        void setTroops(int newTroops);
        void increaseTroops();

    private:
        string id;
        string name;
        player* owner = nullptr;
        int troops = 0;
};