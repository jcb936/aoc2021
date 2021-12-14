#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <limits>

using namespace std;

void get_input(map<string, char>& rules, map<string, int64_t>& str, map<char, uint64_t>& distr)
{
    string line{};
    getline(cin, line);
    auto it = begin(line);
    for (size_t i{}; i < line.size(); ++i)
        distr[line[i]]++;
    
    string current_char{};
    while (it != end(line))
    {
        current_char.push_back(*it);
        if (current_char.size() == 2)
        {
            str[current_char]++;
            current_char.erase(begin(current_char));
        }
        it++;
    }
    
    while (!cin.eof())
    {
        string code{};
        char insert{};
        string trim{};
        cin >> code >> trim >> insert;
        rules[code] = insert;
    }
}

map<string, int64_t> tick_polymer(const map<string, char>& rules, map<string, int64_t>& str, map<char, uint64_t>& distr)
{
    map<string, int64_t> result{};
    for (auto& pair : rules)
    {
        if (str.find(pair.first) != end(str))
        {
            int64_t value = str[pair.first];
            string c1{};
            string c2{};
            c1.push_back((pair.first)[0]);
            c2.push_back(pair.second);
            c2.push_back((pair.first)[1]);
            c1.push_back(pair.second);
            result[c1] += value;
            result[c2] += value;
            distr[pair.second] += value;
        }
    }
    
    return move(result);
}

uint64_t compute_difference(map<char, uint64_t>& distr)
{
    uint64_t current_max{};
    uint64_t current_min{numeric_limits<uint64_t>::max()};
    for (auto& element : distr)
    {
        if (element.second > current_max)
            current_max = element.second;
        
        if (element.second < current_min)
            current_min = element.second;
    }
    
    return current_max - current_min;
}

int main()
{
    map<char, uint64_t> distr{};
    map<string, char> rules{};
    map<string, int64_t> str{};

    get_input(rules, str, distr);

    for (size_t i{}; i < 40; ++i)
        str = tick_polymer(rules, str, distr);

    cout << compute_difference(distr) << endl;
}
