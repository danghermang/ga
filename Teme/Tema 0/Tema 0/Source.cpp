#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <time.h>
#include <algorithm>
#include <random>
#define M_PI 3.14159265358979323846
#define parameters 100
#define replace_locals() {if (glob_min_ans>min_ans) glob_min_ans=min_ans; if (glob_max_ans<max_ans) glob_max_ans=max_ans;if (glob_min_time>min_time) glob_min_time=min_time;if (glob_max_time<max_time) glob_max_time=max_time;}

using namespace std;

double get_rng(double min, double max)
{
	if (max < min)
	{
		double aux = min;
		min = max;
		max = aux;
	}
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> distReal(min, max);

	return round(distReal(gen) * 100) / 100;
}
void get_vector(int number, double a[parameters], double min, double max)
{
	if (max < min)
	{
		double aux = min;
		min = max;
		max = aux;
	}
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> distReal(min, max);
	for (int i = 0; i < number; i++)
		a[i]=round(distReal(gen) * 100) / 100;
}

/*double get_rng(double min, double max)
{
	srand(time(NULL));
	if (max < min)
	{
		double aux = min;
		min = max;
		max = aux;
	}
	double val=((double(rand()) / double(RAND_MAX)) * (max - min)) + min;
	return roundf(val * 100) / 100;
}
void get_vector(int number, double a[parameters], double min, double max)
{
	for (int it = 0; it < number; it++)
		a[it] = get_rng(min, max);
}*/
double de_jong(int n, double a[])
{//-5.12,5.12
	double suma = 0;
	for (int i = 0; i<n; i++)
	{
		suma += pow(a[i], 2);
	}
	return suma;
}
double schwefel7(int n, double a[])
{//-500,500
	double suma = 0;
	for (int i = 0; i<n; i++)
	{
		suma += -a[i] * sin(M_PI*sqrt(abs(a[i]))/100);
	}
	return suma;
}
double ackley10(int n, double x[])
{//-32.768,32,678
	double a = 20, b = 0.2, c = 2 * M_PI, rezultat_partial = 0;
	for (int i = 0; i<n; i++)
	{
		rezultat_partial += cos(M_PI*c*x[i]/100);
	}
	return (-1*a)*exp(-b*sqrt(1 / n*de_jong(n, x))) - exp(1 / n*rezultat_partial) + a + exp(1);

}
double six_hump_camel(double a[])
{//-3,3 ; -2,2
	return (4 - 2.1 * pow(a[0], 2) + pow(a[0], 4) / 3)*pow(a[0], 2) + a[0] * a[1] + (-4 + 4 * pow(a[1], 2))*pow(a[1], 2);
}
static double diffclock(clock_t clock1, clock_t clock2)
{
	double diffticks = clock2 - clock1;
	double diffms = (diffticks) / (CLOCKS_PER_SEC / 1000);
	return diffms;
}
void test_function(/*double (*f)(int, double)*/)
{
	int n = 30;
	double a[parameters], min, max, sum = 0, times, elapsed_secs = 0;
	double glob_min_ans = DBL_MAX, glob_max_ans = -DBL_MAX,glob_mean_ans=0, glob_min_time = DBL_MAX, glob_max_time = -DBL_MAX;
	double min_ans, max_ans, mean_ans, min_time, max_time, mean_time;
	int choice = 0;
	do
	{
		cout << "Press one of the following numbers to choose a function \n \n 1.De Jong 1 \n 2.Schwefel 7 \n 3.Ackley 10 \n 4.Six-Hump Camel Back \n 0.Exit \n\n";
		cin >> choice;
		if (choice <= 0 || choice > 4)	break;
		clock_t begin, end;
		switch (choice) {
		case 1: {
			cout << "Insert a value for number of tests:";
			cin >> times;
			cout << "Insert a minimum value for rng array:";
			cin >> min;
			cout << "Insert a maximum value for rng array:";
			cin >> max;
			cout << endl << endl;
			for (int it = 1; it <= n; it = it + 5)
			{
				min_ans = DBL_MAX, max_ans = -DBL_MAX, mean_ans = 0, min_time = DBL_MAX, max_time = -DBL_MAX, mean_time = 0;
				cout << "We're testing for " << it << " parameters now." << endl;

				for (int j = 1; j <= times; j++)
				{
					begin = clock();
					get_vector(it, a, min, max);
					sum = de_jong(it, a);
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
			break;
		}
		case 2: {
			cout << "Insert a value for number of tests:";
			cin >> times;
			cout << "Insert a minimum value for rng array:";
			cin >> min;
			cout << "Insert a maximum value for rng array:";
			cin >> max;
			cout << endl << endl;
			for (int it = 1; it <= n; it = it + 5)
			{
				min_ans = DBL_MAX, max_ans = -DBL_MAX, mean_ans = 0, min_time = DBL_MAX, max_time = -DBL_MAX, mean_time = 0;
				cout << "We're testing for " << it << " parameters now." << endl;

				for (int j = 1; j <= times; j++)
				{
					begin = clock();
					get_vector(it, a, min, max);
					sum = schwefel7(it, a);
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
			glob_mean_ans /= 7;
			cout << "Global results are: minimum value=" << glob_min_ans << ", maximum value=" << glob_max_ans << ", and average=" << glob_mean_ans << ", \n minimum time " << glob_min_time / CLOCKS_PER_SEC << " seconds, maximum " << glob_max_time / CLOCKS_PER_SEC << " seconds and average " << round(mean_time / times * 100 / CLOCKS_PER_SEC) / 100 << " seconds.\n\n";
			break;
		}
		case 3: {
			cout << "Insert a value for number of tests:";
			cin >> times;
			cout << "Insert a minimum value for rng array:";
			cin >> min;
			cout << "Insert a maximum value for rng array:";
			cin >> max;
			cout << endl << endl;
			for (int it = 1; it <= n; it = it + 5)
			{
				min_ans = DBL_MAX, max_ans = -DBL_MAX, mean_ans = 0, min_time = DBL_MAX, max_time = -DBL_MAX, mean_time = 0;
				cout << "We're testing for " << it << " parameters now." << endl;

				for (int j = 1; j <= times; j++)
				{
					begin = clock();
					get_vector(it, a, min, max);
					sum = ackley10(it, a);
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
			glob_mean_ans /= 7;
			cout << "Global results are: minimum value=" << glob_min_ans << ", maximum value=" << glob_max_ans << ", and average=" << glob_mean_ans << ", \n minimum time " << glob_min_time / CLOCKS_PER_SEC << " seconds, maximum " << glob_max_time / CLOCKS_PER_SEC << " seconds and average " << round(mean_time / times * 100 / CLOCKS_PER_SEC) / 100 << " seconds.\n\n";
			break;
		}
		case 4: {
			double min_x1, max_x1, min_x2, max_x2;
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
			min_ans = DBL_MAX, max_ans = -DBL_MAX, mean_ans = 0, min_time = DBL_MAX, max_time = -DBL_MAX, mean_time = 0;
			cout << "We're testing now." << endl;
			for (int j = 1; j <= times; j++)
			{
				begin = clock();
				a[0] = get_rng(min_x1, max_x1);
				a[1] = get_rng(min_x2, max_x2);
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
				break;
		}
}while (choice >= 1 && choice <= 4);
}

int main()
{	
	double a[parameters];
	test_function();
	
	return 0;
}