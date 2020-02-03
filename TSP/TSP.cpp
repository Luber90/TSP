#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <math.h>
#include <time.h>
#include "tsp1.h"

using namespace std;

struct dane;

void bestalpha(Dane* dane)
{
	double i=1.4, j=1;
	
	//for (i; i <= 1.5; i = i+0.1)
	//{
		for (j; j <= 1.5; j = j +0.1)
		{
			cout << "alfa " << i << "beta" << j << endl;
			TSP_ACO(dane, 20000, j, i);
			for (int k = 0; k < dane->vnumber; k++)
			{
				for (int d = 0; d < dane->vnumber; d++)
				{
					dane->pheromone_tab[k][d] = 2;
				}
			}
		}
	//}
}

int main()
{
	srand(time(NULL));
	Dane *dane;
	//Otwieramy plik, rozwijamy tablice oraz zapisujemy wierzchołki z pliku
	dane =& wczytaj("eil51.txt");
	//Zachlanny
	TSP(1, dane);
	cout << "Dystans: " << dane->dist << endl;
	//dane->dist = 0;
	//bestalpha(dane);
	//Mroweczki Piotreczka
	TSP_ACO(dane, 50000, 1, 1);
	//show1(dane);
	system("PAUSE");
	return 0;
}

