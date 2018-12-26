#pragma once
#include <string>
#include <vector>

using std::vector;
using std::string;

bool solve_sle(vector<vector<double>> &matrix, vector<double> &solution);

vector<vector<double>> fill_matrix_from_file(string &file_with_matrix, size_t &size);

void output_solution_to_file(bool exist, const vector<double> &solution, string &solution_file);// throw(const char *);

double residual_of_matrix(vector<vector<double>> &original_matrix, vector<double> &solution);
