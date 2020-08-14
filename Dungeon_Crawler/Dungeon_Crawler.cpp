// Dungeon_Crawler.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
using namespace std;
#include <iostream>
#include <string>
#include <fstream>
#include <vector>


bool gameover = false;
int pPos[2];
char map[10][30];
char oldState;

//Player Details
int goals = 3;
int moves = 0;

//Monster Details

void readFile(string filename) {
    //Open File
    vector<string> inputLines;
    ifstream myfile(filename);
    std::string line;  
    if (myfile.is_open())
    {
        //Add To array
        while (getline(myfile, line))
        {
            inputLines.push_back(line);
        }
        myfile.close();
        for (int i = 0; i < inputLines.size(); i++)
        {
            for (int j = 0; j < inputLines[i].size(); j++)
            {
                if (inputLines[i][j] == 'S')
                {
                    pPos[0] = i;
                    pPos[1] = j;
                }
                map[i][j] = inputLines[i][j];
            }
        }
    }
    else cout << "Unable to open map file, is it in the right place?";
}
void renderGame() {
    //Render Map to Scene
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 31; ++j)
        {
            cout << map[i][j];
        }
        cout << endl;
    }
}
void updateMap(int oldPos[2], int newPos[2]) {
    //replace old pos with a '.'
    if (pPos[0] == 5 && pPos[1] == 17)
    {
        map[oldPos[0]][oldPos[1]] = 'E';
        // 17 5
    }
    else {
        map[oldPos[0]][oldPos[1]] = '.';
    }
    
    //set new place to 'S'
    map[newPos[0]][newPos[1]] = 'S';
    //Update Position
    pPos[0] = newPos[0];
    pPos[1] = newPos[1];
}
void checkPosition(int newPos[2]) {
    //Check new Positions and Move if ok
    if (map[newPos[0]][newPos[1]] != '#')
    {
        //Add onto Moves
        moves++;
        //Set teh old state of the tile being moved too.
        oldState = map[newPos[0]][newPos[1]];
        //If tile is a G or E state
        switch (map[newPos[0]][newPos[1]])
        {
        case'G':
            goals--;
            break;
        case'E':
            if (goals == 0)
            {
                gameover = true;
            }
            break;
        }
        //Update the map and render
        updateMap(pPos, newPos);
    }
}

void movePlayer(char key) {
    int newPos[2];
    switch (key) {
    case 'w':
        //Move Up
        newPos[0] = pPos[0] - 1;
        newPos[1] = pPos[1];
        checkPosition(newPos);
        break;
    case 'a':
        //Move Left
        //check new pos != wall
        newPos[0] = pPos[0];
        newPos[1] = pPos[1]-1;
        checkPosition(newPos);
        break;
    case 'd':
        //Move Right
        //check new pos != wall
        newPos[0] = pPos[0];
        newPos[1] = pPos[1] + 1;
        checkPosition(newPos);
        break;
    case 's':
        //Move Down
        //check new pos != wall
        newPos[0] = pPos[0] + 1;
        newPos[1] = pPos[1];
        checkPosition(newPos);
        break;
    default:
        //Wrong Key Pressed
        cout << "Error, Please Enter A Valid Key" << endl;
    }
}
void gameTick(char map[10][30]) {
    char key;     
    cout << "Number of Goals: " << goals <<endl;
    cout << "Make a move:";
    cin >> key;
    movePlayer(key);
}

void omain()
{
    //Open and Read FIle
    char map[10][30];
    readFile("map.txt");
    //Start Game Tick
    while (!gameover) {
        system("cls");
        renderGame();
        gameTick(map);
    }
    system("cls");
    renderGame();
    cout << "Game Over!" << endl;
    cout << "SCORE: " << moves;
    //End Game
}
