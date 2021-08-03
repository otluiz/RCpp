## Comparação entre funções R e RC++
library(Rcpp)

# cppFunction('int add(int x, int y, int z) {
#   int sum = x + y + z;
#   return sum;
# }')
# # add works like a regular R function
# add
# #> function (x, y, z) 
# #> .Call(<pointer: 0x107536a00>, x, y, z)
# add(1, 2, 3)
# #> [1] 6

sumR <- function(x){
  total <- 0
  for (i in seq_along(x)) {
    total <- total + x[i]
  }
  total
}

## Cpp funciont
cppFunction('double sumC(NumericVector x){
            int n = x.size();
            double total = 0;
            for(int i; i < n; ++i){
            total += x[i];
            }
            return total;
}')


x <- runif(1e6)
bench::mark(
  sum(x),
  sumR(x),
  sumC(x)
)

## Rastringin
x<-seq(-5.12,5.12,length=100)
y <- x

rastringin <-function(x,y) { 20+(x^2-10*cos(2*pi*x))+
    (y^2-10*cos(2*pi*y)) }

z<-outer(x,y,rastringin)
jet.colors <- colorRampPalette(c("midnightblue",
                                 "blue", "cyan", "green", "yellow", "orange",
                                 "red", "darkred"))
nbcol <- 64
color <- jet.colors(nbcol)
nrz <- nrow(z)
ncz <- ncol(z)
zfacet <- z[-1,-1] + z[-1,-ncz] +
  z[-nrz,-1] + z[-nrz,-ncz]
facetcol <- cut(zfacet, nbcol)

persp(x, y, z, col=color[facetcol],
      phi=15, theta=-35, ticktype="detailed",
      d=10, r=1, shade=0.1, expand=0.7)
## Fim

# ## Schwefel  z =  (xsen(√|x|) + ysen(√|y|))
# x <- seq(-500, 500, length=100)
# y <- x
# schwefel <- function(x,y) {
#   837.96542 -1*(x*sin(sqrt(abs(x))) + 
#                   y*sin(sqrt(abs(y))) )
# }
# z<-outer(x,y,schwefel)
# z[is.na(z)]<-1
# persp(x,y,z,theta=30,phi=30,expand=0.5,col="red",
#       ltheta=90,shade=0.50,ticktype="detailed",d=5,r=1)
# ## Fim

## Exponential z = x*exp−(x^2 +y^2 )
# x <- seq(-2, 2, length=100)
# exponencial <- function(x,y){
#   x * exp(-1*(x^2 + y^2))
# }
# z<-outer(x,y,exponencial)
# #z[is.na(z)]<-1
# jet.colors <- colorRampPalette(c("midnightblue",
#                                  "blue", "cyan", "green", "yellow", "orange",
#                                  "red", "darkred"))
# nbcol <- 64
# color <- jet.colors(nbcol)
# 
# nrz <- nrow(z)
# ncz <- ncol(z)
# 
# zfacet <- z[-1,-1] + z[-1,-ncz] +
#   z[-nrz,-1] + z[-nrz,-ncz]
# facetcol <- cut(zfacet, nbcol)
# 
# persp(x, y, z, col=color[facetcol],
#       phi=15, theta=-35, ticktype="detailed",
#       d=10, r=1, shade=0.1, expand=0.7)
## Fim