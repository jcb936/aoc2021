#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Entry
{
    vector<string> entries{};
};

struct Keys
{
    string k1{};
    string k2{};
    string k3{};
    string k4{};

    Keys(string& str1, string& str4, string& str7, string& str8) 
    {
        k1 = str1;
        // get k2 and k3
        string tempk4 = str7;
        string tempk2 = str4;
        string tempk3 = str8;

        for (int i = 0; i < k1.size(); ++i)
        {
            tempk2.erase(remove(begin(tempk2), end(tempk2), k1[i]), end(tempk2));
            tempk4.erase(remove(begin(tempk4), end(tempk4), k1[i]), end(tempk4));
            tempk3.erase(remove(begin(tempk3), end(tempk3), k1[i]), end(tempk3));
        }

        k2 = tempk2;
        k4 = tempk4;
        // get k3
        for (int i = 0; i < k2.size(); ++i)
            tempk3.erase(remove(begin(tempk3), end(tempk3), k2[i]), end(tempk3));

        for (int i = 0; i < k4.size(); ++i)
            tempk3.erase(remove(begin(tempk3), end(tempk3), k4[i]), end(tempk3));

        k3 = tempk3;
    }
};

void get_input(vector<Entry>& ten_digits, vector<Entry>& values)
{
    while (!cin.eof())
    {
        char separator;
        Entry ten_digit{};
        Entry value{};
        for (int i = 0; i < 10; ++i)
        {
            string to_add{};
            cin >> to_add;
            ten_digit.entries.push_back(to_add);
        }
        cin >> separator;
        for (int i = 0; i < 4; ++i)
        {
            string to_add{};
            cin >> to_add;
            value.entries.push_back(to_add);
        }
        
        ten_digits.push_back(ten_digit);
        values.push_back(value);
    }
}

int is_contained(string& substr, string& str)
{
    int result{};
    for (int i = 0; i < substr.size(); ++i)
    {
        bool char_found{};
        char current_char = substr[i];
        for (int j = 0; j < str.size(); ++j)
        {
            if (current_char == str[j])
            {
                char_found = true;
                break;
            }
        }
        
        if (char_found)
            result++;
    }
    
    return result;
}

int decode5(int numK1, int numK2, int numK3)
{
    if (numK1 == 1 && numK2 == 1 && numK3 == 2)
        return 2;
    else if (numK1 == 1 && numK2 == 2 && numK3 == 1)
        return 5;
    else if (numK1 == 2 && numK2 == 1 && numK3 == 1)
        return 3;
    else
        return -1; // couldn't decode    
}

int decode6(int numK1, int numK2, int numK3)
{
    if (numK1 == 1 && numK2 == 2 && numK3 == 2)
        return 6;
    else if (numK1 == 2 && numK2 == 1 && numK3 == 2)
        return 0;
    else if (numK1 == 2 && numK2 == 2 && numK3 == 1)
        return 9;
    else
        return -1; // couldn't decode    
}

int decode(string& str, Keys& keys)
{
    // get trivial cases out
    if (str.size() == 2)
        return 1;
    else if (str.size() == 4)
        return 4;
    else if (str.size() == 3)
        return 7;
    else if (str.size() == 7)
        return 8;


    int numK1 = is_contained(keys.k1, str);
    int numK2 = is_contained(keys.k2, str);
    int numk3 = is_contained(keys.k3, str);

    return str.size() == 5 ? decode5(numK1, numK2, numk3) : decode6(numK1, numK2, numk3);
}

vector<Keys> generate_keys(vector<Entry>& digits)
{
    vector<Keys> keys{};

    for (int i = 0; i < digits.size(); ++i)
    {
        string str1{};
        string str4{};
        string str7{};
        string str8{};

        for (auto& entry : digits[i].entries)
        {
            if (entry.size() == 2)
                str1 = entry;
            else if (entry.size() == 4)
                str4 = entry;
            else if (entry.size() == 3)
                str7 = entry;
            else if (entry.size() == 7)
                str8 = entry;
        }

        keys.push_back(Keys(str1, str4, str7, str8));
    }

    return move(keys);
}

int main()
{
    vector<Entry> ten_digits{};
    vector<Entry> values{};

    get_input(ten_digits, values);

    vector<Keys> keys = generate_keys(ten_digits);
    int result{};
    
    for (int i = 0; i < values.size(); ++i)
    {
        int multiplier{1000};
        for (auto& str : values[i].entries)
        {
            int dec = decode(str, keys[i]);
                
            result += (dec * multiplier);

            multiplier /= 10;
        }
        result += temp_result;
    }
    
    cout << result << endl;
    
    return 0;
}