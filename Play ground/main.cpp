#include <iostream>
#include <vector>
#include <list>
#include <random>
#include <ctime>
#include <windows.h> // to use windows time


//helper function used in quicksort
template<typename Comparator>
void insertionSort(std::vector<Comparator> & a, int left, int right)
{
    for(auto i = left; i != right; i++)
    {
        //begin with the last element
        auto j = i-1;
        // record the value needed to insert
        auto key = std::move( a[ i ] );
        /* Move the top (i-1)th elements, that are greater/less
         * than key, to one position ahead of their current position */
        while(j >= left && key < a[ j - 1])
        {
            a[j+1] = std::move(a[ j ]);
            // move to the previous element
            --j;
        }
        // insert the key to correct position
        a[j+1] = std::move(key);
    }
}

/* Creat three containers, "smaller" for elements smaller than the pivot
 * "same" for values equal to the pivot and "bigger" for values larger than the pivot.
 * Recursively sort the "smaller" and "bigger" groups, and concatenate them.
 */
template<typename T>
void naiveQuickSortList(std::list<T> & list)
{
    if(list.size() > 1)
    {
        auto pivot = list.back();

        std::list<T> smaller, same, bigger;

        for(auto &i : list)
        {
            if(i < pivot) smaller.push_back(std::move(i));
            else if(i == pivot) same.push_back(std::move(i));
            else bigger.push_back(std::move(i));
        }
        naiveQuickSortList(smaller);
        naiveQuickSortList(bigger);

        smaller.splice(smaller.end(), same);
        smaller.splice(smaller.end(), bigger);
        std::move(smaller.begin(), smaller.end(), list.begin());
    }
}

template <typename T>
void naiveQuickSortVector( std::vector<T> & vector )
{
    if( vector.size( ) > 1 )
    {
        std::vector<T> smaller;
        std::vector<T> same;
        std::vector<T> bigger;

        auto chosenItem = vector[vector.size() / 2];
        for (auto &i : vector) {
            if (i < chosenItem) smaller.push_back(std::move(i));
            else if (chosenItem < i) bigger.push_back(std::move(i));
            else same.push_back(std::move(i));
        }
        naiveQuickSortVector(smaller);
        naiveQuickSortVector(bigger);

        std::move(begin(smaller), end(smaller), begin(vector));
        std::move(begin(same), end(same), begin(vector) + smaller.size());
        std::move(begin(bigger), end(bigger), end(vector) - bigger.size());
    }
}

//Implementation of in-place swap
//Referenced from http://www.programming-algorithms.net/article/40648/In-place-swap
/**
 * In-place swap using XOR operation
 */
void xorSwap(int *a, int *b)
{
    if(a != b){
        *a ^= *b; // a = A XOR B
        *b ^= *a; // b = B XOR ( A XOR B ) = A
        *a ^= *b; // a = ( A XOR B ) XOR A = B
    }
}

/**
 * In-place swap using addition and subtraction
 */
void addSwap(int *a, int *b)
{
    if(a != b){
        *a = *a + *b; // a = A+B
        *b = *a - *b; // b = A+B-B = A
        *a = *a - *b; // a = A+B-A = B
    }
}

//Implementation of quick sort
//Referenced from "Data Structures and Algorithm Analysis in C++"
/**
 * Return median of left, center, and right.
 * Order these and hide the pivot.
 * @param a is an array of Comparable items
 * @param left is the left-most index of the subarray.
 * @param right is the right-most index of the subarray.
 * @return pivot
 */
template <typename Comparable>
const Comparable & median3( std::vector<Comparable> & a, int left, int right)
{
    int center = (left + right) / 2;

    if( a[ center ] < a[ left ] )
        std::swap( a[ left ], a[ center ]);
    if( a[ right ] < a[ left ])
        std::swap(a[ left ], a[ right ]);
    if( a[ right ] < a[ center ])
        std::swap( a[ center ], a[ right ]);

    //Place pivot at position right - 1
    std::swap( a[ center ], a[ right - 1] );
    return a[right - 1];
}

/*
 * Pseudo code of quicksort:
 * if(container is not small size)
 *      find(pivot);
 *      smaller, bigger = partition(container, pivot);
 *      quicksort(smaller);
 *      quicksort(bigger);
 * else
 *     insertionSort(container)
 * endif
 */
/**
 * Internal quicksort methond that makes recursive calls.
 * Use median-of-three partitioning and a cutoff of 10.
 * @param a is an array of Comparable items
 * @param left is the left-most index of the subarray.
 * @param right is the right-most index of the subarray.
 */
template <typename Comparable>
void quicksort( std::vector<Comparable> & a, int left, int right)
{

    //For very small arrays, quick sort doesn't perform as well as insertion sort
    if (left + 10 <= right) {
        const Comparable &pivot = median3(a, left, right);

        /**begin partitioning**/
        int i = left + 1, j = right - 2;
        for (;;) {
            //move i right, skipping over elements that are smaller than the pivot.
            while (a[i++] < pivot) {}
            //move j left, skipping over elements that are larger than the pivot.
            while (pivot < a[j--]) {}

            // When i and j have stopped, i is pointing at a large element
            // and j is pointing at a small element.
            // if i is to the left of j, those elements are swapped.
            if (i < j)
                std::swap(a[i], a[j]);
                // repeat the above process until i and j cross
            else
                break;
        }
        std::swap(a[i], a[right - 1]); // restore pivot
        /**end partitioning**/
        quicksort(a, left, i - 1); // sort smaller group
        quicksort(a, i + 1, right); // sort larger group
    } else // Do an insertion sort on the small subarray
        insertionSort(a, left, right);
}

//! random initialize an array of a particular size, whose range is between MIN and MAX
template <typename T>
T initContainer(int size)
{
    T contr(size);
    std::default_random_engine e(time(NULL));
    //generate random number between 0 and 1000
    std::uniform_int_distribution<int> u(0, 100);
    for(auto i=contr.begin(); i!=contr.end(); i++)
    {
        *i = u(e);
    }
    return contr;
}

template<typename T>
std::ostream& operator << (std::ostream& o, std::vector<T> a){
    o << "[ ";
    for(auto &x : a){
        o << x  << " ";
    }
    o << " ]";
    return o;
}


int main()
{
    //initialize a vector for a particular size
    auto vector1=initContainer<std::vector<int>>(20);
    std::cout << vector1 << std::endl;
    naiveQuickSortVector(vector1);
//    quicksort(vector1, 0, vector1.size() - 1);
    std::cout << vector1 << std::endl;
    return 0;
}