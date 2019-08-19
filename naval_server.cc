#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netdb.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>﻿
using namespace std;
#define PORT 6325

struct jogada{
  int linha;
  int coluna;
};
struct jogada jo;
/*Função comparador
*   verifica se a posição do escolhida pelo jogador
*   tem ou não "navios"
*   retorna true (1) caso tenha acertado
*   retorna false(0) caso tenha errado
*/
bool comparar(char tabu[8][8],int linha,int coluna){
  printf("Linha:%d\tcoluna:%d\n",linha,coluna );
  printf("teste ==  %c\n",tabu[linha][coluna] );

  if((tabu[linha][coluna])=='n'){
    return true;
  }else{
    return false;
  }
}

void testaVitoria(bool *vitoria,int frota){
  if (frota==0) {
    *vitoria = true;
    }
    return;
}
void fim_de_jogo(bool vitoria){
  if (vitoria==true) {
    printf("Fim de jogo, jogadores ganharam\n" );
  }
}

int main() {
  int sock, length,rval, i, s0, s1,s2, vez;
  int  j0=0,j1=1,j2=2,frota=14;
  bool vitoriaJogadores=false;// se for true os jogadores ganham e o jogo acaba
  char tabuleiro[8][8]={
    {'?','?','?','?','?','?','?','?'},
    {'?','?','?','?','?','?','?','?'},
    {'?','?','?','?','?','?','?','?'},
    {'?','?','?','?','?','?','?','?'},
    {'?','?','?','?','?','?','?','?'},
    {'?','?','?','?','?','?','?','?'},
    {'?','?','?','?','?','?','?','?'},
    {'?','?','?','?','?','?','?','?'}
  };

  char resposta[8][8] = {
    {'a','a','n','n','n','a','a','a'},
    {'a','a','a','a','a','a','a','a'},
    {'n','n','a','a','a','a','a','a'},
    {'n','a','a','a','a','a','a','a'},
    {'n','a','n','n','n','n','a','a'},
    {'n','a','a','a','a','a','a','a'},
    {'n','a','a','a','a','a','a','a'},
    {'a','a','a','a','n','n','a','a'}
  };

  struct sockaddr_in server, client;
  //time_t ticks;
  //char buff[N] ;
  sock = socket(AF_INET, SOCK_STREAM, 0); /* Create socket. */
  if (sock < 0) {
  perror("opening stream socket");
  exit(0);
  }
  /* adresse */
  bzero(&server, sizeof(server)) ;
  server.sin_family = AF_INET ;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons (PORT) ;
  length = sizeof (server) ;
  if (bind(sock, (struct sockaddr *)&server, length) < 0){
  perror("binding stream socket");
  exit(0);
  }

  /*Aguarda conexoes do cliente */
  listen(sock,5);
  for (;;) {
  printf("Servidor: Aguardando conexao!\n") ;
  s0 = accept(sock,(struct sockaddr *)0,0) ;
  send(s0,&j0,sizeof(j0),0);
  printf("Servidor: Aguardando conexao!\n") ;
  s1 = accept(sock,(struct sockaddr *)0,0) ;
  send(s1,&j1,sizeof(j1),0);
  printf("Servidor: Aguardando conexao!\n") ;
  s2 = accept(sock,(struct sockaddr *)0,0) ;
  send(s2,&j2,sizeof(j2),0);
  printf("Todos conectados\n" );
//começa agora.

//send(s0,&tabuleiro,sizeof(tabuleiro),0);
//send(s1,&tabuleiro,sizeof(tabuleiro),0);
//send(s2,&tabuleiro,sizeof(tabuleiro),0);

for (int i =0; i < 28; i++) {
  printf("Start\n" );
  vez =0;
  printf("Vez =%d ,i=%d \n",vez,i);//dbug
  send(s0,&vez,sizeof(vez),0);
  send(s1,&vez,sizeof(vez),0);
  send(s2,&vez,sizeof(vez),0);
  testaVitoria(&vitoriaJogadores,frota);
  send(s0,&vitoriaJogadores,sizeof(vitoriaJogadores),0);
  send(s1,&vitoriaJogadores,sizeof(vitoriaJogadores),0);
  send(s2,&vitoriaJogadores,sizeof(vitoriaJogadores),0);
  fim_de_jogo(vitoriaJogadores);
  printf("Esperando jogador 0\n" );
  recv(s0,&jo,sizeof(struct jogada),0);
  // comparar a resposta-----
  printf("Vou comparar com a rseposta\n" );
  if(comparar(resposta,jo.linha,jo.coluna)){
    printf("Acertou\n");
    tabuleiro[jo.linha][jo.coluna] = 'X';
    frota=frota-1;
  }else{
    printf("ERROU\n" );
    tabuleiro[jo.linha][jo.coluna]='A';
  }//end if
  //-----
  printf("Enviando resusltado\n");
  send(s0,&tabuleiro,sizeof(tabuleiro),0);
  send(s1,&tabuleiro,sizeof(tabuleiro),0);
  send(s2,&tabuleiro,sizeof(tabuleiro),0);
  printf("enviei o tabuleiro\n");
  //------------------------------------------------------
  vez =1;
  printf("Vez =%d ,i=%d \n",vez,i);//dbug
  send(s0,&vez,sizeof(vez),0);
  send(s1,&vez,sizeof(vez),0);
  send(s2,&vez,sizeof(vez),0);
  testaVitoria(&vitoriaJogadores,frota);
  send(s0,&vitoriaJogadores,sizeof(vitoriaJogadores),0);
  send(s1,&vitoriaJogadores,sizeof(vitoriaJogadores),0);
  send(s2,&vitoriaJogadores,sizeof(vitoriaJogadores),0);
  fim_de_jogo(vitoriaJogadores);
  printf("Esperando jogador 1\n" );
  recv(s1,&jo,sizeof(struct jogada),0);
  // comparar a resposta-----
  if(comparar(resposta,jo.linha,jo.coluna)){
    printf("Acertou\n");
    tabuleiro[jo.linha][jo.coluna]='X';
    frota= frota -1;
  }else{
    printf("ERROU\n" );
  tabuleiro[jo.linha][jo.coluna]='A';
  }//end if
  //-----
  printf("Enviando resusltado\n");
  send(s0,&tabuleiro,sizeof(tabuleiro),0);
  send(s1,&tabuleiro,sizeof(tabuleiro),0);
  send(s2,&tabuleiro,sizeof(tabuleiro),0);
  //-----------------------------------------------------------
  vez =2;
//  printf("Vez =%d ,i=%d \n",vez,i);//dbug
  send(s0,&vez,sizeof(vez),0);
  send(s1,&vez,sizeof(vez),0);
  send(s2,&vez,sizeof(vez),0);
  testaVitoria(&vitoriaJogadores,frota);
  send(s0,&vitoriaJogadores,sizeof(vitoriaJogadores),0);
  send(s1,&vitoriaJogadores,sizeof(vitoriaJogadores),0);
  send(s2,&vitoriaJogadores,sizeof(vitoriaJogadores),0);
  fim_de_jogo(vitoriaJogadores);
  printf("Esperando jogador 2\n" );
  recv(s2,&jo,sizeof(struct jogada),0);
  // comparar a resposta-----
  if(comparar(resposta,jo.linha,jo.coluna)){
    printf("Acertou\n");
    tabuleiro[jo.linha][jo.coluna]='X';
    frota= frota -1;
  }else{
    printf("ERROU\n" );
    tabuleiro[jo.linha][jo.coluna]='A';
  }//end if
  //------------
  printf("Enviando resultado\n" );
  send(s0,&tabuleiro,sizeof(tabuleiro),0);
  send(s1,&tabuleiro,sizeof(tabuleiro),0);
  send(s2,&tabuleiro,sizeof(tabuleiro),0);
}



  }
  close (s0); //close(sock); fecha conexão
  close (s1);
  close (s2);
}
