// Rachel Tieu
// 5-14-20
// This program creates a subsequence matrix that we search through in order to find the longest subsequence
//  it contains functions to create the matrix, to find the subsequence, and to print the subsequence itself

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// @worda: the first word that the user enters in the terminal
// @wordb: the second word that the user enters in the terminal
// @return: this function will return the matrix that we will search through for the
//  longest subsequence
// @func: this function will create the matrix that we will search through
vector<vector<int>> create_matrix(string worda, string wordb){
  vector<vector<int>> result(worda.length()+1, vector<int>(wordb.length()+1,0));     //intializing the 2d array to have 0's
  //iterating through the 2d matrix
  for(int i = 1; i < worda.length()+1; i++){
    for(int j = 1; j < wordb.length()+1; j++){
      if(worda[i-1] == wordb[j-1]){
         result[i][j] = result[i-1][j-1] + 1;
       }
      else{
        result[i][j] = max(result[i-1][j], result[i][j-1]);
      }
    }
  }
  return result;
}

// @subseq_matrix: this is the matrix that we will search through for the longest sequence
// @worda: the first word the user entered in the terminal
// @wordb: the second word the user entered in the terminal
// @return: returns a vector that stores the longest subsequence
// @func: this function searches the matrix for the longest subsequence
vector<char> find_subseq(vector<vector<int>> subseq_matrix, string worda, string wordb){
  vector<char> subseq;  //vector that will store the longest subsequence

  //setting indexes so we start at the bottom right corner
  int row = worda.length();
  int col = wordb.length();

  //while rows & cols > 1, preventing from going out of bounds
  while(row >= 1 && col >= 1){
    //if the col before has the same num, move left
    if(subseq_matrix[row][col] == subseq_matrix[row][col-1]){
      col--;
    }
    //if the value in the row above the element we are at is greater than the num in the cell next to the element
    //  decerment rows
    else if(subseq_matrix[row-1][col] > subseq_matrix[row][col-1]){
      row--;
    }

    else{
      subseq.insert(subseq.begin(), wordb[col-1]);   //adding the letter from wordb to the vector, as a part of the longest sequence
      row--;
      col--;
    }
  }

  return subseq;
}


// @longest_subseq: the vector that contains the longest subsequence
// @func: this function iterates through the vector and prints out the longest subsequence
//  and also prints out the size of the lonest subsequence by getting the size of the vector
void print_longest_seq(vector<char> longest_subseq){

  //length of longest subsequence
  cout << longest_subseq.size() << endl;

  //printing out letters of longest subsequence
  for(int i = 0; i < longest_subseq.size(); i++){
    cout << longest_subseq[i];
  }

  cout << endl;
}

// @func: subsequence_driver, calls all the functions above, and will
//  print the lingest subsequence
int subsequence_driver(int argc, char **argv) {
    vector<vector<int>> subseq_matrix;     //2d matrix with values
    vector<char> longest_subsequence;      //vector with longest subsequence

    //create 2d matrix
    subseq_matrix = create_matrix(argv[1], argv[2]);
    //search for longest sequence, save it in the vector
    longest_subsequence = find_subseq(subseq_matrix, argv[1], argv[2]);
    //print the longest sequence 
    print_longest_seq(longest_subsequence);

}

int main(int argc, char **argv) {
    if (argc != 3) {
		cout << "Usage: " << argv[0] << "<word_a>" << "<word_b>" << endl;
		return 0;
    }

    subsequence_driver(argc, argv);

    return 0;
}
