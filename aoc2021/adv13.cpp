#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;
using coord = pair<int, int>;
using grid = set<coord>;
using fold = pair<char, int>;

void get_input(grid& gr, vector<fold>& folds)
{
    string line{};
    // get coordinates
    while (getline(cin, line) && !line.empty())
    {
        int x, y;
        size_t pos = line.find(",");
        gr.insert(coord(stoi(line.substr(0, pos)), stoi(line.substr(pos + 1))));
    }
    //get folds
    while (!cin.eof())
    {
        string word{};
        char direction{};
        char equal_sign{};
        int value{};
        cin >> word >> word >> direction >> equal_sign >> value;
        cout << direction << ", " << value << endl;
        folds.push_back(fold(direction, value));
    }
}

void fold_paper(grid& gr, fold& fl)
{
    if (fl.first == 'x')
    {
        auto it = begin(gr);
        while (it != end(gr))
        {
            auto old = it;
            it++;
            if (old->first > fl.second)
            {
                int dist = abs(old->first - fl.second);
                coord new_coord{fl.second - dist, old->second};
                gr.erase(old);
                gr.insert(new_coord);
            }
        }
    }
    else
    {
        auto it = begin(gr);
        while (it != end(gr))
        {
            auto old = it;
            it++;
            if (old->second > fl.second)
            {
                int dist = abs(old->second - fl.second);
                coord new_coord{old->first, fl.second - dist};
                gr.erase(old);
                gr.insert(new_coord);
            }
        } 
    }
}

void print_code(const grid& gr)
{
    int columns_size = max_element(begin(gr), end(gr))->first + 1;

    for (int r = 0; r < 10; ++r)
    {
        for (int c = 0; c < columns_size; ++c)
        {
            if (auto it = gr.find(coord(c, r)); it != end(gr))
                cout << '#';
            else
                cout << '.';
        }
        cout << endl;
    }
}

int main()
{
    grid gr{};
    vector<fold> folds{};
    get_input(gr, folds);
    
    for (auto& fl : folds)
        fold_paper(gr, fl);
    
    cout << gr.size() << endl;
    print_code(gr);
}
