#include <iostream>
#include <vector>
#include <map>

using namespace std;

void tick(map<int8_t, uint64_t>& elements)
{
    map<int8_t, int64_t> diff{};

    for (auto& element : elements)
    {
        int8_t first = element.first;
        diff[first] -= element.second;

        first--;

        if (first == -1)
        {
            diff[6] += element.second;
            diff[8] += element.second;
        }
        else
        {
            diff[first] += element.second;
        }
    }

    for (auto& element : elements)
    {
        element.second += diff[element.first];
    }
}

void solve(vector<int8_t>& initialState, int days)
{
    map<int8_t, uint64_t> elements{};

    // initialise map

    for (int i = 0; i < 9; ++i)
    {
        elements[i] = 0;
    }

    for (auto& fish : initialState)
    {
        elements[fish] += 1;
    }

    for (int i = 0; i < days; ++i)
    {
        cout << "Starting day " << i << endl;

        tick(elements);
    }

    uint64_t total{};
    for (auto& element : elements)
    {
        total += element.second;
    }

    cout << total << endl;
}

int main()
{
    vector<int8_t> initialState{ 3,4,3,1,2,1,5,1,1,1,1,4,1,2,1,1,2,1,1,1,3,4,4,4,1,3,2,1,3,4,1,1,3,4,
        2,5,5,3,3,3,5,1,4,1,2,3,1,1,1,4,1,4,1,5,3,3,1,4,1,5,1,2,2,1,1,5,5,2,5,1,1,1,1,3,1,4,1,1,1,4,1,
        1,1,5,2,3,5,3,4,1,1,1,1,1,2,2,1,1,1,1,1,1,5,5,1,3,3,1,2,1,3,1,5,1,1,4,1,1,2,4,1,5,1,1,3,3,3,4,2,
        4,1,1,5,1,1,1,1,4,4,1,1,1,3,1,1,2,1,3,1,1,1,1,5,3,3,2,2,1,4,3,3,2,1,3,3,1,2,5,1,3,5,2,2,1,1,1,1,
        5,1,2,1,1,3,5,4,2,3,1,1,1,4,1,3,2,1,5,4,5,1,4,5,1,3,3,5,1,2,1,1,3,3,1,5,3,1,1,1,3,2,5,5,1,1,4,2,1,
        2,1,1,5,5,1,4,1,1,3,1,5,2,5,3,1,5,2,2,1,1,5,1,5,1,2,1,3,1,1,1,2,3,2,1,4,1,1,1,1,5,4,1,4,5,1,4,3,4,1,
        1,1,1,2,5,4,1,1,3,1,2,1,1,2,1,1,1,2,1,1,1,1,1,4 };

    solve(initialState, 256);

    return 0;
}