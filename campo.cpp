#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

#define linhas 0
#define colunas 0
#define minas 0

int main() {
    int vlinhas = linhas, vcolunas = colunas, vminas = minas, opcao; //tranforma as constantes em variaveis para que possa ser manipulada durante o codigo!

    // Garantir que haja pelo menos 2 minas e que o tabuleiro tenha mais de 1 linha e coluna
    if (vminas < 2) vminas = 2;
    if (vlinhas < 2) vlinhas = 2;
    if (vcolunas < 2) vcolunas = 2;

    int tabuleiro[vlinhas][vcolunas];
    bool revelado[vlinhas][vcolunas];

    // Inicializa o tabuleiro e o estado das células reveladas
    for (int i = 0; i < vlinhas; i++) {
        for (int j = 0; j < vcolunas; j++) {
            tabuleiro[i][j] = 0;
            revelado[i][j] = false;
        }
    }

    // Distribui as minas aleatoriamente e atualiza os números adjacentes
    srand(time(NULL));
    int minasColocadas = 0;
    while (minasColocadas < vminas) {
        int linha = rand() % vlinhas;
        int coluna = rand() % vcolunas;
        if (tabuleiro[linha][coluna] != 9) {
            tabuleiro[linha][coluna] = 9;
            minasColocadas++;
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    int adjLinha = linha + i;
                    int adjColuna = coluna + j;
                    if (adjLinha >= 0 && adjLinha < vlinhas && adjColuna >= 0 && adjColuna < vcolunas && 
                      tabuleiro[adjLinha][adjColuna] != 9) {
                        tabuleiro[adjLinha][adjColuna]++;
                    }
                }
            }
        }
    }

    int jogadasValidas = 0;
    bool jogoTerminado = false;

    // Loop do jogo
    while (!jogoTerminado) {
        // Exibe o tabuleiro
        cout << "  ";
        for (int j = 0; j < vcolunas; j++) {
            cout << j << " ";
        }
        cout << endl;
        for (int i = 0; i < vlinhas; i++) {
            cout << i << " ";
            for (int j = 0; j < vcolunas; j++) {
                if (revelado[i][j]) {
                    if (tabuleiro[i][j] == 9) {
                        cout << "X ";
                    } else {
                        cout << tabuleiro[i][j] << " ";
                    }
                } else {
                    cout << ". ";
                }
            }
            cout << endl;
        }

        // Lê a entrada do jogador
        int linha, coluna;
        cout << "Informe uma linha (0-" << vlinhas - 1 << "): ";
        cin >> linha;
        cout << "Informe uma coluna (0-" << vcolunas - 1 << "): ";
        cin >> coluna;

        // Verifica se a jogada é válida
        if (linha < 0 || linha >= vlinhas || coluna < 0 || coluna >= vcolunas || revelado[linha][coluna]) {
            cout << "Coordenadas inválidas ou posição já revelada. Tente novamente." << endl;
        } else {
            revelado[linha][coluna] = true;
            jogadasValidas++;

            // Verifica se o jogador acertou uma mina
            if (tabuleiro[linha][coluna] == 9) {
                cout << "Você acertou uma mina! Fim de jogo." << endl;
                jogoTerminado = true;
            } else {
                // Verifica se o jogador revelou todas as posições livres
                bool vitoria = true;
                for (int i = 0; i < vlinhas; i++) {
                    for (int j = 0; j < vcolunas; j++) {
                        if (tabuleiro[i][j] != 9 && !revelado[i][j]) {
                            vitoria = false;
                        }
                    }
                }
                if (vitoria) {
                    cout << "Parabéns! Você revelou todas as posições livres!" << endl;
                    jogoTerminado = true;
                }
            }
        }
    }

    // Exibe o tabuleiro final
    cout << "Tabuleiro final:" << endl;
    cout << "  ";
    for (int j = 0; j < vcolunas; j++) {
        cout << j << " ";
    }
    cout << endl;
    for (int i = 0; i < vlinhas; i++) {
        cout << i << " ";
        for (int j = 0; j < vcolunas; j++) {
            if (tabuleiro[i][j] == 9) {
                cout << "X ";
            } else {
                cout << tabuleiro[i][j] << " ";
            }
        }
        cout << endl;
    }

    cout << "Número de jogadas válidas: " << jogadasValidas << endl;
    return 0;
}
