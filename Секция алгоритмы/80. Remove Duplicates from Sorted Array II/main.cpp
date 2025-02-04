#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

int removeDuplicates(vector<int> &nums)
{

    if (nums.size() >= 0 && nums.size() <= 2)
        return nums.size();

    int prev = nums[0];
    int insert_ptr = 1;
    int iter_ptr = 1;
    int cnt = 1;

    for (; iter_ptr < nums.size(); iter_ptr++)
    {

        if (prev == nums[iter_ptr] && cnt < 2)
        {
            nums[insert_ptr] = nums[iter_ptr];
            cnt++;
            insert_ptr++;
        }

        if (prev != nums[iter_ptr])
        {
            nums[insert_ptr] = nums[iter_ptr];
            prev = nums[insert_ptr];
            insert_ptr++;

            cnt = 1;
        }
    }

    return insert_ptr;
}

int removeDuplicates(vector<int> &nums)
{
    int k = 2;

    if (nums.size() <= 2)
        return nums.size();

    for (int i = 2; i < nums.size(); i++)
    {
        if (nums[i] != nums[k - 2])
        {
            nums[k] = nums[i];
            k++;
        }
    }

    return k;
}

int main()
{

    vector<int> nums{0, 0, 1, 1, 1, 1, 2, 3, 3};

    std::cout << removeDuplicates(nums) << std::endl;

    std::cout << "nums = [ ";
    for (auto e : nums)
    {
        std::cout << e << " ";
    }

    std::cout << "]\n";

    return 0;
}
