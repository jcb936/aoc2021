#include <iostream>
#include <stack>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

bool match(char& to_match, char& stack_char)
{
    return (to_match == ')' && stack_char == '(') ||
           (to_match == ']' && stack_char == '[') ||
           (to_match == '}' && stack_char == '{') ||
           (to_match == '>' && stack_char == '<');
}

uint64_t compute_score(char& ch)
{
    switch (ch)
    {
        case ']':
            return 57;
        case ')':
            return 3;
        case '}':
            return 1197;
        case '>':
            return 25137;
    }
    return 0;
}

uint64_t compute_score_p2(stack<char>& matcher)
{
    uint64_t score{};
    while (!matcher.empty())
    {
        score *= 5;
        char ch = matcher.top();
        matcher.pop();
        switch (ch)
        {
            case '[':
                score += 2;
                break;
            case '(':
                score += 1;
                break;
            case '{':
                score += 3;
                break;
            case '<':
                score += 4;
                break;
        }
    }
    
    return score;
}

int main()
{
    stack<char> matcher{};
    string line{};
    uint64_t score_puzzle1{};
    vector<uint64_t> scores_p2{};
    
    while (getline(cin, line))
    {
        for (size_t i{}; i < line.size(); ++i)
        {
            char& to_match = line[i];
            if (to_match == '(' || to_match == '[' || to_match == '{' || to_match == '<')
            {
                matcher.push(to_match);
            }
            else if (match(to_match, matcher.top()))
            {
                matcher.pop();
            }
            else
            {
                score_puzzle1 += compute_score(to_match);
                matcher = stack<char>{};
                break;
            }
        }
        
        if (!matcher.empty())
        {
            // the function also resets the stack
            scores_p2.push_back(compute_score_p2(matcher));
        }
    }
    
    sort(begin(scores_p2), end(scores_p2));
    
    cout << "Puzzle 1 :" << score_puzzle1 << endl;
    cout << "Puzzle 2 :" << scores_p2[floor(scores_p2.size() / 2.f)] << endl;

    return 0;
}