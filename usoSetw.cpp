#include <iostream>
#include <iomanip>
//#include <Rcpp.h>
//using namespace Rcpp;
using namespace std;

// Este programa implementa um função recursiva
// a função timesTwo imprime o resultado em duas colunas

// [[Rcpp::export]]
int timesTwo(const int linha = 1, const int coluna = 1, const int contador = 6) {

  if (contador < 1) {
    cout << endl;
    return 0;
  }
  
  else if (linha < 5) {
    cout << setw(3) << linha;
    cout << endl;
    timesTwo(linha + 1, coluna, contador - 1);
  }
  else if (coluna < 5) {
    cout << setw(3) << linha;
    timesTwo(linha,  coluna + 1, contador - 1);
  }
  else return timesTwo(linha, coluna, contador - 1);
}

int main(){

  timesTwo();
 
  return 0;
}
// You can include R code blocks in C++ files processed with sourceCpp
// (useful for testing and development). The R code will be automatically 
// run after the compilation.
//

/*** R
timesTwo(42)
*/
