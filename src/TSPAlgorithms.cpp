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
    for(int i=0;i< (1 << size);i++ )
	{
		for(int j=0;j<size;j++)
		{
			dp[i][j]=-1;
			minPath[i][j]=-1;		
		}
	}
}

void Dynamic::display_path(int source)
{
    int count=0,i=0;
	int brr[size];
	for(i=0;i<size;i++)
	{
		brr[i]=-1;
	}

	printf("\n shortest path\t\t: %d ->",source+1);
	while(count<size-1)
	{
		for(i=0;i<(1 << size);i++)
		{
			if(minPath[i][source]!=-1 && brr[minPath[i][source]]==-1)
			{
				brr[minPath[i][source]]++;
				source=minPath[i][source];
				printf(" %d -> ",source+1);
				count++;

				break;
			}
		}
	}
	printf("%d\n\n",pos+1);	
}

double Dynamic::tsd(int visited,int mask,int source){
    
    if(mask==visited)
	{
		return matrix[source][pos];
	}
		
	else if (dp[mask][source]!=-1)
	{
		return dp[mask][source];
	
	}
	
	double ans=DBL_MAX,minAns=0;
    int i,k;
	for(i=0;i<size;i++)
	{

		if((mask&(1<<i))==0)
		{
			minAns=matrix[source][i]+tsd(visited,mask|(1<<i),i);
			if(ans>minAns)
			{
				ans=minAns;				
				k=i;			
			}
		}
	}
	
	minPath[mask][source]=k;
	return dp[mask][source]=ans;
}

void Dynamic::runInRange(int begin, int end){
    for (int i = begin; i <= end; i++)
        run(i);
}

void Dynamic::run(int inputSize){
    int cost = 0, mask,visited = (1 << size) - 1;
    start();
    int *graphPath = new int[inputSize];
    for (int i = 0; i < inputSize; i++)
        graphPath[i] = i;

    minDist = DBL_MAX;

    Graph graph = InputManager::readGraphInFile(inputSize);
    matrix = graph.matrix;
    pos = inputSize;
    pos--;
    mask = 1 << pos;
    cost = tsd(visited,mask,pos);
    display_path(pos);
}