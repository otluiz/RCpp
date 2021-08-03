#include <Rcpp.h>
using namespace Rcpp;
using namespace std;

// The RcppParallel package includes high level functions for doing parallel programming 
// with Rcpp. For example, the parallelFor function can be used to convert the work of a 
// standard serial “for” loop into a parallel one. This article describes using RcppParallel 
// to transform an R matrix in parallel.
//
// **** Versão Serial de multiplicação de matriz
//
#include <cmath>
#include <algorithm>

// [[Rcpp::export]]
NumericMatrix matrixSqrt (NumericMatrix orig) {
  
  // aloca a matriz que irá retornar
  NumericMatrix mat (orig.nrow(), orig.ncol());
  
  // Transforma isso
  transform(orig.begin(), orig.end(), mat.begin(), ::sqrt);
  
  // retorna a nova matriz
  return mat;
}

// [[Rcpp::depends(RcppParallel)]]
#include <RcppParallel.h>
using namespace RcppParallel;

struct SquareRoot : public Worker{
  // source matrix
  const RMatrix<double> input;
  
  // destination matrix
  RMatrix<double> output;
  
  // initizalize with source and destination
  SquareRoot(const NumericMatrix input, NumericMatrix output)
    : input(input), output(output) {}
  
  // take the square root of the range of elements requested             
  void operator() (size_t begin, size_t end) {
    transform(input.begin() + begin, 
              input.begin() + end,
              output.begin() + begin,
              ::sqrt);
  }
};

// [[Rcpp::export]]
NumericMatrix parallelMatrixSqrt(NumericMatrix x){
  // allocate the output matrix
  NumericMatrix output(x.nrow(), x.ncol());
  
  // SquareRoot functor (pass input and output matrixes)
  SquareRoot squareRoot(x, output);
  
  // call parallelFor to do the work
  parallelFor(0, x.length(), squareRoot);
  
  // return the output matrix
  return output;
}

// You can include R code blocks in C++ files processed with sourceCpp
// (useful for testing and development). The R code will be automatically 
// run after the compilation.
//

// Benchmarks

/*** R
# allocate a matrix
m <- matrix(as.numeric(c(1:100)), nrow = 10, ncol = 10)

# ensure that serial and parallel versions give the same result
stopifnot(identical(matrixSqrt(m), parallelMatrixSqrt(m)))

# compare performance of serial and parallel
library(rbenchmark)
res <- benchmark(parallelMatrixSqrt(m),
                 matrixSqrt(m),
                 order = "relative")

res[,1:4]

*/
