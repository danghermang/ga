#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <time.h>
#include <algorithm>
#include <random>
#include <bitset>
#define precizie 6
#define PI 3.1415926
#define parameters 100
#define replace_locals() {if (glob_min_fitness>min_fitness) glob_min_fitness=min_fitness; if (glob_max_fitness<max_fitness) glob_max_fitness=max_fitness;if (glob_min_time>min_time) glob_min_time=min_time;if (glob_max_time<max_time) glob_max_time=max_time;}

using namespace std;
float de_jong(int n, vector<float> a)
{//-5.12,5.12
	float suma = 0;
	for (int i = 0; i<n; i++)
	{
		suma += pow(a[i], 2);
	}
	return suma;
}
float schwefel7(int n, vector<float> a)
{//-500,500
	float suma = 0;
	for (int i = 0; i<n; i++)
	{
		suma += -a[i] * (float)sin(PI*sqrt(abs(a[i])) / 100);
	}
	return suma;
}
float ackley10(int n, vector<float> x)
{//-32.768,32,678
	float a = 20, b = (float)0.2, c, rezultat_partial = 0;
	c = 2 * (float)PI;
	for (int i = 0; i<n; i++)
	{
		rezultat_partial += (float)cos(PI*c*x[i] / 100);
	}
	return (-1 * a)*exp(-b*sqrt(1 / n*de_jong(n, x))) - exp(1 / n*rezultat_partial) + a + (float)exp(1);

}
float six_hump_camel(vector<float> a)
{//-3,3 ; -2,2
	return (float)(4 - 2.1 * pow(a[0], 2) + pow(a[0], 4) / 3)*pow(a[0], 2) + a[0] * a[1] + (-4 + 4 * pow(a[1], 2))*pow(a[1], 2);
}
float rastigin(int n,vector<float> a)
{//-5.12,5.12
	float partial = 0;
	for (int i = 0; i < n; i++)
	{
		partial += pow(a[i], 2) - 10 * (float)cos(2 * PI*a[i]);
	}
	return 10 * n + partial;
}
float rosenbrock(int n, vector<float> a)
{//-2.048,2.048
	float partial = 0;
	for (int i = 0; i < n-1; i++)
	{
		partial = 100 * pow((a[i + 1] - pow(a[i], 2)), 2) + pow(1 - a[i], 2);
	}
	return partial;
}
float  griewangk(int n, vector<float> a)
{//-600,600
	float partial1 = 0, partial2 = 0;
	for (int i = 0; i < n; i++)
	{
		partial1 = pow(a[i], 2);
		partial2 = (float)cos(a[i] / sqrt(i));
	}
	return partial1 - partial2 + 1;
}
static float diffclock(clock_t clock1, clock_t clock2)
{
	double diffticks = clock2 - clock1;
	double diffms = (diffticks) / (CLOCKS_PER_SEC / 1000);
	return (float)diffms;
}

int get_int_rng(int min, int max)
{
	if (max < min)
	{
		int aux = min;
		min = max;
		max = aux;
	}
	default_random_engine generator;
	uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}

float get_flt_rng(float min, float max)
{
	if (max < min)
	{
		float aux = min;
		min = max;
		max = aux;
	}
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> distReal(min, max);

	return distReal(gen);
}
bitset<sizeof(float) * CHAR_BIT> flt_to_bitset(float nr)
{
	union
	{
		float input;
		long long  output;
	}data;
	data.input = nr;
	bitset<sizeof(float) * CHAR_BIT>   bits(data.output);
	return bits;
}

bitset<sizeof(float)*CHAR_BIT> get_bit_rng()
{
	bitset<sizeof(float)*CHAR_BIT> number;
	int bit;
	for (int i = 0; i < sizeof(float)*CHAR_BIT; i++)
	{
		bit = get_int_rng(0, 1);
		if (bit == 1)
			number.flip(i);
	}
	return number;

}
vector<bitset<sizeof(float)*CHAR_BIT> > get_bit_vector(float min, float max, int length)
{
	vector<bitset<sizeof(float)*CHAR_BIT> > thing;
	for (int i = 0; i < length; i++)
		thing.push_back(get_bit_rng());
	return thing;
}
float bit_to_float(bitset<sizeof(float)* CHAR_BIT> number, float min, float max)
{
	if (max < min)
	{
		float aux = max;
		max = min;
		min = aux;
	}
	float sum = 0, n;
	n = (max - min)*((float)pow(10, precizie));
	n = (float)ceil(log(n) / (float)log(2));
	for (int i = 0; i < sizeof(float)*CHAR_BIT; i++)
	{
		sum += number[i] * (float)pow(2, i);
	}
	sum = sum*(max - min) / ((float)pow(2, n) - 1);
	return min + sum;
}
vector<float> bit_to_float_vector(vector<bitset<sizeof(float)*CHAR_BIT> > array, float min, float max)
{
	vector<float> a;
	float aux;
	for (vector<bitset<sizeof(float)*CHAR_BIT> >::iterator j = array.begin(); j != array.end(); j++)
	{
		aux = bit_to_float(*j, min, max);
		a.push_back(aux);
	}

	return a;
}

