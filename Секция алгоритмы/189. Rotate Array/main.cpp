#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void rotate(vector<int>& nums, int k) 
{
    k = k % nums.size();
    std::size_t start_size = nums.size();
    nums.insert(nums.begin(), nums.end()-k, nums.end());
    nums.resize(start_size);
}   

int main()
{
    vector<int> nums{1,2,3};
    rotate(nums, 1);

    for(auto n: nums)
        cout << n << " ";

    return 0;
}