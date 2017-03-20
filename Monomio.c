#include "Monomio.h"

Monom *newExpre(int c, char v, int e){
  Monom *new = (Monom *)malloc(sizeof(Monom));
  new -> val = (Valor *)malloc(sizeof(Valor));
  new -> val -> exp = (Expressao *)malloc(sizeof(Expressao));

  new -> val -> exp->coeficiente = c;
  new -> val -> exp->variavel = v;
  new -> val -> exp->expoente = e;

  new -> flag = Expre;

  return new;
}

Monom *newConstante(int c){
  Monom *new = (Monom *)malloc(sizeof(Monom));
  new -> val = (Valor *)malloc(sizeof(Valor));
  new -> val -> constante = c;
  new -> flag = Consta;
  return new;
}
