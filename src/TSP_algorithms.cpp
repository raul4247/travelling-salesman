#include "../lib/TSP_algorithms.hpp"

using namespace std;
namespace traveling_salesman
{
    double BruteForce::weigth_of_path(int *path, int size, double **matrix)
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
            double w = weigth_of_path(arr, n, matrix);
            if (w <= min_dist)
            {
                min_path = Utils::copy_arr(arr, n);
                min_dist = w;
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

    void BruteForce::run(int input_size)
    {
        int *graph_path = new int[input_size];
        for (int i = 0; i < input_size; i++)
            graph_path[i] = i;

        min_dist = DBL_MAX;

        Graph graph = InputManager::read_graph_in_file(input_size);
        Timer timer;

        timer.start();
        permutation(graph_path, 1, input_size, graph.matrix);
        TSPResult result(input_size, min_dist, min_path, timer.stop());

        result.show_result("brute_force");

        min_dist = DBL_MAX;
        delete[] graph_path;
    }

    void BruteForce::run_in_range(int begin, int end)
    {
        for (int i = begin; i <= end; i++)
            run(i);
    }

    double BranchAndBound::weigth_of_path(int *path, int size, double **matrix)
    {
        double weight = 0.0;

        for (int i = 1; i < size; i++)
        {
            weight += matrix[path[i]][path[i - 1]];
            if (weight > lower_bound && weight > min_dist)
                return DBL_MAX;
        }
        weight += matrix[path[size - 1]][0];

        return weight;
    }

    void BranchAndBound::permutation(int *arr, int i, int n, double **matrix)
    {
        if (i == n)
        {
            double w = weigth_of_path(arr, n, matrix);
            if (w <= min_dist)
            {
                min_path = Utils::copy_arr(arr, n);
                min_dist = w;
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

    double BranchAndBound::calculate_lower_bound(double **matrix, int n)
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

    void BranchAndBound::run(int input_size)
    {
        int *graph_path = new int[input_size];
        for (int i = 0; i < input_size; i++)
            graph_path[i] = i;

        min_dist = DBL_MAX;

        Graph graph = InputManager::read_graph_in_file(input_size);

        lower_bound = calculate_lower_bound(graph.matrix, input_size);
        Timer timer;

        timer.start();
        permutation(graph_path, 1, input_size, graph.matrix);
        TSPResult result(input_size, min_dist, min_path, timer.stop());

        result.show_result("branch_and_bound");

        min_dist = DBL_MAX;
        delete[] graph_path;
    }

    void BranchAndBound::run_in_range(int begin, int end)
    {
        for (int i = begin; i <= end; i++)
            run(i);
    }

}
