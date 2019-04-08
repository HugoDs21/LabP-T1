# LabP-T1 Interpretador de Linguagem Personalizada

[![Build Status](https://travis-ci.org/xPudimx/LabP-T1.svg?branch=master)](https://travis-ci.org/xPudimx/LabP-T1)


Instruções aceites:

Leitura: ler(var);

Escrita: escrever(var);

Atribuição: var = número;

Operações
 - Soma 2 campos: "var = var + var;"
 - Subtração 2 campos: "var = var - var;"
 - Multiplicação 2 campos: "var = var * var;"
If: "if: var"
Goto: goto: Label
Label: label: Label
Terminar o programa: quit;


As variaveis têm que ser minusculas.
Não é sensivel a espaçamento.
O programa acaba com uma isntrução "quit;" ou quando nao tem mais instruções

Exemplo prático:

```
ler(k);
if: k;
goto: L1;
k = 10;
escrever(k);
quit;
label: L1;
escrever(k);
quit;
```

Para compilar o programa deverá aceder ao diretório do mesmo e executar

```$make```

Para executar

```$./main {files.txt}```
