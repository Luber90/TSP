#include "tsp1.h"

using namespace std;



int Probability_ACO(int v, Dane* dane)
{
	int i, next, counter = 0, random_number, actual = -1;
	double numbers, distance, alfa = 2, beta = 3, probability, licznik, mianownik = 0, probability_tab[15000] = { 0 };

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
	for (i = 0; i <= dane->vnumber; i++)
	{
		if (dane->visited[i] == 0)
		{
			//jak ze wzoru
			distance = 1 / dane->matrix[v][i];
			licznik = pow(dane->pheromone_tab[v][i], alfa) * pow(distance, beta);
			probability = licznik / mianownik;
			probability = round(probability * 100.0) / 100.0;
			numbers = probability * 10000.0;
			//cout <<"numbers: " << numbers << endl;
			while (counter < numbers)
			{
				probability_tab[actual + 1 + counter++] = i;
			}
			actual += counter;
			counter = 0;
		}
	}
	//losowanko ale nie wiem czy dobrze odmierzylem zeby robilo akurat 100 miejsc - do zweryfikowania
	random_number = rand() % actual;
	//cout << "random: "<< random_number<< " " <<probability_tab[random_number] << endl;
	return probability_tab[random_number];
}


void Pheromone_ACO(Dane* dane)
{
	int i, j;
	double reduction = 0.92, pheromone_change = 10000 / dane->dist;
	
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

void find_path_ACO(int v, int counter, Dane* dane)
{
	int next;
	//cout << "Wierzcholek: "<< v << endl;
	dane->visited[v] = 1;
	dane->path[counter++] = v;

	//next = (funkcja na wybor nastepnego wierzcholka - prawdopodobienstwo)
	next = Probability_ACO(v, dane);



	if (counter < dane->vnumber)
	{
		dane->dist += dane->matrix[v][next];
		find_path_ACO(next, counter, dane);
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

void TSP_ACO(Dane* dane, int ile)
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
		find_path_ACO(v, 0, dane);
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
				cout << "blad" << j << endl;
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

	/*
	double suma = 0;
	double min = 0;
	int current = 0;
	double dystans=0;
	
	// zerowanie odwiedzonych
	for (i = 0; i < dane->vnumber; i++)
		dane->visited[i] = 0;

	// WYbieramy najkrotsza scie¿ke tylko wed³ug feromonow

	dane->path[0] = 0;
	dane->visited[0] = 1;

	for (i = 1; i < dane->vnumber; i++)
	{
		
		for (j = 0; j < dane->vnumber; j++)
		{
			if (dane->visited[j]==0)
			{
				if (dane->pheromone_tab[current][j] > min)
				{
					min = dane->pheromone_tab[current][j];
					dane->path[i] = j;

				}
			}
		}

		dane->visited[dane->path[i]] = 1;
		dystans += dane->matrix[current][dane->path[i]];
		current = dane->path[i];
		min = 0;
	}
	
	dystans += dane->matrix[0][dane->path[dane->vnumber-1]];

	// tutaj printujemy odleglosc ostatniej wykonanej sciezki na podstawie feromonow i odleglosci

	for (j = 0; j < dane->vnumber-1; j++)
	{
		//cout << dane->path[j] + 1 << " - "<< dane->path[j+1] +1 << " dystans:    "<< dane->matrix[j][j+1] << " ";
		//suma += dane->matrix[dane->path[j]][dane->path[j + 1]];

		//cout << "wierzcholek: " << dane->path[j] + 1 << endl;
	}

	//cout <<"wierzcholek: "<< dane->path[0] + 1 << endl;
	//cout << dystans<< " "<< dane->dist << endl;
	//show1(dane);
	*/
}