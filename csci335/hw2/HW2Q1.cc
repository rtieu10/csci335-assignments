// Rachel Tieu
// 3-1-20
// This program iterates through some container and returns an iterator
// to the object that we are looking for

#include <iostream>
#include <iterator>

template<typename iterator, typename object>

// @start:gives us the iterator to the beginning of some container
// @end:gives us the iterator to the end of some container
// @x:the object we are looking for in the container
// @post:returns the iterator to the object, if not found returns end
iterator my_find(iterator start, iterator end, const object& x){
  for(auto it = start; it != end; it++){
    if(*it == x){
      return it;
    }
  }
    return end;
}
