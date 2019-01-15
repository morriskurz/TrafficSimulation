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
    const int timeSteps = 600;
    const double dallyFactor = 0.2;
    const int amountOfSimulationRuns = 10000;
    std::ofstream outputFile;
    outputFile.open("traffic.txt");
    int cells[nrCells*(timeSteps+1)];

    int k = 8;
    int checkpoint = std::max((int) (std::rand() % nrCells), k);
    int carsCounted = 0;

    for (int i = 0; i < nrCells*timeSteps; i++){
        cells[i] = -1;
    }

    std::cout << "Checkpoint at: " << checkpoint << "\n";
    std::cout << "Max velocity: " << maxCellsPerStep * cellLength / timeStepSec * 3.6 << ".\n";
    int count = 0;
    for (int i = 0; i < nrCells; i++){
        if ((std::rand()*1.0)/RAND_MAX <= nrCarsRel){
            count += 1;
            cells[i] = (std::rand() % (maxCellsPerStep + 1));
        }
    }


    std::cout << "Initialized with " << count << " cars.\n";
    for (int i = 1; i <= timeSteps; i++){
        //  outputFile << "\n";
        for (int cellIndex = 0; cellIndex < nrCells; cellIndex++){
            int currentVel = cells[(i-1)*nrCells + cellIndex];
            if (currentVel >= 0){
                // Accelerate
                int distance = maxCellsPerStep;
                for (int j = 1; j <= currentVel+1; j++){
                    //std::cout << "Cell " << (i-1)*nrCells + cellIndex << ", inspecting " << (i-1)*nrCells + ((cellIndex+j) % nrCells) << "\n";
                    if (cells[(i-1)*nrCells + ((cellIndex+j) % nrCells)] >= 0){
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
                int newPos = ((cellIndex + newVel) % nrCells);
                cells[i*nrCells + newPos] = newVel;
                if (newPos > checkpoint and cellIndex < checkpoint){
                    std::cout << "At time step " << i << ", a car passed through the checkpoint.\n";
                    carsCounted++;
                }
            }
            outputFile << cells[(i-1)*nrCells + cellIndex] << " ";
        }
        outputFile << "\n";
    }
    std::cout << "Cars counted: " << carsCounted << ", flow: " << carsCounted/(timeSteps*1.0)*3600 << " cars per hour.";
    std::cout << "\nAverage Density: " << count/(cellLength*nrCells)*1000.0 << " cars per km.";
}