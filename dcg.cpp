#include "dcg.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>

int main(int argc, char * argv[])
{

  using dcg_t = DCG<double>;

  dcg_t dcg;

  const int n = argc > 1 ? atoi(argv[1]) : 100;
  fprintf(stderr, " n =%d\n ", n);

  dcg_t::matrix_t A(n,n);
  dcg_t::vector_t b(n),x(n);

  for (auto& a : A) a = drand48();
  for (auto& v : b) v = drand48();
  for (auto& v : x) x = 0;

  dcg_t::solve(A,b,x);
  


  return 0;

}