vector<bitset<sizeof(float)*CHAR_BIT>> incrucisare(vector<bitset<sizeof(float)*CHAR_BIT>> array, int chromosome1, int chromosome2, int position)
{
	bool aux;
	for (auto it = position; it < sizeof(float)*CHAR_BIT; it++)
	{
		aux = array[chromosome1][it];
		array[chromosome1][it] = array[chromosome2][it];
		array[chromosome2][it] = aux;
	}
	return array;
}
vector<bitset<sizeof(float)*CHAR_BIT>> incrucisare_n(vector<bitset<sizeof(float)*CHAR_BIT>> array, int chromosome1, int chromosome2, int positions)
{
	for (int i = 0; i < positions; i++)
	{
		int position = get_int_rng(0, sizeof(float)*CHAR_BIT);
		array = incrucisare(array, chromosome1, chromosome2, position);
	}
	return array;
}

void change_bit(bitset<sizeof(float)*CHAR_BIT> bits, int position)
{
	bits.flip(position);
}

vector<float> get_vector(int number, float min, float max)
{
	vector<float> a;
	if (max < min)
	{
		float aux = min;
		min = max;
		max = aux;
	}
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> distReal(min, max);
	for (int i = 0; i < number; i++)
		a.push_back(round(distReal(gen) * 100) / 100);
	return a;
}

