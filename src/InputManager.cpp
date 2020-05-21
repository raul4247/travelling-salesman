#include "../lib/InputManager.hpp"

using namespace std;
using Point = TravelingSalesman::Point;
using Graph = TravelingSalesman::Graph;
using InputManager = TravelingSalesman::InputManager;

vector<Point> InputManager::genPoints(int n)
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

void InputManager::genRandomInput(int vertexCount)
{
    if (vertexCount <= 0 || vertexCount > MAX_N)
    {
        cout << "Exception: vertexCount invalid in generateRandomInput"
             << "\n";
        return;
    }

    if (vertexCount > ((MAX_XY + 1) * (MAX_XY + 1)))
    {
        cout << "Exception: Impossible to generate " << vertexCount << " vertices with only " << (MAX_XY + 1) * (MAX_XY + 1) << " combinations of XY\n";
        return;
    }

    vector<Point> points = genPoints(vertexCount);

    ofstream outputFile;
    outputFile.open(INPUT_FILE_PATH(to_string(vertexCount)));

    outputFile << to_string(vertexCount) << "\n";
    for (Point p : points)
        outputFile << p.getX() << " " << p.getY() << '\n';
    outputFile.close();
}

void InputManager::genAllAllowedRandomInputs()
{
    for (int i = 1; i <= MAX_N; i++)
        genRandomInput(i);
}

Graph InputManager::readGraphInFile(int inputSize)
{
    fstream inputFile(INPUT_FILE_PATH(to_string(inputSize)), ios_base::in);

    int n;
    inputFile >> n;

    Graph g(n);
    for (int i = 0; i < n; i++)
    {
        int x, y;
        inputFile >> x >> y;
        g.addPoint(Point(x, y));
    }
    return g;
}