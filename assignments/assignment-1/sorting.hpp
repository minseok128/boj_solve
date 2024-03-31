#ifndef SORTING_HPP
# define SORTING_HPP
# include <iostream>
# include <fstream>
# include <vector>
# include <sstream>

using namespace std;

void	insertion_sort(vector<int> arr);
void	merge_sort(vector<int> arr);
void	merge_insertion_sort(vector<int> arr);
void	print_array(vector<int> &arr);

#endif