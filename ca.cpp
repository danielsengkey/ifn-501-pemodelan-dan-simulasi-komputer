#include <iostream>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <vector>

int randomSeed = std::time(0);
int matrixDimension = 20;
std::vector < std::vector <int> > cellMatrix(matrixDimension, std::vector<int>(matrixDimension,0));
std::vector < std::vector <int> > tempMatrix(matrixDimension, std::vector<int>(matrixDimension,0));

enum cellState{
        DEAD = 0,
        LIVE = 1
    };

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
    system("clear");
    for (int i=0; i<matrixDimension; i++)
    {
        for (int j=0; j<matrixDimension; j++)
        {
            std::cout << cellMatrix[i][j];
        }
        std::cout << std::endl;
    }
}

void changeState(){

}

std::vector<int> getNeighbours(int row, int col){
    std::vector<int> neighbourStates;

    return neighbourStates;
}

int main()
{
    initializeMatrix();
    printMatrix();
    return 0;
}
