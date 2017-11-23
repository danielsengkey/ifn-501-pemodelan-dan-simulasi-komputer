#include <iostream>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <vector>
#include <map>
#include <string>

/*
    Any live cell with fewer than two live neighbours dies, as if caused by underpopulation.
    Any live cell with two or three live neighbours lives on to the next generation.
    Any live cell with more than three live neighbours dies, as if by overpopulation.
    Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

*/
enum cellState{
        DEAD = 0,
        LIVE = 1
    };

int randomSeed = std::time(0);
int matrixDimension = 35;
std::vector < std::vector <cellState> > cellMatrix(matrixDimension, std::vector<cellState>(matrixDimension,DEAD));
std::vector < std::vector <cellState> > tempMatrix(matrixDimension, std::vector<cellState>(matrixDimension,DEAD));

cellState getRandomState(){
    srand(randomSeed);
    cellState randomval = static_cast<cellState>(rand() % 2);
    randomSeed++;
    return randomval;
}

void initializeMatrix(){
    for (int i=0; i<matrixDimension; i++)
    {
        for (int j=0; j<matrixDimension; j++)
        {
            cellMatrix[i][j] = getRandomState();
        }
    }
}

void printMatrix(){
    std::string stateMask;

    for (int i=0; i<matrixDimension; i++)
    {
        for (int j=0; j<matrixDimension; j++)
        {
            if(cellMatrix[i][j] == LIVE) stateMask = "▣";
            else stateMask = "▢";
            //std::cout << cellMatrix[i][j];
            std::cout << stateMask << " ";
        }
        std::cout << std::endl;
    }
}

int countLiveNeighbours(std::map<std::string, cellState> neighbourStates){
    int liveCounter = 0;

    for(auto it: neighbourStates){
        if(it.second == LIVE) liveCounter++;
    }

    return liveCounter;
}
cellState newState(cellState currentState, int numLiveNeighbours){
    cellState ns = currentState;
    if((currentState==DEAD)&& (numLiveNeighbours==3)) {
            ns = LIVE;
    }
    else {
        // Cell lives
        if(numLiveNeighbours<2) { ns = DEAD; }
        else if((numLiveNeighbours==2)||(numLiveNeighbours==3)) { ns = LIVE; }
        else if(numLiveNeighbours>=3) { ns = DEAD; }
        else {std::cout << "Uncovered condition. Cell state = " << currentState << std::endl;}
    }
    return ns;
}

std::map<std::string, cellState> getNeighbours(int row, int col){
    std::map<std::string, cellState> neighbourStates;
    if((row>0)&&(col>0)&&(row<matrixDimension-1)&&(col<matrixDimension-1)){
    /* Cell(s) in the middle */
        neighbourStates["northwest"] = cellMatrix[row-1][col-1];
        neighbourStates["north"] = cellMatrix[row-1][col];
        neighbourStates["northeast"] = cellMatrix[row-1][col+1];
        neighbourStates["east"] = cellMatrix[row][col+1];
        neighbourStates["southeast"] = cellMatrix[row+1][col+1];
        neighbourStates["south"] = cellMatrix[row+1][col];
        neighbourStates["southwest"] = cellMatrix[row+1][col-1];
        neighbourStates["west"] = cellMatrix[row][col-1];
    }
    else if((row==0)&&(col==0)){
        /* The first cell */
        neighbourStates["east"] = cellMatrix[row][col+1];
        neighbourStates["southeast"] = cellMatrix[row+1][col+1];
        neighbourStates["south"] = cellMatrix[row+1][col];
    }
    else if((row==matrixDimension-1)&&(col==0)){
        /* The cell at the bottom-left*/
        neighbourStates["north"] = cellMatrix[row-1][col];
        neighbourStates["northeast"] = cellMatrix[row-1][col+1];
        neighbourStates["east"] = cellMatrix[row][col+1];
    }
    else if((row==matrixDimension-1)&&(col==matrixDimension-1)){
        /* The cell at the bottom-right a.k.a the last cell*/
        neighbourStates["north"] = cellMatrix[row-1][col];
        neighbourStates["west"] = cellMatrix[row][col-1];
        neighbourStates["northwest"] = cellMatrix[row-1][col-1];
    }
    else if((row==0)&&(col==matrixDimension-1)){
        /* The cell at the top-right*/
        neighbourStates["south"] = cellMatrix[row+1][col];
        neighbourStates["southwest"] = cellMatrix[row+1][col-1];
        neighbourStates["west"] = cellMatrix[row][col-1];
    }
    else if((row!=0)&&(col==0)){
        /* The cell at the first column but not in the first row*/
        neighbourStates["north"] = cellMatrix[row-1][col];
        neighbourStates["northeast"] = cellMatrix[row-1][col+1];
        neighbourStates["east"] = cellMatrix[row][col+1];
        neighbourStates["southeast"] = cellMatrix[row+1][col+1];
        neighbourStates["south"] = cellMatrix[row+1][col];
    }
    else if((row!=matrixDimension-1)&&(col==matrixDimension-1)){
        /* The cell at the last column but not in the last row*/
        neighbourStates["northwest"] = cellMatrix[row-1][col-1];
        neighbourStates["north"] = cellMatrix[row-1][col];
        neighbourStates["south"] = cellMatrix[row+1][col];
        neighbourStates["southwest"] = cellMatrix[row+1][col-1];
        neighbourStates["west"] = cellMatrix[row][col-1];
    }
    else if((row==0)&&(col!=0)){
        /* The cell at the first row but not the first column*/
        neighbourStates["south"] = cellMatrix[row+1][col];
        neighbourStates["southwest"] = cellMatrix[row+1][col-1];
        neighbourStates["west"] = cellMatrix[row][col-1];
        neighbourStates["east"] = cellMatrix[row][col+1];
        neighbourStates["southeast"] = cellMatrix[row+1][col+1];
    }
    else if((row==matrixDimension-1)&&(col!=matrixDimension-1)){
        /* The cell at the last row but not the last column*/
        neighbourStates["north"] = cellMatrix[row-1][col];
        neighbourStates["west"] = cellMatrix[row][col-1];
        neighbourStates["northwest"] = cellMatrix[row-1][col-1];
        neighbourStates["northeast"] = cellMatrix[row-1][col+1];
        neighbourStates["east"] = cellMatrix[row][col+1];
    }
    else std::cout << "Error while listing neighbours! Exiting..." << std::endl;
    return neighbourStates;
}

