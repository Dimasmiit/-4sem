#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
#include <iterator>

using namespace std;
using namespace std::placeholders;

int main() {
    int K;
    cout << "Enter const K: ";
    cin >> K;

    vector<int> all_numbers((istream_iterator<int>(cin)), istream_iterator<int>());

    if (all_numbers.size() % 2 != 0) {
        cerr << "Error: the total number of elements must be even to split into two vectors of equal size.\n";
        return 1;
    }

    size_t half = all_numbers.size() / 2;
    vector<int> V1(all_numbers.begin(), all_numbers.begin() + half);
    vector<int> V2(all_numbers.begin() + half, all_numbers.end());

    transform(V1.begin(), V1.end(),
              V2.begin(),
              V1.begin(),
              bind(plus<>(),
                   bind(multiplies<>(), _1, K),
                   _2));

    cout << "Result (V1[i]*K + V2[i]): ";
    copy(V1.begin(), V1.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    return 0;
}