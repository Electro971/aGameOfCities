#include "territory.h"
#include "player.h"
#include <iostream>
#include <osmanip/manipulators/colsty.hpp>
using namespace std;
using namespace osm;

territory::territory() : id("AAA"), name("Unknown"), owner(nullptr) {}

territory::territory(const string& id, const string& name) : id(id), name(name), owner(nullptr) {}

territory::territory(const territory& other) : id(other.id), name(other.name), owner(other.owner) {}

territory& territory::operator=(const territory& other)
{
    if (this != &other)
    {
        id = other.id;
        name = other.name;
        owner = other.owner;
    }
    return *this;
}

void territory::printTerritory() const
{
    if (owner) cout << feat(col, owner->getColor());
    cout << "Territory ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Number of Troops: " << troops << endl;
    if (owner) {
        cout << "Owner: " << owner->getName() << endl;
        cout<<feat(rst, "all");
    } else {
        cout << "Owner: None" << endl;
    }
}

void territory::setId(const string& newId)
{
    id = newId;
}

void territory::setName(const string& newName)
{
    name = newName;
}

string territory::getId() const
{
    return id;
}

string territory::getName() const
{
    return name;
}

int territory::getTroops() const
{
    return troops;
}

player& territory::getOwner() const
{
    return *owner;
}

void territory::setOwner(player& newOwner)
{
    owner = &newOwner;
}

void territory::setTroops(int newTroops)
{
    if (newTroops >= 0)
    {
        troops = newTroops;
    }
    else
    {
        cout << "Number of troops cannot be negative." << endl;
    }
}

void territory::increaseTroops()
{
    troops++;
}
