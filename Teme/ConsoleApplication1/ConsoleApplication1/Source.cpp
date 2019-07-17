#include<stdio.h>
#include <iostream>
#include<conio.h>

using namespace std;

int a[100][100], visited[10], n, cost = 0;

int least(int);

void get(int &n,int a[][100])

{

	int i, j;

	printf("Enter No. of Cities: ");

	cin >> n;

	printf("\nEnter Cost Matrix\n");

	for (i = 0; i < n; i++)

	{

		printf("\nEnter Elements of Row # : %d\n", i + 1);

		for (j = 0; j < n; j++)

			cin >> a[i][j];

		visited[i] = 0;

	}

	printf("\n\nThe cost list is:\n\n");

	for (i = 0; i < n; i++)

	{

		printf("\n\n");

		for (j = 0; j < n; j++)

			printf("\t%d", a[i][j]);

	}

}
void mincost(int city)

{

	int ncity;

	visited[city] = 1;

	printf("%d -->", city + 1);

	ncity = least(city);

	if (ncity == 999)

	{

		ncity = 0;//printf("hii");

		printf("%d", ncity + 1);

		cost += a[city][ncity];

		return;

	}

	mincost(ncity);

}

int least(int c)

{

	int i, nc = 999;

	int min = 999, kmin;

	for (i = 0; i<n; i++)

	{

		if ((a[c][i] != 0) && (visited[i] == 0))

			if (a[c][i] < min)

			{

				min = a[i][0] + a[c][i];

				kmin = a[c][i];

				nc = i;

			}

	}

	if (min != 999)

		cost += kmin;

	return nc;

}

void put()

{

	printf("\n\nMinimum cost:");

	printf("%d", cost);

}

int main()

{

	get(n,a);

	printf("\n\nThe Path is:\n\n");

	mincost(0);

	put();

	_getch();

	return 0;

}