#include <iostream>

#include <cstddef>

#include <cstdint>

struct MyCls

{

     std::uint32_t x, y;

     std::int32_t *p;



     MyCls (std::size_t n): x(0), y(0), p (new std::int32_t [n]) {}

     ~MyCls () {delete [] p;}

};

int main ()

{

  MyCls c(42);

  std::cout <<sizeof(c);

  return 0;

}