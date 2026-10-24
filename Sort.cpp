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
            else hi = mid;
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

vector<int> partitionHoare(vector<int>& a, const size_t n, vector<int>& result, long long& cmp)
{
    if (n == 0) return result;

    int refElIndex = (n - 1) / 2;
    int refEl = a[refElIndex];
    int i = 0;
    int nLeft = 0;
    int nRight = 0;
    vector<int> leftArr;
    vector<int> rightArr;
    do
    {
        if (i == refElIndex)
        {
            i++;
            continue;
        }
        ++cmp;
        if (a[i] <= refEl)
        {
            leftArr.push_back(a[i]);
            nLeft++;
        }
        else
        {
            rightArr.push_back(a[i]);
            nRight++;
        }
        i++;
    } while (i < static_cast<int>(n));

    if (nLeft > 1)
    {
        partitionHoare(leftArr, nLeft, result, cmp);
    }
    else if (nLeft == 1)
    {
        result.push_back(leftArr[nLeft - 1]);
    }
    result.push_back(refEl);
    if (nRight > 1)
    {
        partitionHoare(rightArr, nRight, result, cmp);
    }
    else if (nRight == 1)
    {
        result.push_back(rightArr[nRight - 1]);
    }
    return result;
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
    setlocale(LC_ALL, "Russian");

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
    vector<int> result;
    long long cmpQuick = 0;
    partitionHoare(work, work.size(), result, cmpQuick);
    

    cout << "\nОтсортированный массив: ";
    printArray(result);

    cout << "\nКоличество сравнений:\n";
    cout << "Вставками: " << cmpInsertion << "\n";
    cout << "Перебором: " << cmpSelection << "\n";
    cout << "Хоара: " << cmpQuick << "\n";

    return 0;
}