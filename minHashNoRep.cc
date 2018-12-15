#include <iostream> 
#include <list>
#include <set>
#include <ctime>
#include <vector>
#include <limits>
   
#include <algorithm>    
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

/*
	ESTRUCTURAS DE DATOS
*/

// numero de funciones hash diferentes para el MinHash
int numHashFunctions = 200; 
int numDocs;
// funcion de hash de la que derivaremos todas las demas funciones
hash<string> mainHashFunction;
// vector donde guardaremos los numeros aleatorios para crear
// las diferentes funciones de hash
vector<int> hashFunctions(numHashFunctions); 

// primer documento
vector<string> doc1;
// segundo documento
vector<string> doc2;

vector<vector<unsigned int>> signatureMatrix;

#include <unordered_set>
unordered_set<string> repe;

/*
	FUNCIONES
*/

// funcion que llena un vector de numeros aleatorios
void fillWithRandom(vector<int>& v){
	//srand ( unsigned ( time(0) + getpid()) );
	/* Seed */
  	std::random_device rd;

  	/* Random number generator */
 	std::default_random_engine generator(rd());

  	/* Distribution on which to apply the generator */
  	std::uniform_int_distribution<long long unsigned> distribution(0,0xFFFFFFFFFFFFFFFF);
	
	for (int i=0; i<v.size(); ++i) {
		v[i] = distribution(generator);	
	}
}

// funcion que lee un documento
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

// funcion para obtener el MinHash de un documento
// por muy grande que sea el documento, solo generaremos un valor
// fijo de hashes que representaran todo el contenido del documento
void GetMinHash(string palabra,int doc) {
	// para cada k-shingles, calculamos el hash del que derivaremos
	// todos los demas hashes
		unsigned int mainHash = mainHashFunction(palabra);
		
		// generamos las funciones de hash haciendo un xor de la funcion de
		// hash principal con un numero aleatorio y guardamos en minHashes
		// los menores valores que encontremos
		for (int i=0; i<numHashFunctions; i++){
			
			unsigned int hash = mainHash xor hashFunctions[i];
			if (hash < signatureMatrix[i][doc]) signatureMatrix[i][doc] = hash;
		}
}

// funcion que genera k-shingles de dimension k a partir
// de un string original
void k_shingles(int k, const vector<string>& v,int doc) {
	// para cada palabra obtenemos un string formado de esa palabra
	// y las k siguientes
  	for (int i = 0; i < v.size(); ++i) {
		if (i+k-1 < v.size()) {
		    string kshingle = v[i];
		    for (int j = 1; j < k; ++j) kshingle = kshingle +" "+ v[i+j];
		    auto it = repe.find(kshingle);
			if (it == repe.end()) {
				GetMinHash(kshingle,doc);
				repe.insert(kshingle);
			}
		}
  }
}

// funcion para obtener la similitud de Jaccard entre dos conjuntos
//Calcula la vida
void simHash(){
	int count;
	for (int j = 1; j < numDocs; ++j) {
		count = 0;
		for (int i = 0; i < numHashFunctions; ++i) {
	    	if (signatureMatrix[i][0] == signatureMatrix[i][j]) {
	    		++count;
			}
	 	}
	 	cout << "Result MinHash: r" << j << " " << (float)count / (float)numHashFunctions << endl;
	}
}

void init() {
	fillWithRandom(hashFunctions);
	numDocs = 21;
	int infinit =  numeric_limits<unsigned int>::max();
	signatureMatrix = vector<vector<unsigned int>> (numHashFunctions, vector<unsigned int>(numDocs,infinit));
}

int main(int argc, char *argv[]) {
	int k;
	if (argc == 2) k = atoi(argv[1]);
	else k = 2;
	// leemos los documentos a comparar
	auto t = 0;
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	init();
	for(int i = 0; i < numDocs; ++i) {
		string base1 = "Docs/r";
		string base2 = ".txt";
		string var = to_string(i);
		string aux = base1 + var + base2;
		read(doc2,aux);
		// obtenemos los k-shingles de los documentos
		k_shingles(k,doc2,i);
		doc2.resize(0);
		repe.clear();
	}
	// calculamos la similitud de Jaccard a partir de los minHashes
	simHash();

	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	t = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
	cout << "Total time execution: " << t/1000000.0 << " seconds" << endl;
} 
