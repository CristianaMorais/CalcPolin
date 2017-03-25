# CalcPolin
## *Laboratório de Programação - 2017*
Programa que calcula a derivada, o integral e a normalizaçao de um polinomio ou a soma de dois polinomios.

#### Como utilizar o programa:
1. Para compilar faz-se `$ make`.
2. Para executar e usar o programa corre `./PolinomioCalc`.

##### Síntaxe dos polinomios
O programa só aceita os polinómios utilizando a seguinte síntaxe:
* O monómio escreve-se da sequinte forma:  [coeficiente]*[parte literal sem grau]^[grau da parte literal], todos os monómios devem respeitar esta forma à expção se for uma constante, nesse caso basta usar a constante. Exemplo monómio dois x ao quadrado e constante 2:
```
> 2*x^4
> 2
```

* Num Polinomio, entre cada monómio utiliza-se o sinal '+'.
  Exemplo dois x ao quadrado mais três y ao cubo:
  
  ```
  > 2*x^4 + 3*y^3
  ```

##### Funções implementadas e sua síntaxe
* normaliza: Função que normaliza o polinómio. `> normaliza [Polinómio]`
* deriva: Função que deriva um polinómio em ordem a uma determinada variável. `> deriva [variável] [Polinómio]`
* integra: Função que integra um polinómio em ordem a uma determinada variável. `> integra [variável] [Polinómio]`
* soma: Função que soma dois polinómios. `> soma [Polinómio] [Polinómio]`
* help: Mostra o menu de ajuda.
* exit: Fecha a consola.

#### Trabalho realizado por:

[André Cirne](https://sigarra.up.pt/fcup/pt/fest_geral.cursos_list?pv_num_unico=201505860)

[José Pedro](https://sigarra.up.pt/fcup/pt/fest_geral.cursos_list?pv_num_unico=201503443)
