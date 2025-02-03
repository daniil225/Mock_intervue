#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

int removeDuplicates(vector<int> &nums)
{
    if (nums.size() == 0)
        return 0;
    if (nums.size() == 1)
        return 1;

    int prev = nums[0];
    int insert_ptr = 1;
    int iter_ptr = 1;

    for (; iter_ptr < nums.size(); iter_ptr++)
    {
        if (prev != nums[iter_ptr])
        {
            nums[insert_ptr] = nums[iter_ptr];
            prev = nums[insert_ptr];
            insert_ptr++;
        }
    }

    return insert_ptr;
}

int removeDuplicates(vector<int> &nums)
{
    //distance - вернет расстояние между итераторами
    // unique(nums.begin(), nums.end()) - идалит последовательно идущие дубликаты. 
                                        //Для отсортированного массива перетасует его так, что бы вначале шли уникальные элементы
    // Сама функция возвращает итератор на последний элемент, который уже как бы не нужен (начинаются дубликаты)
    // Если хочется обчикрыжить массива, то это можно сделать так: nums.erase(last, nums.end());
    return distance(nums.begin(), unique(nums.begin(), nums.end()));
}

int main()
{
    vector<int> nums{0,0,1,1,1,2,2,3,3,4};

    std::cout << distance(nums.begin(), unique(nums.begin(), nums.end())) << "\n";
   
    //auto last = unique(nums.begin(), nums.end());
    
    
    //nums.erase(last, nums.end());

    for(int i = 0; i < nums.size(); i++)
        cout << nums[i] << " ";


    return 0;
}