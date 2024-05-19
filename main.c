#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

FILE *arquivo;
char *nomearq="compturadores.dat";

typedef struct{
    char modelo[30];
    char marca[30];
    char processador[30];
    int memoria;
    int hd;
    float tela;
    char tipohd;  // Só serão aceitas as letras s para ssd e c para convencional
}Computador;

void Mostrar1PC(){
  arquivo = fopen(nomearq, "rb");
  Computador PC;
  int tam=0;
  int num;
  fseek(arquivo, 0, SEEK_SET);
  while(!feof(arquivo)){
    fread(&PC, sizeof(Computador), 1, arquivo);
    if(feof(arquivo)){break;};
    tam++;
  }
  printf("\nTAMANHO: %i\n", tam);
  printf("Digite qual o número do computador: ");
  scanf("%i", &num);
  getchar();
  while(num < 0 || num > (tam - 1)){
    printf("Opção inválida, digite novamente: ");
    scanf("%i", &num);
    getchar();
  }
  fseek(arquivo, num*sizeof(Computador), SEEK_SET);
  fread(&PC, sizeof(Computador), 1, arquivo);
  printf("\nComputador Nº%i", num);
  printf("\nModelo: %s", PC.modelo);
  printf("\nMarca: %s", PC.marca);
  printf("\nProcessador: %s", PC.processador);
  printf("\nMemória: %i", PC.memoria);
  printf("\nHD: %i", PC.hd);
  printf("\nTela: %f", PC.tela);
  printf("\nTipo HD: %c\n", PC.tipohd);
  fclose(arquivo);
  printf("\n\n");
}
void MostrarPC(){
  system("clear");
  arquivo = fopen(nomearq, "rb");
  Computador PC;
  int tam=0;
  fseek(arquivo, 0, SEEK_SET);
  while(!feof(arquivo)){
    fread(&PC, sizeof(Computador), 1, arquivo);
    if(feof(arquivo)){break;};
    printf("//------------------------------//");
    printf("\nComputador Nº%i", tam);
    printf("\nModelo: %s", PC.modelo);
    printf("\nMarca: %s", PC.marca);
    printf("\nProcessador: %s", PC.processador);
    printf("\nMemória: %i", PC.memoria);
    printf("\nHD: %i", PC.hd);
    printf("\nTela: %f", PC.tela);
    printf("\nTipo HD: %c\n\n", PC.tipohd);
    tam++;
  }
  fclose(arquivo);
  printf("\n");
}
void InserirPC(){
  system("clear");
  arquivo = fopen(nomearq, "ab+");
  Computador PC;
  fseek(arquivo, 0, SEEK_END);
  printf("Digite as informações sobre o computador\nDigite o modelo: ");
  gets(PC.modelo);
  printf("Digite a marca: ");
  gets(PC.marca);
  printf("Digite o processador: ");
  gets(PC.processador);
  printf("Digite a memória: ");
  scanf("%i", &PC.memoria);
  getchar();
  printf("Digite o HD: ");
  scanf("%i", &PC.hd);
  getchar();
  printf("Digite a tela: ");
  scanf("%f", &PC.tela);
  getchar();
  printf("Digite o tipo do HD, 'S' para SSD e 'C' para convencional: ");
  scanf("%c", &PC.tipohd);
  getchar();
  while(PC.tipohd != 's' && PC.tipohd != 'S' && PC.tipohd != 'c' && PC.tipohd != 'C'){
    printf("Digite uma opção válida, 'S' para SSD ou 'C' para convencional: ");
    scanf("%c", &PC.tipohd);
    getchar();
  }
  fwrite(&PC, sizeof(Computador), 1, arquivo);
  fclose(arquivo);
  printf("\n\n");
}
void RemoverPC(){
  int num;
  int tam=0;
  arquivo = fopen(nomearq, "rb");
  while(!feof(arquivo)){
    Computador test;
    fread(&test, sizeof(Computador), 1, arquivo);
    if(feof(arquivo)){break;};
    tam++;
  }
  Computador *vet;
  vet = malloc(tam*sizeof(Computador));
  printf("Digite o número do computador que deseja excluir: ");
  scanf("%i", &num);
  getchar();
  while(num < 0 || num >= tam){
    printf("Opção inválida, digite novamente: ");
    scanf("%i", &num);
    getchar();
  }
  fclose(arquivo);
  arquivo = fopen(nomearq, "rb");
  int x=0;
  while(!feof(arquivo)){
    Computador a;
    fread(&a, sizeof(Computador), 1, arquivo);
    if(feof(arquivo)){break;};
    strcpy(vet[x].modelo, a.modelo);
    strcpy(vet[x].marca, a.marca);
    strcpy(vet[x].processador, a.processador);
    vet[x].memoria = a.memoria;
    vet[x].hd = a.hd;
    vet[x].tela = a.tela;
    vet[x].tipohd = a.tipohd;
    x++;
  }
  fclose(arquivo);
  arquivo = fopen(nomearq, "wb");
  x=0;
  for(x = 0; x < tam; x++){
    Computador PC;
    if(x != num){
      strcpy(PC.modelo, vet[x].modelo);
      strcpy(PC.marca, vet[x].marca);
      strcpy(PC.processador, vet[x].processador);
      PC.memoria = vet[x].memoria;
      PC.hd = vet[x].hd;
      PC.tela = vet[x].tela;
      PC.tipohd = vet[x].tipohd;
      fwrite(&PC, sizeof(Computador), 1, arquivo);
      fseek(arquivo, 0, SEEK_END);
    }
  }
  free(vet);
  fclose(arquivo);
}

main(){
  system("clear");
  int esc;
  do{
    printf("Digite uma opção\n1 - Mostrar um computador\n2 - Mostrar todos computadores\n3 - Incluir um computador\n4 - Excluir um computador\n0 - Sair\n");
    scanf("%i", &esc);
    getchar();
    if(esc==1){Mostrar1PC();}
    else if(esc==2){MostrarPC();}
    else if(esc==3){InserirPC();}
    else if(esc==4){RemoverPC();}
    else if(esc==0){printf("\nPrograma finalizado");}
    else {printf("Opção inválida");};
  }while(esc!=0);
}