#include <iostream>
#include <string>

// @param:the string is the string being permuted
// @low : the first inex to be permuted, high: the last index to be permuted
// @high: the last index to be permuted
void permute(const std::string& str, int low, int high){
  std::string test = str;
  if(low == high){        //if the indexes are equal its already permuted
    std::cout << str << std::endl;
    return;
  }
  else{
    char temp;
    for(int i = low; i < high+1; i++){
      temp = test[i];
      test[i] = test[low];
      test[low] = temp;
      permute(test, low+1, high);     //consistenly update low, so we can iterate through the string 
    }

  }
}

void permute(const std::string& str){
  permute(str, 0, str.length() -1);
}
