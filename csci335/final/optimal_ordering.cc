#include <iostream>
#include <string>

using namespace std;


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <limits>

using namespace std;

vector<int> create_dimensions_list(string filename){
  string strdimension;
  vector<int> dimensions_list;  //storing dimensions from the textfile

  ifstream fin;
  fin.open(filename);

  while(getline(fin, strdimension)){
    if(strdimension.length() > 0){
      dimensions_list.push_back(stoi(strdimension));
    }
  }

  // for(int i = 0; i < dimensions_list.size(); i++){
  //   cout << dimensions_list[i] << " ";
  // }
  return dimensions_list;
}


vector<vector<int>> create_matrix(vector<int> dim_list){
  vector<vector<int>> mult_matrix;
  mult_matrix.resize(dim_list.size());

  //initializing the size of the 2d matrix
  for(int i = 0; i < mult_matrix.size(); i++){
    mult_matrix[i].resize(dim_list.size());
  }

  //setting the diagnol, first row, and col = 0
  for(int i = 0; i < dim_list.size(); i++){
    mult_matrix[i][i] = 0;
    mult_matrix[0][i] = 0;
    mult_matrix[i][0] = 0;
  }

  return mult_matrix;
}


vector<vector<int>> matrix_multiplication(vector<int> dimensions_list, vector<vector<int>> mult_matrix){
  //1st for loop isfor going diagnolly in the graph
  for(int l = 1; l < dimensions_list.size()-1; l++)
    for(int i = 0; i < dimensions_list.size()-l; i++){
      int j = i + l;
      int min_val = std::numeric_limits<int>::max();
      for(int k = i; k < j; k++){
        int optimal = mult_matrix[i][k] + mult_matrix[k+1][j] + (dimensions_list[i-1]*dimensions_list[k]* dimensions_list[j]);
        if(optimal < min_val){
          min_val = optimal;
          mult_matrix[i][j] = k;
        }
      }
    }
    return mult_matrix;
}



int multiplication_driver(int argc, char **argv) {
    //Please place all functionality in here instead of the main.
    //Feel free to make any functions or objects you wish, as long as we only call this function.
    vector<int> dimensions;
    vector<vector<int>> result_matrix;
    dimensions = create_dimensions_list(argv[1]);

    result_matrix = create_matrix(dimensions);
    result_matrix = matrix_multiplication(dimensions, result_matrix);

    //SEG FAULT!!!
    cout << result_matrix[1][dimensions.size()-1] << endl;

    for(int i = 0; i < dimensions.size(); i++){
      for(int j = 0; j < dimensions.size(); j++){
        cout << result_matrix[i][j] << " ";
      }
      cout << endl;
    }

}


int ordering_driver(int argc, char **argv) {
    //Please place all functionality in here instead of the main.
    //Feel free to make any functions or objects you wish, as long as we only call this function.

    vector<int> dimensions;
    vector<vector<int>> result_matrix;
    dimensions = create_dimensions_list(argv[1]);

    result_matrix = create_matrix(dimensions);
    result_matrix = matrix_multiplication(dimensions, result_matrix);

    //SEG FAULT!!!
    cout << result_matrix[1][dimensions.size()-1] << endl;

    for(int i = 0; i < dimensions.size(); i++){
      for(int j = 0; j < dimensions.size(); j++){
        cout << result_matrix[i][j] << " ";
      }
      cout << endl;
    }

}

int main(int argc, char **argv) {
    if (argc != 2) {
		cout << "Usage: " << argv[0] << "<dimensions_file>" << endl;
		return 0;
    }

    ordering_driver(argc, argv);

    return 0;
}
