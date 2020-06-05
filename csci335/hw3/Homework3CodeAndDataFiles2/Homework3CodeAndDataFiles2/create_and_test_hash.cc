// Rachel Tieu

#include "quadratic_probing.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table, const string &words_filename, const string &query_filename) {

  hash_table.MakeEmpty();
  ifstream words(words_filename);
  string input;

  while(words >> input){    //inserting the words into the hashtable
     hash_table.Insert(input);
   }

   words.close();

   cout << "number_of_elements: " << hash_table.currsize() << endl;
   cout << "size_of_table: " << hash_table.tablesize() << endl;
   cout << "load_factor: " << hash_table.currsize() / hash_table.tablesize() << endl;
   cout << "collisions: " << hash_table.numofcoll() << endl;
   cout << "avg_collisions: " << hash_table.numofcoll() / hash_table.currsize() << endl;
   //float probes = 0;
   // ifstream query;
   // string qinput;
   // query.open(query_filename);
   //
   // while(query >> qinput){
   //   if(hash_table.Contains(qinput, probes)){
   //     std::cout << qinput << " Found " << probes;
   //   }
   //     std::cout << qinput << " Not Found " << probes;
   // }
}

int testFunctionWrapper(int argument_count, char **argument_list) {
  const string words_filename(argument_list[1]);
  const string query_filename(argument_list[2]);
  const string param_flag(argument_list[3]);

  if (param_flag == "linear") {
    // HashTableLinear<string> linear_probing_table;
    // TestFunctionForHashTable(linear_probing_table, words_filename, query_filename);
  } else if (param_flag == "quadratic") {
    HashTable<string> quadratic_probing_table;
    TestFunctionForHashTable(quadratic_probing_table, words_filename, query_filename);
  } else if (param_flag == "double") {
    // HashTableDouble<string> double_probing_table;
    // TestFunctionForHashTable(double_probing_table, words_filename, query_filename);
  } else {
    cout << "Unknown tree type " << param_flag << " (User should provide linear, quadratic, or double)" << endl;
  }
  return 0;
}

// Sample main for program create_and_test_hash.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE MAIN.
// WE WILL DIRECTLY CALL testFunctionWrapper. ALL FUNCTIONALITY SHOULD BE THERE.
// This main is only here for your own testing purposes.
int main(int argc, char **argv) {

  if (argc != 4) {
    cout << "Usage: " << argv[0] << " <wordsfilename> <queryfilename> <flag>" << endl;
    return 0;
  }

  testFunctionWrapper(argc, argv);
  return 0;
}
