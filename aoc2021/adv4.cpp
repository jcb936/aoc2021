// Input for bingo cards is in cin, in the format given in the puzzle input

#include <iostream>
#include <vector>

using namespace std;

class Card
{
public:
    // first row, then column
    int grid[5][5];
    bool discard{};
    
    void initialiseGrid()
    {
        for (int i = 0; i < 5; ++i)
        {
            for (int j = 0; j < 5; ++j)
            {
                int read{};
                cin >> read;
                grid[i][j] = read;
            }
        }
    }
    
    void markEntry(int entry)
    {
        for (int i = 0; i < 5; ++i)
        {
            for (int j = 0; j < 5; ++j)
            {
                if (grid[i][j] == entry)
                {
                    grid[i][j] = -1;
                }
            }
        }
    }
    
    bool checkBingo()
    {
        // checking rows
        for (int i = 0; i < 5; ++i)
        {
            for (int j = 0; j < 5; ++j)
            {
                if (grid[i][j] != -1)
                {
                    break;
                }
                else
                {
                    if (j == 4)
                    {
                        return true;
                    }
                }
            }
        }
        
        //checking columns
        for (int i = 0; i < 5; ++i)
        {
            for (int j = 0; j < 5; ++j)
            {
                if (grid[j][i] != -1)
                {
                    break;
                }
                else
                {
                    if (j == 4)
                    {
                        return true;
                    }
                }
            }
        }
        
        return false;
    }
    
    int getCardScore()
    {
        int score{};
        for (int i = 0; i < 5; ++i)
        {
            for (int j = 0; j < 5; ++j)
            {
                if (grid[i][j] != -1)
                {
                    score += grid[i][j];
                }
            }
        }
        
        return score;
    }
};

int playGame(vector<int>& entries, vector<Card>& cards)
{
    int score{-1};
    for (auto& entry : entries)
    {
        for (auto& card : cards)
        {
            if (!card.discard)
                card.markEntry(entry);
        }
        
        for (int i = 0; i < cards.size(); ++i)
        {
            if (!cards[i].discard && cards[i].checkBingo())
            {
                score = cards[i].getCardScore() * entry;
                cards[i].discard = true;
                // uncomment for puzzle1
                // return score;
            }
        }
    }
    
    return score;
}

int main()
{
    vector<int> entries{87,12,53,23,31,70,37,79,95,16,72,9,98,92,5,74,17,60
    ,96,80,75,11,73,33,3,84,81,2,97,93,59,13,77,52,69,83,51,64,48,82,7,49,20,
    8,36,66,19,0,99,41,91,78,42,40,62,63,57,39,55,47,29,50,58,34,27,43,30,35,22,
    28,4,14,26,32,10,88,46,65,90,76,38,6,71,67,44,68,86,25,21,24,56,94,18,89,61,15,1,45,54,85};
    
    vector<Card> cards{};
    
    while (!cin.eof())
    {
        Card newCard{};
        newCard.initialiseGrid();
        cards.push_back(newCard);
    }
    
    cout << playGame(entries, cards);

    return 0;
}