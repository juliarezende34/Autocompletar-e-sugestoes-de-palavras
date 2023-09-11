#include "functions.hpp"

int Kaux = K + 1;
struct CompararOcorrencias{
   bool operator()(itemHuffman * a, itemHuffman * b){
        return a->ocorrencia > b->ocorrencia;
   }
};

priority_queue<itemHuffman*, vector<itemHuffman*>, CompararOcorrencias> pq;

void addMap(unordered_map<string, Palavra> &wordMap, string token){
    if(wordMap.find(token) != wordMap.end()){
        wordMap[token].ocorrencias++;
    }
    else{
        Palavra novaPalavra;
        novaPalavra.texto = token;
        novaPalavra.ocorrencias = 1;
        wordMap[token] = novaPalavra;
    }
}

bool isStopWord(unordered_map<string, string> &stopWordMap, string token){
    if(stopWordMap.find(token) != stopWordMap.end()){
        return true;
    }
    else{
        return false;
    }
}

void criarHeapK(unordered_map<string, Palavra> &wordMap, vector<Palavra> &vetorPalavras){
    auto iterator = wordMap.begin();
    int contador = 0;

    while(contador < K){
        //cout << iterator->second.texto << endl;
        vetorPalavras.push_back(iterator->second);
        contador++;
        iterator++;
    }
}

void Swap(Palavra *a, Palavra *b){
	Palavra aux = *a;
	*a = *b;
	*b = aux;
}

void rebuildHeap(vector<Palavra> &vetorPalavras, int i, int tamanho) {
    int filho = 2 * i + 1;
    if ((filho < tamanho - 1) && (vetorPalavras[filho].ocorrencias > vetorPalavras[filho + 1 /*Filho 2*/].ocorrencias)) {
        filho++;
    }
    if ((filho < tamanho) && (vetorPalavras[i].ocorrencias > vetorPalavras[filho].ocorrencias)) {
        swap(vetorPalavras[i], vetorPalavras[filho]);
        rebuildHeap(vetorPalavras, filho, tamanho);
    }
}

void buildHeap(vector<Palavra> &vetorPalavras) {
    int tamanho = vetorPalavras.size();
    for (int i = tamanho / 2 - 1 /*Definição do pai*/; i >= 0; i--) {
        rebuildHeap(vetorPalavras, i, tamanho);
    }
}

void check(unordered_map<string, Palavra> &wordMap, vector<Palavra> &vetorPalavras){
    auto iterator = wordMap.begin();
    int contador = 0;

    while(contador <= Kaux){
        contador++;
        iterator++;
    }
    while(iterator != wordMap.end()){
        if(iterator->second.ocorrencias > vetorPalavras[0].ocorrencias){
            Swap(&vetorPalavras[0], &iterator->second);
            buildHeap(vetorPalavras);
        }
        iterator++;
    }
}

void BubbleSort(vector<pair<int,int>> &vec) {
    int n = vec.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (vec[j].second < vec[j + 1].second) {
                swap(vec[j], vec[j + 1]);
            }
        }
    }
}

void arvoreBinaria(itemArvore ** no, Palavra &item){
    if((*no) == NULL){
       (*no) = new itemArvore(item);
    }
    else{
        if(item.texto != (*no)->palavra){
            if(item.ocorrencias <= (*no)->ocorrencia){
                arvoreBinaria(&(*no)->filhoEsquerdo, item);
            }
            else{
                arvoreBinaria(&(*no)->filhoDireito, item);
            }
        }
    }
}

void arvoreAVL(itemArvoreAVL ** no, Palavra &item){
    if((*no) == NULL){
        (*no) = new itemArvoreAVL(item);
    }
    else{
        if(item.texto != (*no)->palavra){
            if(item.ocorrencias <= (*no)->ocorrencia){
                arvoreAVL(&(*no)->filhoEsquerdo, item);
                if((getWeight(&(*no)->filhoEsquerdo) - getWeight(&(*no)->filhoDireito)) == 2){
                    if(item.ocorrencias <= (*no)->filhoEsquerdo->ocorrencia){
                        rotacaoSimplesDireita(no);
                    }
                    else{
                        rotacaoDuplaDireita(no);
                    }
                }
            }
            if(item.ocorrencias > (*no)->ocorrencia){
                arvoreAVL(&(*no)->filhoDireito, item);
                if((getWeight(&(*no)->filhoDireito) - getWeight(&(*no)->filhoEsquerdo)) == 2){
                    if(item.ocorrencias > (*no)->filhoDireito->ocorrencia){
                        rotacaoSimplesEsquerda(no);
                    }
                    else{
                        rotacaoDuplaEsquerda(no);
                    }
                }
            }
        }
    }
    (*no)->peso = getMaxWeight(getWeight(&(*no)->filhoEsquerdo), getWeight(&(*no)->filhoDireito)) + 1;
}

int getWeight(itemArvoreAVL ** no){
    if((*no) == NULL){
        return -1;
    }
    else{
        return (*no)->peso;
    }
}

int getMaxWeight(int left, int right){
    if(left > right){
        return left;
    }
    else{
        return right;
    }
}

