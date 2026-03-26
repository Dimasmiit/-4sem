#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> V;
    int n;

    cout << "Введите количество элементов (чётное число): ";
    cin >> n;

    if (n % 2 != 0) {
        cout << "Ошибка: количество элементов должно быть чётным.\n";
        return 1;
    }

    cout << "Введите " << n << " элементов: ";
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        V.push_back(x);
    }

    size_t mid = V.size() / 2;           
    V.insert(V.begin() + mid, 5, 0);     

    cout << "Результат: ";
    for (int val : V) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}