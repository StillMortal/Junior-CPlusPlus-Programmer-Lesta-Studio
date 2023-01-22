// Самый быстрый алгоритм сортировки - это тот, который использует
// особенности данных на имеющемся оборудовании с учетом внешних ограничений.

// Так как по условию задачи массив может быть любого размера со случайным порядком чисел,
// то подобрать один алгоритм, который быстрее всего отсортирует произвольный массив чисел,
// невозможно, потому что я могу назвать хотя бы два различных алгоритма,
// использующиеся в одних из самых популярных языков программирования, а именно:
// 1. Timsort в Python, Java, Android, 2. Introsort в C++

// Timsort использует то, что часть чисел (в данном случае) массива уже упорядочена.
// В таком случае возможно более эффективно отсортировать оставшееся.
// Если массив уже отсортирован, то Timsort отработает за линейное время от длины массива.
// В худшем случае - за O(nlogn), где n - длина массива.

// Introsort, являющийся комбинацией Quicksort, Heapsort и Insertion sort
// в среднем имеет более малую скрытую константу (в О-символике),
// но в лучшем, среднем и худшем случаях сортирует за O(nlogn), где n - длина массива.

// Потому что C++ использует Introsort в качестве сортировки по умолчанию,
// то для ответа на задачу представлена реализация Introsort.



#include <algorithm>
#include <cmath>

using namespace std;

void swapValue(int *a, int *b)
{
    int *temp = a;
    a = b;
    b = temp;
}

void InsertionSort(int arr[], int *begin, int *end)
{
    int left = begin - arr;
    int right = end - arr;

    for (int i = left+1; i <= right; i++)
    {
        int key = arr[i];
        int j = i-1;

        while (j >= left && arr[j] > key)
        {
            arr[j+1] = arr[j];
            j = j-1;
        }
        arr[j+1] = key;
    }
}

// A function to partition the array and return
// the partition point
int* Partition(int arr[], int low, int high)
{
    int pivot = arr[high]; // pivot
    int i = (low - 1); // Index of smaller element

    for (int j = low; j <= high- 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;

            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (arr + i + 1);
}

int *MedianOfThree(int * a, int * b, int * c)
{
    if (*a < *b && *b < *c)
        return (b);

    if (*a < *c && *c <= *b)
        return (c);

    if (*b <= *a && *a < *c)
        return (a);

    if (*b < *c && *c <= *a)
        return (c);

    if (*c <= *a && *a < *b)
        return (a);

    if (*c <= *b && *b <= *a)
        return (b);
}

// A Utility function to perform intro sort
void IntrosortUtil(int arr[], int * begin, int * end, int depthLimit)
{
    // Count the number of elements
    int size = end - begin;

    if (size < 16)
    {
        InsertionSort(arr, begin, end);
        return;
    }

    if (depthLimit == 0)
    {
        make_heap(begin, end+1);
        sort_heap(begin, end+1);
        return;
    }

    int * pivot = MedianOfThree(begin, begin+size/2, end);

    swapValue(pivot, end);

    int * partitionPoint = Partition(arr, begin-arr, end-arr);
    IntrosortUtil(arr, begin, partitionPoint-1, depthLimit - 1);
    IntrosortUtil(arr, partitionPoint + 1, end, depthLimit - 1);
}

void Introsort(int arr[], int *begin, int *end)
{
    int depthLimit = 2 * log(end-begin);

    IntrosortUtil(arr, begin, end, depthLimit);
}
