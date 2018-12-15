#include <iostream>     
#include <algorithm>    
#include <vector> 
#include <map>
#include <ctime>        
#include <cstdlib>      
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fstream>
#include <string>
#include <chrono>
#include <time.h>  
using namespace std;
using namespace std::chrono;

vector<string> original;
vector<string> d1;
map<unsigned int,int> so;
map<unsigned int,int> s1;
int sizeo,size1,numDocs;


double jaccardSimilarity() {
  double cont = 0;
  for (auto i = so.begin(); i != so.end(); ++i) {
  	for (auto j = s1.begin(); j != s1.end(); ++j) {
  		if (i->first == j->first) {
  			cont += j->second * i->second;
  			break;
  		} else if (j->first > i->first) break;
    }
  }
  double tot = sizeo+size1 - cont;
  return (cont/tot);
}

void read(vector<string>& v, string nom) {
	ifstream file;
	file.open(nom);
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

map<unsigned int,int> k_shingles(int k,const vector<string>& v, int& mida) {
	map<unsigned int,int> s;
	if(k > v.size()) k = 50;
  for (int i = 0; i < v.size(); ++i) {
		if (i+k-1 < v.size()) {
		    string n = v[i];
		    for (int j = 1; j < k; ++j) n = n+" "+v[i+j];
		    unsigned int h = hashCode(n);
		    auto it = s.find(h);
			if (it == s.end()) s[h] = 1;
			else s[h]++;
			++mida;
		}
  }
  return s;
}

int main(int argc, char *argv[]) {
	int k;
	if (argc == 2) k = atoi(argv[1]);
	else k = 2;
	numDocs = 21;
	read(original,"Docs/r0.txt");
	auto t = 0;
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	so = k_shingles(k,original,sizeo);
	for(int i = 1; i < numDocs; ++i) {
		string base1 = "Docs/r";
		string base2 = ".txt";
		string var = to_string(i);
		string aux = base1 + var + base2;
		read(d1,aux);
		s1 = k_shingles(k,d1,size1);
		cout << "Result: r" << var << " " << jaccardSimilarity() << endl;
		size1 = 0;
		d1.resize(0);
		s1.clear();
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	t = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
	cout << "Total time execution: " << t/1000000.0 << " seconds" << endl;
}