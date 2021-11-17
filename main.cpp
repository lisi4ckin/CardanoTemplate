#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <map>

using namespace std;

const int MatrixSize = 3;

typedef vector<vector<int>> matrix_t;
typedef vector<vector<char>>matrix_c;

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
template<typename T>
void WriteMatrix(const T&Matrix){
    for (int i = 0; i < Matrix.size(); i++){
        for (int j = 0; j < Matrix.size(); j++){
            cout << Matrix[i][j] << " ";
        }
        cout << endl;
    }
}

matrix_t GenerateTemplateCardano(multimap<int, pair<int, int>>& MyMap) {
    vector< pair<int, int> >res;
    for (auto it = MyMap.begin(); it != MyMap.end(); ++it){
        //empty for
    }
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

matrix_t TurnMatrix(matrix_t &Matrix){
    matrix_t AuxilaryMatrix(Matrix.size(), vector<int>(Matrix.size()));
    for (int i = 0; i < Matrix.size(); i++){
        for (int j = 0; j < Matrix.size(); j++){
            AuxilaryMatrix[j][Matrix.size() - i - 1] = Matrix[i][j];
        }
    }
    return AuxilaryMatrix;
}

matrix_c CodingText(string text, matrix_t &Matrix){
    matrix_c Result(Matrix.size(), vector<char>(Matrix.size(), ' '));
    for (int i = 0; i < 4 * MatrixSize * MatrixSize; i++) {
        [&] {
            for (int j = 0; j < 2 * MatrixSize; j++) {
                for (int k = 0; k < 2 * MatrixSize; k++) {
                    if (Matrix[j][k] == 0){
                        continue;
                    }
                    if ((i + 1) % (MatrixSize * MatrixSize) == 0 && Matrix[j][k] == (MatrixSize * MatrixSize)){
                        Result[j][k] = text[i];
                        return;
                    }
                    else if (Matrix[j][k] == (i + 1) % (MatrixSize * MatrixSize)) {
                        Result[j][k] = text[i];
                        return;
                    }
                }
            }
        }();
        if ((i + 1) % (MatrixSize * MatrixSize) == 0){
            WriteMatrix(Result);
            cout << i + 1 << endl;
            Matrix = TurnMatrix(Matrix);
            cout << "Turn template" << endl;
            WriteMatrix(Matrix);
        }
    }
    return Result;
}

int main() {
    srand(time(NULL));
    multimap <int, pair<int, int>> Coordinates;
    matrix_t Matrix(MatrixSize, vector<int>(MatrixSize));
	ReadMatrix(Matrix, MatrixSize, Coordinates);
	Matrix = TurnMatrix(Matrix);
	WriteMatrix(Matrix);
	matrix_t Template = GenerateTemplateCardano(Coordinates);
	WriteMatrix(Template);
	WriteMatrix(CodingText("mamalrkamamalrkamamalrkamamalrkamama", Template));
    return 0;
}
