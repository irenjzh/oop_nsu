#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <fstream>
#include <atomic>

using namespace std;

void rd(ifstream &fin, vector<string> &mas, mutex &mn) {
	string x;
	while (true) {
		lock_guard<mutex> loc(mn); 
		if (fin.peek() != EOF) {
			fin >> x;
			mas.push_back(x);
		}
		else break;
	}
}

void find_count(vector<string>& mas, string &word, atomic<int> &count, int a, int b) {
	for (int i = a; i < b; ++i) {
		if (mas[i] == word) {
			++count;
		
		}
	}
	
}

int main() {
	atomic <int> count=0;
	mutex mn;
	ifstream fin("input.txt");
	int N = 0;
	string word;
	fin >> N >> word;
	vector<string> mas;
	vector<thread> flow;
	for (int i = 0; i < N; ++i) {
		flow.emplace_back(rd, std::ref(fin), std::ref(mas), std::ref(mn));
	}
	for (int i = 0; i < flow.size(); ++i) {
		flow[i].join();
	}
	fin.close();
	flow.clear();
	int d = 0;
	int a = mas.size()/N; 
	int b = mas.size()%N;

	for (int i = 0; i < b; ++i) {
		flow.emplace_back(find_count, std::ref(mas), std::ref(word), std::ref(count), d, d + a + 1);
		d = (d + a + 1);
	}

	for (int i = b; i < N; ++i) {
		flow.emplace_back(find_count, std::ref(mas), std::ref(word), std::ref(count), d, (d + a));
		d = (d + a);
	}

	
	for (int i = 0; i < flow.size(); ++i) {
		flow[i].join();
	}
	ofstream fout("output.txt");
	fout << count;
	fout.close();
}