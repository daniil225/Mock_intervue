#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

/* 
    Time: O((n+m)log(n+m))
    Memory: O(1)
*/
void merge1(vector<int> &nums1, int m, vector<int> &nums2, int n)
{
    for (int i = m, j = 0; i < nums1.size(); i++, j++)
    {
        nums1[i] = nums2[j];
    }

    sort(nums1.begin(), nums1.end());
}

/*
    Time: O(n + m)
    Memory: O(m)
*/
void merge2(vector<int> &nums1, int m, vector<int> &nums2, int n)
{
    vector<int>nums1_copy(nums1.begin(), nums1.begin() + m);
    int i = 0;
    int j = 0;
    int ptr = 0;

    while(i < m && j < n)
    {
        if(nums1_copy[i] <= nums2[j])
        {
            nums1[ptr] = nums1_copy[i];
            i++;
            ptr++;
        }
        else
        {
            nums1[ptr] = nums2[j];
            j++;
            ptr++;
        }
    }

    while(j < n)
    {
        nums1[ptr] = nums2[j];
        ptr++;
        j++;
    }

    while(i < m)
    {
        nums1[ptr] = nums1_copy[i];
        ptr++;
        i++;
    }
    
}

/*
    Time: O(n+m)
    Memory: O(1)
*/
void merge(vector<int> &nums1, int m, vector<int> &nums2, int n)
{
    int p1 = m-1;
    int p2 = n-1;
    int ptr = m+n-1;

    while(p2 >= 0)
    {
        if(p1 >= 0 && nums1[p1] > nums2[p2])
        {
            nums1[ptr--] = nums1[p1--];
        }   
        else
        {
            nums1[ptr--] = nums2[p2--];
        } 
    }
}


int main()
{

    vector<int> num1 = {1, 2, 3,0,0,0};
    vector<int> num2 = {4, 5, 6};
    int m = 3;
    int n = 3;

    merge(num1, m, num2, n);

    cout << "num1 = [";
    for (auto it = num1.begin(); it != num1.end(); ++it)
    {
        cout << *it << " ";
    }

    cout << "]\n";

    return 0;
}