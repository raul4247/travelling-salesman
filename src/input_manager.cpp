#include "../lib/input_manager.hpp"

using std::runtime_error;
using std::to_string;
using std::ofstream;
using std::fstream;
using std::ios_base;

namespace traveling_salesman
{
    vector<Point> InputManager::gen_points(int n)
    {
        vector<Point> points;

        srand((unsigned)time(NULL));
        do
        {
            int x = rand() % (MAX_XY + 1);
            int y = rand() % (MAX_XY + 1);

            Point p(x, y);
            if (!(find(points.begin(), points.end(), p) != points.end()))
                points.push_back(Point(x, y));
        } while (points.size() != n);

        return points;
    }

    void InputManager::gen_random_input(int vertex_count)
    {
        if (vertex_count <= 0 || vertex_count > MAX_N)
            throw runtime_error("vertexCount invalid in generateRandomInput: " + to_string(vertex_count));

        if (vertex_count > ((MAX_XY + 1) * (MAX_XY + 1)))
            throw runtime_error("Exception: Impossible to generate " + to_string(vertex_count) + " vertices with only " + to_string((MAX_XY + 1) * (MAX_XY + 1)) + " combinations of XY");

        vector<Point> points = gen_points(vertex_count);

        ofstream output_file;
        output_file.open(INPUT_FILE_PATH(to_string(vertex_count)));

        output_file << to_string(vertex_count) << "\n";
        for (Point p : points)
            output_file << p.get_x() << " " << p.get_y() << '\n';
        output_file.close();
    }

    void InputManager::gen_all_allowed_random_inputs()
    {
        for (int i = 1; i <= MAX_N; i++)
            gen_random_input(i);
    }

    Graph InputManager::read_graph_in_file(int input_size)
    {
        fstream input_file(INPUT_FILE_PATH(to_string(input_size)), ios_base::in);
        if (input_file.fail())
            throw runtime_error("File not exist: " + INPUT_FILE_PATH(to_string(input_size)));

        int n;
        input_file >> n;

        Graph g(n);
        for (int i = 0; i < n; i++)
        {
            int x, y;
            input_file >> x >> y;
            g.add_point(Point(x, y));
        }
        return g;
    }

}
