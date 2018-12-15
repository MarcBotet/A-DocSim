
Algorithmics in Facultat d'Informàtica de Barcelona.

Jaccard, jaccard minhash, Locality-Sensitive Hashing

Authors:

Marc Botet Colomer

Roberto Fernández Reguero

Enrique Alexandre González Sequeira


Per compilar executem la comanda "make".

Per executar:
	- Jaccard.cc 	-> make run_jac
	- jaccardBag.cc -> make run_bag
	- jaccardBagHash.cc -> make run_HashBag
	- jacHash.cc 	-> make run_hash
	- Minhashing.cc -> make run_min
	- minHashNoRep.cc -> make run_nrmin
	- lsh.cc 		-> make run_lsh

Per canviar el conjunt de dades a probar:
	Els conjunts de dades es troben a /DocsP (documents amb 50 paraules), 
	/DocsM(documents amb 350 paraules), 
	/DocsL (documents amb 10000 paraules) i 
	/Mix (documents mixtos de 50, 350 i 10000 paraules).

	Per canviar la ruta dels fitxers a comparar:
		- En la funció main():
			· On hi hagi "/DocsX", 
				canviar per "/DocsP", "/DocsM" o "DocsL" 
				segons quin conjunt de dades es vulgui provar. 

	Per canviar k, on k es la longitud dels k-shingles:
		- En la funcio main():
			· Canviar la variable k per la longitud que es vulgui provar.
