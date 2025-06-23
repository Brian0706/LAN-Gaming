#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/socket.h> 
#include <time.h> 
#include <netdb.h>
#include <dirent.h>

#ifndef GAME_H
#define GAME_H
#define NAME_SIZE 128


struct fileinfo {
  int size;
  char name[NAME_SIZE];
};
struct clientDetails {
  int guess;
  int wins;
  int connection;
  int isAlive;
  char identifier[NAME_SIZE];
};

struct writeFile {
  int wins; 
  char name [NAME_SIZE]; 
};

struct fileinfo randFile();
struct clientDetails* retrieveNumber(struct clientDetails* client1, struct clientDetails* client2);
struct clientDetails* game(struct clientDetails* client1, struct clientDetails* client2);
struct clientDetails* rockPaperScissors (struct clientDetails* client1, struct clientDetails* client2);
#endif
