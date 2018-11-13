#include <iostream>
#include <vector>
//#include <cstdlib>
#include <random>
#include <time.h>

struct Car{
    int position;
};

int main() {
    // Experiment parameters
    std::srand(time(NULL));
    const int maxCellsPerStep = 5;
    const int nrLanes = 1;
    const double nrCarsRel = 0.1;
    const int nrCells = 300;
    const double cellLength = 7.5;
    const double timeStepSec = 1;
    const int timeSteps = 100;
    int cells[nrCells*timeSteps];

    std::cout << "Max velocity: " << maxCellsPerStep * cellLength / timeStepSec * 3.6 << ".\n";

    for (int i = 0; i < nrCells; i++){
        if ((std::rand()*1.0f)/RAND_MAX <= nrCarsRel){
            cells[i] = (std::rand() % (maxCellsPerStep + 1));
        }else {
            cells[i] = -1;
        }
    }
    for (int i = 1; i < timeSteps; i++){
        for (int cellIndex = (i-1)*nrCells; cellIndex < i*nrCells; cellIndex++){
            if (cells[cellIndex] >= 0){
                // Accelerate
                for (int j = 1; j <= maxCellsPerStep; j++)
                int newVel;
            }
        }
    }
}