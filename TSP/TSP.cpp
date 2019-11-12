#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <math.h>
#include <time.h>
//#include "c:\users\piotr\source\repos\tsp algorithm\tsp algorithm\generator.cpp"
//#include "C:\Users\piotr\source\repos\TSP algorithm\TSP algorithm\ACO optimalization.cpp"

using namespace std;

struct Dane {
	int** verticals, * path, vnumber;
	double** matrix, dist = 0;
	bool* visited;
};

void distance(Dane *dane)
{
	int i, j;
	double x1, x2, y1, y2;
	for (i = 0; i < dane->vnumber; i++)
	{
		for (j = i; j < dane->vnumber; j++)
		{
			if (i != j)
			{
				x1 = dane->verticals[i][0];
				y1 = dane->verticals[i][1];
				x2 = dane->verticals[j][0];
				y2 = dane->verticals[j][1];
				dane->matrix[i][j] = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
				dane->matrix[j][i] = dane->matrix[i][j];
			}
			else
			{
				dane->matrix[i][j] = 0;
			}
		}
	}
}
void find_path(int v, Dane *dane, int counter)
{
	int i, j;
	double min = 9999;
	dane->visited[v] = 1;
	dane->path[counter++] = v;
	for (j = 0; j < dane->vnumber; j++)
	{
		if (dane->matrix[v][j] < min && dane->visited[j] == 0)
		{
			min = dane->matrix[v][j];
			i = j;
		}
	}
	if (counter < dane->vnumber) {
		dane->dist += min;
		find_path(i, dane, counter);
	}
	else
		return;
}
void TSP(int v, Dane *dane)
{
	int j;
	//v = rand() % vnumber;
	v = v - 1;
	find_path(v, dane, 0);
	for (j = 0; j < dane->vnumber; j++)
	{
		dane->visited[j] = 0;
		cout << dane->path[j] + 1 << " ";
	}
	dane->dist += dane->matrix[v][dane->path[j - 1]];
	cout << dane->path[0] + 1 << endl;
}
void show(Dane dane)
{
	int i, j;
	for (i = 0; i < dane.vnumber; i++)
	{
		for (j = 0; j < dane.vnumber; j++)
		{
			cout << dane.matrix[i][j] << " ";
		}
		cout << endl;
	}
}



Dane wczytaj(string nazwa) {
	ifstream plik;
	Dane dane;
	int num;
	plik.open("plik.txt", ios::in);
	if (plik.good() == true)
	{
		//zapisujemy liczbe wierzcholkow
		plik >> dane.vnumber;

		//tablica z odleglosciami
		dane.matrix = new double* [dane.vnumber];



		//tablica z wspolrzednymi wierzcholkow
		dane.verticals = new int* [dane.vnumber];

		//tablica odwiedzonych
		dane.visited = new bool[dane.vnumber];

		//tablica sciezki
		dane.path = new int[dane.vnumber];

		for (int i = 0; i < dane.vnumber; i++)
		{
			dane.matrix[i] = new double[dane.vnumber];



			dane.verticals[i] = new int[2];

			dane.visited[i] = 0;
		}
		while (!plik.eof())
		{
			plik >> num;
			plik >> dane.verticals[num - 1][0];
			plik >> dane.verticals[num - 1][1];
		}
		plik.close();
		return dane;
	}
}

int main()
{
	srand(time(NULL));
	Dane *dane;
	//Otwieramy plik, rozwijamy tablice oraz zapisujemy wierzchołki z pliku
	dane =& wczytaj("plik.txt");
	cout << (*dane).verticals[0][1]<<endl;

	distance(dane);
	//show(vnumber);
	TSP(1, dane);
	//TSP_ACO(vnumber);
	cout << "Dystans: " << dane->dist << endl;
	system("PAUSE");
	return(0);
}

