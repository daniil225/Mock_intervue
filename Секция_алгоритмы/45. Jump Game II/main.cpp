#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int jump(vector<int>& nums) {
        
        int n = nums.size();
        int jmp = 0,fareast = 0,reached = 0;

        for(int i = 0; i < n - 1; i++)
        {
            fareast = max(fareast, i + nums[i]);
            if(i == reached)
            {
                jmp++;
                reached = fareast; 
            }
        }

        return jmp;

    }
};

int main()
{
    
    return 0;
}