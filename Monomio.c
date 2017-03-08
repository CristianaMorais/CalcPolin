#include "Monomio.h"


union Monom{
  enum {Expre, Consta} flag;

  int constante;

  struct {
    int coeficiente;
    char variavel;
    int expoente;
  } exp;
}

Monom *newExpre(int c, char v, int e){
  Monom *new = (Monom *)malloc(sizeof(struct exp));
  new -> exp.coeficiente = c;
  new -> exp.variavel = v;
  new -> exp.expoente = e;

  new -> flag = Expre;

  return new;
}

Monom *newConstante(int c){
  Monom *new = (Monom *)malloc(sizeof(int));
  new -> constante = c;

  new -> flag = Consta;

  return new;
}