float function(vector<bitset<sizeof(float)*CHAR_BIT>> array, int choice, int parameter, float min, float max)
{
	vector<float> a = bit_to_float_vector(array, min, max);
	switch (choice)
	{
	case 1: return de_jong(parameter, a);
		break;
	case 2: return schwefel7(parameter, a);
		break;
	case 3: return ackley10(parameter, a);
		break;
	case 4: return six_hump_camel(a);
		break;
	}
	return -1;
}
float function_single(bitset<sizeof(float)*CHAR_BIT> element, int choice, float min, float max)
{
	vector<float> a;
	a.push_back(bit_to_float(element, min, max));
	a.push_back(0);
	switch (choice)
	{
	case 1: return de_jong(1, a);
		break;
	case 2: return schwefel7(1, a);
		break;
	case 3: return ackley10(1, a);
		break;
	case 4: return six_hump_camel(a);
		break;
	}
	return -1;
}
struct population {
	vector<bitset<sizeof(float)*CHAR_BIT>> array;
	float fitness;
};
 int* select(vector<bitset<sizeof(float)*CHAR_BIT>> array, int choice, int times, float min, float max)
{
	 int selected[10000],size=0;
	 float total = 0, r, eval[10000] = { 0 }, p[10000] = { 0 }, q[100000] = { 0 };
	 for (int i = 0; i < 30; i++)
	 {
		 selected[i] = 0;
	 }
	for (int i=0; i != array.size(); i++)
	{
		eval[i] = function_single(array[i], choice, min, max);
		total += eval[i];
	}
	for (int i = 0; i != array.size(); i++)
	{
		p[i] = eval[i] / total;
	}
	q[0] = 0;
	for (int i = 0; i != array.size(); i++)
	{
		q[i + 1] = q[i] + p[i];
	}
	for (int i = 0; i != array.size(); i++)
	{
		r = get_flt_rng((float)0.0001, 1);
		if (q[i] < r && r <= q[i + 1])
			selected[i]=1;
	}
	return selected;
}
vector < bitset < sizeof(float)*CHAR_BIT >> recombine(vector < bitset < sizeof(float)*CHAR_BIT >> array, int * selected)
{
	bool aux;
	int n = 0,chr;
	vector < bitset < sizeof(float)*CHAR_BIT >> cromozomi;
	for (int i = 0; i < sizeof(float)*CHAR_BIT; i++)
	{
		if (selected[i] == 0) {
			cromozomi.push_back(array[i]);
			n++;
		}
	}
	for (int i = 0; i < n; i++)
	{
		float r = get_flt_rng(0, 1);
		if (r <= 0.1)
		{
			int a = get_int_rng(1, sizeof(float)*CHAR_BIT - 2);
			do { chr = get_int_rng(0, n); } while (chr == i);
			for (int j = a; j < sizeof(float)*CHAR_BIT; j++)
			{
				aux = array[i][j];
				array[i][j] = array[chr][j];
				array[chr][j] = aux;
			}
		}
	}
	return cromozomi;
}
vector < bitset < sizeof(float)*CHAR_BIT >> mutatie(vector < bitset < sizeof(float)*CHAR_BIT >> array, int * selected)
{
	int n = 0;
	vector < bitset < sizeof(float)*CHAR_BIT >> cromozomi;
	for (int i = 0; i < sizeof(float)*CHAR_BIT; i++)
	{
		if (selected[i] == 0) {
			cromozomi.push_back(array[i]);
			n++;
		}
	}
	for (int i = 0; i < n; i++)
	{
		float r = get_flt_rng(0, 1);
		if (r <= 0.25)
		{
			int a = get_int_rng(0, sizeof(float)*CHAR_BIT - 1);
			cromozomi[i].flip(a);
		}
	}
	return cromozomi;
}
void genetic_testing()
{
	int t = 0,choice=0,times,* selected;
	float fitness[10000],min, max, sum = 0, elapsed_secs = 0, min_time=FLT_MAX, glob_max_time = -FLT_MAX, glob_min_time = FLT_MAX, max_time=-FLT_MAX, mean_time=0, min_fitness = FLT_MAX, max_fitness = -FLT_MAX, mean_fitness = 0, glob_min_fitness = FLT_MAX, glob_max_fitness = -FLT_MAX, glob_mean_fitness = 0;
	population generations[10000];
	vector<bitset<sizeof(float)*CHAR_BIT>>partial/* ,previous, next*/;
	clock_t begin, end;
	do
	{
		cout << "Press one of the following numbers to choose a function \n \n 1.De Jong 1(-5.12,5.12) \n 2.Schwefel(-500,500) 7 \n 3.Ackley(-32.768,32.768) 10 \n 4.Six-Hump Camel(-3,3 ; -2,2) Back \n 0.Exit \n\n";
		cin >> choice;
		if (choice <= 0 || choice > 4) {
			cout << "goodbye"<<endl;  break;
		}
		cout << "Insert a value for number of tests:";
		cin >> times;
		cout << "Insert a minimum value for rng array:";
		cin >> min;
		cout << "Insert a maximum value for rng array:";
		cin >> max;
		cout << endl << endl;
		for (int it = 1; it <= 30; it = it + 5)
		{
			t = 0;
			sum = 0;
			cout << "We're testing for " << it << " parameters now." << endl;
			generations[t].array = get_bit_vector(min, max, it);
			generations[t].fitness = function(generations[t].array, choice, it, min, max);
			sum += generations[t].fitness;
			/*previous = get_bit_vector(min, max, it);
			fitness[t] = function(previous, choice, it, min, max);
			sum += fitness[t];*/
			for (t = 1; t <= times; t++)
			{
				begin = clock();
				generations[t].array = generations[t-1].array;
				selected = select(generations[t].array, choice, it, min, max);
				partial = mutatie(generations[t].array, selected);
				partial = recombine(generations[t].array,selected);
				while (partial.size() < generations[t].array.size())
				{
					int a = get_int_rng(0, partial.size());
					partial.push_back(partial[a]);
				}
				generations[t].array = partial;
				generations[t].fitness = function(generations[t].array, choice, it, min, max);
				sum += generations[t].fitness;
				if (min_fitness > generations[t].fitness)
					min_fitness = generations[t].fitness;
				if (max_fitness < generations[t].fitness)
					max_fitness = generations[t].fitness;
				/*next = previous;
				selected = select(next, choice, it, min, max);
				partial = mutatie(next, selected);
				partial = recombine(next, selected);
				while (partial.size() < next.size())
				{
					int a = get_int_rng(0, partial.size());
					partial.push_back(partial[a]);
				}
				next = partial;
				fitness[t] = function(next, choice, it, min, max);
				sum += fitness[t];
				if (min_fitness > fitness[t])
					min_fitness = fitness[t];
				if (max_fitness < fitness[t])
					max_fitness = fitness[t];*/
				end = clock();
				elapsed_secs = diffclock(begin, end);
				mean_time += elapsed_secs;
				if (min_time > elapsed_secs)
					min_time = elapsed_secs;
				if (elapsed_secs > max_time)
					max_time = elapsed_secs;
			}
			mean_fitness = sum / (times + 1);
			replace_locals();
			cout << "Local results are: minumum value=" << min_fitness << ", maximum value=" << max_fitness << ", and average=" << mean_fitness;
			cout << endl << endl;
			cout << "Time elapsed for " << it << " parameters is minimum " << min_time / CLOCKS_PER_SEC << " seconds, maximum " << max_time / CLOCKS_PER_SEC << " seconds and average " << round(mean_time / times * 100 / CLOCKS_PER_SEC) / 100 << " seconds.";
			cout << endl << endl;
			if (it == 1) it--;
		}
		glob_mean_fitness = glob_mean_fitness / 7;
		cout << "Global results are: minimum value=" << glob_min_fitness << ", maximum value=" << glob_max_fitness << ", and average=" << glob_mean_fitness << ", \n minimum time " << glob_min_time / CLOCKS_PER_SEC << " seconds, maximum " << glob_max_time / CLOCKS_PER_SEC << " seconds and average " << round(mean_time / times * 100 / CLOCKS_PER_SEC) / 100 << " seconds.\n\n";
		;
	} while (choice != 0);
	
}
int main()
{
	genetic_testing();
	return 0;
}