#include <iostream>
#include <vector>      
#include <algorithm>
#include <random>
using namespace std;

long long insertionSort(vector<int>& a) 
{
    long long cmp = 0;
    const int n = static_cast<int>(a.size());   
    for (int i = 1; i < n; ++i) 
    {
        const int key = a[i];

        int lo = 0, hi = i;
        while (lo < hi) 
        {
            const int mid = lo + (hi - lo) / 2;
            ++cmp;
            if (a[mid] <= key) lo = mid + 1;
            else  hi = mid;
        }

        for (int j = i - 1; j >= lo; --j)
            a[j + 1] = a[j];

        a[lo] = key;
    }
    return cmp;
}

long long selectionSort(vector<int>& a) 
{
    long long cmp = 0;
    const int n = static_cast<int>(a.size());   
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

int partitionHoare(vector<int>& a, int lo, int hi, long long &cmp) 
{
    const int mid = lo + (hi - lo) / 2;
    const int pivot = a[mid];

    {
        int tmp = a[mid];
        a[mid] = a[hi];
        a[hi] = tmp;
    }

    int i = lo;
    for (int j = lo; j < hi; ++j) 
    {
        ++cmp;
        if (a[j] <= pivot) 
        {
            int tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
            ++i;
        }
    }
    {
        int tmp = a[i];
        a[i] = a[hi];
        a[hi] = tmp;
    }

    return i;
}

void quickSortHoare(vector<int>& a, int lo, int hi, long long &cmp) 
{
    if (lo >= hi) return;

    const int p = partitionHoare(a, lo, hi, cmp);

    quickSortHoare(a, lo, p - 1, cmp);
    quickSortHoare(a, p + 1, hi, cmp);   
}


vector<int> generateArray(const int n, const int minVal, const int maxVal) 
{
    vector<int> a;
    a.reserve(n);                         
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(minVal, maxVal);
    for (int i = 0; i < n; ++i)
        a.push_back(dist(gen));            
    return a;                              
}

void printArray(const vector<int>& a, const int limit = 30) 
{
    const int n = static_cast<int>(a.size());   
    if (n <= limit) 
    {
        for (int x : a) cout << x << " ";       
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

    const int minVal = -100, maxVal = 100;

    vector<int> original = generateArray(n, minVal, maxVal);

    cout << "\nИсходный массив: ";
    printArray(original);


    vector<int> work = original;
    long long cmpInsertion = insertionSort(work);

    work = original;                       
    long long cmpSelection = selectionSort(work);

    work = original;                       
    long long cmpQuick = 0;
    quickSortHoare(work, 0, static_cast<int>(work.size()) - 1, cmpQuick);

    cout << "\nОтсортированный массив: ";
    printArray(work);

    cout << "Вставками:  сравнений = " << cmpInsertion << "\n";
    cout << "Перебором:  сравнений = " << cmpSelection << "\n";
    cout << "Хоара:      сравнений = " << cmpQuick     << "\n";

    return 0;
}