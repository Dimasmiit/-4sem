#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> V;
    int n;

    cout << "Input number of elements: ";
    cin >> n;

    if (n % 2 != 0) {
        cout << "Error: the number of elements must be even.\n";
        return 1;
    }

    cout << "Input " << n << " elements: ";
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        V.push_back(x);
    }

    size_t mid = V.size() / 2;           
    V.insert(V.begin() + mid, 5, 0);     
    cout << "Result: ";
    for (int val : V) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}