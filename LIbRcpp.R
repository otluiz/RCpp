library(Rcpp)

# A função abaixo em R 'cppFunction' introduz um código C++
# foi criado uma função em C++ 'add' que o compilador R irá interpretar
cppFunction('int add(int x, int y, int z) {
            int sum = x+y+z;
            return sum;
            }')
#add
add(1, 2, 3)
