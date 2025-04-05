// 2D Conduction Slover for Finite Element Difference Method

#include<iostream>
#include<vector>
#include<cmath>
#include<fstream>

using namespace std;

const int M = 20;  // Grid rows
const int N = 20; // Grid Columns
const double tol = 1e-5;  // Convergence tolerance
const int maxIter = 5000;  // Maximum iterations

void initializeGrid(vector<vector<double>>& T){
    for (int i = 0; i < M; i++){
        for (int j = 0; j < N; j++){
            if (j == 0)
            T[i][j] = 100.0;  // Left boundary
            else if (j == N-1)
            T[i][j] = 50.0;  // Right Boundary
            else
            T[i][j] = 0.0; // Initial guess (interior)
        }
    }
}

void solveHeatEquation(vector<vector<double>>& T){
    bool converged = false;
    int iter = 0;

    while (!converged && iter < maxIter){
        converged = true;

        for (int i = 1; i < M-1; i++) {
            for (int j = 1; j < N-1; j++) {
                double oldT = T[i][j];

                T[i][j] = 0.25 * (T[i+1][j] + T[i-1][j] + T[i][j+1] + T[i][j-1]);

                if (fabs(T[i][j] - oldT) > tol)
                converged = false;
            }
        }

        iter++;
    }

    cout << "Converged after " << iter << " Iterations .\n";
}

void exportToCSV(const vector<vector<double>>& T, const string& Projects){
    string filepath = "D:\\Projects\\C++ Programs\\" + Projects;
    ofstream file(Projects);

    if (!file) {
        cerr << "Error: Could not open file for writing.\n";

        return;
    }

    for (int i = 0; i < M; i++){
        for (int j = 0; j < N; j++){
            file << T[i][j];
            if (j < N-1)file << ", ";
        }
        file << "\n";
    }

    file.close();
    cout << "Results exported to " << Projects << " \n";
}

int main(){
    vector<vector<double>> T(M, vector<double>(N, 0.0));

    initializeGrid(T);
    solveHeatEquation(T);
    exportToCSV(T, "heat_distribution.csv");

    cout << "Results exported to heat_distribution.csv\n";

    return 0;
}