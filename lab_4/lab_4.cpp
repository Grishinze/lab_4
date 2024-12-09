#include <iostream>
using namespace std;

void inputMatrix(double** matrix, int N, int M)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
			cin >> matrix[i][j];
	}
}

void outputMatrix(double** matrix, int N, int M)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
			cout << matrix[i][j] << " ";
		cout << endl;
	}
	
}


int main(int argc, char* argv[])
{
	int N, M;
	cin >> N >> M;

	double** matrix = new double* [N];
	for (int i = 0; i < N; i++)
	{
		matrix[i] = new double[M];
	}
	inputMatrix(matrix, N, M);
	outputMatrix(matrix, N, M);

}