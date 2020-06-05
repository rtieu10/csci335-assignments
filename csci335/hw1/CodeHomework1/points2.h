//Rachel Tieu
// Few comments describing the class Points2

#ifndef CSCI335_HOMEWORK1_POINTS2_H_
#define CSCI335_HOMEWORK1_POINTS2_H_

#include <array>
#include <iostream>
#include <cstddef>
#include <string>
#include <sstream>

namespace teaching_project {
// Place comments that provide a brief explanation of the class,
// and its sample usage.
template<typename Object>
class Points2 {
 public:
  // Default "big five" -- you have to alter them for your assignment.
  // That means that you will remove the "= default" statement.
  //  and you will provide an implementation.

  // Zero-parameter constructor.
  // Set size to 0.
  Points2(){
    size_ = 0;
    sequence_ = new::std::array<Object,2>[size_];
  }

  // Copy-constructor.
  // @rhs a Points2 object
  // @post this function creates a deep copy of the rhs object
  Points2(const Points2 &rhs){
    size_ = rhs.size();
    sequence_ = new std::array<Object,2>[size_];
    for(int i = 0; i < rhs.size(); i++){
      sequence_[i] = rhs[i];
    }
  }

  // Copy-assignment. If you have already written
  // the copy-constructor and the move-constructor
  // you can just use:
  // {
  // Points2 copy = rhs;
  // std::swap(*this, copy);
  // return *this;
  // }

  // @post this function creates a deep copy of
  //   the object rhs that is being passed
  Points2& operator=(const Points2 &rhs){
    if(this == &rhs){  //check if the memory is pointing to the same address
      return *this;
    }
    size_ = rhs.size();
    sequence_ = new std::array<Object,2>[size_];
    for(int i = 0; i < size(); i++){
      sequence_[i][0] = rhs.sequence_[i][0];
      sequence_[i][1] = rhs.sequence_[i][1];
    }
    return *this;
  }

  // Move-constructor.
  // @rhs: a Points2 object which we need to Copy
  // @post: This function will copy the properties from rhs and store it into the
  //    the object we are currently working on
  Points2(Points2 &&rhs){
    this->sequence_ = rhs.sequence_;
    this->size_= rhs.size_;
    rhs.size_ = 0;
    rhs.sequence_ = nullptr;
  }

  // Move-assignment.
  // Just use std::swap() for all variables.

  // @post this function moves the rvalues into lvalues
  Points2& operator=(Points2 &&rhs){
    this->size_ = 0;
    delete [] sequence_;
    sequence_ = nullptr;
    std::swap(this->sequence_, rhs.sequence_);
    std::swap(size_, rhs.size_);
    return *this;
  }

//DECONSTRUCTOR, deleting the subarrays, and then the array itself
  ~Points2(){
    size_ = 0;
    delete [] sequence_;
    sequence_ = nullptr;
  }

  // End of big-five.

  // One parameter constructor.
  //shallow copy is creating a pointer that points to
  //@item: a constant array of size 2 that stores Objects
  //@post creates a sequence pointer that points to the address of item (an array)
  Points2(const std::array<Object, 2>& item) {
    this->size_ = 1;
    this->sequence_ = new std::array<Object,2>[this->size_];
    sequence_[0] = item;

  }

  // Read a chain from standard input.
  // @post this function iterates through a text file, and stores it in sequence_
  void ReadPoints2() {
    // Part of code included (without error checking).
    std::string input_line;
    std::getline(std::cin, input_line);
    std::stringstream input_stream(input_line);
    if (input_line.empty()) return;
    int size_of_sequence;
    input_stream >> size_of_sequence;
    this->size_ = size_of_sequence;
    sequence_ = new std::array<Object,2>[this->size_];

    Object token;
    for (int i = 0 ;input_stream >> token; ++i) {   //token will store each number in the line of the text file
      int first = i/2;
      int second = i % 2;
      sequence_[first][second] = token;             //will add the numbers from the txt file to the sequence
    }

  }

  size_t size() const {
    return size_;
  }


  // @location: an index to a location in the sequence.
  // @returns the point at @location.
  // const version.
  // abort() if out-of-range.
  const std::array<Object, 2>& operator[](size_t location) const {  //return type of array size two, given a location return the item there
    if(location > size_ || location < 0){  //if the location provided is greater than the size, then exit because it is out of bounds
      abort();
    }
    return sequence_[location];
  }

 //  @c1: A sequence.
 //  @c2: A second sequence.
 //  @return their sum. If the sequences are not of the same size, append the
 //    result with the remaining part of the larger sequence.

 // @post this function loops through c1 and c2, and finds the larger sequence, it
 //   sets the values of the new object to the larger one, and loops through
 //   the smaller size in order to get the sum and modify the larger object
 friend Points2 operator+(const Points2 &c1, const Points2 &c2) {
   size_t size;
   Points2<Object> sum;
   if(c1.size() > c2.size()){
     size = c2.size();
     sum.size_ = c1.size();
     sum.sequence_ = new std::array<Object,2>[sum.size_];   //creates an object Point2, which has size of the larger object
     sum = c1;                     //storing the values of the larger sequence into the object

   }
   else{
     size = c1.size();
     sum.size_ = c2.size();
     sum.sequence_ = new std::array<Object,2>[sum.size_];
     sum = c2;

   }
   for(int i = 0; i < size; i++){    //goes up to the size of the smaller array, and adds everything and the rest stays the same
      sum.sequence_[i][0] = c1.sequence_[i][0] + c2.sequence_[i][0];
      sum.sequence_[i][1] = c1.sequence_[i][1] + c2.sequence_[i][1];
   }

   return sum;

 }

 // Overloading the << operator.
 // @post function checks if object passed through is empty,
 //   else we can print it using out
 friend std::ostream &operator<<(std::ostream &out, const Points2 &some_points2) {
   if(some_points2.size_ == 0){
     out << "() ";
     return out;
   }
   for(int i = 0; i < some_points2.size(); i++){
     out << "(" << some_points2[i][0] << ", " << some_points2[i][1] << ") ";
   }
   return out;

 }

 private:
  // Sequence of points.
  std::array<Object, 2> *sequence_;
  // Size of sequence.
  size_t size_;

};

}  // namespace teaching_project
#endif // CSCI_335_HOMEWORK1_POINTS2_H_
