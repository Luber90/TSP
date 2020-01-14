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
	int i=1, j=1;
	for (i; i <= 2; i++)
	{
		for (j; j <= 4; j++)
		{
			cout << "alfa " << i << "beta" << j << endl;
			TSP_ACO(dane, 20000, i, j);
			for (int k = 0; k < dane->vnumber; k++)
			{
				for (int d = 0; d < dane->vnumber; d++)
				{
					dane->pheromone_tab[k][d] = 2;
				}
			}
		}
	}
}

int main()
{
	srand(time(NULL));
	Dane *dane;
	//Otwieramy plik, rozwijamy tablice oraz zapisujemy wierzchołki z pliku
	dane =& wczytaj("att48.txt");
	//Zachlanny
	//TSP(1, dane);
	//cout << "Dystans: " << dane->dist << endl;
	//dane->dist = 0;
	//bestalpha(dane);
	//Mroweczki Piotreczka
	TSP_ACO(dane, 30000, 1.025, 1);
	//show1(dane);
	system("PAUSE");
	return 0;
}

