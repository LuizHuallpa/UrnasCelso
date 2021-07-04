#include <stdio.h>

#include <string.h>

#include <stdlib.h>

#include <conio.h>

#include <ctype.h>      //contém declarações para manipulação de caracteres.

#include <locale.h>     //para o programa aceitar acentuação

#include <string.h>

#define TAM 100 //TAM recebe o valor de 100 inteiros

typedef struct Voto {
    int Urna;
    int Secao;
    int Candidato;
}
votos;

void Incluir(void); // função para Incluir dados
void Listar(void); // função para Mostrar os votos ja incluidos
char AddMais(); // função para Adicionar mais votos na Voto
void Formata(void); // função para Apaga todos os votos na Voto

static int qtd = 0; // qtd é uma variavel do tipo estatica que conta a quantidade de votos incritos
votos max[TAM]; // agora max[100] é um vetor do tipo votos definido com o typedef
FILE * arq; // declarar a variável(*arq) como ponteiro do arquivo(FILE)

void Incluir(void) {
    int cont = 0; //cont sera a variavel contadora
    int retorno; //retorno seve para definir se fwrite funcionou
    char op = 's'; //seve para definir a opção na função AddMais()

    arq = fopen("Voto.txt", "a"); // fopen cria arquivo de entrada
    if (arq == NULL) { //caso o sistema não consiga criar o arquivo
        printf("Erro!\nO arquivo da lista não pode ser aberto!\n"); //sera mostrada esta mensagen
        getch(); // espera que o usuário pressione uma tecla
        exit(1); //caso esse erro ocorra este comando encerra o programa
    }
    while ((op == 's')) {
        do {
            printf("\nSeção ");
            scanf("%d", & max[cont].Secao);

        } while (max[cont].Secao > 5);
        do {

            printf("\nUrna ");
            scanf("%d", & max[cont].Urna);
        } while (max[cont].Urna > 5);

        do {
            printf("\nCandidato ");
            scanf("%d", & max[cont].Candidato);
            if (max[cont].Candidato > 5) {
                printf("\n Digite um valor de 1 até 5 ");
            };
        } while (max[cont].Candidato > 5);

        retorno = fwrite( & max[cont], sizeof(max[cont]), 1, arq);

        if (retorno == 1) {
            printf("\n Gravacao ok! ");
        } else
            printf("\n não gravei!\n\n ");
        cont++; //enquanto cont for menor 100 adiciona mais um contato
        op = AddMais(); //chama a função que pergunta se deseja inserir novos votos
        qtd++; //acrecenta 1 contato a mais
    }
    fclose(arq); //fecha o arquivo Voto.txt
}
void bubble_sort(int * vetor, int n ) {
    int k, j, aux;
	char *aux_char;
    for (k = 1; k < n; k++) {
        for (j = 0; j < n - k; j++) {
            if (vetor[j] > vetor[j + 1]) {
                aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j+1] = aux;
            }
        }
    }
}

//==============  Adicionar mais votos  ===============/
char AddMais() {
    char op;
    do {
        printf("\n Deseja adicionar outro voto[S ou N]? ");
        op = getch();
        printf("\n");
    } while (op != 's' && op != 'n');
    return op;
}

//=====================  Apagar tudo  ====================/
void Formata() {

    arq = fopen("Voto.txt", "w+"); //recria um arquivo limpo
    printf("\n\tVotação Encerrada! Todos os votos apagados!\n ");
    fclose(arq); //fecha o arquivo Voto.txt
    getch(); // espera que o usuário pressione uma tecla
}

//=====================  finaliza votacao  ====================/
void finaliza() {

    int i = 0, retorno, vencedor;

    arq = fopen("Voto.txt", "r"); //fopen abre o arquivo no modo leitura "r"
    if (arq == NULL) { //caso o SO não consiga abrir o arquivo
        printf("Erro!\nO arquivo da lista não pode ser aberto!\n"); //sera mostrada esta mensagens
        getch(); //espera que o usuário pressione uma tecla
        exit(1); //caso esse erro ocorra este comando encerra o programa
    }
    int candidatos[5] = {
        0
    };
    int total = 0;
    int cnt = 0;
    while (fread( & max[cnt], sizeof(votos), 1, arq) == 1) {
        candidatos[max[cnt].Candidato-1]++;
        total++;
        cnt++;

    }
    printf("\n");
    i = 0;
    for (i = 0; i < 5; i++) {
        double percent = (candidatos[i] * 100) / total;
        printf("Candidato %d - %d votos %.2f%% \n", i, candidatos[i], percent);
    }
    Formata();
}

//================== Lista os votos cadastrados ======================/
void Listar(void) {
    int i = 0, retorno;

    arq = fopen("Voto.txt", "r"); //fopen abre o arquivo no modo leitura "r"
    if (arq == NULL) { //caso o SO não consiga abrir o arquivo
        printf("Erro!\nO arquivo da lista não pode ser aberto!\n"); //sera mostrada esta mensagens
        getch(); //espera que o usuário pressione uma tecla
        exit(1); //caso esse erro ocorra este comando encerra o programa
    }

    int candidatos[5] = {
        0
    };
    int total = 0;
    int cnt = 0;
    while (fread( & max[cnt], sizeof(votos), 1, arq) == 1) {
        candidatos[max[cnt].Candidato-1]++;
        total++;
        cnt++;
    }
    printf("\n");
    i = 0;
    char *cand[] = {"Candidato 1","Candidato 2","Candidato 3","Candidato 4","Candidato 5"};
    
    for (i = 0; i <5; i++) {
        double percent = (candidatos[i] * 100) / total;
        printf("%s - %d votos %.2f%% \n", cand[i], candidatos[i], percent);
    }
    
    printf("\n");
    bubble_sort(candidatos, 5);
    for (i = 0; i <5; i++) {
        double percent = (candidatos[i] * 100) / total;
        printf("Candidato %d - %d votos %.2f%% \n", i+1, candidatos[i], percent);
    }
    system("pause");
}

//=====================   Menu   =======================/
void menu(void) {
    char op; //variavel de opção
    do {
        system("cls"); // limpar tela
        printf("\n\n\t\tVOTAÇÃO DO CONSELHOC\n");
        printf("\n 1 = Votar\n 2 = Resultados Parciais\n 3 = Encerrar Votação\n");
        op = getch();
        switch (op) {
        case '1':
            Incluir();
            break;
        case '2':
            Listar();
            break;
        case '3':
           // finaliza();
           printf("por enquanto n");
            break;
        default:
            printf("\a Digite uma opção valida\n");
            getch(); //espera que o usuário pressione uma tecla
        }
    }
    while (op);
}

//=========== Função Principal ================/
int main() {
    int var;
    setlocale(LC_ALL, "Portuguese"); //Define no console o idioma Portugues
    printf("\n\n\t\tVotação do Conselho Tutelar - Pressione qualquer tecla para continuar \n\t\tOu pressione spacebar para sair\n\n");

    var = getch();
    if (var == 32) {
        exit(0);
    }
    menu(); // chamando a funçao menu para a main
    system("pause");
}
