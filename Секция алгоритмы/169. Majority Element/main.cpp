#include <vector>
#include <iostream>
#include <unordered_map>
#include <algorithm>

using namespace std;


/*
    majorityElement - это такой элемент, который встречается в массиве >= int(nums.size()/2)
    Alghorithm use HashTable. 
    Time: O(n)
    Memory: O(n)
*/
int majorityElement(vector<int>& nums) 
{
    unordered_map<int, int> cnt_elem;

    for(int n: nums)
        cnt_elem[n]++;

    return std::max_element(cnt_elem.begin(), cnt_elem.end(), [](auto& p1, auto& p2){ return p1.second < p2.second; })->first;
}

/*
    Use idea from leatcode
    We can select element (for example first element). And start iteration in array. 
    If nums[i] == element => cnt++ 
    else cnt--;

    if cnt == 0 we change the element. Iteratin in array we get majority element
*/
int majorityElement(vector<int>& nums) 
{
    int element = 0;
    int count = 0;

    for(std::size_t i = 0; i < nums.size(); i++)
    {
        if(count == 0)
        {
            element = nums[i];
            count = 1;
        }
        else if(element == nums[i])
        {
            count++;
        }
        else
        {
            count--;
        }
    }

    return element;
}

int main()
{
    vector<int> nums{2,2,1,1,1,2,2};

    majorityElement(nums);


    return 0;
}