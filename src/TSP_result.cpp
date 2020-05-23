#include "../lib/TSP_result.hpp"

namespace traveling_salesman
{
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

        ofstream outputFile;
        outputFile.open(OUTPUT_FILE_PATH(algorithmName), ios::out | ios::app);
        outputFile << inputSize << ", " << std::fixed << std::setprecision(7) << (timeTakenInMicroseconds / 1000000.0) << '\n';
        outputFile.close();
    }

}
