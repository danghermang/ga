#include <iostream>
#include "tsp.h"
using namespace std;

int main()
{
	int pop_size, generations, mutation_rate;
	cout << "How large would you like your population to be?"<<endl;
	cin >> pop_size;
	cout << "How many generations do you want?"<<endl;
	cin >> generations;
	cout << "What should the mutation rate be?"<<endl;
	cin >> mutation_rate;
	srand(time(NULL));
	Graph * graph = new Graph(50, 0, true);
	graph->showInfoGraph();
	
	
	Genetic genetic(graph, pop_size, generations, mutation_rate, true);

	const clock_t begin_time = clock(); 
	genetic.run();
	cout << "\n\nTime for to run the genetic algorithm: " << float(clock () - begin_time) /  CLOCKS_PER_SEC << " seconds."<<endl; 
	
	return 0;
}
