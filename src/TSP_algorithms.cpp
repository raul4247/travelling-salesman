#include "../lib/TSP_algorithms.hpp"

using namespace std;

namespace traveling_salesman
{
    double BruteForce::weigth_of_path(int *path, int size)
    {
        double weight = 0.0;

        for (int i = 1; i < size; i++)
            weight += graph->get_conection(path[i], path[i - 1]);
        weight += graph->get_conection(path[size - 1], 0);

        return weight;
    }

    void BruteForce::permutation(int *arr, int i, int n)
    {
        if (i == n)
        {
            double w = weigth_of_path(arr, n);
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
            permutation(arr, i + 1, n);
            swap(arr[i], arr[j]);
        }
    }

    long long BruteForce::run(int input_size)
    {
        int *graph_path = new int[input_size];
        for (int i = 0; i < input_size; i++)
            graph_path[i] = i;

        min_dist = DBL_MAX;

        graph = InputManager::read_graph_in_file(input_size);
        Timer timer;

        timer.start();
        permutation(graph_path, 1, input_size);
        long long stop_time = timer.stop();
        TSPResult result(input_size, min_dist, min_path, stop_time);

        result.show_result("brute_force");

        min_dist = DBL_MAX;
        delete[] graph_path;
        return stop_time;
    }

    void BruteForce::run_in_range(int begin, int end)
    {
        for (int i = begin; i <= end; i++)
            run(i);
    }

    void BruteForce::run_in_range_statistic(int begin, int end)
    {
        for (int i = begin; i <= end; i++)
        {
            cout << "N: " << i << "\n";
            long long sum = 0;
            for (int j = 0; j < SAMPLES; j++)
                sum += run(i);

            ofstream outputCSV;
            string algorithm_name = "brute_force";
            outputCSV.open(OUTPUT_CSV_PATH(algorithm_name), ios::out | ios::app);
            stringstream stream;
            stream << std::fixed << std::setprecision(7) << ((sum / SAMPLES) / 1000000.0);
            string time = stream.str();
            replace(time.begin(), time.end(), '.', ',');
            outputCSV << time << '\n';
            outputCSV.close();
        }
    }

    double BranchAndBound::weigth_of_path(int *path, int size)
    {
        double weight = 0.0;

        for (int i = 1; i < size; i++)
        {
            weight += graph->get_conection(path[i], path[i - 1]);
            if (weight > lower_bound && weight > min_dist)
                return DBL_MAX;
        }
        weight += graph->get_conection(path[size - 1], 0);

        return weight;
    }

    void BranchAndBound::permutation(int *arr, int i, int n)
    {
        if (i == n)
        {
            double w = weigth_of_path(arr, n);
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
            permutation(arr, i + 1, n);
            swap(arr[i], arr[j]);
        }
    }

    double BranchAndBound::calculate_lower_bound(int n)
    {
        double sum = 0.0;
        for (int i = 0; i < n; i++)
        {
            double tmp = graph->get_conection(i, i);
            graph->set_conection(i, i, DBL_MAX);

            int min1 = graph->get_conection(i, 0);
            int min2 = graph->get_conection(i, 1);
            if (min2 < min1)
            {
                min1 = graph->get_conection(i, 1);
                min2 = graph->get_conection(i, 0);
            }

            for (int j = 2; j < n; j++)
            {
                auto tmp = graph->get_conection(j, j);
                if (tmp < min1)
                {
                    min2 = min1;
                    min1 = tmp;
                }
                else if (tmp < min2)
                    min2 = tmp;
            }
            graph->set_conection(i, i, tmp);
            sum += min1 + min2;
        }
        return sum;
    }

    long long BranchAndBound::run(int input_size)
    {
        int *graph_path = new int[input_size];
        for (int i = 0; i < input_size; i++)
            graph_path[i] = i;

        min_dist = DBL_MAX;

        graph = InputManager::read_graph_in_file(input_size);

        if(input_size > 1)
            lower_bound = calculate_lower_bound(input_size);
        else lower_bound = 0;
        Timer timer;

        timer.start();
        permutation(graph_path, 1, input_size);
        long long stop_time = timer.stop();
        TSPResult result(input_size, min_dist, min_path, stop_time);

        result.show_result("branch_and_bound");

        min_dist = DBL_MAX;
        delete[] graph_path;
        return stop_time;
    }

    void BranchAndBound::run_in_range(int begin, int end)
    {
        for (int i = begin; i <= end; i++)
            run(i);
    }