void rotacaoSimplesDireita(itemArvoreAVL ** no){
    itemArvoreAVL *aux;
    aux = (*no)->filhoEsquerdo;
    (*no)->filhoEsquerdo = aux->filhoDireito;
    aux->filhoDireito = (*no);
    (*no)->peso = getMaxWeight(getWeight(&(*no)->filhoEsquerdo), getWeight(&(*no)->filhoDireito)) + 1;
    aux->peso = getMaxWeight(getWeight(&aux->filhoEsquerdo), (*no)->peso) + 1;
    (*no) = aux;
}

void rotacaoSimplesEsquerda(itemArvoreAVL ** no){
    itemArvoreAVL * aux;
    aux = (*no)->filhoDireito;
    (*no)->filhoDireito = aux->filhoEsquerdo;
    aux->filhoEsquerdo = (*no);
    (*no)->peso = getMaxWeight(getWeight(&(*no)->filhoEsquerdo), getWeight(&(*no)->filhoDireito)) + 1;
    aux->peso = getMaxWeight(getWeight(&aux->filhoEsquerdo), (*no)->peso) + 1;
    (*no) = aux;
}

void rotacaoDuplaDireita(itemArvoreAVL ** no){
    rotacaoSimplesEsquerda(&(*no)->filhoEsquerdo);
    rotacaoSimplesDireita(no);
}

void rotacaoDuplaEsquerda(itemArvoreAVL ** no){
    rotacaoSimplesDireita(&(*no)->filhoDireito);
    rotacaoSimplesEsquerda(no);
}

void deleteTree(itemArvore* root) {
    if (root == NULL) {
        return; // Árvore vazia, nada a fazer
    }

    // Deleta os nós filhos (subárvores) primeiro
    deleteTree(root->filhoEsquerdo);
    deleteTree(root->filhoDireito);

    // Deleta o nó atual
    delete root;
}

void deleteTreeAVL(itemArvoreAVL* root){
    if (root == NULL) {
        return; // Árvore vazia, nada a fazer
    }

    // Deleta os nós filhos (subárvores) primeiro
    deleteTreeAVL(root->filhoEsquerdo);
    deleteTreeAVL(root->filhoDireito);

    // Deleta o nó atual
    delete root;
}

void printVector(vector<itemArvore*> &v,ofstream &arquivo){
    for(int i = 0; i < (int)v.size(); i++){
        arquivo << "["<< v[i]->palavra << "|" << v[i]->ocorrencia << "]"<< " ";
    }
}

void printVectorAVL(vector<itemArvoreAVL*> &v,ofstream &arquivo){
    for(int i = 0; i < (int)v.size(); i++){
        arquivo << "["<< v[i]->palavra << "|" << v[i]->ocorrencia << "]"<< " ";
    }
}

void central(itemArvore *t, vector<itemArvore*> &v)
{
  if(!(t == NULL)){
    central(t->filhoEsquerdo, v); 
    v.push_back(t);
    central(t->filhoDireito, v); 
  }
}

void centralAVL(itemArvoreAVL *t, vector<itemArvoreAVL*> &v)
{
  if(!(t == NULL)){
    centralAVL(t->filhoEsquerdo, v); 
    v.push_back(t);
    centralAVL(t->filhoDireito, v); 
  }
}

void outputFileIntro(ofstream &arquivo,int i){
    arquivo << "=====================================================================================================================================================================================================================================================================================================================" << endl;
    arquivo << "                                                                                      Texto "<< i+1 << "                                                                            " << endl;
    arquivo << "=====================================================================================================================================================================================================================================================================================================================" << endl;
}


void outputFile(ofstream &arquivo, string palavra, int ocorrencia, vector<itemArvore*> vetorArvore, vector<itemArvoreAVL*> vetorArvoreAVL){
    arquivo << endl << palavra << endl;
    arquivo <<"Frequência: " << ocorrencia << endl;
    arquivo << "Árvore binária - Central:\n";
    printVector(vetorArvore, arquivo);
    arquivo << "\nÁrvore AVL - Central:\n";
    printVectorAVL(vetorArvoreAVL, arquivo);
    arquivo << endl;
}

//Codificação de Huffman
void codificacaoHuffman(vector<Palavra> &vetorPalavras, itemHuffman * raiz){
    for(int i = 0; i < (int)vetorPalavras.size(); i++){
        pq.push(new itemHuffman(vetorPalavras[i].texto, vetorPalavras[i].ocorrencias));
    }
    while(pq.size() > 1){
        itemHuffman * esquerdo = pq.top();
        pq.pop();
        itemHuffman * direito = pq.top();
        pq.pop();

        itemHuffman * pai = new itemHuffman("\0", esquerdo->ocorrencia + direito->ocorrencia);
        pai->filhoDireito = direito;
        pai->filhoEsquerdo = esquerdo;
        pq.push(pai);
    }
    raiz = pq.top();
    raiz->ocorrencia = pq.top()->ocorrencia;
}

void gerarCodigoHuffman(itemHuffman * raiz, string codigo){
    if(!raiz){
        return;
    }    
    raiz->codigo = codigo;
    gerarCodigoHuffman(raiz->filhoEsquerdo, codigo + "0");
    gerarCodigoHuffman(raiz->filhoDireito, codigo + "1");
}