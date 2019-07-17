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
#define replace_locals() {if (glob_min_ans>min_ans) glob_min_ans=min_ans; if (glob_max_ans<max_ans) glob_max_ans=max_ans;if (glob_min_time>min_time) glob_min_time=min_time;if (glob_max_time<max_time) glob_max_time=max_time;}

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
	float a = 20, b = 0.2, c, rezultat_partial = 0;
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
	n = (max - min)*pow(10, precizie);
	n = ceil(log(n) / log(2));
	for (int i = 0; i < sizeof(float)*CHAR_BIT; i++)
	{
		sum += number[i] * pow(2, i);
	}
	sum = sum*(max - min) / (pow(2, n) - 1);
	return min + sum;
}
vector<float> bit_to_float_vector(vector<bitset<sizeof(float)*CHAR_BIT> > array, float min, float max)
{
	vector<float> a;
	float aux;
	for (vector<bitset<sizeof(float)*CHAR_BIT> >::iterator j = array.begin(); j != array.end(); j++)
	{
		aux=bit_to_float(*j, min, max);
		a.push_back(aux);
	}
		
	return a;
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
		a.push_back( round(distReal(gen) * 100) / 100);
	return a;
}
/*
for (int j = 1; j <= times; j++)
{
begin = clock();
get_vector(it, a, min, max);
switch (choice) {
case 1: sum = de_jong(it, a);
break;
case 2: sum = schwefel7(it, a);
break;
case 3: sum = ackley10(it, a);
break;
}
mean_ans += sum;
if (min_ans > sum)
min_ans = sum;
if (max_ans < sum)
max_ans = sum;
end = clock();
elapsed_secs = diffclock(begin, end);
mean_time += elapsed_secs;
if (min_time > elapsed_secs)
min_time = elapsed_secs;
if (elapsed_secs > max_time)
max_time = elapsed_secs;
replace_locals();
}*/
void hill_climbing_test()
{
	cout <<endl<< "Hill climbing test" << endl;
	int iterations, bit_pos, length,n=30;
	float elapsed_secs,fitness, max_fitness, min_fitness, global_max_fitness, global_min_fitness, max, min, min_time = FLT_MAX, max_time = -FLT_MAX, mean_time = 0;
	vector<bitset<sizeof(float)*CHAR_BIT> > global_max_hilltop, global_min_hilltop, min_hilltop, max_hilltop, hilltop;
	bool increase_found, check_null_max = true, check_null_min = true;
	int choice = 0;
	do
	{
		cout << "Press one of the following numbers to choose a function \n \n 1.De Jong 1(-5.12,5.12) \n 2.Schwefel(-500,500) 7 \n 3.Ackley(-32.768,32.768) 10 \n 4.Six-Hump Camel(-3,3 ; -2,2) Back \n 0.Exit \n\n";
		cin >> choice;
		if (choice <= 0 || choice > 4)	break;
		clock_t begin, end;
		cout << "Insert a value for number of iterations:";
		cin >> iterations;
		if (choice != 4)
		{
			cout << "Insert a minimum value for rng array:";
			cin >> min;
			cout << "Insert a maximum value for rng array:";
			cin >> max;
			cout << endl << endl;
			for (int it = 1; it <= n; it = it + 5)
			{
				max_fitness = 0;
				fitness = 0;
				global_max_fitness = 0;
				{//maximum fitness
					cout << "\nWe're testing maximum value for " << it << " parameters now.\n" << endl;

					for (int j = 1; j <= iterations; j++)
					{
						begin = clock();
						max_hilltop = get_bit_vector(min, max, it);
						switch (choice) {
						case 1: max_fitness = de_jong(it, bit_to_float_vector(max_hilltop, min, max));
							break;
						case 2: max_fitness = schwefel7(it, bit_to_float_vector(max_hilltop, min, max));
							break;
						case 3: max_fitness = ackley10(it, bit_to_float_vector(max_hilltop, min, max));
							break;
						}
						if (check_null_max)
						{
							global_max_hilltop = max_hilltop;
							global_max_fitness = max_fitness;
							check_null_max = false;
						}
						increase_found = true;
						while (increase_found)
						{
							increase_found = false;
							for (int i = 0; i < it; i++)
								for (bit_pos = 0; bit_pos < sizeof(float)*CHAR_BIT; bit_pos++)
								{
									hilltop = max_hilltop;
									change_bit(hilltop[i], bit_pos);
									switch (choice) {
									case 1: fitness = de_jong(it, bit_to_float_vector(hilltop, min, max));
										break;
									case 2: fitness = schwefel7(it, bit_to_float_vector(hilltop, min, max));
										break;
									case 3: fitness = ackley10(it, bit_to_float_vector(hilltop, min, max));
										break;
									}
									if (fitness > max_fitness)
									{
										max_fitness = fitness;
										max_hilltop = hilltop;
										increase_found = true;
									}

								}
						}
						if (max_fitness > global_max_fitness)
						{
							global_max_fitness = max_fitness;
							global_max_hilltop = max_hilltop;
						}
						end = clock();
						elapsed_secs = diffclock(begin, end);
						mean_time += elapsed_secs;
						if (min_time > elapsed_secs)
							min_time = elapsed_secs;
						if (elapsed_secs > max_time)
							max_time = elapsed_secs;
					}
					cout << "\nFor " << it << " parameters we have a maximum fitness of " << global_max_fitness << "and time elapsed for each iteration was \n minimum " << min_time / CLOCKS_PER_SEC << ", maximum " << max_time / CLOCKS_PER_SEC << " and an average of" << mean_time / CLOCKS_PER_SEC << " seconds\n";
				}
				{//minimum fintess
					cout << "\nWe're testing minimum value for " << it << " parameters now.\n" << endl;
					for (int j = 1; j <= iterations; j++)
					{
						begin = clock();
						min_hilltop = get_bit_vector(min, max, it);
						switch (choice) {
						case 1: min_fitness = de_jong(it, bit_to_float_vector(min_hilltop, min, max));
							break;
						case 2: min_fitness = schwefel7(it, bit_to_float_vector(min_hilltop, min, max));
							break;
						case 3: min_fitness = ackley10(it, bit_to_float_vector(min_hilltop, min, max));
							break;
						}
						if (check_null_min)
						{
							global_min_hilltop = min_hilltop;
							global_min_fitness = min_fitness;
							check_null_min = false;
						}
						increase_found = true;
						while (increase_found)
						{
							increase_found = false;
							for (int i=0;i<it; i++)
								for (bit_pos = 0; bit_pos < sizeof(float)*CHAR_BIT; bit_pos++)
								{
									hilltop = min_hilltop;
									change_bit(hilltop[i], bit_pos);
									switch (choice) {
									case 1: fitness = de_jong(it, bit_to_float_vector(hilltop, min, max));
										break;
									case 2: fitness = schwefel7(it, bit_to_float_vector(hilltop, min, max));
										break;
									case 3: fitness = ackley10(it, bit_to_float_vector(hilltop, min, max));
										break;
									}
									if (fitness > min_fitness)
									{
										min_fitness = fitness;
										min_hilltop = hilltop;
										increase_found = true;
									}

								}
						}
						if (min_fitness > global_min_fitness)
						{
							global_min_fitness = min_fitness;
							global_min_hilltop = min_hilltop;
						}
						end = clock();
						elapsed_secs = diffclock(begin, end);
						mean_time += elapsed_secs;
						if (min_time > elapsed_secs)
							min_time = elapsed_secs;
						if (elapsed_secs > max_time)
							max_time = elapsed_secs;
					}
					cout << "\nFor " << it << " parameters we have a minimum fitness of " << global_min_fitness << "and time elapsed for each iteration was \n minimum " << min_time / CLOCKS_PER_SEC << ", maximum " << max_time / CLOCKS_PER_SEC << " and an average of" << mean_time / CLOCKS_PER_SEC << " seconds\n";
				}
				if (it == 1) it--;
			}
		}

		if (choice == 4) {
			
			float min_x1, max_x1, min_x2, max_x2;
			cout << "Insert a minimum value for x1:";
			cin >> min_x1;
			cout << "Insert a maximum value for x1:";
			cin >> max_x1;
			cout << "Insert a minimum value for x2:";
			cin >> min_x2;
			cout << "Insert a maximum value for x2:";
			cin >> max_x2;
			cout << endl << endl;
			float min_time = FLT_MAX, max_time = -FLT_MAX, mean_time = 0;
			max_fitness = 0;
			fitness = 0;
			global_max_fitness = 0;
			{//maximum fitness
				cout << "\nWe're testing maximum value now.\n" << endl;

				for (int j = 1; j <= iterations; j++)
				{
					
					begin = clock();
					max_hilltop.push_back(get_bit_rng());
					max_hilltop.push_back(get_bit_rng());
					switch (choice) {
					case 1: max_fitness = de_jong(2, bit_to_float_vector(max_hilltop, min, max));
						break;
					case 2: max_fitness = schwefel7(2, bit_to_float_vector(max_hilltop, min, max));
						break;
					case 3: max_fitness = ackley10(2, bit_to_float_vector(max_hilltop, min, max));
						break;
					}
					if (check_null_max)
					{
						global_max_hilltop = max_hilltop;
						global_max_fitness = max_fitness;
						check_null_max = false;
					}
					increase_found = true;
					while (increase_found)
					{
						increase_found = false;
						for (int i=0;i<2; i++)
							for (bit_pos = 0; bit_pos < sizeof(float)*CHAR_BIT; bit_pos++)
							{
								hilltop = max_hilltop;
								change_bit(hilltop[i], bit_pos);
								switch (choice) {
								case 1: fitness = de_jong(2, bit_to_float_vector(hilltop, min, max));
									break;
								case 2: fitness = schwefel7(2, bit_to_float_vector(hilltop, min, max));
									break;
								case 3: fitness = ackley10(2, bit_to_float_vector(hilltop, min, max));
									break;
								}
								if (fitness > max_fitness)
								{
									max_fitness = fitness;
									max_hilltop = hilltop;
									increase_found = true;
								}

							}
					}
					if (max_fitness > global_max_fitness)
					{
						global_max_fitness = max_fitness;
						global_max_hilltop = max_hilltop;
					}
					end = clock();
					elapsed_secs = diffclock(begin, end);
					mean_time += elapsed_secs;
					if (min_time > elapsed_secs)
						min_time = elapsed_secs;
					if (elapsed_secs > max_time)
						max_time = elapsed_secs;
				}
				cout << "\nWe have a maximum fitness of " << global_max_fitness << "and time elapsed for each iteration was \n minimum " << min_time / CLOCKS_PER_SEC << ", maximum " << max_time / CLOCKS_PER_SEC << " and an average of" << mean_time / CLOCKS_PER_SEC << " seconds\n";
			}
			{//minimum fintess
				cout << "\nWe're testing minimum value now.\n" << endl;
				for (int j = 1; j <= iterations; j++)
				{
					begin = clock();
					min_hilltop.push_back(get_bit_rng());
					min_hilltop.push_back(get_bit_rng());
					switch (choice) {
					case 1: min_fitness = de_jong(2, bit_to_float_vector(min_hilltop, min, max));
						break;
					case 2: min_fitness = schwefel7(2, bit_to_float_vector(min_hilltop, min, max));
						break;
					case 3: min_fitness = ackley10(2, bit_to_float_vector(min_hilltop, min, max));
						break;
					}
					if (check_null_min)
					{
						global_min_hilltop = min_hilltop;
						global_min_fitness = min_fitness;
						check_null_min = false;
					}
					increase_found = true;
					while (increase_found)
					{
						increase_found = false;
						for (int i = 0; i < 2; i++)
							for (bit_pos = 0; bit_pos < sizeof(float)*CHAR_BIT; bit_pos++)
							{
								hilltop = min_hilltop;
								change_bit(hilltop[i], bit_pos);
								switch (choice) {
								case 1: fitness = de_jong(2, bit_to_float_vector(hilltop, min, max));
									break;
								case 2: fitness = schwefel7(2, bit_to_float_vector(hilltop, min, max));
									break;
								case 3: fitness = ackley10(2, bit_to_float_vector(hilltop, min, max));
									break;
								}
								if (fitness > min_fitness)
								{
									min_fitness = fitness;
									min_hilltop = hilltop;
									increase_found = true;
								}

							}
					}
					if (min_fitness > global_min_fitness)
					{
						global_min_fitness = min_fitness;
						global_min_hilltop = min_hilltop;
					}
					end = clock();
					elapsed_secs = diffclock(begin, end);
					mean_time += elapsed_secs;
					if (min_time > elapsed_secs)
						min_time = elapsed_secs;
					if (elapsed_secs > max_time)
						max_time = elapsed_secs;
				}
				cout << "\nWe have a minimum fitness of " << global_min_fitness << "and time elapsed for each iteration was \n minimum " << min_time / CLOCKS_PER_SEC << ", maximum " << max_time / CLOCKS_PER_SEC << " and an average of" << mean_time / CLOCKS_PER_SEC << " seconds\n";
			}
			cout << endl << endl;
		}
	} while (choice >= 1 && choice <= 4);
}

