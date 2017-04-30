#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <string>
#include <exception>

using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::ios;
using std::sort;

int* readAndSort(char* input, int& len) {
	ifstream in(input, ios::in | ios::binary);
	if (!in.is_open()) {
		cout << "ERROR: failed to open input file '" << input  << "'" << endl;
		return NULL;
	}
	in.read((char*) &len, sizeof(int));
	int* data = new int[len];
	in.read((char*) data, sizeof(int) * len);
	in.close();
	cout << "read " << len << endl;
	sort(data, data + len);
	return data;
}

void smj(int* dataR, int lenR, int* dataS, int lenS, char* output) {
	ofstream out(output, ios::out | ios::binary);
	// TODO: IMPLEMENT HERE
	// ex) out.write((char*) (dataR + i), sizeof(int));
	// ex) out.write((char*) (dataS + j), sizeof(int));
	int i = 0;
	int j = 0;
	int k = 0;
	while (i < lenR && k < lenS) {
	    while (dataR[i] < dataS[k]) {
		i++;
	    }
	    while (dataR[i] > dataS[k]) {
		k++;
	    }
	    j = k;
	    while (dataR[i] == dataS[k]) {
		j = k;
		while (dataS[j] == dataR[i]) {
		    out.write((char*) (dataR + i), sizeof(int));
		    out.write((char*) (dataS + j), sizeof(int));
		    cout << dataR[i] << " " << dataS[j] << endl;
		    j++;
		}
		i++;
	    }
	    k = j;
	}
	out.close();
}

void sortMergeJoin(char* tableR, char* tableS, char* output) {
	int lenR, lenS;
	int* dataR = readAndSort(tableR, lenR);
	if (NULL == dataR) return;
	int* dataS = readAndSort(tableS, lenS);
	if (NULL == dataS) return;
	smj(dataR, lenR, dataS, lenS, output);
	delete[] dataR;
	delete[] dataS;
}

int main(int argc, char* argv[]) {
	if (argc != 4) {
		cout << "usage: <R> <S> <output>" << endl;
		return 1;
	}
	sortMergeJoin(argv[1], argv[2], argv[3]);
	return 0;
}

