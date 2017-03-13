#include <stdlib.h>

typedef union Monom Monom;

union Monom{
  enum {Expre, Consta} flag;

  int constante;

  struct ex{
    int coeficiente;
    char variavel;
    int expoente;
  } exp;
};

Monom *newExpre(int c, char v, int e);
Monom *newConstante(int c);
