#include "../lib/TSP_result.hpp"
#define llong long long

using std::cout;
using std::fixed;
using std::setprecision;
using std::ofstream;
using std::ios;
namespace traveling_salesman
{
    TSPResult::TSPResult(int input_size, double min_dist, int *min_path, llong time_taken_in_microseconds)
    {
        this->input_size = input_size;
        this->min_dist = min_dist;
        this->min_path = min_path;
        this->time_taken_in_microseconds = time_taken_in_microseconds;
    }

    void TSPResult::show_result(string algorithm_name)
    {
        cout << algorithm_name << "\n";
        cout << "Input size: " << input_size << "\n";
        cout << "Min dist: " << min_dist << "\n";
        cout << "Min path: ";
        for (int i = 0; i < input_size; i++)
            cout << min_path[i] << " ";

        if (time_taken_in_microseconds < 1000)
            cout << "\nTime taken: " << time_taken_in_microseconds << " microseconds\n\n";
        else
        {
            if (time_taken_in_microseconds > 1000000)
            {
                if (time_taken_in_microseconds > 60000000)
                    cout << "\nTime taken: " << fixed << setprecision(4) << (time_taken_in_microseconds / 60000000.0) << " minutes\n\n";
                else
                    cout << "\nTime taken: " << fixed << setprecision(4) << (time_taken_in_microseconds / 1000000.0) << " seconds\n\n";
            }
            else
                cout << "\nTime taken: " << fixed << setprecision(4) << (time_taken_in_microseconds / 1000.0) << " miliseconds\n\n";
        }

        ofstream outputFile;
        outputFile.open(OUTPUT_FILE_PATH(algorithm_name), ios::out | ios::app);
        outputFile << input_size << ", " << std::fixed << std::setprecision(7) << (time_taken_in_microseconds / 1000000.0) << '\n';
        outputFile.close();
    }

}
