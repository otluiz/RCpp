#include <iostream>
#include <Rcpp.h>
using namespace Rcpp;
using namespace std;



// [[Rcpp::export]]
double meanC(NumericVector x){
  int n = x.size();
  double total = 0;
  
  for(int i = 0; i < n; ++i){
    total += x[i];
  }
  return total/n;
}


// You can include R code blocks in C++ files processed with sourceCpp
// (useful for testing and development). The R code will be automatically 
// run after the compilation.
//

/*** R
library(microbenchmark)
x <- runif(1e5)
microbenchmark(
  mean(x),
  meanC(x)
)
*/