void simulated_annealing_test()
{
	cout << endl<<"Simulated annealing"<<endl;
	int iterations, bit_pos, length,n=30;
	float elapsed_secs,acceptance_probability, probability, fitness, max_fitness, min_fitness, global_max_fitness, global_min_fitness, max, min, min_time = FLT_MAX, max_time = -FLT_MAX, mean_time = 0;
	vector<bitset<sizeof(float)*CHAR_BIT> > global_max_hilltop, global_min_hilltop, min_hilltop, max_hilltop, hilltop;
	bool increase_found, check_null_max = true, check_null_min = true;
	int choice = 0;
	do
	{
		float temperature = FLT_MAX, temperature_step;
		cout << "Press one of the following numbers to choose a function \n \n 1.De Jong 1(-5.12,5.12) \n 2.Schwefel(-500,500) 7 \n 3.Ackley(-32.768,32.768) 10 \n 4.Six-Hump Camel(-3,3 ; -2,2) Back \n 0.Exit \n\n";
		cin >> choice;
		if (choice <= 0 || choice > 4)	break;
		clock_t begin, end;
		cout << "Insert a value for number of iterations:";
		cin >> iterations;
		cout << "Insert a value for the temperature step;";
		cin >> temperature_step;
		if (choice != 4)
		{
			cout << "Insert a minimum value for rng array:";
			cin >> min;
			cout << "Insert a maximum value for rng array:";
			cin >> max;

			cout << endl << endl;
			for (int it = 1; it <= n; it = it + 5)
			{
				max_fitness = 0;
				fitness = 0;
				global_max_fitness = 0;
				{//maximum fitness
					cout << "\nWe're testing maximum value for " << it << " parameters now.\n" << endl;
					while (temperature > 0)
					{
						max_hilltop = get_bit_vector(min, max, it);
						switch (choice)
						{
						case 1: max_fitness = de_jong(it, bit_to_float_vector(max_hilltop, min, max));
							break;
						case 2: max_fitness = schwefel7(it, bit_to_float_vector(max_hilltop, min, max));
							break;
						case 3: max_fitness = ackley10(it, bit_to_float_vector(max_hilltop, min, max));
							break;
						}
						if (check_null_max)
						{
							global_max_hilltop = max_hilltop;
							global_max_fitness = max_fitness;
							check_null_max = false;
						}
						for (int j = 1; j <= iterations; j++)
						{
							begin = clock();
							int iterator_vector = get_int_rng(0, it-1), iterator_bit = get_int_rng(0, sizeof(float)*CHAR_BIT);
							hilltop = max_hilltop;
							change_bit(hilltop[iterator_vector], iterator_bit);
							switch (choice)
							{
							case 1: fitness = de_jong(it, bit_to_float_vector(hilltop, min, max));
								break;
							case 2: fitness = schwefel7(it, bit_to_float_vector(hilltop, min, max));
								break;
							case 3: fitness = ackley10(it, bit_to_float_vector(hilltop, min, max));
								break;
							}
							if (fitness > max_fitness)
							{
								max_fitness = fitness;
								max_hilltop = hilltop;
							}
							else
							{
								probability = get_flt_rng(0, 1);
								acceptance_probability = exp((max_fitness - fitness) / temperature);
								if (probability < acceptance_probability)
								{
									max_fitness = fitness;
									max_hilltop = hilltop;
								}
							}
						}
						temperature = temperature*temperature_step;

						if (max_fitness > global_max_fitness)
						{
							global_max_fitness = max_fitness;
							global_max_hilltop = max_hilltop;
						}
						end = clock();
						elapsed_secs = diffclock(begin, end);
						mean_time += elapsed_secs;
						if (min_time > elapsed_secs)
							min_time = elapsed_secs;
						if (elapsed_secs > max_time)
							max_time = elapsed_secs;
					}
					cout << "\nFor " << it << " parameters we have a maximum fitness of " << global_max_fitness << "and time elapsed for each iteration was \n minimum " << min_time / CLOCKS_PER_SEC << ", maximum " << max_time / CLOCKS_PER_SEC << " and an average of" << mean_time / CLOCKS_PER_SEC << " seconds\n";
				}
				{//minimum fitness
					cout << "\nWe're testing maximum value for " << it << " parameters now." << endl;
					while (temperature > 0)
					{
						min_hilltop = get_bit_vector(min, max, it);
						switch (choice)
						{
						case 1: min_fitness = de_jong(it, bit_to_float_vector(min_hilltop, min, max));
							break;
						case 2: min_fitness = schwefel7(it, bit_to_float_vector(min_hilltop, min, max));
							break;
						case 3: min_fitness = ackley10(it, bit_to_float_vector(min_hilltop, min, max));
							break;
						}
						if (check_null_min)
						{
							global_min_hilltop = min_hilltop;
							global_min_fitness = min_fitness;
							check_null_min = false;
						}
						for (int j = 1; j <= iterations; j++)
						{
							begin = clock();
							int iterator_vector = get_int_rng(0, it-1), iterator_bit = get_int_rng(0, sizeof(float)*CHAR_BIT);
							hilltop = min_hilltop;
							change_bit(hilltop[iterator_vector], iterator_bit);
							switch (choice)
							{
							case 1: fitness = de_jong(it, bit_to_float_vector(hilltop, min, max));
								break;
							case 2: fitness = schwefel7(it, bit_to_float_vector(hilltop, min, max));
								break;
							case 3: fitness = ackley10(it, bit_to_float_vector(hilltop, min, max));
								break;
							}
							if (fitness > min_fitness)
							{
								min_fitness = fitness;
								min_hilltop = hilltop;
							}
							else
							{
								probability = get_flt_rng(0, 1);
								acceptance_probability = exp((min_fitness - fitness) / temperature);
								if (probability < acceptance_probability)
								{
									min_fitness = fitness;
									min_hilltop = hilltop;
								}
							}
						}
						temperature = temperature*temperature_step;

						if (min_fitness < global_min_fitness)
						{
							global_min_fitness = min_fitness;
							global_min_hilltop = min_hilltop;
						}
						end = clock();
						elapsed_secs = diffclock(begin, end);
						mean_time += elapsed_secs;
						if (min_time > elapsed_secs)
							min_time = elapsed_secs;
						if (elapsed_secs > max_time)
							max_time = elapsed_secs;
						cout << "\nFor " << it << " parameters we have a maximum fitness of " << global_max_fitness << "and time elapsed for each iteration was \n minimum " << min_time / CLOCKS_PER_SEC << ", maximum " << max_time / CLOCKS_PER_SEC << " and an average of" << mean_time / CLOCKS_PER_SEC << " seconds\n";
					}
				}
				if (it == 1) it--;
			}
		}
		if (choice == 4)
		{
			float min_x1, max_x1, min_x2, max_x2;
			cout << "Insert a minimum value for x1:";
			cin >> min_x1;
			cout << "Insert a maximum value for x1:";
			cin >> max_x1;
			cout << "Insert a minimum value for x2:";
			cin >> min_x2;
			cout << "Insert a maximum value for x2:";
			cin >> max_x2;
			cout << endl << endl;
			float min_time = FLT_MAX, max_time = -FLT_MAX, mean_time = 0;
			max_fitness = 0;
			fitness = 0;
			global_max_fitness = 0;
			{//maximum fitness
				cout << "\nWe're testing maximum value now.\n" << endl;
				while (temperature > 0)
				{
					max_hilltop.push_back(get_bit_rng());
					max_hilltop.push_back(get_bit_rng());
					switch (choice)
					{
					case 1: max_fitness = de_jong(2, bit_to_float_vector(max_hilltop, min, max));
						break;
					case 2: max_fitness = schwefel7(2, bit_to_float_vector(max_hilltop, min, max));
						break;
					case 3: max_fitness = ackley10(2, bit_to_float_vector(max_hilltop, min, max));
						break;
					}
					if (check_null_max)
					{
						global_max_hilltop = max_hilltop;
						global_max_fitness = max_fitness;
						check_null_max = false;
					}
					for (int j = 1; j <= iterations; j++)
					{
						begin = clock();
						int iterator_vector = get_int_rng(0, 1), iterator_bit = get_int_rng(0, sizeof(float)*CHAR_BIT);
						hilltop = max_hilltop;
						change_bit(hilltop[iterator_vector], iterator_bit);
						switch (choice)
						{
						case 1: fitness = de_jong(2, bit_to_float_vector(hilltop, min, max));
							break;
						case 2: fitness = schwefel7(2, bit_to_float_vector(hilltop, min, max));
							break;
						case 3: fitness = ackley10(2, bit_to_float_vector(hilltop, min, max));
							break;
						}
						if (fitness > max_fitness)
						{
							max_fitness = fitness;
							max_hilltop = hilltop;
						}
						else
						{
							probability = get_flt_rng(0, 1);
							acceptance_probability = exp((max_fitness - fitness) / temperature);
							if (probability < acceptance_probability)
							{
								max_fitness = fitness;
								max_hilltop = hilltop;
							}
						}
					}
					temperature = temperature*temperature_step;

					if (max_fitness > global_max_fitness)
					{
						global_max_fitness = max_fitness;
						global_max_hilltop = max_hilltop;
					}
					end = clock();
					elapsed_secs = diffclock(begin, end);
					mean_time += elapsed_secs;
					if (min_time > elapsed_secs)
						min_time = elapsed_secs;
					if (elapsed_secs > max_time)
						max_time = elapsed_secs;
				}
				cout << "\nWe have a maximum fitness of " << global_max_fitness << "and time elapsed for each iteration was \n minimum " << min_time / CLOCKS_PER_SEC << ", maximum " << max_time / CLOCKS_PER_SEC << " and an average of" << mean_time / CLOCKS_PER_SEC << " seconds\n";
			}
			{//maximum fitness
				cout << "\nWe're testing minimum value now.\n" << endl;
				while (temperature > 0)
				{
					min_hilltop.push_back(get_bit_rng());
					min_hilltop.push_back(get_bit_rng());
					switch (choice)
					{
					case 1: min_fitness = de_jong(2, bit_to_float_vector(min_hilltop, min, max));
						break;
					case 2: min_fitness = schwefel7(2, bit_to_float_vector(min_hilltop, min, max));
						break;
					case 3: min_fitness = ackley10(2, bit_to_float_vector(min_hilltop, min, max));
						break;
					}
					if (check_null_max)
					{
						global_min_hilltop = min_hilltop;
						global_min_fitness = min_fitness;
						check_null_min = false;
					}
					for (int j = 1; j <= iterations; j++)
					{
						begin = clock();
						int iterator_vector = get_int_rng(0, 1), iterator_bit = get_int_rng(0, sizeof(float)*CHAR_BIT);
						hilltop = min_hilltop;
						change_bit(min_hilltop[iterator_vector], iterator_bit);
						switch (choice)
						{
						case 1: fitness = de_jong(2, bit_to_float_vector(hilltop, min, max));
							break;
						case 2: fitness = schwefel7(2, bit_to_float_vector(hilltop, min, max));
							break;
						case 3: fitness = ackley10(2, bit_to_float_vector(hilltop, min, max));
							break;
						}
						if (fitness < min_fitness)
						{
							min_fitness = fitness;
							min_hilltop = hilltop;
						}
						else
						{
							probability = get_flt_rng(0, 1);
							acceptance_probability = exp((max_fitness - fitness) / temperature);
							if (probability < acceptance_probability)
							{
								min_fitness = fitness;
								min_hilltop = hilltop;
							}
						}
					}
					temperature = temperature*temperature_step;

					if (min_fitness < global_min_fitness)
					{
						global_min_fitness = min_fitness;
						global_min_hilltop = min_hilltop;
					}
					end = clock();
					elapsed_secs = diffclock(begin, end);
					mean_time += elapsed_secs;
					if (min_time > elapsed_secs)
						min_time = elapsed_secs;
					if (elapsed_secs > max_time)
						max_time = elapsed_secs;
				}
				cout << "\nWe have a maximum fitness of " << global_min_fitness << "and time elapsed for each iteration was \n minimum " << min_time / CLOCKS_PER_SEC << ", maximum " << max_time / CLOCKS_PER_SEC << " and an average of" << mean_time / CLOCKS_PER_SEC << " seconds\n";
			}
			cout << endl << endl;
		}
	} while (choice >= 1 && choice <= 4);
}

