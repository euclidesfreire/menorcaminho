#include <stdio.h>
#include <stdlib.h>

int** criarGrafo();
void viewGrafo(int **m);
int procuraMenorDistancia(float *dist, int *visitado, int NV);
void dijkstra(int **m, int vertices, int arestas, int ini, int destino, int *ant, float *dist);
void prim(int **m, int vertices, int arestas, int orig, int destino, int *pai);
void kruscal(int **m, int vertices, int arestas, int orig, int destino, int *pai);
void sobre();
void menu();

void main() {
    int **m = criarGrafo();
    int op = -1, i, j, linhas, origem, destino, colunas, *ant, *pai;
    float *dist;
    FILE *arquivo = fopen("grafo.txt", "r");

    //PEGANDO OS VALORES DE LINHA E COLUNAS
    if(arquivo == NULL){
        printf("Erro, nao foi possivel abrir o arquivo\n");
    }else{
        fscanf(arquivo, "%d %d\n", &linhas, &colunas);
	}

	fclose(arquivo);

   do {
    system("cls || clear");
    menu();
    scanf("%d",&op);

    switch (op) {
      case 1:
        viewGrafo(m);
        break;
      case 2:
        printf("\nDigite a origem: ");
        scanf("%d", &origem);
        printf("\nDigite a destino: ");
        scanf("%d", &destino);
        ant = (int *) malloc(linhas * sizeof(int));
        dist = (float *) malloc(linhas * sizeof(float));
        dijkstra(m, linhas, colunas, origem, destino, ant, dist);
        break;
      case 3:
          printf("\nDigite a origem: ");
          scanf("%d", &origem);
          printf("\nDigite a destino: ");
          scanf("%d", &destino);
          pai = (int *) malloc(linhas * sizeof(int));
          prim(m, linhas, colunas, origem, destino, pai);
        break;
      case 4:
          printf("\nDigite a origem: ");
          scanf("%d", &origem);
          printf("\nDigite a destino: ");
          scanf("%d", &destino);
          pai = (int *) malloc(linhas * sizeof(int));
          kruscal(m, linhas, colunas, origem, destino, pai);
        break;
      case 5:
        break;
      case 8:
        sobre();
        break;
      case 0:
        return;
    }

    printf("\n\nTECLE ENTER PARA VOLTAR ");
    //Sequencia de comandos equivalentes ao system("pause");
    getchar();
    scanf("c\n");
  } while (op != 0);
}

int** criarGrafo(){
    int i, j, p, linhas, colunas;
    int **m;
    FILE *arquivo = fopen("grafo.txt", "r");

    //PEGANDO OS VALORES DE LINHA E COLUNAS
    if(arquivo == NULL){
        printf("Erro, nao foi possivel abrir o arquivo\n");
    }else{
        fscanf(arquivo, "%d %d\n", &linhas, &colunas);
	}
	//ALOCANDO MEMORIA PARA A MATRIZ
    m = (int **) malloc(linhas * sizeof(int *));

    if(m != NULL){
        for(i = 0; i < linhas; i++){
            m[i] = (int *) malloc(colunas * sizeof(int));
            for(j=0; j<colunas; j++){
                m[i][j] = 0;
            }
        }
    }

    while((fscanf(arquivo, "%d %d %d\n", &i, &j, &p))!= EOF ){
            m[i][j] = p;
    }

    fclose(arquivo);
    return m;
}

void viewGrafo(int **m){
    int i, j, linhas, colunas;
    FILE *arquivo = fopen("grafo.txt", "r");

    //PEGANDO OS VALORES DE LINHA E COLUNAS
    if(arquivo == NULL){
			printf("Erro, nao foi possivel abrir o arquivo\n");
    }else{
        fscanf(arquivo, "%d %d\n", &linhas, &colunas);
        printf("\n");
        for(i = 0; i < linhas; i++){
            for(j = 0; j < colunas; j++){
                printf("%d ", m[i][j]);
            }
            printf("\n");
        }
	}
	fclose(arquivo);
}

