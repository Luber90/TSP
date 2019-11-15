#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <math.h>
#include <time.h>
#include "tsp1.h"

using namespace std;

struct dane;

int main()
{
	srand(time(NULL));
	Dane *dane;
	//Otwieramy plik, rozwijamy tablice oraz zapisujemy wierzchołki z pliku
	dane =& wczytaj("plik.txt");
	//Zachlanny
	//TSP(1, dane);
	//cout << "Dystans: " << dane->dist << endl;
	//dane->dist = 0;
	
	//Mroweczki Piotreczka
	TSP_ACO(dane, 100000);
	//show1(dane);
	system("PAUSE");
	return 0;
}

