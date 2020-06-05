// Rachel Tieu
// 5-14-20
// This program contains the code to create a matrix that contains the efficient ways to multiply the matrices that are provided in the text file
//  that's provided

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <limits>


using namespace std;

// @filename: this is the textfile that we are given in the terminal
// @function: this function reads the textfile and formats a vector that stores the dimensions of
//  the matrix
// @return: this function returns the vector that contains the dimensions of the matrices
vector<int> create_dimensions_list(string filename){
  string strdimension;
  vector<int> dimensions_list;  //storing dimensions from the textfile

  //open text file
  ifstream fin;
  fin.open(filename);

  //iterate through text file, push values to vector
  while(getline(fin, strdimension)){
    if(strdimension.length() > 0){
      dimensions_list.push_back(stoi(strdimension));
    }
  }

  return dimensions_list;
}

// @dim_list: this is the vector that stores the dimensions of the matrices
// @func: this function formats the 2d matrix, and intializes the first row, column, and diagnol to 0's
// @return: this returns the 2d matrix that we will be modifying the values of
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

// @dimensions_list: this is the vector that contains the dimensions of the matrices
// @mult_matrix: this is the 2d matrix that we created, and will be inserting values into
// @return: this function will return the 2d matrix with the optimal multiplication
// @func: this function inserts optimal mutiplications into the 2d matrix
vector<vector<int>> matrix_multiplication(vector<int> dimensions_list, vector<vector<int>> mult_matrix){
  //1st for loop is for going diagnolly in the graph
  for(int l = 1; l < dimensions_list.size()-1; l++){
    for(int i = 0; i < dimensions_list.size()-l; i++){
      //initialize j
      int j = i + l;
      int min_val = std::numeric_limits<int>::max();     //setting value to infinity
      for(int k = i; k < j; k++){
        int optimal = mult_matrix[i][k] + mult_matrix[k+1][j] + (dimensions_list[i-1]*dimensions_list[k]* dimensions_list[j]);  //finding optimal multiplication
        //if the optimal value is less than the min val, update optimal
        if(optimal < min_val){
          min_val = optimal;
        }
      }
        mult_matrix[i][j] = min_val;
    }
  }
    return mult_matrix;
}


// @func: this is the driver function that calls all the helper functions, that stores the values from the text values,
//  and creates the 2d matrix and fills it with optimal multiplication and prints the last value we inserted in the matrix
int multiplication_driver(int argc, char **argv) {

    vector<int> dimensions;               //vector storing dimensions for the matrix
    vector<vector<int>> result_matrix;    //2d matrix that stores the optimal multiplications

    //creating the vector to store the dimensions
    dimensions = create_dimensions_list(argv[1]);

    //creating our matrix, and initiliazing diagnol, first row, and col to 0
    result_matrix = create_matrix(dimensions);

    //performing matrix multiplication and saving values into the 2d matrix
    result_matrix = matrix_multiplication(dimensions, result_matrix);

    //outputting the last value we inserted into the matrix
    cout << result_matrix[1][dimensions.size()-1] << endl;

}

int main(int argc, char **argv) {
    if (argc != 2) {
		cout << "Usage: " << argv[0] << "<dimensions_file>" << endl;
		return 0;
    }

    multiplication_driver(argc, argv);

    return 0;
}
