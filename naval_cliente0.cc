#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>﻿
using namespace std;
#define clear system ("clear")
#define PORT 6325
//#define IP_SERVER "127.0.0.1"
//#define IP_SERVER "10.34.58.194"
#define IP_SERVER "10.34.58.79"
struct jogada{
  int linha;
  int coluna;
};
struct jogada jo;

void exibeMatriz(char  tabuleiro[8][8] ){
  int i,j,count=8;

  for (int k = 0; k < count; k++) {
    printf("%d\t",k );
  }
  printf("\n" );
  for ( i = 0; i < count; i++) {

    for ( j = 0; j < count; j++) {
      printf("%c\t",tabuleiro[i][j]);
    }
    printf("%d\n",i);
  }
  return;
}

void vitoria(bool estado) {
  if (estado == true){
    printf("Os jogadores destruiarm a frota do sevidor e ganharam \n" );
  //  esxibeMatruz(tabuleiro);
    exit(0);
  }else{
    return;
  }
}

int main(int argc, char const *argv[]) {
int s0, s1, f, length, rval, i, N=30,meunumero=0;
int estado;
bool vitoriaJogadores=false;
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

  struct sockaddr_in server;
  time_t ticks;

  s0=socket(AF_INET, SOCK_STREAM, 0);

  if (s0<0){
  perror("opening stream socket");
  exit(1);
  }
  //conexao com o server
  bzero(&server, sizeof(server)) ;
  server.sin_family = AF_INET ;
  server.sin_port = htons (PORT) ;
  server.sin_addr.s_addr = inet_addr(IP_SERVER);
  if (connect(s0, (struct sockaddr *) &server, sizeof (server ) ))
  {
  perror("connectando stream socket");
  exit(0);
}//pronto para começar

//recv(s0,&tabuleiro,sizeof(tabuleiro),0);
//printf("Tabuleiro=%d\n",tabuleiro);

recv(s0,&meunumero,sizeof(meunumero),0);
for ( i = 0; i < 84; i++) {
  printf("Esperadndo sevidor\n");
  //printf("contador=%d\n",i );//dbug
  recv(s0,&estado,sizeof(estado),0);
  recv(s0,&vitoriaJogadores,sizeof(vitoriaJogadores),0);//vesrifica vitoria
  vitoria(vitoriaJogadores);//verifica
  printf("vez=%d\n",estado);//dbug
//  printf("meu numero=%d\n",meunumero );//dbug
  if(estado == meunumero){
    printf("Digite a sua jogada\n");
    cin >> jo.linha;
    cin >> jo.coluna;
  //  printf("jo.linha=%d  jo.coluna=%d\n",jo.linha,jo.coluna);//dbug
    send(s0,&jo,sizeof(struct jogada),0);
    printf("Enviei a jogada\n");
    recv(s0,&tabuleiro,sizeof(tabuleiro),0);
    exibeMatriz(tabuleiro);
    printf("\n" );
  }else{
    printf("Vez jogador %d\n",estado );
    recv(s0,&tabuleiro,sizeof(tabuleiro),0);
    exibeMatriz(tabuleiro);
    printf("\n" );
  }
}

if (vitoriaJogadores==false) {
  printf("servidor ganhou :(\n" );
}
  //rval = recv(s0, &buff, sizeof(buff), 0) ;
  //printf("%s\n", buff) ;
printf("Terminei\n" );
}
