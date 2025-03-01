#include <vector>
#include <iostream>

using namespace std;

/*
    Time: O(n^2)
    Memory: O(1)
*/
int maxProfit(vector<int> &prices)
{
    int res = 0;

    for (int i = 0; i < prices.size() - 1; i++)
    {
        for (int j = i + 1; j < prices.size(); j++)
        {
            int tmp = prices[j] - prices[i];
            if (tmp > res)
            {
                res = tmp;
            }
        }
    }

    return res;
}


/*
    Time: O(n)
    Memory: O(1)

    We use dynamic programming. 

    In start we supose to buy = prices[0] and profit = 0
    and then we start iterating from 1 to n and then we we come across an element that less then buy so
    it equel condition: buy < prices[i] we assign buy = prices[i]. It gives us the opportunity maximize the sum.
    If prices[i]-buy > profit => profit = prices[i]-buy. 

    And the end we get the maximize profit  
*/
int maxProfit(vector<int> &prices)
{
    int buy = prices[0];
    int profit = 0;

    for (int i = 1; i < prices.size(); i++)
    {
        if (buy > prices[i])
            buy = prices[i];
        if ((prices[i] - buy) > profit)
            profit = prices[i] - buy;
    }

    return profit;
}

int main()
{

    return 0;
}