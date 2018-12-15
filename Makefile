all: jaccard hash random bag minhash NRminhash lsh HashBag
	
jaccard:
	g++ -std=c++11 -o Jaccard.o Jaccard.cc

bag:
	g++ -std=c++11 -o bag.o jaccardBag.cc

HashBag:
	g++ -std=c++11 -o HashBag.o jaccardBagHash.cc

run_bag:
	./bag.o

hash:
	g++ -std=c++11 -o hash.o jacHash.cc

minhash:
	g++ -std=c++11 -o min.o Minhashing.cc

NRminhash:
	g++ -std=c++11 -o nrmin.o minHashNoRep.cc

lsh:
	g++ -std=c++11 -o lsh.o lsh.cc

random:
	g++ -std=c++11 -o rand.o random.cc	

run_jac:
	./Jaccard.o
	
run_hash:
	./hash.o

run_HashBag:
	./HashBag.o
	
run_rand:
	./rand.o

run_nr:
	./nrmin.o

run_min:
	./min.o

run_lsh:
	./lsh.o

clean:
	rm -f *.o