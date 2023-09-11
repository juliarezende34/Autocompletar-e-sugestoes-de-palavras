#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "palavra.hpp"
#include "arvore.hpp"

void addMap(unordered_map<string, Palavra> &wordMap, string token);//
bool isStopWord(unordered_map<string, string> &stopWordMap, string token);//
void criarHeapK(unordered_map<string, Palavra> &wordMap, vector<Palavra> &vetorPalavras);//
void buildHeap(vector<Palavra> &vetorPalavras);
void rebuildHeap(vector<Palavra> &vetorPalavras, int i, int size);//
void Swap(Palavra *a, Palavra *b);
void check(unordered_map<string, Palavra> &wordMap, vector<Palavra> &vetorPalavras);
void BubbleSort(vector<pair<int,int>> &v);
void outputFile(ofstream &arquivo, string palavra, int ocorrencia,vector<itemArvore*> vetorArvore, vector<itemArvoreAVL*> vetorArvoreAVL);
void arvoreBinaria(itemArvore ** no, Palavra &item);
void central(itemArvore *t, vector<itemArvore*> &v);
void centralAVL(itemArvoreAVL *t, vector<itemArvoreAVL*> &v);
void deleteTree(itemArvore* root);
void deleteTreeAVL(itemArvoreAVL* root);
void printVector(vector<itemArvore*> &v,ofstream &arquivo);
void printVectorAVL(vector<itemArvoreAVL*> &v,ofstream &arquivo);
void outputFileIntro(ofstream &arquivo,int i);
void arvoreAVL(itemArvoreAVL ** no, Palavra &item);
int getWeight(itemArvoreAVL ** no);
int getMaxWeight(int left, int right);
void rotacaoSimplesDireita(itemArvoreAVL ** no);
void rotacaoSimplesEsquerda(itemArvoreAVL ** no);
void rotacaoDuplaDireita(itemArvoreAVL ** no);
void rotacaoDuplaEsquerda(itemArvoreAVL ** no);
void codificacaoHuffman(vector<Palavra> &vetorPalavras, itemHuffman * raiz);
void gerarCodigoHuffman(itemHuffman * raiz, string codigo);
#endif