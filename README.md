<h1 align="center" font-size="200em"><b>Autocompletar e sugestões de palavras</b></h1>

<div align = "center" >

[![requirement](https://img.shields.io/badge/IDE-Visual%20Studio%20Code-informational)](https://code.visualstudio.com/docs/?dv=linux64_deb)
![Make](https://img.shields.io/badge/Compilacao-Make-orange)
![Linguagem](https://img.shields.io/badge/Linguagem-C%2B%2B-blue)
</div>

## Introdução
<p align="justify">
Este é um programa desenvolvido em C++ para a disciplina de Algoritmos e Estruturas de Dados II. 

</p>

## Objetivos

## Arquivos
### dataset
- ```filosofia.txt```, ```filosofia2.txt```, ```globalizacao.txt```, ```politica.txt```, ```ti.txt```, ```ti2.txt```: textos a terem suas palavras analisadas e organizadas, agrupando as mais frequentes;
- ```stopwords.txt```: palavras a serem ignoradas durante a leitura do texto;
- ```input.data```: palavras a serem buscadas nos textos;
- ```output.data```: impressão dos resultados.
## src
- ```palavra.hpp```: assinatura da estrutura que representa uma palavra;
- ```arvore.hpp```: assinatura das estruturas que representam itens das árvores;
- ```arvore.cpp```: implementação das funções relacionadas às árvores;
- ```functions.hpp```: assinatura das funções gerais;
- ```functions.cpp```: implementação das funções gerais;
- ```comparador.hpp```: estrutura de comparação para inserção na priority queue;
- ``` main.cpp```: arquivo principal.

## Resolução do problema
### Leitura dos arquivos e contagem das frequências
O primeiro procedimento é ler o arquivo de stop words, adicionando-as em um unordered map para futura conferência. Depois, lê-se todos os arquivos de entrada, organizados em um vetor estático, organizando suas palavras em um unordered map (cada texto tem o seu) após a remoção de caracteres especiais e conversão da palavra para minúscula. Caso a palavra já exista no unordered map to texto que está sendo lido no momento, seu número de ocorrências é incrementado. Se o usuário desejar modificar os textos de entrada, basta mudar o número de itens e a declaração do vetor ```vetorArquivos```, declarado na linha 13 do arquivo ```main.cpp```.

<b>Os procedimentos descritos abaixo ocorrem da mesma maneira para cada um dos arquivos de entrada:</b>

Cria-se um heap com as top (K+1) palavras do texto, sendo esse a base para a construção das árvores e da codificação de Huffman. Agora, percorrendo o vetor que contém as palavras do ```input.data```, realiza-se as manipulações necessárias por palavra.

Caso a palavra esteja contida no heap de palavras mais frequentes, ela é removida, mas caso contrário, remove-se a última posição do heap (a menos frequente). Dessa forma, de um jeito ou de outro, obtém-se um heap de K elementos. Se o número de ocorrências da palavra no texto atual for diferente de 0, começa o processo de contrução das árvores.

### Árvore binária

### Árvore AVL

### Codificação de Huffman

## Resultados

## Conclusão

## Referências

## Compilação e execução
* Especificações da máquina em que o código foi rodado:
  * Processador Intel Core i5, 7th Gen;
  * Sistema Operacional Windows 10;
  * Terminal do WSL: Ubuntu 20.04.5;
  * 8GB de RAM.
* | Comando                |  Função                                                                                           |                     
  | -----------------------| ------------------------------------------------------------------------------------------------- |
  |  `make clean`          | Apaga a última compilação realizada contida na pasta build                                        |
  |  `make`                | Executa a compilação do programa utilizando o gcc, e o resultado vai para a pasta build           |
  |  `make run`            | Executa o programa da pasta build após a realização da compilação                                 |

## Contato
<div>
 <p align="justify"> Julia Rezende Gomes Rocha</p>
 <a href="https://t.me/juliarezende34">
 <img align="center" src="https://img.shields.io/badge/Telegram-2CA5E0?style=for-the-badge&logo=telegram&logoColor=white"/> 
 </div>
 <br>
<a style="color:black" href="mailto:juliarezende34@gmail.com?subject=[GitHub]%20Source%20Dynamic%20Lists">
✉️ <i>juliarezende34@gmail.com</i>
</a>