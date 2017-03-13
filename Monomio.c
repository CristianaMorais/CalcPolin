#include "Monomio.h"

Monom *newExpre(int c, char v, int e){
  Monom *new = (Monom *)malloc(sizeof(Expressao));
  new -> exp = (Expressao *)malloc(sizeof(Expressao));
  new -> exp->coeficiente = c;
  new -> exp->variavel = v;
  new -> exp->expoente = e;

  new -> flag = Expre;

  return new;
}

Monom *newConstante(int c){
  Monom *new = (Monom *)malloc(sizeof(int));
  new -> constante = c;

  new -> flag = Consta;

  return new;
}
