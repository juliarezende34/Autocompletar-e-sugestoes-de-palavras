#include "palavra.hpp"
#include "arvore.hpp"
#include "functions.hpp"
#include <sstream>
#include <vector>
#include <numeric>
#include <chrono>
#define NUMERO_ARQUIVOS 6



int main() {    
    string vetorArquivos[NUMERO_ARQUIVOS] = {"dataset/filosofia.txt", "dataset/filosofia2.txt", "dataset/globalizacao.txt", "dataset/politica.txt", "dataset/ti.txt", "dataset/ti2.txt"}, linha;
    string palavraAtual;
    ifstream arquivo, arquivoStopWords, arquivoInput;
    ofstream output;
    vector<string> tokens;
    vector<Palavra> vetorPalavras, copiaHeap, vetorInput;
    vector<itemArvore*> vetorArvore;
    vector<itemArvoreAVL*> vetorArvoreAVL;
    vector<pair<int,int>> vetorOcorrencias;
    vector<pair<string,string>> codigosHuffman;
    string token, stopword; 
    unordered_map<string, Palavra> vetorMaps[NUMERO_ARQUIVOS];
    unordered_map<string, string> stopWordMap;
    int controle = 0;
    vector<int> tempoBinaria, tempoAVL, tempoHuffman;
    priority_queue<itemHuffman*, vector<itemHuffman*>, CompararOcorrencias> pq;

    arquivoStopWords.open("dataset/stopwords.txt", ios::in);
    if (!arquivoStopWords.is_open()) {
        cout << "Não foi possível abrir o arquivo de stop words." << endl;
        return 1;
    }
    while(!arquivoStopWords.eof()){
        arquivoStopWords >> stopword;
        stopWordMap[stopword] = stopword;
    }
    arquivoStopWords.close();

    for(int i = 0; i < NUMERO_ARQUIVOS; i++){

        arquivo.open(vetorArquivos[i], ios::in);

        if (!arquivo.is_open()) {
            cout << "Não foi possível abrir o arquivo." << endl;
            return 1;
        }

        while (getline(arquivo, linha)) {
            linha.erase(remove(linha.begin(), linha.end(), ','), linha.end());
            linha.erase(remove(linha.begin(), linha.end(), '.'), linha.end());
            linha.erase(remove(linha.begin(), linha.end(), '?'), linha.end());
            linha.erase(remove(linha.begin(), linha.end(), '!'), linha.end());
            linha.erase(remove(linha.begin(), linha.end(), '"'), linha.end());
            linha.erase(remove(linha.begin(), linha.end(), ';'), linha.end());
            linha.erase(remove(linha.begin(), linha.end(), '/'), linha.end());
            linha.erase(remove(linha.begin(), linha.end(), '-'), linha.end());
            linha.erase(remove(linha.begin(), linha.end(), ':'), linha.end());
            linha.erase(remove(linha.begin(), linha.end(), '\n'), linha.end());
            linha.erase(remove(linha.begin(), linha.end(), '\t'), linha.end());
            linha.erase(remove(linha.begin(), linha.end(), ')'), linha.end());
            linha.erase(remove(linha.begin(), linha.end(), '('), linha.end());
            linha.erase(remove(linha.begin(), linha.end(), '>'), linha.end());
            linha.erase(remove(linha.begin(), linha.end(), '<'), linha.end());
            linha.erase(remove(linha.begin(), linha.end(), '~'), linha.end());
            linha.erase(remove(linha.begin(), linha.end(), '\''), linha.end());
            linha.erase(0, linha.find_first_not_of(" "));
            linha.erase(linha.find_last_not_of(" ") + 1);
            istringstream iss(linha); 
            while (iss >> token) {
                if ((token != "--") && (token != "—") && (token != "“") && (token != "”") && (token != "É") && (!token.empty())) { 
                    if (token.size() > 2 && token.substr(0, 2) == "--") {
                        token = token.substr(2); // Remove os primeiros dois caracteres "--", para quando não há espaço
                    }
                    for (char& c : token) {
                        c = std::tolower(c);
                    }
                    if(!isStopWord(stopWordMap, token)){
                        addMap(vetorMaps[i], token);
                    }
                }
            }
            linha.clear();
        }
        arquivo.close();
    }

    arquivoInput.open("dataset/input.data", ios::in);
    if (!arquivoInput.is_open()) {
        cout << "Não foi possível abrir o arquivo de input." << endl;
        return 1;
    }
    while(!arquivoInput.eof()){
        arquivoInput >> palavraAtual;
        Palavra * palavraNova = new Palavra(palavraAtual);
        vetorInput.push_back(*palavraNova);
    }    
    arquivoInput.close();

    output.open("dataset/output.data", ios::out);
    if (!output.is_open()) {
        cout << "Não foi possível abrir o arquivo de output." << endl;
        return 1;
    }
    for(int i = 0; i < NUMERO_ARQUIVOS; i++){
        //itemArvore * raiz = new itemArvore();
        outputFileIntro(output, i);
        criarHeapK(vetorMaps[i], vetorPalavras);
        check(vetorMaps[i], vetorPalavras);
        copiaHeap = vetorPalavras;
        for(int j = 0; j < (int)vetorInput.size(); j++){ 
            vetorInput[j].ocorrencias = vetorMaps[i][vetorInput[j].texto].ocorrencias;
            for(int k = 0; k < (int)vetorPalavras.size(); k++){
                if(vetorPalavras[k].texto == vetorInput[j].texto){
                    controle = 1;
                    break;
                }
            }
            if(controle == 1){
                //A palavra do input está no heap
                for(int k = 0; k < (int)vetorPalavras.size(); k++){
                    if(vetorPalavras[k].texto == vetorInput[j].texto){
                        vetorPalavras.erase(vetorPalavras.begin() + k);
                        break;
                    }
                }
            }
            else{
                vetorPalavras.erase(vetorPalavras.begin());
            } 
            if(vetorMaps[i][vetorInput[j].texto].ocorrencias != 0){
                itemArvore * raiz = new itemArvore(vetorPalavras[0]);
                itemArvoreAVL * raizAVL = new itemArvoreAVL(vetorPalavras[0]);
                auto start = std::chrono::high_resolution_clock::now();
                for(int k = 0; k < (int)vetorPalavras.size(); k++){
                    arvoreBinaria(&raiz, vetorPalavras[k]);
                }
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
                //std::cout << "Tempo de execução - Árvore binária - Texto " << i+1 << " - "<< vetorInput[j] << ": " << duration.count() << " nanossegundos" << std::endl;
                tempoBinaria.push_back((int)duration.count());

                start = std::chrono::high_resolution_clock::now();
                for(int k = 0; k < (int)vetorPalavras.size(); k++){
                    arvoreAVL(&raizAVL, vetorPalavras[k]);
                }
                end = std::chrono::high_resolution_clock::now();
                duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
                //std::cout << "Tempo de execução - Árvore AVL - Texto " << i+1 << " - "<< vetorInput[j] << ": " << duration.count() << " nanossegundos" << std::endl;
                tempoAVL.push_back((int)duration.count());
                
                start = std::chrono::high_resolution_clock::now();
                codificacaoHuffman(vetorPalavras, pq);
                itemHuffman * raizHuffman =  pq.top();
                gerarCodigoHuffman(raizHuffman, "", codigosHuffman);
                end = std::chrono::high_resolution_clock::now();
                duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
                //std::cout << "Tempo de execução - Codificação de Huffman - Texto " << i+1 << " - "<< vetorInput[j] << ": " << duration.count() << " nanossegundos" << std::endl << endl;
                tempoHuffman.push_back((int)duration.count());

                central(raiz, vetorArvore);
                centralAVL(raizAVL, vetorArvoreAVL);
                outputFile(output, vetorInput[j].texto, vetorInput[j].ocorrencias, vetorArvore, vetorArvoreAVL, codigosHuffman);
                deleteTree(raiz);
                while (!pq.empty()) {
                    pq.pop();
                }
                deleteTreeAVL(raizAVL);
                controle = 0;
                vetorArvore.clear();
                vetorArvoreAVL.clear();
                codigosHuffman.clear();
            }
            vetorPalavras = copiaHeap;  
        }
        vetorPalavras.clear();
    }
    output.close();

    cout << "Tempo médio de execução - Árvore binária: " << accumulate(tempoBinaria.begin(), tempoBinaria.end(), 0) / tempoBinaria.size() * 1.0 << endl;
    cout << "Tempo médio de execução - Árvore AVL: " << accumulate(tempoAVL.begin(), tempoAVL.end(), 0) / tempoAVL.size() * 1.0 << endl;
    cout << "Tempo médio de execução - Codificação de Huffman: " << accumulate(tempoHuffman.begin(), tempoHuffman.end(), 0) / tempoHuffman.size() * 1.0 << endl;
    
    return 0;
}