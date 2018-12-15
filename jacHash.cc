#include <iostream>     
#include <algorithm>    
#include <vector> 
#include <set>
#include <ctime>        
#include <cstdlib>      
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fstream>
#include <string>
#include <functional>
#include <chrono>
#include <time.h>  
using namespace std;
using namespace std::chrono;

vector<string> original;
vector<string> d1;
set<unsigned int> so;
set<unsigned int> s1;
int numDocs;

/*
 * Pel primer comparem paraules o hashes? Paraules
 */
double jaccardSimilarity(/*algo*/) {
  double cont = 0;
  for (auto i : so) {
    for (auto j : s1) {
	if (i == j) {
		++cont;
		break; // en un set no hi ha iguals
	} else if (j > i) break;
    }
  }
  double tot = so.size()+s1.size() - cont;
  return (cont/tot);
}

void read(vector<string>& v, string nom) {
	ifstream file;
	file.open(nom);
	int i = 0;
	if (!file.is_open()) return;
	string word;
	while(file >> word) {
		v.push_back(word);
	}
	file.close();
}

unsigned int hashCode(string s) {
    hash<string> h;
    return h(s);
}

set<unsigned int> k_shingles(int k,const vector<string>& v) {
	set<unsigned int> s;
  for (int i = 0; i < v.size(); ++i) {
		if (i+k-1 < v.size()) {
		    string n = v[i];
		    for (int j = 1; j < k; ++j) n = n+" "+v[i+j];
		    s.insert(hashCode(n));
		}
  }
  return s;
}

int main(int argc, char *argv[]) {
	int k;
	if (argc == 2) k = atoi(argv[1]);
	else k = 2;
	read(original,"Docs/r0.txt");
	auto t = 0;
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	numDocs = 21;
	so = k_shingles(k,original);
	for(int i = 1; i < numDocs ; ++i) {
		string base1 = "Docs/r";
		string base2 = ".txt";
		string var = to_string(i);
		string aux = base1 + var + base2;
		read(d1,aux);
		s1 = k_shingles(k,d1);
		cout << "Result: r" << var << " " << jaccardSimilarity() << endl;
		d1.resize(0);
		s1.clear();
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	t = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
	cout << "Total time execution: " << t/1000000.0 << " seconds" << endl;
}