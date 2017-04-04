#include <iostream>
#include <fstream>
#include <cstdlib>

#define PAGE_SIZE 100
#define RUN 3

using std::cout;
using std::endl;
using std::ofstream;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "usage: <output>" << endl;
        return 1;
    }
    int len = PAGE_SIZE << RUN;
    int range = len;
    int x;

    ofstream out(argv[1]);
    for (int i = 0; i < len; ++i) {
        x = std::rand() % range;
        cout << x << endl;
        out.write((char*) &x, sizeof(int));
    }
    out.close();

    return 0;
}
