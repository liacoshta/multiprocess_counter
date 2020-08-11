/* Contador de primos
 * Autora: Lia Costa
 * RA: 159834
 * Este programa recebera um texto na entrada e contar quantos números primos 
 * existem nessa entrada.
 * Porém o objetivo é fazer um sistema operar como multi-processos, usando 
 * a instrução fork ().
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

int a=0;

       int Verificaprimo(int num){
/*função que verifica cada primo*/
	for (int i=2; i<num; i++){
		if (num % i == 0|| num ==1){
 			       
         		a=0;//flag para alterar variável contador
			return a;
                        }
	               }
	    	if(num>=2)a=1;
			return a;  			
	}





int main() {



	int j=0;
	int var[100];//vetor de variáveis que armazena número a ser avaliado

	
  /* Definir flags de protecao e visibilidade de memoria */
  int protection = PROT_READ | PROT_WRITE;
  int visibility = MAP_SHARED | MAP_ANON;

  /* Criar area de memoria compartilhada */
	int *nprocessos; 
	int *contador;
	int *i;
  contador = (int*) mmap(NULL, sizeof(int)*100, protection, visibility, 0, 0);
		
	 if ((long int)contador==-1) printf("Erro de alocacao!\n");
	i= (int*)mmap(NULL, sizeof(int)*100, protection, visibility, 0,0);
	nprocessos = (int*)mmap(NULL, sizeof(int)*100, protection, visibility,0,0);
	(*contador)=0;
	(*i)=0;
	(*nprocessos)=0;
	//cria proecssos filhos
	pid_t filho[3];
	filho[0] = fork();/*
	for (int j=0; j<3;j++){
		filho[j] = fork();
		(*nprocessos)++;
	}*/

		//esta parte só executa no processo filho
		if (filho[(0)]==0){//execução do filho	

			Verificaprimo(var[(*i)]);
			if(Verificaprimo(var[(*i)])==1) (*contador)++;
//			(*i)++;
			exit(1);
	
		       } 
	//esta parte executa no processo pai*/
			char lixo;
			do{
			scanf("%d",&var[(*i)]);
			scanf("%c",&lixo);
			 Verificaprimo(var[(*i)]);
			if (Verificaprimo(var[(*i)])==1) (*contador)++;
			if (lixo =='\n') break;
			(*i)++;
			}while (lixo !='\n');
	//esta parte elimina os processos que ainda não acabaram*/
		//	while ((*nprocessos)!=0){
			waitpid(filho[(0)],0,0);
		//	(*nprocessos)--;
			//	}
	/*esse é o fim do programa*/
	printf("%d\n", *contador);	 
	exit(1);
	return 0;


}