int procuraMenorDistancia(float *dist, int *visitado, int NV){
    int i, menor = -1, primeiro = 1;
    for(i=0; i < NV; i++){
        if(dist[i] >= 0 && visitado[i] == 0){
            if(primeiro){
                menor = i;
                primeiro = 0;
            }else{
                if(dist[menor] > dist[i])
                    menor = i;
            }
        }
    }
    return menor;
}

void dijkstra(int **m, int vertices, int arestas, int ini, int destino, int *ant, float *dist){
    int i, j, cont, NV, ind, *visitado, vert, *vetor;
    cont = NV = vertices;
    vetor = (int*) malloc(NV * sizeof(int));
    visitado = (int*) malloc(NV * sizeof(int));
    for(i=0; i < NV; i++){
        ant[i] = -1;
        dist[i] = -1;
        visitado[i] = 0;
        vetor[i] = -1;
    }
    dist[ini] = 0;
    while(cont > 0){
        vert = procuraMenorDistancia(dist, visitado, NV);
        //printf("u = %d\n",u);
        if(vert == -1)
            break;

        visitado[vert] = 1; 
        cont--;
        for(i=0, j=0; i<arestas, j<vertices; i++, j++){

            if(m[vert][i] != 0){
                ind = j;
                if(dist[ind] < 0){
                    dist[ind] = dist[vert] + m[vert][i];//peso da aresta
                    ant[ind] = vert;
                }else{
                    if(dist[ind] > dist[vert] + 1){
                        dist[ind] = dist[vert] + m[vert][i];//peso da aresta
                        ant[ind] = vert;
                    }
                }
            }
        }
    }

    if(ant[destino] != -1){
        for(i=0; i<NV; i++){
            if(ant[destino] == -1)
               break;
             vetor[i] = ant[destino];
             destino = ant[destino];
            }

        for(i=NV-1; i>=0; i--){
            if(vetor[i] != -1)
            printf("%d ", vetor[i]);
        }
    } else {
            printf("\nNão existe caminho para %d partindo de %d\n", destino, ini);
    }

    free(visitado);
}

void prim(int **m, int vertices, int arestas, int orig, int destino, int *pai){
	int aux, i, j, k, dest, primeiro, NV = vertices, **arvGer, *vetor;
	double menorPeso;

	for(i=0; i<NV; i++)
		pai[i] = -1;
	pai[orig] = orig;
	while(1){
		primeiro = 1;

		for(i=0; i<NV; i++){
			if(pai[i] != -1) {
				for(j=0, k=0; j<arestas, k<NV; j++, k++){
                  if(m[i][j] != 0){
					if(pai[k] == -1){
						if(primeiro){
							menorPeso = m[i][j];
							orig =i;
							dest = k;
							primeiro = 0;
						} else{
							if(menorPeso > m[i][j]){
                                menorPeso = m[i][j];
                                orig =i;
                                dest = k;
							}
						}
					}
				  }
				}
			}
		}
	if(primeiro == 1)
		break;
	pai[dest] = orig;
	}

    //MOSTRAR OS PAI DE CADA VERTICE E A ARVORE GERADORA
	printf("\nArvore Geradora Minima Prim: \n");
          for(i=0; i<NV; i++){
              if(pai[i] != -1)
                printf("%d ", pai[i]);
          }
          printf("\n");
          arvGer = (int **) malloc(NV * sizeof(int*));
          for(i = 0; i < NV; i++){
            arvGer[i] = (int *) malloc(arestas * sizeof(int));
            for(j=0; j<arestas; j++){
                arvGer[i][j] = 0;
            }
          }
          for(i = 0; i < NV; i++){
            aux = pai[i];
            arvGer[i][aux] = 1;
          }
          for(i = 0; i < NV; i++){
             printf("\n");
            for(j=0; j<arestas; j++){
                printf("%d ",arvGer[i][j]);
            }
          }

    //CAMINHO DA ORIGEM ATÉ O DESTINO
    vetor = (int *) malloc(NV * sizeof(int));
    printf("\n\n");
    if(pai[destino] != -1){
        for(i=0; i<NV; i++){
            if(pai[destino] == -1)
               break;
             vetor[i] = pai[destino];
             destino = pai[destino];
            }

        for(i=NV-1; i>=0; i--){
            if(vetor[i] != -1)
            printf("%d ", vetor[i]);
        }
    } else {
            printf("\nNão existe caminho para %d partindo de %d\n", destino, orig);
    }
}

