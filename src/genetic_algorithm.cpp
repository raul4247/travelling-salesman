#include "../lib/genetic_algorithm.hpp"
#include <algorithm>

using std::find;

namespace genetic_algorithm {

    Population GeneticAlgorithm::evolve_population(Population p){
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

    TravelRoute GeneticAlgorithm::crossover(TravelRoute a, TravelRoute b){
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
    void GeneticAlgorithm::mutate(TravelRoute &tr){
        // Percorre pelas cidades da rota
        for(int route_pos1 = 1; route_pos1 < tr.size(); route_pos1++){
            // Aplica a taxa de mutação
            if(((double) rand() / RAND_MAX) < mutation_rate){
                int route_pos2 = rand() % (tr.size() - 1) + 1;
                tr.swap_cities(route_pos1, route_pos2);
            }
        }
    }

    TravelRoute GeneticAlgorithm::tournament_selection(Population p){
        Population tournament(tournament_size);
        for(int i = 0; i < tournament_size; i++){
            int random_idx = rand() % p.size();
            tournament.save_route(0, p.get_route(random_idx));
        }
        return tournament.get_best_route();
    }


}