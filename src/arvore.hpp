#ifndef ARVORE_HPP
#define ARVORE_HPP
#include "palavra.hpp"

class itemArvore{
    public:
        //pair<string,int> palavraEocorrencia;
        string palavra;
        int ocorrencia;
        itemArvore *filhoEsquerdo, *filhoDireito;
        itemArvore(Palavra item);
        itemArvore();
        /*itemArvore& operator=(const itemArvore& outro){
            palavra = outro.palavra;
            ocorrencia = outro.ocorrencia;
            filhoDireito = outro.filhoDireito;
            filhoEsquerdo = outro.filhoEsquerdo;
            return *this;
        }*/
};

#endif