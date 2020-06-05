// Rachel Tieu
// Main file for Part2(a) of Homework 2.
// 3-1-20
// This program will parse through a given text file and build a tree from the textfile
// it allows the user to input recognition_sequence_ and it prints the values associated
// with the recognition sequence
#include "avl_tree_p2a.h"
#include "sequence_map.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>

using namespace std;

namespace {

// @db_filename: the text file that needs to be parsed, we are using it to build
//                our tree
// @a_tree: the tree that we are going to insert the SequenceMap obects to
// @post: this function parses the textfile that is passed through, and inserts the
//        SequenceMap object into the tree
template <typename TreeType>
void parser(const string &db_filename, TreeType& a_tree){
   std::string db_line;
   std::string junk;
   std::ifstream fin(db_filename.c_str());

   for(int i = 0; i < 10; i++){ //stores all lines of junk
     getline(fin,junk);
   }

  while(getline(fin,db_line)){
     std::string an_enz_acro;
     std::string a_rec_seq;
     db_line = db_line.substr(0, db_line.length()-2);
     std::stringstream strstream(db_line);
     getline(strstream,an_enz_acro, '/');  //a delimiter that parses by the slash
     //an_enz_acro = an_enz_acro;  //saves the parsed part of the strign
     while(getline(strstream, a_rec_seq,'/')){   // how to grab the rest of the line after delimiter
         SequenceMap new_sequence_map(a_rec_seq,an_enz_acro);
         a_tree.insert(new_sequence_map);
     }
   }

   //allow the user to input the recognition sequence they want to use
   std::string rec_seq_search;
   while(cin >> rec_seq_search){
     SequenceMap temp(rec_seq_search, "");
     cout << a_tree.find(temp) << endl;
   }


   fin.close();
 }


// @db_filename: an input filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
// @post: this function calls the parser function that parses through the file
template <typename TreeType>
void QueryTree(const string &db_filename, TreeType &a_tree) {
  parser(db_filename, a_tree);
  cout << "-------------------" << endl;
  a_tree.printTree();
}


}  // namespace

 int
 main(int argc, char **argv) {
   if (argc != 2) {
     cout << "Usage: " << argv[0] << " <databasefilename>" << endl;
     return 0;
   }
   const string db_filename(argv[1]);
   cout << "Input filename is " << db_filename << endl;
   // Note that you will replace AvlTree<int> with AvlTree<SequenceMap>
   AvlTree<SequenceMap> a_tree;
   QueryTree(db_filename, a_tree);
   return 0;
 }
