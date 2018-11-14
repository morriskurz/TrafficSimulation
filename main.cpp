#include <iostream>
#include <vector>
//#include <cstdlib>
#include <random>
#include <time.h>
#include <cmath>
#include <chrono>
#include <fstream>

struct Car{
    int position;
};

int main() {
    // Experiment parameters
    std::srand(time(NULL));
    const int maxCellsPerStep = 5;
    const int nrLanes = 1;
    const double nrCarsRel = 0.16;
    const int nrCells = 300;
    const double cellLength = 7.5;
    const double timeStepSec = 1;
    const int timeSteps = 150;
    const double dallyFactor = 0.2;
    std::ofstream outputFile;
    outputFile.open("traffic.txt");
    int cells[nrCells*timeSteps];
    for (int i = 0; i < nrCells*timeSteps; i++){
        cells[i] = -1;
    }

    std::cout << "Max velocity: " << maxCellsPerStep * cellLength / timeStepSec * 3.6 << ".\n";
    int count = 0;
    for (int i = 0; i < nrCells; i++){
        if ((std::rand()*1.0)/RAND_MAX <= nrCarsRel){
            count += 1;
            cells[i] = (std::rand() % (maxCellsPerStep + 1));
        }
        outputFile << cells[i] << " ";
    }
    std::cout << "Initialized with " << count << " cars.\n";
    for (int i = 1; i < timeSteps-1; i++){
        outputFile << "\n";
        for (int cellIndex = 0; cellIndex < nrCells; cellIndex++){
            int currentVel = cells[(i-1)*nrCells + cellIndex];
            if (currentVel >= 0){
                // Accelerate
                int distance = maxCellsPerStep;
                for (int j = 1; j <= currentVel+1; j++){
                    if (cells[(i-1)*nrCells + (cellIndex+j) % nrCells] >= 0){
                        distance = j-1;
                        break;
                    }
                }
                int newVel = std::min(currentVel + 1, maxCellsPerStep);
                // Decelerate
                newVel = std::min(newVel, distance);
                // Randomize
                if ((std::rand()*1.0)/RAND_MAX <= dallyFactor){
                    newVel = std::max(newVel - 1, 0);
                }
                // Move
                cells[i*nrCells + ((cellIndex + newVel) % nrCells)] = newVel;
            }
            outputFile << cells[(i-1)*nrCells + cellIndex] << " ";
        }
    }
}