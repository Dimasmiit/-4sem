#include <iostream>
#include <algorithm>
#include <random>      
#include <cstring> 
using namespace std;

// Сортировка вставками
long long insertionSort(int a[], const int n) 
{
    long long cmp = 0;
    for ( size_t i = 1; i < n; ++i) 
    {
        int key = a[i];
        int j = i - 1;
        while (j >= 0) 
        {
            ++cmp;
            if (a[j] > key) 
            {
                a[j + 1] = a[j];
                --j;
            } else break;
        }
        a[j + 1] = key;
    }
    return cmp;
}

// Сортировка перебором 
long long selectionSort(int a[], const int n) 
{
    long long cmp = 0;
    for ( size_t i = 0; i < n - 1; ++i) 
    {
        int minIdx = i;
        for ( size_t j = i + 1; j < n; ++j) 
        {
            ++cmp;
            if (a[j] < a[minIdx]) 
            {
                minIdx = j;
            }
        }
        if (minIdx != i)
        {
            swap(a[i], a[minIdx]);
        } 
    }
    return cmp;
}

// Сортировка Хоара 
int partitionHoare(int a[], int lo, int hi, long long &cmp) {
    int mid = lo + (hi - lo) / 2;    
    int pivot = a[mid];

    swap(a[mid], a[hi]);

    int i = lo;                      
    for (int j = lo; j < hi; ++j) {
        ++cmp;
        if (a[j] <= pivot) {
            swap(a[i], a[j]);
            ++i;
        }
    }

    swap(a[i], a[hi]);

    return i;
}

void quickSortHoare(int a[], int lo, int hi, long long &cmp) {
    if (lo >= hi) return;

    int p = partitionHoare(a, lo, hi, cmp);

    quickSortHoare(a, lo, p - 1, cmp);
    quickSortHoare(a, p + 1, hi, cmp);   
}

// Генерация массива 
int* generateArray(const int n, const int minVal,  const int maxVal) 
{
    int* a = new int[n];
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(minVal, maxVal);
    for ( size_t i = 0; i < n; ++i)
        a[i] = dist(gen);
    return a;
}

void printArray(int a[], const int n, const int limit = 30) 
{
    if (n <= limit) 
    {
        for ( size_t i = 0; i < n; ++i) 
        cout << a[i] << " ";
        cout << "\n";
    } 
    else 
    {
        for ( size_t i = 0; i < limit; ++i) cout << a[i] << " ";
        cout << "... (всего " << n << " элементов)\n";
    }
}

int main() 
{
    int n;
    cout << "Введите количество элементов n: ";
    cin >> n;

    if (n <= 0) 
    {
        cout << "n должно быть положительным\n";
        return 1;
    }

    int minVal = -100, maxVal = 100;

    int* original = generateArray(n, minVal, maxVal);

    int* work = new int[n];

    cout << "\nИсходный массив: ";
    printArray(original, n);

    memcpy(work, original, n * sizeof(int));
    long long cmpInsertion = insertionSort(work, n);

    memcpy(work, original, n * sizeof(int));
    long long cmpSelection = selectionSort(work, n);

    memcpy(work, original, n * sizeof(int));
    long long cmpQuick = 0;
    quickSortHoare(work, 0, n - 1, cmpQuick);

    cout << "\nОтсортированный массив: ";
    printArray(work, n);

    cout << "Вставками:  сравнений = " << cmpInsertion;
    cout << "Перебором:  сравнений = " << cmpSelection;
    cout << "Хоара:      сравнений = " << cmpQuick;

    delete[] original;
    delete[] work;
    return 0;
}