    void BranchAndBound::run_in_range_statistic(int begin, int end)
    {
        for (int i = begin; i <= end; i++)
        {
            long long sum = 0;
            for (int j = 0; j < SAMPLES; j++)
                sum += run(i);

            ofstream outputCSV;
            string algorithm_name = "branch_and_bound";
            outputCSV.open(OUTPUT_CSV_PATH(algorithm_name), ios::out | ios::app);
            stringstream stream;
            stream << std::fixed << std::setprecision(7) << ((sum / SAMPLES) / 1000000.0);
            string time = stream.str();
            replace(time.begin(), time.end(), '.', ',');
            outputCSV << time << '\n';
            outputCSV.close();
        }
    }

    double Dynamic::weigth_of_path(int *path, int size)
    {
        double weight = 0.0;

        for (int i = 1; i < size; i++)
            weight += graph->get_conection(path[i], path[i - 1]);
        weight += graph->get_conection(path[size - 1], 0);

        return weight;
    }

    void Dynamic::start()
    {
        path = new int *[1 << size];
        dp = new double *[1 << size];
        for (int i = 0; i < (1 << size); i++)
        {
            path[i] = new int[size];
            dp[i] = new double[size];
        }
        for (int i = 0; i < (1 << size); i++)
        {
            for (int j = 0; j < size; j++)
            {
                dp[i][j] = -1;
                path[i][j] = -1;
            }
        }
    }

    int *Dynamic::display_path(int source)
    {
        int count = 1, i = 0;
        int brr[size];
        for (i = 0; i < size; i++)
        {
            brr[i] = -1;
        }
        int *arrya = new int[size];
        arrya[0] = 0;
        while (count < size)
        {
            for (i = 0; i < (1 << size); i++)
            {
                if (path[i][source] != -1 && brr[path[i][source]] == -1)
                {
                    brr[path[i][source]]++;
                    source = path[i][source];
                    arrya[count] = source;
                    count++;

                    break;
                }
            }
        }
        return arrya;
    }

    double Dynamic::tsd(int mask, int source)
    {
        if (mask == visited)
        {
            return graph->get_conection(source, pos);
        }
        else if (dp[mask][source] != -1)
        {
            return dp[mask][source];
        }
        double ans = DBL_MAX, minAns = 0, k;
        int i;
        for(i = 0; i < size; i++)
        {
            if((mask&(1 << i)) == 0)
            {
                minAns = graph->get_conection(source, i) + tsd(mask|(1<<i),i);
                if(ans > minAns)
                {
                    ans = minAns;
                    k = i;
                }
            }
        }
        path[mask][source] = k;
        dp[mask][source] = ans;
        return dp[mask][source];
    }

    void Dynamic::run_in_range(int begin, int end)
    {
        for (int i = begin; i <= end; i++)
            run(i);
    }

    long long Dynamic::run(int input_size)
    {
        size = input_size;

        double cost = 0;
        int mask;

        visited = (1 << size) - 1;
        start();

        graph = InputManager::read_graph_in_file(input_size);
        pos = 0;
        mask = 1 << pos;

        Timer timer;

        timer.start();
        cost = tsd(mask, pos);
        long long stop_time = timer.stop();
        TSPResult result(input_size, cost, display_path(0), stop_time);
        result.show_result("dynamic_programming");
        return stop_time;
    }

    void Dynamic::run_in_range_statistic(int begin, int end)
    {
        for (int i = begin; i <= end; i++)
        {
            long long sum = 0;
            for (int j = 0; j < SAMPLES; j++)
                sum += run(i);

            ofstream outputCSV;
            string algorithm_name = "dynamic_programming";
            outputCSV.open(OUTPUT_CSV_PATH(algorithm_name), ios::out | ios::app);
            stringstream stream;
            stream << std::fixed << std::setprecision(7) << ((sum / SAMPLES) / 1000000.0);
            string time = stream.str();
            replace(time.begin(), time.end(), '.', ',');
            outputCSV << time << '\n';
            outputCSV.close();
        }
    }

    Population Genetic::evolve_population(Population p)
    {
        Population next_gen(p.size());
        int elitism_offset{};

        // Manter a melhor rota, se elitism estiver habilitado
        if (elitism)
        {
            next_gen.save_route(0, p.get_best_route());
            elitism_offset = 1;
        }

        // Fazer o crossover da população
        for (int i = elitism_offset; i < p.size(); i++)
        {
            // Seleciona os "pais"
            TravelRoute p1 = tournament_selection(p);
            TravelRoute p2 = tournament_selection(p);
            // Faz o cruzamento
            TravelRoute child = crossover(p1, p2);
            // Adicionar o "Filho" na nova geracao
            next_gen.save_route(i, child);
        }

        // Mudando um pouco a população, para adicionar
        // algum novo "material genetico"
        for (int i = elitism_offset; i < next_gen.size(); i++)
        {
            mutate(next_gen.get_route(i));
        }

        return next_gen;
    }

