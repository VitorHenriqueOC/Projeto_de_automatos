#include <stdio.h>
#include <stdlib.h>

#define MAX_ESTADOS 10

// Estrutura para representar um nó da lista
typedef struct No {
  int valor;
  struct No* proximo;
  struct No* anterior;
} No;

// Função para calcular o comprimento de uma string
int calcularComprimento(const char* str) {
  int tamanho = 0;
  while (str[tamanho] != '\0') {
    tamanho++;
  }
  return tamanho;
}

// Função para verificar se uma string é subpalavra de outra
int verificarSubpalavra(const char* string, const char* substring) {
  int tamanho_string = calcularComprimento(string);
  int tamanho_substring = calcularComprimento(substring);

  for (int i = 0; i <= tamanho_string - tamanho_substring; i++) {
    int j;
    for (j = 0; j < tamanho_substring; j++) {
      if (string[i + j] != substring[j])
        break;
    }
    if (j == tamanho_substring)
      return 1;  // substring encontrada
  }

  return 0;  // substring não encontrada
}

// Função para extrair uma substring de uma string
char* substr(const char* str, int partida, int tamanho) {
  char* substring = (char*)malloc((tamanho + 1) * sizeof(char));
  int i;

  for (i = 0; i < tamanho && str[partida + i] != '\0'; i++) {
    substring[i] = str[partida + i];
  }

  substring[i] = '\0';

  return substring;
}
int minhaStrncmp(const char* str1, const char* str2, int n) {
  for (int i = 0; i < n; i++) {
    if (str1[i] != str2[i])
      return str1[i] - str2[i];
    else if (str1[i] == '\0')
      return 0;
  }
  return 0;
}


// Função para copiar uma string com tamanho definido
void copiarString(const char* palavra_do_automato, char* destino, int tamanho) {
  int i;
  for (i = 0; i < tamanho && palavra_do_automato[i] != '\0'; i++) {
    destino[i] = palavra_do_automato[i];
  }
  for (; i < tamanho; i++) {
    destino[i] = '\0';
  }
}

// Função para construir a função de transição
int** constroi(const char* w) {
  int** transicao =
      (int**)malloc((calcularComprimento(w) + 1) * sizeof(int*));
  for (int i = 0; i <= calcularComprimento(w); i++) {
    transicao[i] = (int*)malloc(2 * sizeof(int));
    for (int j = 0; j < 2; j++) {
      char automato[100];
      copiarString(w, automato, i);
      automato[i] = (j == 0) ? 'a' : 'b';
      automato[i + 1] = '\0';
      int compAutomato = calcularComprimento(automato);
      while (minhaStrncmp(w, automato + calcularComprimento(automato) - compAutomato, compAutomato) != 0) {

        compAutomato--;
      }
      transicao[i][j] = compAutomato;
    }
  }
  return transicao;
}

// Função para imprimir a saída da tabela de transição e a resposta se é
// subpalavra ou não
void Printar(const char* w, int* const* transicao, const char** v, int tam_w,int tam_v) {
  // Imprimir os estados de transição de w
  for (int i = 0; i <= 0; i++) {
    char* automato = substr(w, 0, i);
    int est_a = transicao[i][0];
    int est_b = transicao[i][1];
    if (i == 0) {
      printf("%s", automato);
    } else {
      printf("%s", automato);
    }
    printf("eps %s %s\n",
           (est_a == 0) ? "eps" : substr(w, 0, est_a),
           (est_b == 0) ? "eps" : substr(w, 0, est_b));
  }

  for (int i = 1; i <= tam_w - 1; i++) {
    char* automato = substr(w, 0, i);
    int est_a = transicao[i][0];
    int est_b = transicao[i][1];
    printf("%s %s %s\n", automato,
           (est_a == 0) ? "eps" : substr(w, 0, est_a),
           (est_b == 0) ? "eps" : substr(w, 0, est_b));
    if (i == tam_w - 1) {
      char* ultimo_elemento = substr(w, 0, tam_w);
      printf("%s %s %s\n", ultimo_elemento, ultimo_elemento, ultimo_elemento);
    }
  }

  // Verificar se w é subpalavra de cada palavra v
  for (int i = 0; i < tam_v; i++) {
    int subpalavraEncontrada = verificarSubpalavra(v[i], w);
    printf("%d\n", subpalavraEncontrada ? 1 : 0);
  }
}

// Função para adicionar um novo nó no final da lista
void adicionarNoFinal(No** comeco, int valor) {
  No* novoNo = (No*)malloc(sizeof(No));
  novoNo->valor = valor;
  novoNo->proximo = NULL;

  if (*comeco == NULL) {
    novoNo->anterior = NULL;
    *comeco = novoNo;
    return;
  }

  No* ultimoNo = *comeco;
  while (ultimoNo->proximo != NULL) {
    ultimoNo = ultimoNo->proximo;
  }

  ultimoNo->proximo = novoNo;
  novoNo->anterior = ultimoNo;
}

// Função principal
int main() {
  char w[11];
  int k;
  char** v;
  scanf("%s %d", w, &k);
  v = (char**)malloc(k * sizeof(char*));
  for (int i = 0; i < k; i++) {
    v[i] = (char*)malloc(1000 * sizeof(char));
    scanf("%s", v[i]);
  }

  int tam_w = calcularComprimento(w);
  int tam_v = k;

  // Chama a função de transição
  int** transicao = constroi(w);

  Printar(w, (int* const*)transicao, (const char**)v, tam_w, tam_v);

  // Criar a lista duplamente ligada
  No* lista = NULL;

  return 0;
}