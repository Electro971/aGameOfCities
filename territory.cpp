#include "territory.h"
#include <iostream>
using namespace std;

territory::territory() : id("AAA"), name("Unknown") {}

territory::territory(const string& id, const string& name) : id(id), name(name) {}

territory::territory(const territory& other) : id(other.id), name(other.name) {}

territory& territory::operator=(const territory& other)
{
    if (this != &other)
    {
        id = other.id;
        name = other.name;
    }
    return *this;
}

void territory::printTerritory() const
{
    cout << "Territory ID: " << id << ", Name: " << name << endl;
    cout << "Number of Troops: " << troops << endl;
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

string territory::getOwner() const
{
    return owner;
}

void territory::setOwner(const string& newOwner)
{
    owner = newOwner;
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
