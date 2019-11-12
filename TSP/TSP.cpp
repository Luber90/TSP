#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <math.h>
#include <time.h>
//#include "c:\users\piotr\source\repos\tsp algorithm\tsp algorithm\generator.cpp"
//#include "C:\Users\piotr\source\repos\TSP algorithm\TSP algorithm\ACO optimalization.cpp"

using namespace std;
int* path;
int** verticals;
double** matrix, dist;
bool* visited;


void distance(int vnumber)
{
	int i, j;
	double x1, x2, y1, y2;
	for (i = 0; i < vnumber; i++)
	{
		for (j = i; j < vnumber; j++)
		{
			if (i != j)
			{
				x1 = verticals[i][0];
				y1 = verticals[i][1];
				x2 = verticals[j][0];
				y2 = verticals[j][1];
				matrix[i][j] = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
				matrix[j][i] = matrix[i][j];
			}
			else
			{
				matrix[i][j] = 0;
			}
		}
	}
}
void find_path(int v, int vnumber, int counter)
{
	int i, j;
	double min = 9999;
	visited[v] = 1;
	path[counter++] = v;
	for (j = 0; j < vnumber; j++)
	{
		if (matrix[v][j] < min && visited[j] == 0)
		{
			min = matrix[v][j];
			i = j;
		}
	}
	if (counter < vnumber) {
		dist += min;
		find_path(i, vnumber, counter);
	}
	else
		return;
}
void TSP(int vnumber, int v)
{
	int j;
	//v = rand() % vnumber;
	v = v - 1;
	find_path(v, vnumber, 0);
	for (j = 0; j < vnumber; j++)
	{
		visited[j] = 0;
		cout << path[j] + 1 << " ";
	}
	dist += matrix[v][path[j - 1]];
	cout << path[0] + 1 << endl;
}
void show(int vnumber)
{
	int i, j;
	for (i = 0; i < vnumber; i++)
	{
		for (j = 0; j < vnumber; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}
int main()
{
	srand(time(NULL));
	int vnumber, i, j, null;

	//Generujemy plik
	//gen(11, "plik.txt");

	//Otwieramy plik, rozwijamy tablice oraz zapisujemy wierzchołki z pliku
	ifstream plik;
	plik.open("plik.txt", ios::in);
	if (plik.good() == true)
	{
		//zapisujemy liczbe wierzcholkow
		plik >> vnumber;

		//tablica z odleglosciami
		matrix = new double* [vnumber];



		//tablica z wspolrzednymi wierzcholkow
		verticals = new int* [vnumber];

		//tablica odwiedzonych
		visited = new bool[vnumber];

		//tablica sciezki
		path = new int[vnumber];

		for (i = 0; i < vnumber; i++)
		{
			matrix[i] = new double[vnumber];



			verticals[i] = new int[2];

			visited[i] = 0;
		}
		while (!plik.eof())
		{
			plik >> null;
			plik >> verticals[null - 1][0];
			plik >> verticals[null - 1][1];
		}
		plik.close();
	}
	distance(vnumber);
	//show(vnumber);
	TSP(vnumber, 1);
	//TSP_ACO(vnumber);
	cout << "Dystans: " << dist << endl;
	system("PAUSE");
	return(0);
}

