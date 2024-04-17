// 20203361 장민석
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>
#include <random>
#include <algorithm>
using namespace std;
using namespace std::chrono;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> dis;

static void	print_array(string type, vector<int> &arr,
	ofstream &ofile, high_resolution_clock::time_point &start);

int	q2_partition(vector<int> &arr, int l, int r)
{
	swap(arr[r], arr[(unsigned int)dis(gen) % (r - l) + l]);

	int	pivot = arr[r];
	int	i = l - 1;

	for (int j = l; j < r; ++j)
		if (arr[j] <= pivot)
		{
			++i;
			swap(arr[i], arr[j]);
		}
	swap(arr[i + 1], arr[r]);
	return (i + 1);
}

int	q1_partition(vector<int> &arr, int l, int r)
{
	int	pivot = arr[r];
	int	i = l - 1;

	for (int j = l; j < r; ++j)
		if (arr[j] <= pivot)
		{
			++i;
			swap(arr[i], arr[j]);
		}
	swap(arr[i + 1], arr[r]);
	return (i + 1);
}

void	quick_divied(vector<int> &arr, int l, int r,
	int (*f)(vector<int> &arr, int l, int r))
{
	int	p;

	if (l >= r)
		return ;
	p = f(arr, l, r);
	quick_divied(arr, l, p - 1, f);
	quick_divied(arr, p + 1, r, f);
}


void	quick_sort(vector<int> &base_arr, ofstream &ofile,
	int (*f)(vector<int> &arr, int l, int r))
{
	auto		start = high_resolution_clock::now();
	int			size = base_arr.size();
	vector<int>	arr(base_arr), tmp(size);

	quick_divied(arr, 0, size - 1, f);

	print_array("time", arr, ofile, start);
	ofile << '\n';
}

// --------utils--------
static int	print_error(const std::string &msg)
{
	cerr << msg << "\n";
	return (1);
}

static void	print_array(string type, vector<int> &arr,
	ofstream &ofile, high_resolution_clock::time_point &start)
{
	int	size = arr.size() - 1;

	cout << type << ": "
		<< duration_cast<microseconds>(high_resolution_clock::now() - start).count() << "ms\n";
	for (int i = 0; i < size; ++i)
		ofile << arr[i] << " ";
	ofile << arr[size];
}

// -------- main--------
int main(int ac, char **av)
{
	if (ac != 3)
		return (print_error("usage: ./sorting [input file] [output file]"));

	ifstream	ifile(av[1]);
	ofstream	ofile(av[2]);
	vector<int>	base_arr;
	int			size;
	
	if (!ifile.is_open() || !ofile.is_open())
		return (print_error("file open error"));

	ifile >> size;
	base_arr.resize(size);
	for (int i = 0; i < size; ++i)
		ifile >> base_arr[i];
	ifile.close();

	quick_sort(base_arr, ofile, q1_partition);
	quick_sort(base_arr, ofile, q2_partition);

	ofile.close();
	return (0);
}
