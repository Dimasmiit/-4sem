#include <iostream>
#include <algorithm>
#include <random>      
using namespace std;

// Сортировка вставками
long long insertionSort(int a[], int n) 
{
    long long cmp = 0;
    for (int i = 1; i < n; ++i) 
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
long long selectionSort(int a[], int n) 
{
    long long cmp = 0;
    for (int i = 0; i < n - 1; ++i) 
    {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) 
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
int partitionHoare(int a[], int lo, int hi, long long &cmp) 
{
    int pivot = a[lo];
    int i = lo - 1, j = hi + 1;
    while (true) 
    {
        do { ++i; ++cmp; } while (a[i] < pivot);
        do { --j; ++cmp; } while (a[j] > pivot);
        if (i >= j) return j;
        swap(a[i], a[j]);
    }
}

void quickSortHoare(int a[], int lo, int hi, long long &cmp) 
{
    if (lo >= hi) return;
    int p = partitionHoare(a, lo, hi, cmp);
    quickSortHoare(a, lo, p, cmp);
    quickSortHoare(a, p + 1, hi, cmp);
}

// Генерация массива 
int* generateArray(int n, int minVal, int maxVal) 
{
    int* a = new int[n];
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(minVal, maxVal);
    for (int i = 0; i < n; ++i)
        a[i] = dist(gen);
    return a;
}

void printArray(int a[], int n, int limit = 30) 
{
    if (n <= limit) 
    {
        for (int i = 0; i < n; ++i) 
        cout << a[i] << " ";
        cout << "\n";
    } 
    else 
    {
        for (int i = 0; i < limit; ++i) cout << a[i] << " ";
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

    int* a1 = new int[n];
    int* a2 = new int[n];
    int* a3 = new int[n];
    copy(original, original + n, a1);
    copy(original, original + n, a2);
    copy(original, original + n, a3);

    cout << "\nИсходный массив: ";
    printArray(original, n);

    // Считаем время + сравнения
    long long cmpInsertion = insertionSort(a1, n);

    long long cmpSelection = selectionSort(a2, n);

    long long cmpQuick = 0;
    quickSortHoare(a3, 0, n - 1, cmpQuick);

    cout << "\nОтсортированный массив: ";
    printArray(a1, n);

    cout << "Вставками:  сравнений = " << cmpInsertion;
    cout << "Перебором:  сравнений = " << cmpSelection;
    cout << "Хоара:      сравнений = " << cmpQuick;

    delete[] original;
    delete[] a1;
    delete[] a2;
    delete[] a3;
    return 0;
}