#include <iostream>
#include <array>

using namespace std;
using grid = array<array<int, 10>, 10>;

void get_input(grid& gr)
{
    string line{};
    int line_number{};
    while (getline(cin, line))
    {
        for (int i{}; i < line.size(); ++i)
        {
            char cur = line[i];
            gr[line_number][i] = stoi(&cur);
        }
        
        line_number++;
    }
}

int propagate(grid& gr, int r, int c)
{
    gr[r][c] += 1;
    int flashes{};

    if (gr[r][c] > 9)
    {
        gr[r][c] = 0;
        int num_rows = gr.size();
        int num_columns = gr[0].size();
        flashes++;
    
        // move left
        if (c > 0 && gr[r][c-1] != 0)
            flashes += propagate(gr, r, c-1);
    
        // move right
        if (c < num_columns - 1 && gr[r][c+1] != 0)
            flashes += propagate(gr, r, c+1);
        
        // move up
        if (r > 0 && gr[r-1][c] != 0)
            flashes += propagate(gr, r-1, c);
        
        // move down
        if (r < num_rows - 1 && gr[r+1][c] != 0)
            flashes += propagate(gr, r+1, c);
            
        // up right
        if (c < num_columns - 1 && r > 0 && gr[r-1][c+1] != 0)
            flashes += propagate(gr, r-1, c+1);
            
        // up left
        if (c > 0 && r > 0 && gr[r-1][c-1] != 0)
            flashes += propagate(gr, r-1, c-1);
            
        // down right
        if (c < num_columns - 1 && r < num_rows - 1 && gr[r+1][c+1] != 0)
            flashes += propagate(gr, r+1, c+1);
            
        // down left
        if (c > 0 && r < num_rows - 1 && gr[r+1][c-1] != 0)
            flashes += propagate(gr, r+1, c-1);
    }

    return flashes;
}

bool tick(grid& gr, int& flashes)
{
    int total_flashes{};
    
    for (int r = 0; r < gr.size(); ++r)
        for (int c = 0; c < gr[0].size(); ++c)
            gr[r][c]++;
    
    for (int r = 0; r < gr.size(); ++r)
        for (int c = 0; c < gr[0].size(); ++c)
            if (gr[r][c] > 9)
                total_flashes += propagate(gr, r, c);
    
    flashes += total_flashes;
    
    return total_flashes == gr.size() * gr[0].size();
}

int main()
{
    grid gr{};
    get_input(gr);
    
    int flashes{};
    int first_sync_step{-1};
    int step{1};
    
    // replace for p1
    // while (step <= 100) 
    while (first_sync_step < 0)
    {
        if (tick(gr, flashes))
            first_sync_step = step;    
        
        step++;
    }
    
    cout << "Tot flashes: " << flashes << endl;
    cout << "First sync step: " << first_sync_step << endl;
    
    return 0;
}