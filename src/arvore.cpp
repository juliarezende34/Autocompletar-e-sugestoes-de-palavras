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