    TravelRoute Genetic::crossover(TravelRoute a, TravelRoute b)
    {
        vector<City *> child_cities(a.size(), nullptr);

        // Obtem uma posicao inicial e final de uma sub rota de 'a'
        int start_pos = rand() % (a.size() - 1) + 1;
        int end_pos = rand() % (a.size() - 1) + 1;

        // Percorre e adiciona a sub rota em child_cities
        for (int i = 0; i < child_cities.size(); i++)
        {
            if (start_pos < end_pos && i > start_pos && i < end_pos)
            {
                child_cities.at(i) = new City(a.get_city(i));
            }
            else if (start_pos > end_pos)
            {
                if (!(i < start_pos && i > end_pos))
                {
                    child_cities.at(i) = new City(a.get_city(i));
                }
            }
        }

        // Percorre a rota b
        for (int i = 0; i < b.size(); i++)
        {
            // Se child_cities não tiver a cidade da rota b, adiciona
            bool found = false;
            City bcity = b.get_city(i);
            for(auto city : child_cities)
            {
                if(city != nullptr && *city == bcity){
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                // Percorre para encontrar uma posicao vazia em child_cities
                for (int j = 0; j < child_cities.size(); j++)
                {
                    if (child_cities.at(j) == nullptr)
                    {
                        child_cities.at(j) = new City(b.get_city(i));
                        break;
                    }
                }
            }
        }

        // Cria novo vector, dessa vez sem pointer.
        vector<City> final;
        for (int i = 0; i < child_cities.size(); i++)
        {
            auto aux = child_cities.at(i);
            if (aux != nullptr)
            {
                final.push_back(*aux);
                delete aux;
                aux = nullptr;
            }
        }

        // Retorna a rota "filha" resultante do crossover
        return TravelRoute(final);
    }

    // Realiza a mutacao da rota por meio de swap.
    void Genetic::mutate(TravelRoute &tr)
    {
        // Percorre pelas cidades da rota
        for (int route_pos1 = 1; route_pos1 < tr.size(); route_pos1++)
        {
            // Aplica a taxa de mutação
            if (((double)rand() / RAND_MAX) < mutation_rate)
            {
                int route_pos2 = rand() % (tr.size() - 1) + 1;
                tr.swap_cities(route_pos1, route_pos2);
            }
        }
    }

    TravelRoute Genetic::tournament_selection(Population p)
    {
        Population tournament(tournament_size);
        for (int i = 0; i < tournament_size; i++)
        {
            int random_idx = rand() % p.size();
            tournament.save_route(i, p.get_route(random_idx));
        }
        return tournament.get_best_route();
    }

    long long Genetic::run(int input_size)
    {
        vector<City> cities = InputManager::read_cities_in_file(input_size);
        // define valores padrao, caso entrada seja 1.
        double best_distance = 0.0;
        int* best_route = new int[input_size];
        best_route[0] = 0;

        Timer timer;
        timer.start();
        if(input_size > 1){
            Population cobaia(population_size);

            for (int i = 0; i < population_size; i++)
            {
                TravelRoute tr(cities);
                tr.generate_individual();
                cobaia.save_route(i, tr);
            }

            cobaia = Genetic::evolve_population(cobaia);
            // Evolui a cobaia por N geracoes
            for (int i = 0; i < generations; i++)
                cobaia = Genetic::evolve_population(cobaia);

            TravelRoute best = cobaia.get_best_route();
            best_distance = best.get_distance();
            best_route = best.get_route();
        }
        long long stop_time = timer.stop();

        TSPResult result(input_size, best_distance, best_route, stop_time);
        result.show_result("genetic");
        delete best_route;
        return stop_time;
    }

    void Genetic::run_in_range(int begin, int end)
    {
        for (int i = begin; i <= end; i++)
            run(i);
    }

    void Genetic::run_in_range_statistic(int begin, int end)
    {
        for (int i = begin; i <= end; i++)
        {
            long long sum = 0;
            for (int j = 0; j < SAMPLES; j++)
                sum += run(i);

            ofstream outputCSV;
            string algorithm_name = "genetic";

            outputCSV.open(OUTPUT_CSV_PATH(algorithm_name), ios::out | ios::app);
            stringstream stream;
            stream << std::fixed << std::setprecision(7) << ((sum / SAMPLES) / 1000000.0);
            string time = stream.str();
            replace(time.begin(), time.end(), '.', ',');
            outputCSV << time << '\n';
            outputCSV.close();
        }
    }
} // namespace traveling_salesman
