#include <iostream>
#include <stdio.h>
#include <cstring>
#include <time.h>

#include "data_structure.h"

#define ARRAY_LEN  (20)

#define INT_SWAP(a, b) \
    do { \
        int x = (a); \
        (a) = (b); \
        (b) = x; \
    }while(0)


void bubble_sort(int un_sorted_array[], int array_len)
{
    int cur, tmp, other;

    for (cur = 0; cur < array_len; ++cur)
    {
        for(other = array_len - 1; other > cur; other--)
        {
            if(un_sorted_array[other] < un_sorted_array[other - 1])
            {
                tmp = un_sorted_array[other];
                un_sorted_array[other] = un_sorted_array[other - 1];
                un_sorted_array[other - 1] = tmp;
            }
        }
    }
}

void bubble_sort_2(int arr[], int len)
{
    int i, j;
    int temp;
    for (i = 0; i < len - 1; i++)
        for (j = 0; j < len - 1 - i; j++)
        if (arr[j] > arr[j + 1])
        {
            temp = arr[j];
            arr[j] = arr[j + 1];
            arr[j + 1] = temp;
        }
}

void bubble_sort_3(int A[], int array_len)
{
    bool sorted = false;
    while ((sorted = !sorted))
    {
//        sorted = true;
        for (int i = 1; i < array_len; i++)
        {
            if(A[i - 1] > A[i])
            {
                INT_SWAP(A[i - 1], A[i]);
            }
            sorted = false;
        }
        array_len--;
    }
}

void bubble_sort_4(int A[], int array_len)
{
    for(bool sorted = false; (sorted = !sorted); array_len--)
    {
        for(int i = 1; i < array_len; i++)
        {
            if(A[i -1] > A[i])
            {
                INT_SWAP(A[i - 1], A[i]);
                sorted = false;
            }
        }
    }
}

int main()
{
//    Bitmap *bitmap = new Bitmap();
//    bitmap->set(10);
//    bitmap->set(20);
    char a[50];
    memset(a, 0xcc, 50);
    std::cout << a << std::endl;
//    std::cout << "The " << 20 << " bit is " << bitmap->check(20) << std::endl;

//    bitmap->clear(10);

//    std::cout << "The " << 10 << " bit is " << bitmap->check(10) << std::endl;
//    std::cout << "The " << 20 << " bit is " << bitmap->check(20) << std::endl;

//    delete bitmap;
    return 0;
}
