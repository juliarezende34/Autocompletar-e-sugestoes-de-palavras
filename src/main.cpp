#include "palavra.hpp"
#include "arvore.hpp"
#include "functions.hpp"
#include <sstream> 
#include <vector>
#include <time.h>
#define NUMERO_ARQUIVOS 6

int main() {
    clock_t startTime, endTime;
    startTime = clock();
    itemArvore * raiz = NULL;
    string vetorArquivos[NUMERO_ARQUIVOS] = {"dataset/filosofia.txt", "dataset/filosofia2.txt", "dataset/globalizacao.txt", "dataset/politica.txt", "dataset/ti.txt", "dataset/ti2.txt"}, linha;
    string palavraAtual;
    ifstream arquivo, arquivoStopWords, arquivoInput;
    ofstream output;
    vector<string> tokens;
    vector<Palavra> vetorPalavras;
    vector<pair<int,int>> vetorOcorrencias;
    string token, stopword; 
    unordered_map<string, Palavra> vetorMaps[NUMERO_ARQUIVOS];
    unordered_map<string, string> stopWordMap;
    int controle = 0;

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
            linha.erase(remove(linha.begin(), linha.end(), ':'), linha.end());

            istringstream iss(linha); 
            while (iss >> token) {
                if ((token != "--") && (token != "—") && (token != "“") && (token != "”")) { 
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
        }
        arquivo.close();
    }

    arquivoInput.open("dataset/input.data", ios::in);
    output.open("dataset/output.data", ios::out);
    if (!arquivoInput.is_open()) {
        cout << "Não foi possível abrir o arquivo de input." << endl;
        return 1;
    }
    while(!arquivoInput.eof()){
        arquivoInput >> palavraAtual;
        for(int i = 0; i < NUMERO_ARQUIVOS; i++){
            vetorOcorrencias.push_back(make_pair((i+1),vetorMaps[i][palavraAtual].ocorrencias));
        }
        for(int i = 0; i < NUMERO_ARQUIVOS; i++){
            cout << "\nTexto " << i+1 << endl;
            criarHeapK(vetorMaps[i], vetorPalavras);
            check(vetorMaps[i], vetorPalavras);
            for(int j = 0; j < (int)vetorPalavras.size(); j++){
                if(vetorPalavras[j].texto == palavraAtual){
                    vetorPalavras.erase(vetorPalavras.begin() + j);
                    controle = 1;
                    break;
                }
            }
            if(controle == 0){
                //A palavra digitada não está nos top elementos, então preciso remover o último para ter o top K
                vetorPalavras.pop_back();
            }
            //Aqui terei o vetor das 20 palavras mais frequentes do texto, desconsiderando a palavra atual
            //A palavra ocorre no arquivo i
            for(int k = 0; k < (int)vetorPalavras.size(); k++){
                if(vetorOcorrencias[i].second > 0){
                    arvoreBinaria(&raiz, vetorPalavras[k]);
                }
                cout << vetorPalavras[k].texto << " | " << vetorPalavras[k].ocorrencias << endl;
            }
            vetorPalavras.clear();
        }
        BubbleSort(vetorOcorrencias);
        outputFile(output, palavraAtual, vetorOcorrencias);
        vetorOcorrencias.clear();
    }
    
    arquivoInput.close();
    output.close();

    endTime = clock();
    clock_t elapsedTime = endTime - startTime;
    double elapsedTimeMs = ((double)elapsedTime/CLOCKS_PER_SEC)*1000;
    cout << "TEMPO DE EXECUÇÃO: " << elapsedTimeMs << " ms " << endl;
    
    return 0;
}

//MUDAR O VETOR PALAVRA PARA UM VETOR DE VETORES E FAZER OS HEAPS ANTES DA LEITURA DO ARQUIVO DE INPUT