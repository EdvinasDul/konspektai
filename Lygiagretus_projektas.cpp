// Lygiagretus_projektas.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <omp.h>
#include <random>
#include <ctime>
#include <iomanip>
#include <algorithm>

using namespace std;

const int n = 10;							// count of numbers in vector

// ------------------- FUNCTIONS HEADERS -----------------------
vector<int> FillVector();
vector<int> SelectionSort(vector<int> data, int num_th);
void PrintArray(vector<int> data);

int main()
{
	std::vector<int> test_1(n);
	std::vector<int> test_2(n);
	std::vector<int> test_3(n);
	std::vector<int> test_4(n);

	cout << "Vector size: " << test_1.size() << endl;			// size of vector

	test_1 = FillVector();

	std::copy(std::begin(test_1), std::end(test_1), std::begin(test_2));	// copy vector test_1 to test_2
	std::copy(std::begin(test_1), std::end(test_1), std::begin(test_3));	// copy vector test_1 to test_3
	std::copy(std::begin(test_1), std::end(test_1), std::begin(test_4));	// copy vector test_1 to test_4

	// Testing times of sorting with different threads count


	// Number of Threads: 2
	int num_th = 8;
	clock_t begin = clock();
	test_1 = SelectionSort(test_1, num_th);		// sort vector test_1
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << "2 Threads: " << elapsed_secs << endl;

	// Number of Threads: 4
	num_th = 4;
	begin = clock();
	test_2 = SelectionSort(test_2, num_th);		// sort vector test_2
	end = clock();
	elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << "4 Threads: " << elapsed_secs << endl;

	// Number of Threads: 8
	num_th = 8;
	begin = clock();
	test_3 = SelectionSort(test_3, num_th);		// sort vector test_3
	end = clock();
	elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << "8 Threads: " << elapsed_secs << endl;

	// Number of Threads: 16
	num_th = 16;
	begin = clock();
	test_4 = SelectionSort(test_4, num_th);		// sort vector test_4
	end = clock();
	elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << "16 Threads: " << elapsed_secs << endl;
	
	return 0;
}

// ----------------- METHODS --------------------------------

// Fill vector with random integers
vector<int> FillVector() {
	vector<int> temp(n);

	srand(time(NULL));
	for (int i = 0; i < n; i++)
		temp[i] = rand() % n + 1;

	return temp;
}

// EXECUTE parallel Selection Sort usin OpenMP
vector<int> SelectionSort(vector<int> data, int num_th)
{
	vector<int> temp(n);
	std::copy(std::begin(data), std::end(data), std::begin(temp));		// make a temporary copy of array

	omp_set_num_threads(num_th);										// set threads number
	for (int i = 0; i < n - 1; i++)
	{
		int min_index = i;
#pragma omp parallel for 												// start OpenMP parallel code block
		for (int j = i + 1; j < n; j++)
			if (temp[j] < temp[min_index])
				min_index = j;
		std::swap(temp[i], temp[min_index]);							// std swap method
	}

	return temp;
}

// PRINT vector as 2D array
void PrintArray(vector<int> data)
{
	int rows, elem = 20;												// declare rows variable and column count

	if (n % elem != 0)													// calculate rows count
		rows = n / elem + 1;
	else
		rows = n / elem;

	int iii = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < elem; j++) {
			if (iii != n) {
				cout << setw(3) << left << data[iii] << " ";
				iii++;
			}
			else
				break;
		}
		cout << endl;
	}
	cout << endl;
}