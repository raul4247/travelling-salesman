#include "../lib/TSPAlgorithms.hpp"

using namespace std;
namespace TravelingSalesman
{
    double BruteForce::weigthOfPath(int *path, int size, double **matrix)
    {
        double weight = 0.0;

        for (int i = 1; i < size; i++)
            weight += matrix[path[i]][path[i - 1]];
        weight += matrix[path[size - 1]][0];

        return weight;
    }

    void BruteForce::permutation(int *arr, int i, int n, double **matrix)
    {
        if (i == n)
        {
            double w = weigthOfPath(arr, n, matrix);
            if (w <= minDist)
            {
                minPath = Utils::copyArr(arr, n);
                minDist = w;
            }
            return;
        }

        for (int j = i; j < n; j++)
        {
            swap(arr[i], arr[j]);
            permutation(arr, i + 1, n, matrix);
            swap(arr[i], arr[j]);
        }
    }

    void BruteForce::run(int inputSize)
    {
        int *graphPath = new int[inputSize];
        for (int i = 0; i < inputSize; i++)
            graphPath[i] = i;

        minDist = DBL_MAX;

        Graph graph = InputManager::readGraphInFile(inputSize);
        Timer timer;

        timer.start();
        permutation(graphPath, 1, inputSize, graph.matrix);
        TSPResult result(inputSize, minDist, minPath, timer.stop());

        result.showResult("Brute Force");

        minDist = DBL_MAX;
        delete[] graphPath;
    }

    void BruteForce::runInRange(int begin, int end)
    {
        for (int i = begin; i <= end; i++)
            run(i);
    }

    double BranchAndBound::weigthOfPath(int *path, int size, double **matrix)
    {
        double weight = 0.0;

        for (int i = 1; i < size; i++)
        {
            weight += matrix[path[i]][path[i - 1]];
            if (weight > lowerBound && weight > minDist)
                return DBL_MAX;
        }
        weight += matrix[path[size - 1]][0];

        return weight;
    }

    void BranchAndBound::permutation(int *arr, int i, int n, double **matrix)
    {
        if (i == n)
        {
            double w = weigthOfPath(arr, n, matrix);
            if (w <= minDist)
            {
                minPath = Utils::copyArr(arr, n);
                minDist = w;
            }
            return;
        }

        for (int j = i; j < n; j++)
        {
            swap(arr[i], arr[j]);
            permutation(arr, i + 1, n, matrix);
            swap(arr[i], arr[j]);
        }
    }

    double BranchAndBound::calculateLowerBound(double **matrix, int n)
    {
        double sum = 0.0;
        for (int i = 0; i < n; i++)
        {
            double tmp = matrix[i][i];
            matrix[i][i] = DBL_MAX;

            int min1 = matrix[i][0], min2 = matrix[i][1];
            if (min2 < min1)
            {
                min1 = matrix[i][1];
                min2 = matrix[i][0];
            }

            for (int i = 2; i < n; i++)
            {
                if (matrix[i][i] < min1)
                {
                    min2 = min1;
                    min1 = matrix[i][i];
                }
                else if (matrix[i][i] < min2)
                    min2 = matrix[i][i];
            }
            matrix[i][i] = tmp;
            sum += min1 + min2;
        }
        return sum;
    }

    void BranchAndBound::run(int inputSize)
    {
        int *graphPath = new int[inputSize];
        for (int i = 0; i < inputSize; i++)
            graphPath[i] = i;

        minDist = DBL_MAX;

        Graph graph = InputManager::readGraphInFile(inputSize);

        lowerBound = calculateLowerBound(graph.matrix, inputSize);
        Timer timer;

        timer.start();
        permutation(graphPath, 1, inputSize, graph.matrix);
        TSPResult result(inputSize, minDist, minPath, timer.stop());

        result.showResult("Branch and Bound");

        minDist = DBL_MAX;
        delete[] graphPath;
    }

    void BranchAndBound::runInRange(int begin, int end)
    {
        for (int i = begin; i <= end; i++)
            run(i);
    }

}
