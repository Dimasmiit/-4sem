#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <string>

usind namespace std;

int main() {
    int K;
  string name1, name2;

    cout << "Enter K ( > 0): ";
    cin >> K;
    cout << "Enter the name of the input file: ";
    cin >> name1;
    cout << "Enter the name of the input file: ";
    cin >> name2;

    ifstream in(name1);
    if (!in.is_open()) {
        cerr << "Mistake: couldn't open the file " << name1 << endl;
        return 1;
    }

    ofstream out(name2);
    if (!out.is_open()) {
        cerr << "Mistake: couldn't open the file " << name2 << endl;
        return 1;
    }

    istream_iterator<string> in_iter(in), end;

    ostream_iterator<string> out_iter(out, "\n");

    remove_copy_if(in_iter, end, out_iter,
                        [K](const string& word) {
                            return word.length() > static_cast<size_t>(K);
                        });

    cout << "The words are written in " << name2 << endl;
    return 0;
}