#include "game.h"
#include "networking.h"

struct clientDetails* retrieveNumber(struct clientDetails* client1, struct clientDetails* client2){
  //helper function
  //Gets the number value of a guess from either client
    fd_set read_fds;
    char buff[BUFFER_SIZE];
    int connection1 = client1 -> connection;
    int connection2 = client2 -> connection;
    FD_ZERO(&read_fds);
    FD_SET(connection1, &read_fds);
    FD_SET(connection2, &read_fds);
    int number = 0;
    int largestConnection = 0;
    if(connection1 > connection2){
      largestConnection = connection1;
    } else{
      largestConnection = connection2;
    }
    int i = select(largestConnection + 1, &read_fds, NULL, NULL, NULL);
    if(FD_ISSET(connection1, &read_fds)){
        int readBytes = read(connection1, buff, sizeof(buff));
        if(readBytes == 0){
          client1 -> guess = -1;
          return client1;
        }
        printf("%d\n", readBytes);
        sscanf(buff,"%d", &(client1 -> guess));
        printf("%d\n", client1 -> guess);
        return client1;
    }
    if(FD_ISSET(connection2, &read_fds)){
        int readBytes = read(connection2, buff, sizeof(buff));
        if(readBytes == 0){
          client2 -> guess = -1;
          return client2;
        }
        printf("%s\n", buff);
        sscanf(buff,"%d", &(client2 -> guess));
        return client2;
    }
}


int countFiles(char* dir) {
  DIR* d = opendir(dir);
  int counter = 0;
  struct dirent* entry = readdir(d);
  while (entry != NULL) {
    counter++;
    entry = readdir(d);
  }
  closedir(d);
  return counter;
}

struct fileinfo randFile() {
  // helper function
  // pick a random file and put its size and name in a struct fileinfo
  char dir[256] = "./gamefiles/";
  DIR* d = opendir(dir);
  if (d == NULL) {
    perror("error opening directory");
  }
  else {
    srand( time(NULL) );
    struct dirent* entry = readdir(d);
    for (int i = 0; i < abs(rand()) % countFiles(dir); i++) {
      entry = readdir(d);
    }
    struct stat file;
    strncat(dir, entry->d_name, 127);
    if (stat(dir, &file) == -1) perror("error with struct stat");
    struct fileinfo data;
    data.size = file.st_size;
    strncpy(data.name, entry->d_name, 127);
    closedir(d);
    return data;
  }
}

struct clientDetails* game(struct clientDetails* client1, struct clientDetails* client2) {
  // runs a match between client1 and client2
  // requires the file descriptors for the two clients
  // returns the file descriptor of the winner

  // CASE WHERE THEY ARE TIED IS IMPORTANT


  struct fileinfo data = randFile();
  while (strcmp(data.name, ".") == 0 || strcmp(data.name, "..") == 0) {
    data = randFile();
  }
  int fileSize = data.size; 

  printf("real file size: %d [LINE 94 IN GAME.C]", fileSize); 
  char * msg = malloc(sizeof (char) * BUFFER_SIZE);
  sprintf(msg, "%s %s \n", "Guess the size of the following file: ", data.name); 
  write(client1->connection, msg, BUFFER_SIZE);
  write(client2->connection, msg, BUFFER_SIZE);
  
  struct clientDetails * firstGuess = retrieveNumber(client1, client2);
  struct clientDetails * secondGuess;
  if(firstGuess -> guess == -1){
    if(firstGuess -> connection == client1 -> connection){
      secondGuess = retrieveNumber(client2, client2);
      return client2;
    } else if(firstGuess -> connection == client2 -> connection){
      secondGuess = retrieveNumber(client1, client1);
      return client1;
    }
  } else{
    secondGuess = retrieveNumber(client1, client2);
  }
  if(secondGuess -> guess == -1){
    if(secondGuess -> connection == client1 -> connection){
      return client2;
    } else if(secondGuess -> connection == client2 -> connection){
      return client1;
    }
  }

  int guess1 = abs(fileSize - firstGuess->guess); 
  // printf("GUESS1 FILE TABLE: %d; GUESS1: %d\n", client1->connection, guess1); 
  int guess2 = abs(fileSize - secondGuess->guess); 
  // printf("GUESS2 FILE TABLE: %d; GUESS2 %d\n", client2->connection, guess2); 

  free(msg); 
  
  if (guess1  < guess2) {
    return firstGuess; 
  }
  else if (guess1 > guess2)
    return secondGuess; 
  else  
    return NULL; // return null if we have the same guess

}

struct clientDetails* rockPaperScissors (struct clientDetails* client1, struct clientDetails* client2) { //rename for compiling reasons 
  char msg[BUFFER_SIZE] = "rock = 0; paper = 1; scissors = 2\n";
  write(client1->connection, msg, BUFFER_SIZE);
  write(client2->connection, msg, BUFFER_SIZE);

  struct clientDetails * firstGuess = retrieveNumber(client1, client2);
  struct clientDetails * secondGuess;
  if(firstGuess -> guess == -1){
    if(firstGuess -> connection == client1 -> connection){
      secondGuess = retrieveNumber(client2, client2);
      return client2;
    } else if(firstGuess -> connection == client2 -> connection){
      secondGuess = retrieveNumber(client1, client1);
      return client1;
    }
  } else{
    secondGuess = retrieveNumber(client1, client2);
  }
  if(secondGuess -> guess == -1){
    if(secondGuess -> connection == client1 -> connection){
      return client2;
    } else if(secondGuess -> connection == client2 -> connection){
      return client1;
    }
  }

  int guess1 = firstGuess->guess;
  int guess2 = secondGuess->guess;

  if (guess1 == 0) {
    if (guess2 == 1) {
      return secondGuess; 
    }
    else if (guess2 == 2) {
      return firstGuess;
    }
    else {
      return NULL;
    }
  }
  else if (guess1 == 1) {
    if (guess2 == 2) {
      return secondGuess; 
    }
    else if (guess2 == 0) {
      return firstGuess;
    }
    else {
      return NULL;
    }
  }
  else if (guess1 == 2) {
    if (guess2 == 0) {
      return secondGuess; 
    }
    else if (guess2 == 1) {
      return firstGuess;
    }
    else {
      return NULL;
    }
  }
  else {
    return NULL;
  }
}
