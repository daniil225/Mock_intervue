#include <unordered_map>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

bool canConstruct(string ransomNote, string magazine)
{
    unordered_map<char, int> mag;

    for (char c : magazine)
        mag[c]++;

    for (char c : ransomNote)
    {
        mag[c]--;
        if (mag[c] < 0)
            return false;
    }

    return true;
}



int main()
{

}