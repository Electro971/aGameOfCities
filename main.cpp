#include <iostream>
#include <string>
#include <limits>
#include <osmanip/manipulators/colsty.hpp>
#include "territory.h"
#include "board.h"
#include "player.h"
using namespace std;
using namespace osm;

void mainMenu();
void setupMap();
void createMap(string);
void printControls();
void selectPlayers();
static board playBoard;
static vector<player> playList;

void mainMenu()
{
    bool m, p, e = false;
    char input = '\0';
    while (e == false)
    {
        cout<<"What would you like to do?"<<endl;
        cout<<"1 - Setup "<<feat(sty, "underlined")<<"m"<<feat(rst, "all")<<"ap"<<endl;
        cout<<"2 - Setup "<<feat(sty, "underlined")<<"p"<<feat(rst, "all")<<"layers"<<endl;
        cout<<"3 - "<<feat(sty, "underlined")<<"N"<<feat(rst, "all")<<"ew game"<<endl;
        cout<<"4 - "<<feat(sty, "underlined")<<"L"<<feat(rst, "all")<<"oad game"<<endl;
        cout<<"5 - "<<feat(sty, "underlined")<<"S"<<feat(rst, "all")<<"tart game"<<endl;
        cout<<"Enter a command: ";
        cin>>input;
        switch(input)
        {
            case '1': case 'm':
                setupMap();
                m = true;
                break;
            case '2': case 'p':
                selectPlayers();
                p = true;
                break;
            case '3': case 'n':
                setupMap();    
                selectPlayers();
                m, p, e = true;
                break;
            case '4': case 'l':
                cout<<"Loading is not supported at this time, sorry."<<endl;
                //m = true;
                //p = true;
                break;
            case '5': case 's':
                if (m && p) 
                {
                    e = true;
                    break;
                }
                else
                {
                    cout<<"Please set up a board and players first."<<endl;
                    input = '\0';
                }
                break;
            default:
                cout<<"Command not recognized. Please try again."<<endl;
                input = '\0';
        }
    }
}

void setupMap()
{
    //clear cin
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    vector<string> maps = {"Basic Map", "World Map", "Europe Map", "Asia Map", "Africa Map", "North America Map", "South America Map"};
    
    cout<<feat(col, "red");
    cout<<endl<<"Welcome to Map setup!"<<endl;
    cout<<feat(rst, "all");
    
    cout << "Please select a map from the following list: " << endl;
    int counter = 0;
    for (string i : maps)
    {
        counter++;
        cout << counter << ". " << i << endl;
    }
    string mapChoice;
    cout<<"Enter your choice: ";
    getline(cin, mapChoice);
    try
    {
        {
            int mc = stoi(mapChoice);
            createMap(maps[mc-1]);
            return;
        }
    }
    catch(...)
    {
    
    }
    
    createMap(mapChoice);
}

void createMap(string mapName)
{
    if (mapName == "Basic Map")
    {
        cout << "Begninning construction of Basic Map."<<endl;
        board b(3, 3);
        b[0][0].setName("Alpha");
        b[0][0].setId("APH");
        b[0][1].setName("Bravo");
        b[0][1].setId("BVO");
        b[0][2].setName("Charlie");
        b[0][2].setId("CHL");
        b[1][0].setName("Delta");
        b[1][0].setId("DTA");
        b[1][1].setName("Echo");
        b[1][1].setId("ECO");
        b[1][2].setName("Foxtrot");
        b[1][2].setId("FXT");
        b[2][0].setName("Golf");
        b[2][0].setId("GLF");
        b[2][1].setName("Hotel");
        b[2][1].setId("HTL");
        b[2][2].setName("India");
        b[2][2].setId("IND");
        playBoard = b;
    }
    else if (mapName == "World Map")
    {
        cout << "Creating a World Map with 5 rows and 5 columns." << endl;
        board b(5, 5);
        playBoard = b;
    }
    else if (mapName == "Europe Map")
    {
        cout << "Creating a Europe Map with 4 rows and 4 columns." << endl;
        board b(4, 4);
        playBoard = b;
    }
    else
    {
        cout << "Map not recognized. Defaulting to Basic Map." << endl;
        board b(3, 3);
        playBoard = b;
    }

    cout<<"Map successfully created."<<endl;
}

