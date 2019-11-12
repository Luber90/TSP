#ifndef TSP1_H 
#define TSP1_H
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <math.h>
#include <time.h>
#include <string.h>

using namespace std;

struct Dane {
	int** verticals, * path, vnumber;
	double** matrix, dist = 0;
	bool* visited;
};
bool isin(int n, int* tab, int r);
void gen(int n, string name);

void distance(Dane* dane);
void find_path(int v, Dane* dane, int counter);
void TSP(int v, Dane* dane);
void show(Dane dane);
Dane wczytaj(string nazwa);


#endif
