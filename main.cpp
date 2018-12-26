#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include "Solve_sle.h"

using std::cout;
using std::cin;
using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;
//using std::size_t;
using namespace std::chrono;

int main()
{
	string file_with_matrix;
	string solution_file;

	ifstream fin;
	ofstream fout;
	cout << "Enter .txt file name: ";
	cin >> file_with_matrix;
	cout << "Enter .txt output file name: ";
	cin >> solution_file;
	size_t size;
		
	vector<double> b;
	vector<vector<double>> matrix(fill_matrix_from_file(file_with_matrix, size));
	vector<vector<double>> original_matrix(matrix);
	vector<double> solution(size);

	high_resolution_clock::time_point begin = high_resolution_clock::now();
	bool exist = solve_sle(matrix, solution);
	high_resolution_clock::time_point end = high_resolution_clock::now();
	auto took = duration_cast<milliseconds>(end - begin);
	cout << took.count() << " milisec\n";
	
	cout << residual_of_matrix(original_matrix, solution) << " \n";
	output_solution_to_file(exist, solution, solution_file);

	system("pause");
	return 0;
}

vector<vector<double>> fill_matrix_from_file(string &file_with_matrix, size_t &size) // открытие файла, выделение памяти под матрицу и заполнение
{
	ifstream fin(file_with_matrix);
	if (!fin.is_open()) {
		cout << "\nCan't find this file  ";
		system("pause");
		exit(0);
	}
	fin >> size;
	if (size <= 0) {
		fin.close();
		cout << "wrong size";
		system("pause");
		exit(0);
	}

	vector<vector<double>> matrix(size);
	for (size_t i = 0; i < size; i++)
		matrix[i].resize(size + 1);

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size + 1; j++) {
			fin >> matrix[i][j];
		}
	}

	fin.close();
	return matrix;
}

void output_solution_to_file(bool exist, const vector<double> &solution, string &solution_file) //вывод матриц в файл и проверка файла на существование
{
	ofstream fout(solution_file);
	if (!fout.is_open()) {																	//проверка, есть ли такой файл
		cout << "couldn't open file for output";

		return;
	}
	if (exist) {																			//если есть решение выводим
		for (int i = 0; i < solution.size(); i++) {
			fout << solution[i] << "\n";
		}
	}
	else {																					//если нет решений или их бесконечно много то выводим UNDEFINED
		fout << "UNDEFINED";
	}
	fout.close();
}
