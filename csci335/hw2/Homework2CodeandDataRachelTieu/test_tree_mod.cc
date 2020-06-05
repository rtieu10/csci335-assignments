// Rachel Tieu
// 3-1-20
// This program will parse through a text file, and compare the strings to those
// in a tree storing SequenceMap objects, and the program also has functions
// that search through the tree, and remove elements from the tree

#include "avl_tree_p2c.h"
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
    //Tree<SequenceMap> a_tree;
    std::string db_line;
    std::string junk;
    std::ifstream fin(db_filename.c_str());

    for(int i = 0; i < 10; i++){ //stores all lines of junk
      getline(fin,junk);
    }

    while(getline(fin,db_line)){
      std::string an_enz_acro;
      std::string a_rec_seq;
      std::stringstream strstream(db_line);
      getline(strstream,an_enz_acro, '/');  //a delimiter that parses by the slash
      //an_enz_acro = an_enz_acro;  //saves the parsed part of the strign
      while(getline(strstream, a_rec_seq,'/')){   // how to grab the rest of the line after delimiter

        if(!a_rec_seq.empty()){             // if(a_rec_seq[0] != '/'){
          SequenceMap new_sequence_map(a_rec_seq,an_enz_acro);
          a_tree.insert(new_sequence_map);
        }
      }
    }

    fin.close();
  }


  // @seq_filename: the sequence text file that we are iterating through to compare
  //                the sequences to those stroed in the tree
  // @a_tree: the tree that we are iterating through and checking the SequenceMap objects
  //          stored within it
  // @seqvec: the vector that stores all the recognition sequences from the text file
  // @count: a float value that counts the amount of successful queries
  // @recursivecount: a float variable which counts the amount of recursive calls for the
  //                  find function
  // @post: this function searches through a tree, and compares the recognition sequence
  //         values to the strings in the sequence text file and keeps a count of the
  //         amount of recursive calls and successful queries
template <typename TreeType>
void SeqSearch(const string &seq_filename, TreeType &a_tree, vector<SequenceMap> seqvec, float& count, float& recursivecount){
    std::string seq_line;
    std::ifstream fin(seq_filename.c_str());

    while(getline(fin,seq_line)){
      SequenceMap temp(seq_line, "");
      seqvec.push_back(temp);
    }

    for(int i = 0; i < seqvec.size(); i++){
        if(a_tree.find(seqvec[i],recursivecount).getSeq() != "Not Found"){   //if the search is successful
           count++;
         }
        //cout << seqvec[i] << endl;
      }
      recursivecount = recursivecount/seqvec.size();

}


// @seq_filename: the sequence text file that we are iterating through to compare
//                the sequences to those stroed in the tree
// @a_tree: the tree that we are iterating through and checking the SequenceMap objects
//          stored within it
// @seqvec: the vector that stores all the recognition sequences from the text file
// @removecount: a float value that counts the amount of successful removes
// @recursiveremove: a float variable which counts the amount of recursive calls to the
//                  remove function
// @post: this function searches through a tree, and compares the recognition sequence
//         values to the strings in the sequence text file and keeps a count of the
//         amount of recursive calls and successful removes
template <typename TreeType>
void SeqRemove(const string &seq_filename, TreeType &a_tree, vector<SequenceMap> seqvec, float& removecount, float& recursiveremove){
  std::string seq_line;
  std::ifstream fin(seq_filename.c_str());

  while(getline(fin,seq_line)){      //created temp sequencemap objects and pushed it to sequence vector
    SequenceMap temp(seq_line, "");
    seqvec.push_back(temp);
  }

  removecount = a_tree.TotalNodeCount();

  for(int i=0; i < seqvec.size(); i+=2){
    a_tree.remove(seqvec[i],recursiveremove);
  }

  removecount = removecount - a_tree.TotalNodeCount();


}


// @db_filename: an input database filename.
// @seq_filename: an input sequences filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
// @post: this function will call the functions we created in the sequence_map class
//        and call the search and remove functions and print the results
template <typename TreeType>
void TestTree(const string &db_filename, const string &seq_filename, TreeType &a_tree) {
  // Code for running Part2(b)
  parser(db_filename, a_tree);
  //std::cout << "2: " << a_tree.TotalNodeCount() << std::endl;
  //std::cout << "3a: " << a_tree.AverageDepth() << std::endl;
  //std::cout << "3b: " << a_tree.LogRatio() << std::endl;
  vector<SequenceMap> sequencevec;       //vector that will store lines of sequence text file
  float count = 0;
  float recursivecount = 0;
  SeqSearch<TreeType>(seq_filename, a_tree, sequencevec, count, recursivecount);
  //cout << "4a: " << count << endl;
  //cout << "4b: " << recursivecount<< endl;
  float removes = 0;
  float recursiveremoves = 0;
  SeqRemove<TreeType>(seq_filename,a_tree,sequencevec,removes,recursiveremoves);
  cout << "5a: " << removes << endl;
  cout << "5b: " << recursiveremoves/210 << endl;
  //cout << "6a: " << a_tree.TotalNodeCount() << endl;
  //cout << "6b: " << a_tree.AverageDepth() << endl;
  //cout << "6c: " << a_tree.LogRatio() << endl;
}

}  // namespace

int
main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string seq_filename(argv[2]);
  cout << "Input file is " << db_filename << ", and sequences file is " << seq_filename << endl;
  // Note that you will replace AvlTree<int> with AvlTree<SequenceMap>
  AvlTree<SequenceMap> a_tree;
  TestTree(db_filename, seq_filename, a_tree);

  return 0;
}
