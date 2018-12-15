// random_shuffle example
#include <iostream>     // std::cout
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fstream>
using namespace std;

vector<string> original;
int myrandom (int i) { return rand()%i;}

void random (vector<string> c) {
  srand ( unsigned ( time(0) + getpid()) );

  // using built-in random generator:
  random_shuffle ( c.begin(), c.end() );

  // using myrandom:
  random_shuffle ( c.begin(), c.end(), myrandom);

  // print out content:
  for (string v : c) {
    cout << v << " ";
  }
  cout << '\n';
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

int main() {
  read(original,"Docs/r0.txt");
  random(original);
}