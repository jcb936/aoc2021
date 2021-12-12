#include <iostream>
#include <vector>
 
using namespace std;
 
struct Point
{
    int x{};
    int y{};
};
 
struct Line
{
    Point start{};
    Point end{};
 
    bool is_straight() const
    {
        return start.x == end.x || start.y == end.y;
    }
};
 
class Grid
{
public:
    // first row, then columns
    // y is rows, x is columns
    int grid[1000][1000];
 
    int gridSize = 1000;
 
    Grid()
    {
        for (int i{}; i < gridSize; ++i)
        {
            for (int j{}; j < gridSize; ++j)
            {
                grid[i][j] = 0;
            }
        }
    }
 
    void add_line_straight(const Line& line)
    {
        if (!line.is_straight())
            return;
        
        if (line.start.x == line.end.x)
        {
            int start{};
            int end{};
            if (line.start.y >= line.end.y)
            {
                start = line.start.y;
                end = line.end.y;
            }
            else
            {
                start = line.end.y;
                end = line.start.y;
            }
 
            for (int i = start; i >= end; --i)
            {
                grid[i][line.start.x] += 1;
            }
        }
        else // assume y1 == y2
        {
            int start{};
            int end{};
            if (line.start.x >= line.end.x)
            {
                start = line.start.x;
                end = line.end.x;
            }
            else
            {
                start = line.end.x;
                end = line.start.x;
            }
            
            for (int i = start; i >= end; --i)
            {
                grid[line.start.y][i] += 1;
            }
        }
    }
 
    void add_line_diagonal(const Line& line)
    {
        int x1 = line.start.x;
        int x2 = line.end.x;
        int y1 = line.start.y;
        int y2 = line.end.y;
        int stepX{};
        int stepY{};
 
        if (x1 > x2 && y2 > y1)
        {
            stepX = -1;
            stepY = +1;
        }
        else if (x2 > x1 && y2 > y1)
        {
            stepX = +1;
            stepY = +1;
        }
        else if (x2 > x1 && y1 > y2)
        {
            stepX = +1;
            stepY = -1;
        }
        else if (x1 > x2 && y1 > y2)
        {
            stepX = -1;
            stepY = -1;
        }
 
        int i = y1;
        int j = x1;
        while (i != y2 && j != x2)
        {
            grid[i][j] += 1;
            i += stepY;
            j += stepX;
        }
        grid[y2][x2] += 1;
    }
 
    int count_overlaps(int amount) const
    {
        int result{};
        for (int i{}; i < gridSize; ++i)
        {
            for (int j{}; j < gridSize; ++j)
            {
                if (grid[i][j] >= amount)
                    result += 1;
            }
        }
 
        return result;
    }
};
 
void get_input(vector<Line>& lines)
{
    //elaborate input
    while (!cin.eof())
    {
        int x1{}, x2{}, y1{}, y2{};
        Point start{};
        Point end{};
        char stuff{};
        cin >> x1 >> stuff >> y1 >> stuff >> stuff >> x2 >> stuff >> y2;
        start.x = x1;
        start.y = y1;
        end.x = x2;
        end.y = y2;
        Line line{};
        line.start = start;
        line.end = end;
        lines.push_back(line);
    }
}
 
int main()
{
    Grid grid{};
    vector<Line> lines{};
    get_input(lines);
 
    for (auto& line : lines)
    {
        if (line.is_straight())
        {
            grid.add_line_straight(line);
        }
        else
        {
            grid.add_line_diagonal(line);
        }
    }
 
    cout << grid.count_overlaps(2) << endl;
 
    return 0;
}