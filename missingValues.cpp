#include <Rcpp.h>
using namespace Rcpp;

/*
 * The following code explores what happens when you take one of R’s missing values, 
 * coerce it into a scalar, and then coerce back to an R vector. 
 * Note that this kind of experimentation is a useful way to figure out what 
 * any operation does.
 */


// [[Rcpp::export]]
List scalar_missing() {
  int int_s = NA_INTEGER;
  String char_s = NA_STRING;
  bool lgl_s = NA_LOGICAL;
  double num_s = NA_REAL;
  
  return List::create(int_s, char_s, lgl_s, num_s);
}


/*** R
str(scalar_missing())
*/
