#include <map>
#include <vector>

template <class T>
std::vector<std::vector<T>> JohnsonTrotter(const std::vector<T>& data)
{
    std::vector<std::vector<T>> output_permutations;

    std::map<T, bool> components;
    std::vector<std::map<T, bool>::iterator> permutation;

    for (std::size_t i = 0; i < data.size(); i++)
    {
        auto insert_it = components.insert(std::pair<T, bool>(data[i], false));
        permutation.push_back(insert_it.first); // components to mapa wiec nie wystepuje iterator invalidation 
    }

    bool success_find_mobile_component = false;
    do {

        output_permutations.push_back(std::vector<T>());
        for (const auto p_obj : permutation)
        {
            output_permutations.back().push_back(p_obj->first);
        }

        success_find_mobile_component = false;

        std::size_t it = 0;
        std::size_t max_it = it;

        for (it; it < permutation.size(); it++)
        {
            if (permutation[it]->second == false && it > 0)  // idzie w lewo i nie jest na początku
            {
                if (permutation[it]->first > permutation[it - 1]->first)// jest wiekszy niz element po lewej
                {
                    if (permutation[it]->first > permutation[max_it]->first || !success_find_mobile_component)// jest wiekszy niz aktualne maximum
                    {
                        max_it = it;
                        success_find_mobile_component = true;
                        continue;
                    }
                }
            }

            if (permutation[it]->second == true && it < permutation.size() - 1) // idzie w prawo i nie jest na koncu
            {
                if (permutation[it]->first > permutation[it + 1]->first) // jest wiekszy niz element po prawej
                {
                    if (permutation[it]->first > permutation[max_it]->first || !success_find_mobile_component) // jest wiekszy niz aktualne maximum
                    {
                        max_it = it;
                        success_find_mobile_component = true;
                        continue;
                    }
                }
            }
        }

        if (!success_find_mobile_component)break; // nie mozna znalezc zadnego mobile element

        typename std::map<T, bool>::iterator map_it = permutation[max_it];
        map_it++; // nie zmieniaj kierunku danego maksymalnego mobile element

        if (permutation[max_it]->second == true)
        {
            std::swap(permutation[max_it], permutation[max_it + 1]);
        }
        else
        {
            std::swap(permutation[max_it], permutation[max_it - 1]);
        }

        for (map_it; map_it != components.end(); map_it++) // zmien kierunek ruchu kazdego wiekszego mobile element
        {
            map_it->second = !map_it->second;
        }

    } while (success_find_mobile_component);

    return output_permutations;
}

int main()
{
    std::vector<unsigned int> n{ 1, 2, 3, 4};

    auto p = JohnsonTrotter(n);

    return 0;
}
