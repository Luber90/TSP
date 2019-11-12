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
	//show(vnumber);
	TSP(1, dane);
	//TSP_ACO(vnumber);
	cout << "Dystans: " << dane->dist << endl;
	system("PAUSE");
	return 0;
}

