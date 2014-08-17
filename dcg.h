#pragma once

#include <valarray>
#include <cassert>
#include <cmath>


template<typename real_t>
struct DCG
{
  typedef std::valarray<real_t> vector_t;
  class matrix_t
  {
    private:
      vector_t m;
      int _nrow, _ncol;

    public:
      matrix_t(const int nrow, const int ncol) :
        m(vector_t(nrow*ncol)), _nrow(nrow), _ncol(ncol) {}

      int nrow() const { return _nrow; }
      int ncol() const { return _ncol; }

      const real_t& operator()(const int row, const int col) const 
      {
        return m[row*_ncol + col];
      }
      real_t&& operator()(const int row, const int col) 
      {
        return m[row*_ncol + col];
      }

      auto begin() -> decltype(std::begin(m)) { return std::begin(m); }
      auto end()   -> decltype(std::end(m)  ) { return std::end(m);   }

  };

  static real_t dot(const vector_t& a, const vector_t& b) 
  { 
    return (a*b).sum(); 
  }
  static vector_t matvec(const matrix_t& A, const vector_t& b) 
  {
    vector_t x(b.size());
    const int nrow = A.nrow();
    const int ncol = A.ncol();
    for (int i = 0; i < nrow; i++)
    {
      x[i] = 0.0;
      for (int j = 0; j < ncol; j++)
        x[i] += A(i,j)*b[j];
    }
    return x;
  }

  static void solve(const matrix_t& A, const vector_t& b, vector_t& x)
  {
    vector_t r = b - matvec(A,x);
    vector_t p = r;
    real_t   rsold = dot(r,r);

    for (int i = 0; i < 1000000; i++)
    {
      auto Ap    = matvec(A,p);
      auto alpha = rsold / dot(p,Ap);
      x += alpha*p;
      r -= alpha*Ap;
      auto rsnew = dot(r,r);
      fprintf(stderr," i= %d: rsnew= %g rsold= %g \n",i, rsnew,rsold);
      if (std::sqrt(rsnew) < 1e-10)
        break;
      assert(!std::isnan(rsnew));
      p = r + (rsnew/rsold)*p;
      rsold = rsnew;
    }
  }
  
};
