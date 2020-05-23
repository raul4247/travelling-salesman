#include "../lib/TSP_algorithms.hpp"

using namespace std;

using genetic::City;

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

    double Dynamic::weigth_of_path(int *path, int size, double **matrix)
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

    double Dynamic::tsd(int mask, int source)
    {
        if(mask==visited)
        {
            return matrix[source][pos];
        }
        else if (dp[mask][source]!=-1)
        {
            return dp[mask][source];

        }
        double ans=DBL_MAX, minAns=0, k;
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

    void Dynamic::run_in_range(int begin, int end)
    {
        for (int i = begin; i <= end; i++)
            run(i);
    }

    void Dynamic::run(int input_size)
    {
        size = input_size;
        double cost = 0;
        int mask;
        visited = (1 << size) - 1;
        start();
        Graph graph = InputManager::read_graph_in_file(input_size);
        matrix = graph.matrix;
        pos = 0;
        mask = 1 << pos;
        Timer timer;
        timer.start();
        cout << input_size << endl ;
        cost = tsd(mask,pos);
        TSPResult result(input_size, cost, display_path(0), timer.stop());
        result.show_result("dynamic_programming");

    }

    Population Genetic::evolve_population(Population p){
        Population next_gen(p.size());
        int elitism_offset {};

        // Manter a melhor roda, se elitism estiver habilitado
        if(elitism){
            next_gen.save_route(0, p.get_best_route());
            elitism_offset = 1;
        }

        // Fazer o crossover da população
        for(int i = elitism_offset; i < p.size(); i++){
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
        for(int i = elitism_offset; i < next_gen.size(); i++){
            mutate(next_gen.get_route(i));
        }

        return next_gen;
    }

    TravelRoute Genetic::crossover(TravelRoute a, TravelRoute b){
        vector<City*> child_cities(a.size(), nullptr);

        // Obtem uma posicao inicial e final de uma sub rota de 'a'
        int start_pos = rand() % (a.size() - 1) + 1;
        int end_pos = rand() % (a.size() - 1) + 1;

        // Percorre e adiciona a sub rota em child_cities
        for(int i = 0; i < child_cities.size(); i++){
            if(start_pos < end_pos && i > start_pos && i < end_pos){
                child_cities.at(i) = new City(a.get_city(i));
            }
            else if(start_pos > end_pos){
                if(!(i < start_pos && i > end_pos)){
                    child_cities.at(i) = new City(a.get_city(i));
                }
            }
        }

        // Percorre a rota b
        for(int i = 0; i < b.size(); i++){
            // Se child_cities não tiver a cidade da rota b, adiciona
            bool found = false;
            City bcity = b.get_city(i);
            for(auto city : child_cities){
                if(city != nullptr && city->id == bcity.id){
                    found = true;
                    break;
                }
            }
            if(!found){
                // Percorre para encontrar uma posicao vazia em child_cities
                for(int j = 0; j < child_cities.size(); j++){
                    if(child_cities.at(j) == nullptr) {
                        child_cities.at(j) = new City(b.get_city(i));
                        break;
                    }
                }
            }
        }

        // Cria novo vector, dessa vez sem pointer.
        vector<City> final;
        for(int i = 0; i < child_cities.size(); i++){
            auto aux = child_cities.at(i);
            if(aux != nullptr){
                final.push_back(*aux);
                delete aux;
                aux = nullptr;
            }
        }

        // Retorna a rota "filha" resultante do crossover
        return TravelRoute(final);
    }

    // Realiza a mutacao da rota por meio de swap.
    void Genetic::mutate(TravelRoute &tr){
        // Percorre pelas cidades da rota
        for(int route_pos1 = 1; route_pos1 < tr.size(); route_pos1++){
            // Aplica a taxa de mutação
            if(((double) rand() / RAND_MAX) < mutation_rate){
                int route_pos2 = rand() % (tr.size() - 1) + 1;
                tr.swap_cities(route_pos1, route_pos2);
            }
        }
    }

    TravelRoute Genetic::tournament_selection(Population p){
        Population tournament(tournament_size);
        for(int i = 0; i < tournament_size; i++){
            int random_idx = rand() % p.size();
            tournament.save_route(0, p.get_route(random_idx));
        }
        return tournament.get_best_route();
    }

    void Genetic::run(int input_size)
    {
        vector<City> cities = InputManager::read_cities_in_file(input_size);

        Timer timer;
        timer.start();
        Population cobaia(population_size);

        for(int i = 0; i < population_size; i++){
            TravelRoute tr(cities);
            tr.generate_individual();
            cobaia.save_route(i, tr);
        }

        cobaia = Genetic::evolve_population(cobaia);
        // Evolui a cobaia por N geracoes
        for(int i = 0; i < generations; i++){
            cobaia = Genetic::evolve_population(cobaia);
        }

        TravelRoute best = cobaia.get_best_route();
        TSPResult result(input_size, best.get_distance(), best.get_route(), timer.stop());
        result.show_result("genetic");
    }

    void Genetic::run_in_range(int begin, int end)
    {
        for (int i = begin; i <= end; i++)
            run(i);
    }

}
