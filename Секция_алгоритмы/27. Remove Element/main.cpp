#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

/* Very simple realisation with STL library */
int removeElement1(vector<int> &nums, int val)
{
    erase(nums, val);
    return nums.size();
}

/*
    
*/
int removeElement(vector<int> &nums, int val)
{
    if(nums.size() == 0) return 0;
    
    int first = 0;
    int last = nums.size()-1;

    while(nums[last] == val && last > 0) last--;

    for(; first < last; first++)
    {
        if(nums[first] == val)
        {
            swap(nums[first], nums[last]);
            last--;
            first--;
        }
    }

    if(nums[first] != val) first++;

    return first;
    
}

int main()
{

    vector<int> nums{3,2,2,3};

    std::cout << removeElement(nums, 2) << "\n";

    for (auto it = nums.begin(); it != nums.end(); it++)
    {
        cout << *it << " ";
    }

    return 0;
}

