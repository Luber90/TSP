#include "tsp1.h"
#include<chrono>
#include <random>
#include <array>
#include<windows.h>
#include <limits>
using namespace std;

const int LICZBA = 52;

int Probability_ACO(int v, Dane* dane, double alpha, double betha)
{
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	int i, counter1 = 0, counter2 = 0, last;
	double acu=0.0,mianownik=0.0, distance, alfa = alpha, beta = betha, licznik;
	default_random_engine generator(seed);
	array<double, LICZBA> ar;
	int tabi[52] = { 0 };
	//liczymy mianownik
	for (i = 0; i < dane->vnumber; i++)
	{
		if (dane->visited[i] == 0)
		{

			distance = 1 / dane->matrix[v][i];
			mianownik += pow(dane->pheromone_tab[v][i], alfa) * pow(distance, beta);
		}
	}

	//liczymy prawdopodobienstwa
	for (i = 0; i < dane->vnumber; i++){

		if (dane->visited[i] == 0)
		{
			//jak ze wzoru
			distance = 1 / dane->matrix[v][i];
			licznik = pow(dane->pheromone_tab[v][i], alfa) * pow(distance, beta);
			if (licznik == 0) {
				
				tabi[counter2++] = i;
			}
			ar[i] = licznik;
			last = i;
		}
		else {
			ar[i] = 0;
			counter1++;
		}
		
	}
	if (counter1 == 51) {
		return last;
	}
	if (counter1 + counter2 == dane->vnumber) {
		for (i = 0; i < counter2; i++) {
			ar[tabi[i]] = dane->matrix[v][tabi[i]];
		}

	}
	discrete_distribution<int> distribution(ar.begin(), ar.end());
	int zzz = distribution(generator);
	return zzz;
}


void Pheromone_ACO(Dane* dane)
{
	int i, j;
	double reduction = 0.94, pheromone_change = 10000 / dane->dist;
	
	for (i = 0; i < dane->vnumber - 1; i++)
	{
		for (j = i+1; j < dane->vnumber; j++)
		{
			dane->pheromone_tab[i][j] = reduction * dane->pheromone_tab[i][j];
			dane->pheromone_tab[j][i] = reduction * dane->pheromone_tab[j][i];
		}
	}


	for (i = 0; i < dane->vnumber; i++)
	{
		//jak ze wzoru
		if (i < dane->vnumber - 1)
		{
			dane->pheromone_tab[dane->path[i]][dane->path[i + 1]] += pheromone_change;
			dane->pheromone_tab[dane->path[i + 1]][dane->path[i]] += pheromone_change;
			//cout << "dystans: " << dist << endl;
			//cout << "wierzcholek: " << i << endl;
		}
		else
		{

			//tutaj laczymy ostatni z pierwszym ale nie wiem czy to dobrze
			dane->pheromone_tab[dane->path[i]][dane->path[0]] +=  pheromone_change;
			dane->pheromone_tab[dane->path[0]][dane->path[i]] +=  pheromone_change;
			//cout << "dystans: " << dane->dist << endl;
		}
	}
}

void find_path_ACO(int v, int counter, Dane* dane, double alpha, double betha)
{
	int next;
	//cout << "Wierzcholek: "<< v << endl;
	dane->visited[v] = 1;
	dane->path[counter++] = v;

	//next = (funkcja na wybor nastepnego wierzcholka - prawdopodobienstwo)
	



	if (counter < dane->vnumber)
	{
		next = Probability_ACO(v, dane, alpha, betha);
		dane->dist += dane->matrix[v][next];
		find_path_ACO(next, counter, dane, alpha, betha);
	}
	else
		return;
}


void show1(Dane* dane)
{
	int i, j;
	for (i = 0; i < dane->vnumber; i++)
	{
		for (j = 0; j < dane->vnumber; j++)
		{
			cout << dane->pheromone_tab[i][j] << " ";
		}
		cout << endl;
	}
}

void TSP_ACO(Dane* dane, int ile, double alpha, double betha)
{
	int j, i, v, * minitab = new int[dane->vnumber];
	double mini = 999999999;
	

	//robimy to dla kilku mrowek, stad petla
	for (j = 0; j <ile; j++)
	{
		//zerowanie odwiedzonych
		for (i = 0; i < dane->vnumber; i++)
			dane->visited[i] = 0;

		//v = rand() % (dane->vnumber) ;
		v = 0;
		//cout << v << endl;
		find_path_ACO(v, 0, dane, alpha, betha);
		dane->dist += dane->matrix[v][dane->path[dane->vnumber-1]];

		if (dane->dist < mini) {
			mini = dane->dist;
			for (int q = 0; q < dane->vnumber; q++) {
				minitab[q] = dane->path[q];
			}
		}
		//(funcja na dodanie feromonow na podstawie path)
		Pheromone_ACO(dane);
		//Sprawdzanie poprawnosci
		/*
		for (int m = 0; m < dane->vnumber; m++) {
			if (!(isin(m, dane->path, dane->vnumber))) {
				cout << "blad "<< m <<"  "<< j << endl;
				for (int z = 0; z < dane->vnumber; z++) {
					cout << dane->path[z] << " ";

				}
				cout << endl;
			}
		}*/
		//show1(dane);

		if (j < ile-1)
			dane->dist = 0;
		
	}
	
	for (int z = 0; z < dane->vnumber; z++) {
		cout << minitab[z] << " ";

	}
	cout << endl << mini << endl;
	 //zerowanie odwiedzonych
	for (i = 0; i < dane->vnumber; i++)
		dane->visited[i] = 0;
}