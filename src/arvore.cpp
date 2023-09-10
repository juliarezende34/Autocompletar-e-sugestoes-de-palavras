#include "arvore.hpp"

itemArvore :: itemArvore(Palavra item){
    this->filhoDireito = NULL;
    this->filhoEsquerdo = NULL;
    this->ocorrencia = item.ocorrencias;
    this->palavra = item.texto;
}

itemArvore :: itemArvore(){
    this->filhoEsquerdo = NULL;
    this->filhoDireito = NULL;
}

itemArvoreAVL :: itemArvoreAVL(Palavra item){
    filhoEsquerdo = NULL;
    filhoDireito = NULL;
    ocorrencia = item.ocorrencias;
    palavra = item.texto;
    peso = 0;
}

itemArvoreAVL :: itemArvoreAVL(){
    filhoEsquerdo = NULL;
    filhoDireito = NULL;
}