/*
void test_function()
{
	cout << endl << "Random test function" << endl;
	int n = 30;
	vector<float> a;
	float min, max, sum = 0, times, elapsed_secs = 0,glob_min_ans = FLT_MAX, glob_max_ans = -FLT_MAX, glob_mean_ans = 0, glob_min_time = FLT_MAX, glob_max_time = -FLT_MAX;
	float min_ans, max_ans, mean_ans, min_time, max_time, mean_time;
	int choice = 0;
	do
	{
		cout << "Press one of the following numbers to choose a function \n \n 1.De Jong 1(-5.12,5.12) \n 2.Schwefel(-500,500) 7 \n 3.Ackley(-32.768,32.768) 10 \n 4.Six-Hump Camel(-3,3 ; -2,2) Back \n 0.Exit \n\n";
		cin >> choice;
		if (choice <= 0 || choice > 4)	break;
		clock_t begin, end;
		cout << "Insert a value for number of tests:";
		cin >> times;
		cout << "Insert a minimum value for rng array:";
		cin >> min;
		cout << "Insert a maximum value for rng array:";
		cin >> max;
		cout << endl << endl;

		for (int it = 1; it <= n; it = it + 5)
		{
			min_ans = FLT_MAX, max_ans = -FLT_MAX, mean_ans = 0, min_time = FLT_MAX, max_time = -FLT_MAX, mean_time = 0;
			cout << "We're testing for " << it << " parameters now." << endl;

			for (int j = 1; j <= times; j++)
			{
				begin = clock();
				get_vector(it, min, max);
				switch (choice) {
				case 1: sum = de_jong(it, a);
					break;
				case 2: sum = schwefel7(it, a);
					break;
				case 3: sum = ackley10(it, a);
					break;
				}
				mean_ans += sum;
				if (min_ans > sum)
					min_ans = sum;
				if (max_ans < sum)
					max_ans = sum;
				end = clock();
				elapsed_secs = diffclock(begin, end);
				mean_time += elapsed_secs;
				if (min_time > elapsed_secs)
					min_time = elapsed_secs;
				if (elapsed_secs > max_time)
					max_time = elapsed_secs;
				replace_locals();
			}
			mean_ans = mean_ans / times;
			glob_mean_ans += mean_ans;
			cout << "Local results are: minumum value=" << min_ans << ", maximum value=" << max_ans << ", and average=" << mean_ans;
			cout << endl << endl;
			cout << "Time elapsed for " << it << " parameters is minimum " << min_time / CLOCKS_PER_SEC << " seconds, maximum " << max_time / CLOCKS_PER_SEC << " seconds and average " << round(mean_time / times * 100 / CLOCKS_PER_SEC) / 100 << " seconds.";
			cout << endl << endl;
			if (it == 1) it--;
		}
		glob_mean_ans = glob_mean_ans / 7;
		cout << "Global results are: minimum value=" << glob_min_ans << ", maximum value=" << glob_max_ans << ", and average=" << glob_mean_ans << ", \n minimum time " << glob_min_time / CLOCKS_PER_SEC << " seconds, maximum " << glob_max_time / CLOCKS_PER_SEC << " seconds and average " << round(mean_time / times * 100 / CLOCKS_PER_SEC) / 100 << " seconds.\n\n";
		;

		if (choice == 4) {
			float min_x1, max_x1, min_x2, max_x2;
			cout << "Insert a value for number of tests:";
			cin >> times;
			cout << "Insert a minimum value for x1:";
			cin >> min_x1;
			cout << "Insert a maximum value for x1:";
			cin >> max_x1;
			cout << "Insert a minimum value for x2:";
			cin >> min_x2;
			cout << "Insert a maximum value for x2:";
			cin >> max_x2;
			cout << endl << endl;
			min_ans = FLT_MAX, max_ans = -FLT_MAX, mean_ans = 0, min_time = FLT_MAX, max_time = -FLT_MAX, mean_time = 0;
			cout << "We're testing now." << endl;
			for (int j = 1; j <= times; j++)
			{
				begin = clock();
				a[0] = get_flt_rng(min_x1, max_x1);
				a[1] = get_flt_rng(min_x2, max_x2);
				sum = six_hump_camel(a);
				mean_ans += sum;
				if (min_ans > sum)
					min_ans = sum;
				if (max_ans < sum)
					max_ans = sum;
				end = clock();
				elapsed_secs = diffclock(begin, end);
				mean_time += elapsed_secs;
				if (min_time > elapsed_secs)
					min_time = elapsed_secs;
				if (elapsed_secs > max_time)
					max_time = elapsed_secs;
			}

			cout << "Results are: minumum value=" << min_ans << ", maximum value=" << max_ans << ", and average=" << mean_ans / times;
			cout << endl << endl;
			cout << "Time elapsed is minimum " << min_time / CLOCKS_PER_SEC << " seconds, maximum " << max_time / CLOCKS_PER_SEC << " seconds and average " << round(mean_time / times * 100 / CLOCKS_PER_SEC) / 100 << " seconds.\n\n";
			cout << endl << endl;
		}
	} while (choice >= 1 && choice <= 4);
}*/
int main()
{
	/*hill_climbing_test();
	simulated_annealing_test();*/
	bitset<sizeof(float)*CHAR_BIT> numar;
	for (int i = 0; i < 100; i++)
	{
		numar = get_bit_rng();
		cout << bit_to_float(numar, -5, 17);
	}
	return 0;
}