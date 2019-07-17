#ifndef TSP_H
#define TSP_H

#include <vector>
#include <map>
#include <set>
#include <utility>
#include <time.h>
#include <stdlib.h>


class Graph
{
private:
	int V;
	int total_edges;
	int initial_vertex;
	std::map<std::pair<int, int>, int> map_edges;
public:
	Graph(int V, int initial_vertex, bool random_graph = false); 
	void addEdge(int v1, int v2, int weight); 
	void showGraph(); 
	void generatesGraph(); // generates a random graph
	void showInfoGraph();
	int existsEdge(int src, int dest); 
	friend class Genetic; // so we can acces the private elements
};

typedef std::pair<std::vector<int>, int> my_pair;


// sort vector with pair
struct sort_pred
{
	bool operator()(const my_pair& firstElem, const my_pair& secondElem)
	{
		return firstElem.second < secondElem.second;
	}
};

class Genetic
{
private:
	Graph* graph;
	std::vector< my_pair > population; // each element is a pair: vector and total cost
	int size_population; 
	int real_size_population; 
	int generations; 
	int mutation_rate; 
	bool show_population;
private:
	void initialPopulation(); 
public:
	Genetic(Graph* graph, int amount_population, int generations, int mutation_rate, bool show_population = true);
	int isValidSolution(std::vector<int>& solution); 
	void showPopulation(); 
	void crossOver(std::vector<int>& parent1, std::vector<int>& parent2); 
	void insertBinarySearch(std::vector<int>& child, int total_cost);
	void run();
	int getCostBestSolution();
	bool existsChromosome(const std::vector<int> & v);
};

#endif
