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
		if (num % i == 0||num==1){
    	        	a=0;//não é primo
			return a;
                        }
	           }
	    	if(num>=2){
			a=1;//é primo
			}else{
			a=0;
			}
		return a;  			
	}

int main() {
	
  /* Definir flags de protecao e visibilidade de memoria */
  int protection = PROT_READ | PROT_WRITE;
  int visibility = MAP_SHARED | MAP_ANON;

  /* Criar area de memoria compartilhada */
	int var[100];
	int *nprocessos; 
	int *contador;
	int *i;
contador = (int*) mmap(NULL, sizeof(int)*1, protection, visibility, 0, 0);
if ((long int)contador==-1) printf("Erro de alocacao!\n");
i = (int*)mmap(NULL, sizeof(int)*1, protection, visibility, 0,0);
nprocessos = (int*)mmap(NULL, sizeof(int)*100, protection, visibility,0,0);
	(*contador)=0;
	(*i)=0;
	(*nprocessos)=0;
	
		char lixo;
		int tam;
		int j;
 //leitura da entrada e armazenamento no vetor de variáveis
			do{
                        scanf("%d",&(var[(*i)]));
                        scanf("%c",&lixo);
                        (*i)++;
                        }while (lixo !='\n');
	
	//cria proecssos filhos
		pid_t filho[3];
	
	for (j=0; j<4;j++){
		filho[j] = fork();
	//esta parte só executa no processo filho
		if (filho[j]==0){
			while((*i)>=0){
				int c, b;
				c = (var[(*i)]);
				(*i)--;
			//	b=Verificaprimo(c);
				if(Verificaprimo(c)){ 
					(*contador)++;
					}
				}
			exit(1);
printf("sou o contador após if%d\n",(*contador));
		
				}
//printf("sou o contador apos while%d\n", *contador);
//exit(1);
	  	}
	 			
		//printf("sou o contador antes waitpid %d\n",*contador);
		/*esse é o fim do programa*/
			for (int k=0;k<4;k++){
				waitpid(filho[k],NULL,0);
			}
	printf("%d\n", (*contador));	 
	exit(1);
}
