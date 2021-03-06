#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <map>

using namespace std;

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
        matrix_t AuxilaryMatrix(size, vector<int>(size));
        for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
                AuxilaryMatrix[i][size - j - 1] = Matrix[i][j];
                if (move == 0) {
                    MyMap.insert(pair<int, pair<int, int>>(Matrix[i][j], {j, 2 * size - i - 1 }));
                }
                if (move == 1){
                    MyMap.insert(pair<int, pair<int, int>>(Matrix[i][j], {2 * size - i - 1, j + size }));
                }
                if (move == 2){
                    MyMap.insert(pair<int, pair<int, int>>(Matrix[i][j], {2 * size - j - 1, i }));
                }
            }
		}
		Matrix = AuxilaryMatrix;
	}
}
template<typename T>
void WriteMatrix(const T&Matrix){
    ofstream out("output.txt");
    for (int i = 0; i < Matrix.size(); i++){
        for (int j = 0; j < Matrix.size(); j++){
            out << Matrix[i][j];
        }
    }
}

template<typename T>
pair<T, T>NormalCoord(pair<T, T>& Coord, int MatrixSize) {
    if (Coord.first >= MatrixSize) {
        Coord.first -= MatrixSize;
    }
    if (Coord.second >= MatrixSize) {
        Coord.second -= MatrixSize;
    }
    return Coord;
}

matrix_t GenerateTemplateCardano(multimap<int, pair<int, int>>& MyMap, int MatrixSize) {
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
        bool f = false;
        while (!f) {
            pair <int, int>position = coord[rand() % 4];
            for (int i = 0; i < res.size(); i++) {
                if (position.second == res[i].first && position.first == res[i].second) {
                    f = true;
                    break;
                }
            }
            if (f) {
                f = false;
            }
            else {
                res.push_back(position);
                f = true;
            }
        }
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
            AuxilaryMatrix[i][j] = Matrix[Matrix.size() -j - 1][i];
        }
    }
    return AuxilaryMatrix;
}

matrix_c CodingText(string text, matrix_t &Matrix, int MatrixSize){
    matrix_c Result(2 * MatrixSize, vector<char>(2 * MatrixSize, ' '));
    for (int i = 0; i < 4 * MatrixSize * MatrixSize; i++) {
        [&] {
            for (int j = 0; j < 2 * MatrixSize; j++) {
                for (int k = 0; k < 2 * MatrixSize; k++) {
                    if (Matrix[j][k] == 0){
                        continue;
                    }
                    if ((i + 1) % (MatrixSize * MatrixSize) == 0 && Matrix[j][k] == (MatrixSize * MatrixSize)){
                        Result[j][k] = char(text[i]);
                        return;
                    }
                    else if (Matrix[j][k] == (i + 1) % (MatrixSize * MatrixSize)) {
                        Result[j][k] = char(text[i]);
                        return;
                    }
                }
            }
        }();
        if ((i + 1) % (MatrixSize * MatrixSize) == 0){
            Matrix = TurnMatrix(Matrix);
        }
    }
    return Result;
}

string EncodingText(matrix_c& Text, matrix_t& Template, int MatrixSize) {
    string result = "";
    for (int move = 0; move < 4; move++) {
        for (int number = 1; number <=MatrixSize*MatrixSize; number++){
            for (int i = 0; i < Template.size(); i++) {
                for (int j = 0; j < Template.size(); j++) {
                    if (Template[i][j] == number) {
                        result += Text[i][j];
                    }
                }
            }
        }
        Template = TurnMatrix(Template);
    }
    return result;
}

string ReadTextFromFile(string FileName){
    string str = "", result = "";
    ifstream input(FileName);
    while(!input.eof()){
        string str = "";
        getline(input, str);
        result += str;
    }
    return result;
}

int main() {
    srand(time(NULL));
    string Text = ReadTextFromFile("D:/Other/Programing/Projects/Summer2021/CourseWork/input.txt");
    int MatrixSize = sqrt(Text.length() / 4);
    multimap <int, pair<int, int>> Coordinates;
    matrix_t Matrix(MatrixSize, vector<int>(MatrixSize));
	ReadMatrix(Matrix, MatrixSize, Coordinates);
	matrix_t Template = GenerateTemplateCardano(Coordinates, MatrixSize);
    cout << "Template is: \n";
	WriteMatrix(Template);
	matrix_c Text_Coding = CodingText(ReadTextFromFile("D:/Other/Programing/Projects/Summer2021/CourseWork/input.txt"), Template, MatrixSize);
    cout << "Coded text is: \n";
    WriteMatrix(Text_Coding);
    cout << "Encoded text is: ";
    cout << EncodingText(Text_Coding, Template, MatrixSize) << endl;
    return 0;
}
