#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

int main() {
    std::vector<int> V;

    std::copy(std::istream_iterator<int>(std::cin),
              std::istream_iterator<int>(),
              std::back_inserter(V));

    if (V.size() % 2 != 0) {
        std::cerr << "Error: the number of elements must be even.\n";
        return 1;
    }

    auto mid = V.size() / 2;

    V.insert(V.begin() + mid, 5, 0);

    std::for_each(V.begin(), V.end(), [](int x) {
        std::cout << x << ' ';
    });
    std::cout << std::endl;

    return 0;
}