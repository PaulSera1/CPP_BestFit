#include <iostream>
#include <math.h>
#include <vector>
#include <tuple>

using namespace std;

void inverse(vector<vector<double>> input, vector<vector<double>> &output);
void transpose(vector<vector<double>> input, vector<vector<double>> &output);
vector<vector<double>> multiply(vector<vector<double>> m1, vector<vector<double>> m2);

typedef vector<tuple<double, double>> tuple_list;
const tuple_list points = {
        make_tuple(1, 2),
        make_tuple(2, 5),
        make_tuple(3, 8),
        make_tuple(4, 11)
};

int main() {
    vector<vector<double>> A, b, A_T, A_TA, invA, other;
    int degree;
    cout << "enter degree: ";
    cin >> degree;
    for(tuple_list::const_iterator i = points.begin(); i != points.end(); ++i) {
        vector<double> row;
        double x = get<0>(*i);
        for(int j = 0; j < degree + 1; j++)
            row.push_back(pow(x, j));
        A.push_back(row);
        b.push_back(vector<double>{get<1>(*i)});
    }
    transpose(A, A_T); //A_T is transpose of A
    A_TA = multiply(A_T, A); //A_TA is A_T * A
    inverse(A_TA, invA); //inverse of A_T * A is invA
    other = multiply(multiply(invA, A_T), b);
    for(auto i : other) for(auto j : i) cout << j << " ";
    return 0;
}

void inverse(vector<vector<double>> input, vector<vector<double>> &output) {
    vector<vector<double>> copy = input;
    vector<vector<double>> identity;
    for(size_t i = 0; i < input.size(); i++) {
        vector<double> row;
        for(size_t j = 0; j < input.size(); j++) {
            if(i == j) row.push_back(1.0);
            else row.push_back(0.0);
        }
        identity.push_back(row);
    }
    for(size_t pivot = 0; pivot < input.size(); pivot++) {
        double x = 1.0 / copy[pivot][pivot];
        for(size_t j = 0; j < input.size(); j++) {
            copy[pivot][j] *= x;
            identity[pivot][j] *= x;
        }
        for(size_t i = 0; i < input.size(); i++) {
            if(i != pivot) {
                double y = copy[i][pivot];
                for(size_t j = 0; j < input.size(); j++) {
                    copy[i][j] = copy[i][j] - y * copy[pivot][j];
                    identity[i][j] = identity[i][j] - y * identity[pivot][j];
                }
            }
        }
    }
    output = identity;
}

void transpose(vector<vector<double>> input, vector<vector<double>> &output) {
    for(size_t i = 0; i < input[0].size(); i++) {
        vector<double> row;
        for(size_t j = 0; j < input.size(); j++)
            row.push_back(input[j][i]);
        output.push_back(row);
    }
}

vector<vector<double>> multiply(vector<vector<double>> m1, vector<vector<double>> m2) {
    vector<vector<double>> output;
    for(size_t i = 0; i < m1.size(); i++) {
        vector<double> row;
        for(size_t j = 0; j < m2[0].size(); j++)
            row.push_back(0);
        output.push_back(row);
    }
    for(size_t i = 0; i < m1.size(); i++) {
        for(size_t j = 0; j < m2[0].size(); j++) {
            double sum = 0;
            for(size_t k = 0; k < m1[0].size(); k++)
                sum += (m1[i][k] * m2[k][j]);
            output[i][j] = sum;
            sum = 0;
        }
    }
    return output;
}