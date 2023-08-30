#ifndef ARVORE_HPP
#define ARVORE_HPP
#include "palavra.hpp"

class itemArvore{
    public:
        pair<string,int> palavraEocorrencia;
        itemArvore *filhoEsquerdo, *filhoDireito;
};

#endif