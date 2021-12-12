#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>
​
using namespace std;
​
int main()
{
    vector<bitset<12>> entries{};
    
    while (!cin.eof())
    {
        string readBinary{};
        cin >> readBinary;
        entries.push_back(bitset<12>(readBinary));
    }
​
    vector<bitset<12>> entries_CO2{entries};
    
    // checking bits oxygen
    for (uint j = 11; j >= 0; --j)
    {
        int numZeros{};
        int numOnes{};
        
        for (int i = 0; i < entries.size(); ++i)
        {
            if (entries[i][j])
                numOnes++;
            else
                numZeros++;
        }
        
        if (numOnes >= numZeros)
        {
            erase_if(entries, [j](bitset<12>& entry) {return !entry[j];});            
​
        }
        else
        {
            erase_if(entries, [j](bitset<12>& entry) {return entry[j];});            
        
        }
        
        if (entries.size() <= 1)
            break;
    }
    
    // checking bits co2
    for (uint j = 11; j >= 0; --j)
    {
        int numZeros{};
        int numOnes{};
        
        for (int i = 0; i < entries_CO2.size(); ++i)
        {
            if (entries_CO2[i][j])
                numOnes++;
            else
                numZeros++;
        }
        
        if (numZeros <= numOnes)
        {
            erase_if(entries_CO2, [j](bitset<12>& entry) {return entry[j];});            
​
        }
        else
        {
            erase_if(entries_CO2, [j](bitset<12>& entry) {return !entry[j];});            
        }
        
        if (entries_CO2.size() == 1)
            break;
    }
    
    ulong o2rating = entries[0].to_ulong();
    ulong co2rating = entries_CO2[0].to_ulong();
    cout << o2rating * co2rating;
    
    return 0;
}