#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void rotate(vector<int> &nums, int k)
{
    k = k % nums.size();
    std::size_t start_size = nums.size();
    nums.insert(nums.begin(), nums.end() - k, nums.end());
    nums.resize(start_size);
}

/*
    Time: O(N)
    Memory: O(K)
*/
void rotate(vector<int> &nums, int k)
{

    if (nums.size() <= 1)
        return;
    k = k % nums.size();

    vector<int> last{nums.end() - k, nums.end()};

    for (int i = nums.size() - 1; i >= k; i--)
    {
        nums[i] = nums[i - k];
    }

    for (int i = 0; i < k; i++)
    {
        nums[i] = last[i];
    }
}


/*
    Time: O(n)
    Memory: O(1)
*/
class Solution {

private:
    void reverse(vector<int>& nums, int left, int right)
    {
        while(left < right)
        {
            swap(nums[left], nums[right]);
            left++;
            right--;
        }
    }
public:
    void rotate(vector<int>& nums, int k) {
        
        if(nums.size() <= 1) return;
        k = k % nums.size();

        reverse(nums, 0, nums.size()-1);
        reverse(nums, 0, k-1);
        reverse(nums, k, nums.size()-1);

    }
};


int main()
{
    vector<int> nums{1, 2, 3};
    rotate(nums, 1);

    for (auto n : nums)
        cout << n << " ";

    return 0;
}