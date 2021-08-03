#include <Rcpp.h>
using namespace Rcpp;

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <time.h>
using namespace std;

int tam_genes = 100;
int tam_pop = 50;
int tam_torneios = 20;
int geracoes = 500;
double prob = 0.0;
double prob_mut = 0.2;
double prob_cruz = 0.7;

// população
vector<vector<int> > populacao;

// [[Rcpp::export]]
void inicializaPopulacao(){
  for (int i = 0; i < tam_pop; i++) {
    
    vector<int> individuo;
    
    for (int j = 0; j < tam_genes; j++) {
      int gene = rand() % 2;   // escolhe um número entre 0 e 1
      individuo.push_back(gene); // insere no vetor do individuo
    }
    populacao.push_back(individuo); // insere no vetor da população
  }
}

//[[Rcpp::export]]
void mostrarPopulacao(){
  for(int i = 0; i < tam_pop; i++)
  {
    for(int j = 0; j < tam_genes; j++)
      cout << populacao[i][j] << " ";
    cout << endl;
  }
}

//[[Rcpp::export]]
int obterPontuacao(vector<int> individuo){
  
  int soma = 0;
  
  for (int i = 0; i < tam_genes ; i++ )
    soma += individuo[i];
  return soma;
}

// realiza a mutação de alguns genes
//[[Rcpp::export]]
void mutacao(vector<int> & individuo){
  // escolhe um gene aleatório no intervalo [0, tam_genes - 1]
  int gene = rand() % tam_genes;
  
  if (individuo[gene] == 0)
    individuo[gene] = 1;
  else
    individuo[gene] = 0;
}


// realiza o cruzamento dos genes em 1 ponto
//[[Rcpp::export]]
void cruzamento(int indice_pai1, int indice_pai2, vector<int>& filho){
  
  int ponto = rand() % tam_genes;
  
  for (int i = 0; i <= ponto; i++)
    filho.push_back(populacao[indice_pai1][i]);
  
  for (int i = ponto + 1; i < tam_genes; i++)
    filho.push_back(populacao[indice_pai2][i]);
}

// // gera número aleatório para ponto de mutação
// //[[Rcpp::export]]
// void ponto(){
//   int gene = rand() % tam_genes; // gene = [0; tam_genes]; tam_genes = 100
//   cout << gene << endl;
//   }



// retorna o índice do melhor individuo da população
//[[Rcpp::export]]
int obterMelhor(){
  int indice_melhor = 0;
  int score_melhor = obterPontuacao(populacao[0]);
  
  for (int i = 0; i < tam_pop; i++) {
    
    int  score = obterPontuacao(populacao[i]);
    if (score > score_melhor){
      indice_melhor = i;
      score_melhor = score;
    }
  }
  return indice_melhor;
}

// //[[Rcpp::export]]
// double alea (){
//   for(int i = 0; i < tam_torneios; ++i)
//     srand(time(NULL));
//     prob = ((double) rand() / ((double)RAND_MAX + 1) );
//     return prob;
//   }

// inicio função main()
//[[Rcpp::export]]
int main(){
  srand (time(NULL));
  inicializaPopulacao();
  for (int i = 0; i < geracoes; ++i) {
    for (int j = 0; j < tam_torneios; ++j) {
      // cacula a probabilidade de cruzamento
      double prob = ((double) rand() / ((double)RAND_MAX + 1) );
      if (prob < prob_cruz){
        // escolhe dois pais para fazer o cruzamento
        int indice_pai1 = rand() % tam_pop;
        int indice_pai2;
        
        // garante que os índices dos pais não são iguais
        do {
          indice_pai2 = rand() % tam_pop;
        }
        while ( indice_pai1 == indice_pai2 );
        
        vector<int> filho;
        // aplica o cruzamento de 1 ponto
        cruzamento (indice_pai1, indice_pai2, filho);
        // calcula a probabilidade de mutação
        prob = ((double) rand() / ((double)RAND_MAX + 1) );
        if (prob < prob_mut)
          mutacao(filho);
        
        int score_pai = obterPontuacao(populacao[indice_pai1]);
        int score_filho = obterPontuacao(filho);
        if (score_filho > score_pai){
          for(int k = 0 ; k < tam_genes; ++k )
            populacao[indice_pai1][k] = filho[k];
        }
      }
    }
    
    cout << "Geracao " << i + 1 << endl;
    cout << "Melhor: ";
    
    int indice_melhor = obterMelhor();
    int score_melhor = obterPontuacao(populacao[indice_melhor]);
    
    for (int j = 0; j < tam_genes; ++j)
      cout << populacao[indice_melhor][j] << " ";
    
    cout << "\nPontuação: " << score_melhor << "\n\n";
    if (score_melhor == tam_genes )
      break;
  }
  return 0;
}
// fim função main()

/*** R
 
## Schwefel  z =  (xsen(√|x|) + ysen(√|y|))
x <- seq(-500, 500, length=100)
y <- x
schwefel <- function(x,y) {
  837.96542 -1*(x*sin(sqrt(abs(x))) + 
                y*sin(sqrt(abs(y))) )
}
z<-outer(x,y,schwefel)
z[is.na(z)]<-1
persp(x,y,z,theta=30,phi=30,expand=0.5,col="red",
      ltheta=90,shade=0.50,ticktype="detailed",d=5,r=1)
# ### Rastringin
# x<-seq(-5.12,5.12,length=100)
# y <- x
# rastrigin <-function(x,y) { 20+(x^2-10*cos(2*3.14*x))+
#      (y^2-10*cos(2*3.14*y)) }
# z<-outer(x,y,rastringin)
# z[is.na(z)]<-1
# persp(x,y,z,theta=30,phi=30,expand=0.5,col="red",
#       ltheta=90,shade=0.50,ticktype="detailed",d=5,r=1)
# ### Fim Rastrigin
 
# main()

*/
