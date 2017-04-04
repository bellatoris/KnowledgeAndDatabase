#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <string>
#include <exception>

#define PAGE_SIZE 100
#define MEM_SIZE 2
#define BUF_SIZE (PAGE_SIZE * MEM_SIZE)

using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::sort;
using std::stringstream;

void mad() {
    throw std::exception();
}

void sortAndWrite(int* buf, int len, int fileID) {
    sort(buf, buf + len);
    stringstream ss1, ss2;
    ss1 << "output_binary/temp_0_" << fileID;
    ss2 << "output_debug/temp_0_" << fileID;
    ofstream out(ss1.str().c_str());
    ofstream out_debug(ss2.str().c_str());
    if (!out.is_open()) {
        cout << "failed to open output file" << endl;
        cout << "make sure that the directory \"output_binary/\" exists \n" << endl;
        mad();
    }
    for (int j = 0; j < len; ++j) {
        out.write((char*)(buf + j), sizeof(int));
        out_debug << buf[j] << endl;
    }
    out.close();
    out_debug.close();
}

int pow(int n) {
    int i = 0;
    int power = 1;

    while (i < n) {
	power *= 2;
	i++;
    }

    return power;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "usage: <input>" << endl;
        return 1;
    }
    int fileID = 0;
    int* buf = new int[BUF_SIZE];
    ifstream in(argv[1]);
    if (!in.is_open()) {
        cout << "failed to open input file" << endl;
        mad();
    }

    int pos = 0;
    // Sort the input file by BUF_SIZE.
    while (in.read((char*)(buf + pos), sizeof(int))) {
         ++pos;
        if (pos == BUF_SIZE) {
            sortAndWrite(buf, BUF_SIZE, fileID);
            pos = 0;
            ++fileID;
        }
    }
    // ASSUME that the input size is always PAGE_SIZE * 2^n
    // Then, the buffer is always full
    in.close();
    delete[] buf;

    int* buf1 = new int[PAGE_SIZE];
    int* buf2 = new int[PAGE_SIZE];
    int nRun = 0;

    // ASSUME that the input size is always PAGE_SIZE * 2^n
    // Then, the number of files is always 2^n
    for (int i = fileID; i > 1; i /= 2) {
        int j = 0; // input file index
        int c = 0; // output file index
        while (j < i) {
            stringstream ss1, ss2, ss3, ss4;
            ss1 << "output_binary/temp_" << (nRun + 1) << "_" << c;
            ss2 << "output_debug/temp_" << (nRun + 1) << "_" << (c++);
            ofstream out(ss1.str().c_str());
            ofstream out_debug(ss2.str().c_str());

            // current sorted file, file size is PAGE_SIZE * 2^(nRun+1)
            ss3 << "output_binary/temp_" << nRun << "_" << (j++);
            ss4 << "output_binary/temp_" << nRun << "_" << (j++);
            ifstream in1(ss3.str().c_str());
            ifstream in2(ss4.str().c_str());

            // TODO: merge-sort and output
            // USE: in1.read((char*) (buf1 + k), sizeof(int));
            // USE: out.write((char*) &value, sizeof(int));
            // USE: out_debug << value << endl;
	    int n = PAGE_SIZE;
	    int m = PAGE_SIZE;
	    
	    for (int run = 0; run < 4 * pow(nRun) - 1; run++) {
		if (n == PAGE_SIZE) {
		    int k = 0;
		    n = 0;

		    while (k < PAGE_SIZE) {
			in1.read((char*) (buf1 + k), sizeof(int));
			k++;
		    }
		} 

		if (m == PAGE_SIZE) {
		    int k = 0;
		    m = 0;

		    while (k < PAGE_SIZE) {
			in2.read((char*) (buf2 + k), sizeof(int));
			k++;
		    }
		}

		while (n < PAGE_SIZE && m < PAGE_SIZE) {
		    int value = (buf1[n] < buf2[m]) ? buf1[n++] : buf2[m++];
		    out.write((char*) &value, sizeof(int));
		    out_debug << value << endl;
		}		
	    }

	    while (n < PAGE_SIZE) {
		int value = buf1[n++];
		out.write((char*) &value, sizeof(int));
		out_debug << value << endl;
	    }

	    while (m < PAGE_SIZE) {
		int value = buf2[m++];
		out.write((char*) &value, sizeof(int));
		out_debug << value << endl;
	    }

	    in1.close();
            in2.close();
            out.close();
            out_debug.close();
        }
        ++nRun;
    }
    delete[] buf1;
    delete[] buf2;

    return 0;
}
