// Rachel Tieu
// 3-1-20
// This file holds the SequenceMap class and the big five for the SequenceMap
// class, it holds the merge function, and overloads the << operator

#pragma once
#include <vector>
#include <iostream>
#include <string>

using namespace std;

class SequenceMap{
public:
  //Default Constructor
  SequenceMap()=default;
  //Copy Constructor
  SequenceMap(const SequenceMap &rhs)=default;
  //Move Constructor
  SequenceMap(SequenceMap&& rhs)=default;
  //Copy Assignment
  SequenceMap& operator=(const SequenceMap &rhs)=default;
  //Move Assignment
  SequenceMap& operator=(SequenceMap &&rhs)=default;
  //Destructor
  ~SequenceMap()=default;

  // @a_rec_seq: a recognition sequence which acts as a key for our
  //     SequenceMap object
  // @an_enz_acro: this is an enzyme acronym which will be added to
  //     the enzyme acronym vector, which are the values of the
  //     SequenceMap object
  // @post: parameterized constructor, which will create the SequenceMap
  //      object with a given recognition_sequence_ and an_enz_acro
  SequenceMap(const string &a_rec_seq, const string &an_enz_acro){
    recognition_sequence_ = a_rec_seq;
    enzyme_acronyms_.push_back(an_enz_acro);
  }

  // @rhs: a SequenceMap object that we are checking the recognition_sequence_ of
  // @post: this function compares the recognition_sequence_ of the current object
  //      and the object thats passed through

  bool operator<(const SequenceMap &rhs)const{
    return this->recognition_sequence_ < rhs.recognition_sequence_;
  }

  // @some_sequence_map: a SequenceMap object that we are printing
  //    out the enzyme_acronyms_ vector of
  friend std::ostream &operator<<(std::ostream &out, const SequenceMap &some_sequence_map){
    if(some_sequence_map.enzyme_acronyms_.size()==0){
      out << "Not Found";
    }
    for(int i = 0; i < some_sequence_map.enzyme_acronyms_.size(); i++){
      out << some_sequence_map.enzyme_acronyms_[i] << " ";
    }
    return out;
  }

  // @other_sequence: a SequenceMap object that we are iterating through
  // @post: this function will iterate through the given SequenceMap object
  //      and merge its elements with the elements of the current object

  void Merge(const SequenceMap &other_sequence){
    for(const auto& x: other_sequence.enzyme_acronyms_){
      this->enzyme_acronyms_.push_back(x);
    }
  }

  // @post: this function allows access to the recognition_sequence_
  //      which is a private member
  string getSeq(){
    return recognition_sequence_;
  }

private:
  string recognition_sequence_;
  vector<string> enzyme_acronyms_;
};
