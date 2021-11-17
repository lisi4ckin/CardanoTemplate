#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <map>

using namespace std;

const int MatrixSize = 3;

typedef vector<vector<int>> matrix_t;

void ReadMatrix(matrix_t &Matrix, int size, multimap<int, pair<int, int>>&MyMap) {
	int k = 1;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			Matrix[i][j] = k;
			MyMap.insert(pair<int, pair<int, int>>(k, { i, j }));
			k++;
		}
	}
	for (int move = 0; move < 3; move++) {
        matrix_t AuxilaryMatrix(MatrixSize, vector<int>(MatrixSize));
        for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
                AuxilaryMatrix[j][size - i - 1] = Matrix[i][j];
                if (move == 0) {
                    MyMap.insert(pair<int, pair<int, int>>(Matrix[i][j], {2 * size - i - 1, j}));
                }
                if (move == 1){
                    MyMap.insert(pair<int, pair<int, int>>(Matrix[i][j], {j + size, 2 * size - i - 1}));
                }
                if (move == 2){
                    MyMap.insert(pair<int, pair<int, int>>(Matrix[i][j], {size - i - 1, j + size}));
                }
            }
		}
		Matrix = AuxilaryMatrix;
	}
}

matrix_t GenerateTemplateCardano(multimap<int, pair<int, int>>& MyMap) {
    vector< pair<int, int> >res;
    for (int i = 1; i <=MatrixSize * MatrixSize; i++){
        int count = 0;
        vector<pair <int, int>> coord;
        for(auto it = MyMap.begin(); it != MyMap.end() && count < 4; ++it){
            if (it->first == i){
                coord.push_back(it->second);
                count++;
            }
        }
        res.push_back(coord[rand() % 4]);
    }
    matrix_t Template(2 * MatrixSize, vector <int>(2 * MatrixSize, 0));
    for (int i = 0; i < res.size(); i++){
        Template[res[i].first][res[i].second] = i + 1;
    }
    return Template;
}

int main() {
    srand(time(NULL));
    multimap <int, pair<int, int>> Coordinates;
    matrix_t Matrix(MatrixSize, vector<int>(MatrixSize));
	ReadMatrix(Matrix, MatrixSize, Coordinates);
//	for (int i = 0; i < MatrixSize; i++) {
//		for (int j = 0; j < MatrixSize; j++) {
//			cout << Matrix[i][j] << " ";
//		}
//		cout << endl;
//	}
	matrix_t Template = GenerateTemplateCardano(Coordinates);
	for (int i = 0; i < 2 * MatrixSize; i++){
	    for (int j = 0; j < 2 * MatrixSize; j++){
	        cout << Template[i][j] << " ";
	    }
	    cout << endl;
	}
//	for (auto it = Coordinates.begin(); it != Coordinates.end(); ++it) {
//		cout << it->first << " Cordinates: " << it->second.first << " " << it->second.second << "\n";
//	}
}