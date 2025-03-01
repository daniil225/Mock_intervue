#include <iostream>
#include <vector>
using namespace std;


int minSubArrayLen(int target, vector<int>& nums) {
        
    int cur_sum = 0;
    int left = 0;
    int min_len = 10000000;

    for(int right = 0; right < nums.size(); right++)
    {
        cur_sum += nums[right];
        
        while(cur_sum >= target)
        {
            if((right - left + 1) < min_len) 
            {
                min_len = right - left + 1;
            }
            
            cur_sum -= nums[left];
            left++;
        }
    }

    return min_len != 10000000 ? min_len : 0;
}

int main()
{   
    vector<int> nums = {2,3,1,2,4,3};
    int target = 7;
    
    cout << minSubArrayLen(target, nums);

    return 0;
}