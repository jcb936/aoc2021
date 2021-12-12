// tried vim for the first time, can be refactored to use pointers and avoid string data redundancy

#include <iostream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class graph
{
private:
    unordered_map<string, unordered_set<string>> data{};
public:
    void add_edge(const string&v, const string& u)
    {
        data[v].insert(u);
        data[u].insert(v);
    }

    int dfs_traverse(const string& start, const string& end, unordered_multiset<string>& visited, bool second_time)
    {
        int paths{};

        if (!isupper(static_cast<unsigned char>(start[0])))
            visited.insert(start);

        if (start == end)
            paths = 1;
        else
        {
            for (auto& vert : data[start])
            {
                if (visited.find(vert) == visited.end())
                    paths += dfs_traverse(vert, end, visited, second_time);
                else if (!second_time && vert != "start" && vert != end)
                    paths += dfs_traverse(vert, end, visited, true);
            }
        }

        if (auto it = visited.find(start); it != visited.end())
            visited.erase(it);
        return paths;
    }
};

graph create_graph()
{
    graph gr{};
    string read{};
    while (getline(cin, read))
    {
        size_t pos = read.find("-");
        string v1{read.substr(0, pos)};
        string v2{read.substr(pos + 1)};
        gr.add_edge(v1, v2);
    }

    return move(gr); 
}

int main()
{
    graph gr = create_graph();
    unordered_multiset<string> visited{};
    cout << gr.dfs_traverse("start", "end", visited, false) << endl;
}