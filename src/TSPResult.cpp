#include "../lib/TSPResult.hpp"

using namespace std;
using TSPResult = TravelingSalesman::TSPResult;

TSPResult::TSPResult(int inputSize, double minDist, int *minPath, long long timeTakenInMicroseconds)
{
    this->inputSize = inputSize;
    this->minDist = minDist;
    this->minPath = minPath;
    this->timeTakenInMicroseconds = timeTakenInMicroseconds;
}

void TSPResult::showResult(string algorithmName)
{
    cout << algorithmName << "\n";
    cout << "Input size: " << inputSize << "\n";
    cout << "Min dist: " << minDist << "\n";
    cout << "Min path: ";
    for (int i = 0; i < inputSize; i++)
        cout << minPath[i] << " ";

    if (timeTakenInMicroseconds < 1000)
        cout << "\nTime taken: " << timeTakenInMicroseconds << " microseconds\n\n";
    else
    {
        if (timeTakenInMicroseconds > 1000000)
        {
            if (timeTakenInMicroseconds > 60000000)
                cout << "\nTime taken: " << std::fixed << std::setprecision(4) << (timeTakenInMicroseconds / 60000000.0) << " minutes\n\n";
            else
                cout << "\nTime taken: " << std::fixed << std::setprecision(4) << (timeTakenInMicroseconds / 1000000.0) << " seconds\n\n";
        }
        else
            cout << "\nTime taken: " << std::fixed << std::setprecision(4) << (timeTakenInMicroseconds / 1000.0) << " miliseconds\n\n";
    }
}
