#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
RObject callWithOne(Function f){
  return f(1);
}


// You can include R code blocks in C++ files processed with sourceCpp
// (useful for testing and development). The R code will be automatically 
// run after the compilation.
//

/*** R
y = callWithOne(function(x) x + 1)
y
*/


// [[Rcpp::export]]
List lapply1 (List input, Function f){
  int n = input.size();
  List out(n);
  
  for (int i = 0; i < n; i++)
    out[i] = f(input[i]);
  
  return out;
}

/*** R
lapply1(1, "y")
*/
