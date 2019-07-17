#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <cmath>
#include <time.h>
using namespace std;
int a[100][100], visited[100], n, cost = 0;
int least(int);

double calcdist(int x1, int x2, int y1, int y2){
	return sqrt(pow(x1 - y1, 2) + pow(x2 - y2, 2));
}

void get(int a[][100]){
	int i, j, k;
	int coordList[100][2];

	//Open file
	fstream myfile;
	myfile.open("att48.tsp");

	//Get cost matrix
	if(myfile.is_open()){
		//Get nr of cities
		myfile >> n;
		cout << "N is :" << n << endl;
		
		//Get coord list
		do {
			myfile >> i;
			i--;
			myfile >> coordList[i][0];
			myfile >> coordList[i][1];
		} while (i != n - 1);

		myfile.close();

		//Cost matix
		for (i = 0; i < n; i++){
			for (j = 0; j < n; j++) {
				a[i][j] = calcdist(coordList[i][0], coordList[i][1], coordList[j][0], coordList[j][1]);
			}
			visited[i] = 0;
		}
	}
}

void mincost(int city){
	int ncity;
	visited[city] = 1;
	printf("%d --> ", city + 1);
	ncity = least(city);
	if (ncity == 999999){
		ncity = 0;
		printf("%d", ncity + 1);
		cost += a[city][ncity];
		return;
	}
	mincost(ncity);
}

int least(int city){
	int i, nc = 999999;
	int min = 999999, kmin;
	for (i = 0; i < n; i++){
		if((a[city][i] != 0) && (visited[i] == 0))
			if (a[city][i] < min){
				min = a[i][0] + a[city][i];
				kmin = a[city][i];
				nc = i;
			}
	}
	if (min != 999999)
		cost += kmin;
	return nc;
}

int main(){
	//Calc cost matrix
	get(a);
	const clock_t begin_time = clock();
	//Get path
	printf("\nThe Path is:\n");
	mincost(0);
	
	printf("\n\nMinimum cost: %d\n", cost);
	cout << "\n\nTime for to run the heuristic algorithm: " << float(clock() - begin_time) / CLOCKS_PER_SEC << " seconds." << endl;
	return 0;
}