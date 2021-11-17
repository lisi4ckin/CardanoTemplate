#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

const int MatrixSize = 3;

void ReadMatrix(vector<vector<int>>&Matrix, int size, multimap<int, pair<int, int>>&MyMap) {
	int k = 1;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			Matrix[i][j] = k;
			MyMap.insert(pair<int, pair<int, int>>(k, { i, j }));
			k++;
		}
	}
	for (int move = 0; move < 3; move++) {
		vector<vector<int>>AuxilaryMatrix(MatrixSize, vector<int>(MatrixSize));
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				AuxilaryMatrix[j][size - i - 1] = Matrix[i][j];
				MyMap.insert(pair<int, pair<int, int>>(Matrix[i][j], { j, size - i - 1 }));
			}
		}
		Matrix = AuxilaryMatrix;
	}
}

void GenerateTemplateCardano(multimap<int, pair<int, int>>& MyMap) {
	//function to generate Cardano template to messages
}

int main() {
	multimap <int, pair<int, int>> Coordinates;
	vector<vector<int>>Matrix(MatrixSize, vector<int>(MatrixSize));
	ReadMatrix(Matrix, MatrixSize, Coordinates);
	for (int i = 0; i < MatrixSize; i++) {
		for (int j = 0; j < MatrixSize; j++) {
			cout << Matrix[i][j] << " ";
		}
		cout << endl;
	}
	for (auto it = Coordinates.begin(); it != Coordinates.end(); ++it) {
		cout << it->first << " Cordinates" << it->second.first << " " << it->second.second << "\n";
	}
}