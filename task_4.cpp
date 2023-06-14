#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <ctype.h>
#include <algorithm>
using namespace std;



int main() {
	ifstream fin("input.txt");
	map<string, int> dictionary;
	string x, word;
	int N = 0;
	int max, min;
	while (fin >> x) {
		++N;
		word = "";
		for (size_t i = 0; i < x.length(); ++i) {
			if (isalpha(x[i])) {
				word += x[i];
			}
		}
        std::transform(word.begin(), word.end(), word.begin(), ::toupper);
		pair<map<string, int>::iterator, bool> res = dictionary.insert({ word, 1 });
		if (!res.second) {
			res.first->second++;
			--N;
		}

	}
	fin.close();
	ofstream fout("output.txt");   
	map<string, int>::iterator i;
    max = min = dictionary.begin()->second;
	for (i = dictionary.begin(); i != dictionary.end(); ++i) {
		if (i->second > max) {
			max = i->second;
		}
		if (i->second < min) {
			min = i->second;
		}
     }
	fout << N << " " << max<< " "<< min;
	fout.close();
	return 0;
}