void printControls()
{
    cout << "Controls:" << endl;
    cout << "1. Type 's' or 'S' to select a territory." << endl;
    cout << "2. Type 'b' or 'B' to print the board." << endl;
    cout << "3. Type 'p' or 'P' to view player statistics." << endl;
    cout << "4. Type 'q' or 'Q' to quit the game." << endl;
    cout << "5. Type 'h' or 'H' to print this help message." << endl;
    cout << "6. Type 'exit' or 'quit' to exit the program." << endl;
    cout << endl;
}

void selectPlayers()
{
    int numPlayers;
    
    cout<<feat(col, "red");
    cout<<endl<<"Welcome to Player setup!"<<endl;
    cout<<feat(rst, "all");
    cout << "Enter the number of players (2-4): ";
    while (true)
    {
        cin >> numPlayers;
        if (cin.fail() || numPlayers < 2 || numPlayers > 4)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 2 and 4: ";
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }
    cout<<"You have selected "<<numPlayers<<" players."<<endl<<endl;
    vector<player> playerList;
    for (int i = 0; i < numPlayers; ++i)
    {
        string playerName;
        cout <<"Enter the name for Player " << (i + 1) << ": ";
        getline(cin, playerName);
        player p(playerName);
        //chose color eventually
        //for now, p1 = red, p2 = blue, p3 = yellow, all other = green
        switch ((i+1)%4)
        {
            case 1:
                p.setColor("red");
                break;
            case 2:
                p.setColor("blue");
                break;
            case 3:
                p.setColor("yellow");
                break;
            default:
                p.setColor("green");
                break;
        }
        playerList.push_back(p);
    }
    playList = playerList;
    playBoard.initializeGameState(playList);
}

int main()
{
    cout<<feat(col, "red")<<"Welcome to the Territory Board Game!"<< osm::feat(osm::rst, "color")<<endl;
    mainMenu();
    printControls();
    playBoard.printBoard();
    while (true)
    {
        string input;
        cout << "Enter a command: ";
        cin>>input;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (input == "exit" || input == "quit") {
            break;
        }
        char cmd = input.empty() ? '\0' : tolower(input[0]);
        switch (cmd) {
            case 'q':
                return 0;
            case 's': case 'S':
            {    
            cout << "Enter the three-letter territory ID to select (e.g., APH): ";
                string tid="";
                getline(cin, tid);
                playBoard.selectTerritoryById(tid);
                break;
            }
            case 'p':
            {
                cout << "Select a player:" << endl;
                for (int i = 0; i < playList.size(); ++i)
                {
                    cout << "Player " << i + 1 << "  - " << playList[i].getName() << endl;
                }
                cout << "Enter player number: ";
                int playerIndex;
                cin >> playerIndex;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (playerIndex < 1 || playerIndex > playList.size()) {
                    cout << "Invalid player number." << endl;
                } else {
                    //b.updatePlayers(playerList);
                    playList[playerIndex - 1].playerSummary();
                }
                break;
            }
            case 'a': case 'A':
            {
                cout<<"From: ";
                string start= "";
                cin>>start;
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout<<"To: ";
                string end = "";
                cin>>end;
                cin.ignore(999,'\n');
                if (playBoard.doesBorder(start,end));
                else
                    cout<<"Invalid selection.\nTiles do not border."<<endl;
                if (playBoard.getTerritoryById(start)->getOwner() != playBoard.getTerritoryById(end)->getOwner())
                {
                    cout<<"Attacking tile "<<start<<" from tile "<<end<<endl;
                }
                else
                    cout<<"Invalid selection.\nTiles share an owner."<<endl;
                break;
            }
            case 'h' : case 'H':
                printControls();
                break;
            default:
                playBoard.printBoard();
                break;
            
        }
    }
    return 0;
}