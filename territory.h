#pragma once
#include <string>
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
        string getOwner() const;
        void setOwner(const string& newOwner);
        void setTroops(int newTroops);
        void increaseTroops();

    private:
        string id;
        string name;
        string owner = "None";
        int troops = 0;
};