# LF-AnalisadorLexico

## Analisador léxico de subconjunto da linguagem C 

Fazer um programa que leia um arquivo fonte em C e efetue a análise léxica do mesmo. Como resultado da análise léxica deve ser gerado um arquivo com os tokens reconhecidos, contendo para cada um o token, o lexema, o número da linha e o número da coluna onde ocorre.

Ex:

| linha | coluna | token            | lexema |
|-------|--------|------------------|--------|
| 1     | 1      | tkint            | int    |
| 1     | 5      | tkid             | main   |
| 1     | 9      | tkabreparenteses | (      |
| ...   | ...    | ...              | ...      |


A saída deve ser mostrada também na console.
O subconjunto da linguagem C que deverá ser reconhecido é composto de:

        Declarações e referências a variáveis int, float, char e double, bem como structs, arrays e pointers.

        Expressões: Com a lista completa de operadores aritméticos, bitwise, relacionais e lógicos em C, e 
        tendo como operandos constantes inteiras, identificadores, chamadas de função, expressões entre parênteses
        e referência a elementos de arrays, pointers e structs (e os operadores associados).

        Comandos while, do-while, for e if.

        Comando switch-case. Com a possibilidade da entrada ‘default’.

        Blocos de comandos: grupos de comandos agrupados com chaves.

        O que fica de fora: unions, enums, operador ternário... enfim, tudo que não estiver na lista acima. O programa
        deve exibir na tela e gerar um arquivo de saída com a lista de tokens reconhecidos (identificados por um nome),
        bem como a linha, coluna e o lexema associado.

Da implementação devem ser entregues os arquivos-fonte e um executável do programa, com um arquivo texto descrevendo sua utilização.