void Sleep(float s){
    int sec = int(s*1000000);
    usleep(sec);
}

void playGame(){
    for (int i=0; i<matrixDimension; i++)
    {
        for (int j=0; j<matrixDimension; j++)
        {
            tempMatrix[i][j] = newState(cellMatrix[i][j], countLiveNeighbours(getNeighbours(i,j)));
        }
    }
    cellMatrix = tempMatrix;
}

int main()
{
    int repetition = 100;
    initializeMatrix();
    std::map<std::string, cellState> dbg_neighbours;

    for(int i=0; i<repetition; i++) {
            system("clear");
            std::cout << "Repetition: " << i+1 << std::endl;
            printMatrix();
            if(i==0) std::cin.ignore();
            Sleep(0.5);
            playGame();
            //std::cin.ignore();
    }
//printMatrix();
    /*
    dbg_neighbours = getNeighbours(2,2);
    std::cout << std::endl << "Neighbours of [2,2]: (" << cellMatrix[2][2] <<")" << std::endl;
    for(auto it = dbg_neighbours.cbegin(); it != dbg_neighbours.cend(); ++it){
        std::cout << it->first << " " << it->second << std::endl;//.first << " " << it->second.second << std::endl;
    }

    dbg_neighbours = getNeighbours(0,0);
    std::cout << std::endl << "Neighbours of [0,0]: (" << cellMatrix[0][0] <<")" << std::endl;
    for(auto it = dbg_neighbours.cbegin(); it != dbg_neighbours.cend(); ++it){
        std::cout << it->first << " " << it->second << std::endl;//.first << " " << it->second.second << std::endl;
    }

    dbg_neighbours = getNeighbours(matrixDimension-1,0);
    std::cout << std::endl << "Neighbours of [" << matrixDimension-1 << ",0]: (" << cellMatrix[matrixDimension-1][0] <<")" << std::endl;
    for(auto it = dbg_neighbours.cbegin(); it != dbg_neighbours.cend(); ++it){
        std::cout << it->first << " " << it->second << std::endl;//.first << " " << it->second.second << std::endl;
    }

    dbg_neighbours = getNeighbours(matrixDimension-1,matrixDimension-1);
    std::cout << std::endl << "Neighbours of [" << matrixDimension-1 << "," <<  matrixDimension-1 << "]: (" << cellMatrix[matrixDimension-1][matrixDimension-1] <<")" << std::endl;
    for(auto it = dbg_neighbours.cbegin(); it != dbg_neighbours.cend(); ++it){
        std::cout << it->first << " " << it->second << std::endl;//.first << " " << it->second.second << std::endl;
    }

    dbg_neighbours = getNeighbours(0,matrixDimension-1);
    std::cout << std::endl << "Neighbours of [" << 0 << "," <<  matrixDimension-1 << "]: (" << cellMatrix[0][matrixDimension-1] <<")" << std::endl;
    for(auto it = dbg_neighbours.cbegin(); it != dbg_neighbours.cend(); ++it){
        std::cout << it->first << " " << it->second << std::endl;//.first << " " << it->second.second << std::endl;
    }

    dbg_neighbours = getNeighbours(2,0);
    std::cout << std::endl << "Neighbours of [" << 2 << "," <<  0 << "]: (" << cellMatrix[2][0] <<")" << std::endl;
    for(auto it = dbg_neighbours.cbegin(); it != dbg_neighbours.cend(); ++it){
        std::cout << it->first << " " << it->second << std::endl;//.first << " " << it->second.second << std::endl;
    }

    for (int i=0; i<matrixDimension; i++)
    {
        for (int j=0; j<matrixDimension; j++)
        {
            dbg_neighbours = getNeighbours(i,j);
            std::cout << "Number of live neighbours of [" << i << "," <<  j << "]:" << countLiveNeighbours(dbg_neighbours) << " Next state: " << newState(cellMatrix[i][j], countLiveNeighbours(getNeighbours(i,j))) << std::endl;
        }
    }
    */
    return 0;
}
