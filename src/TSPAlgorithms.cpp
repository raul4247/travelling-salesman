#include "../lib/TSPAlgorithms.hpp"

using Timer = TravelingSalesman::Timer;
using Utils = TravelingSalesman::Utils;
using BruteForce = TravelingSalesman::BruteForce;
using BranchAndBound = TravelingSalesman::BranchAndBound;
using Dynamic = TravelingSalesman::Dynamic;
using Graph = TravelingSalesman::Graph;
using TSPResult = TravelingSalesman::TSPResult;
using InputManager = TravelingSalesman::InputManager;
using namespace std;

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

    result.showResult("brute_force");

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

    result.showResult("branch_and_bound");

    minDist = DBL_MAX;
    delete[] graphPath;
}

void BranchAndBound::runInRange(int begin, int end)
{
    for (int i = begin; i <= end; i++)
        run(i);
}

double Dynamic::weigthOfPath(int *path, int size, double **matrix)

{
    double weight = 0.0;

    for (int i = 1; i < size; i++)
        weight += matrix[path[i]][path[i - 1]];
    weight += matrix[path[size - 1]][0];

    return weight;
}

void Dynamic::start()
{
    path = new int *[1 << size];
    dp = new double *[1 << size];
    for (int i = 0; i < (1<<size); i++)
    {
        path[i] = new int[size];
        dp[i] = new double[size];
    }
    for(int i=0;i< (1 << size);i++ )
	{
		for(int j=0;j<size;j++)
		{
			dp[i][j]=-1;
			path[i][j]=-1;		
		}
	}
}

int* Dynamic::display_path(int source)
{
	int count=1,i=0;
	int brr[size];
	for(i=0;i<size;i++)
	{
		brr[i]=-1;
	}
    int *arrya = new int[size];
    arrya[0] = 0;
	while(count<size)
	{
		for(i=0;i<(1 << size);i++)
		{
			if(path[i][source]!=-1 && brr[path[i][source]]==-1)
			{
				brr[path[i][source]]++;
				source=path[i][source];
                arrya[count] = source;
				count++;

				break;
			}
		}
	}
    return arrya;
}

double Dynamic::tsd(int mask, int source){
    if(mask==visited)
	{
		return matrix[source][pos];
	}
	else if (dp[mask][source]!=-1)
	{
		return dp[mask][source];
	
	}
	double ans=DBL_MAX,minAns=0,k;
    int i;
	for(i=0;i<size;i++)
	{

		if((mask&(1<<i))==0)
		{
			minAns=matrix[source][i]+tsd(mask|(1<<i),i);
			if(ans>minAns)
			{
				ans=minAns;				
				k=i;			
			}
		}
	}
	path[mask][source]=k;
    dp[mask][source]=ans;
	return dp[mask][source];
}

void Dynamic::runInRange(int begin, int end){
    for (int i = begin; i <= end; i++)
        run(i);
}

void Dynamic::run(int inputSize){
    size = inputSize;
    double cost = 0;
    int mask;
    visited = (1 << size) - 1;
    start();
    Graph graph = InputManager::readGraphInFile(inputSize);
    matrix = graph.matrix;
    pos = 0;
    mask = 1 << pos;
    Timer timer;
    timer.start();
    cout << inputSize << endl ;
    cost = tsd(mask,pos);
    TSPResult result(inputSize, cost, display_path(0), timer.stop());
    result.showResult("Dynamic Programming");

}