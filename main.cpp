#include <Rcpp.h>
using namespace Rcpp;


// [[Rcpp::export]]
double meanC(NumericVector x){
  int n = x.size();
  double total = 0;
  
  for(int i = 0; i < n; ++i){
    total += x[i];
  }
  return total/n;
}

/*
 Instalando pacotes direto da Internet
 https://cloud.r-project.org/src/contrib/classInt_0.4-3.tar.gz'
 devtools::install_github("r-lib/rlang", build_vignettes = TRUE)
*/

// You can include R code blocks in C++ files processed with sourceCpp
// (useful for testing and development). The R code will be automatically 
// run after the compilation.
//

/*** R
#library(microbenchmark)
x <- runif(1e5)
# microbenchmark(
#   mean(x),
#   meanC(x)
# )
bench::mark(
  mean(x),
  meanC(x)
)

*/