void kruscal(int **m, int vertices, int arestas, int orig, int destino, int *pai){
	int aux, i, j, k, dest, primeiro, NV = vertices, **arvGer, *vetor;
	double menorPeso;
    int *arv = (int *) malloc(NV * sizeof(int));
	for(i=0; i<NV; i++){
        arv[i] = i;
		pai[i] = -1;
	}
	pai[orig] = orig;
	while(1){
		primeiro = 1;

		for(i=0; i<NV; i++){
				for(j=0, k=0; j<arestas, k<NV; j++, k++){
                  if(m[i][j] != 0){
					if(arv[i] != arv[k]){
						if(primeiro){
							menorPeso = m[i][j];
							orig = i;
							dest = k;
							primeiro = 0;
						} else{
							if(menorPeso > m[i][j]){
                                menorPeso = m[i][j];
                                orig = i;
                                dest = k;
							}
						}
					}
				  }
				}
		}
	if(primeiro == 1) break;
	if(pai[orig] == -1) pai[orig] == dest;
	else pai[dest] == orig;
    for(i = 0; i<NV; i++){
        if(arv[i] == arv[dest])
            arv[i] = arv[orig];
    }
    }

    //MOSTRAR OS PAI DE CADA VERTICE E A ARVORE GERADORA
	printf("\nArvore Geradora Minima Kruscal: \n");
          for(i=0; i<NV; i++){
              if(pai[i] != -1)
                printf("%d ", pai[i]);
          }
          printf("\n");
          arvGer = (int **) malloc(NV * sizeof(int*));
          for(i = 0; i < NV; i++){
            arvGer[i] = (int *) malloc(arestas * sizeof(int));
            for(j=0; j<arestas; j++){
                arvGer[i][j] = 0;
            }
          }
          for(i = 0; i < NV; i++){
            aux = pai[i];
            arvGer[i][aux] = 1;
          }
          for(i = 0; i < NV; i++){
             printf("\n");
            for(j=0; j<arestas; j++){
                printf("%d ",arvGer[i][j]);
            }
          }

    //CAMINHO DA ORIGEM ATÉ O DESTINO
    vetor = (int *) malloc(NV * sizeof(int));
    printf("\n\n");
    if(pai[destino] != -1){
        for(i=0; i<NV; i++){
            if(pai[destino] == -1)
               break;
             vetor[i] = pai[destino];
             destino = pai[destino];
            }

        for(i=NV-1; i>=0; i--){
            if(vetor[i] != -1)
            printf("%d ", vetor[i]);
        }
    } else {
            printf("\nNão existe caminho para %d partindo de %d\n", destino, orig);
    }
}

void menu(){
  printf ("############################\n");
  printf ("========== GRAFOS ==========\n");
  printf ("############################\n\n");

  printf ("============ MENU ==========\n");
  printf ("1 - Matriz do Grafo\n");
  printf ("2 - Dijkstra\n");
  printf ("3 - Prim\n");
  printf ("4 - Kruskal\n");
  printf ("5 - Floyd-Warshall \n");
  printf ("\n");
  printf ("8 - Sobre \n");
  printf ("0 - Sair\n");
  printf ("Informe a opcao desejada: ");
}

void sobre(){
  system("cls || clear");

  printf ("#################################################\n");
  printf ("=================================================\n\n");
  printf ("DESENVOLVEDOR:  Euclides Freire da Silva Abreu\n");
  printf ("E-MAIL:         euclidesfreiresa@gmail.com\n");
  printf ("CURSO:          Engenharia de Computacao - UEMA\n");
  printf ("DISCIPLINA:     Estrutura de Dados Avancada\n");
  printf ("PROFESSOR:      Daniel de Sousa Moraes\n");
  printf ("DATA:           01/07/2017\n\n");
  printf ("O QUE E?: \n");
  printf (" A partir de um arquivo.txt pegar as dimensoes da\n");
  printf ("matriz gerar o grafo e mostrar o menor caminho de\n");
  printf ("acordo com a escolha do agoritmo heuristico.\n");
  printf ("\n=================================================\n");
  printf ("#################################################\n");
}

