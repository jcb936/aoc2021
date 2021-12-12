#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
using grid = vector<vector<int>>;

void get_input(grid& gr)
{
    string line{};
    int line_number{};
    while (getline(cin, line))
    {
        gr.push_back(vector<int>{});
        for (int i{}; i < line.size(); ++i)
        {
            char cur = line[i];
            gr[line_number].push_back(stoi(&cur));
        }
        
        line_number++;
    }
}

int get_basin_size(grid& gr, int r, int c)
{
    int num_rows = gr.size();
    int num_columns = gr[0].size();
    int size{1};
    
    // move left
    if (c > 0 && gr[r][c] < gr[r][c-1] && gr[r][c-1] != 9)
        size += get_basin_size(gr, r, c-1);
    
    // move right
    if (c < num_columns - 1 && gr[r][c] < gr[r][c+1] && gr[r][c+1] != 9)
        size += get_basin_size(gr, r, c+1);
    
    // move up
    if (r > 0 && gr[r][c] < gr[r-1][c] && gr[r-1][c] != 9)
        size += get_basin_size(gr, r-1, c);
    
    // move down
    if (r < num_rows - 1 && gr[r][c] < gr[r+1][c] && gr[r+1][c] != 9)
        size += get_basin_size(gr, r+1, c);
    
    gr[r][c] = 9;
    return size;
}

bool check_low_point(const grid& gr, int r, int c)
{
    int num_rows = gr.size();
    int num_columns = gr[0].size();
    
    //left
    if (c > 0 && gr[r][c] >= gr[r][c-1])
        return false;
    //right
    if (c < num_columns - 1 && gr[r][c] >= gr[r][c+1])
        return false;
    //up
    if (r > 0 && gr[r][c] >= gr[r-1][c])
        return false;
    //down
    if (r < num_rows - 1 && gr[r][c] >= gr[r+1][c])
        return false;
        
    return true;
}


int get_risk(grid& gr, vector<int>& largest_basins)
{
    int num_rows = gr.size();
    int num_columns = gr[0].size();
    int total{};
    largest_basins= vector<int>(3, 0);
    
    for (int r{}; r < num_rows; ++r)
    {
        for (int c{}; c < num_columns; ++c)
        {
            if (check_low_point(gr, r, c))
            {
                total += (1 + gr[r][c]);
                int basin_size = get_basin_size(gr, r, c);

                auto min = min_element(begin(largest_basins), end(largest_basins));
                if (basin_size > *min)
                    *min = basin_size;
            }
        }
    }
    
    return total;
}

int main()
{
    grid gr{};
    get_input(gr);
    vector<int> basins{};
    
    int risk = get_risk(gr, basins);
    
    int tot{1};
    for (auto& b : basins)
        tot *= b;
    
    cout << "Total risk: " << risk << endl;
    cout << "Largest basin sizes combined: " << tot << endl;
    
    return 0;
}