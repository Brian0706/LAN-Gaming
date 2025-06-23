#include "networking.h"
#include "game.h"
#include <sys/select.h> // needed for the retrieve files

void readWins() {
    int recordingFile = open("wins.dat", O_RDONLY); 
    if (recordingFile < 0 )
        perror("could not create the file");
    struct writeFile * reader = malloc(sizeof (struct writeFile)); 
    while (read(recordingFile, reader, sizeof(struct writeFile))) {
        printf("name: %s wins: %d\n", reader->name, reader->wins); 
    }
    close(recordingFile); 
}

void recordWins (char * user, int currentWins) {
    int recordingFile = open("wins.dat", O_RDWR | O_CREAT, 0666); // create the file 
    if (recordingFile < 0 )
        perror("could not create the file");
    int i = 0; // this is to keep track of indexing 
    int totalWins = 0; 
    struct writeFile * reader = malloc(sizeof (struct writeFile)); 
    while (read(recordingFile, reader, sizeof(struct writeFile))) {
        if (strcmp(reader->name, user) == 0){
            totalWins = currentWins + reader->wins; 
            break; 
        }
        i++; 
    }
    close(recordingFile); 
    int bytes = recordingFile = open("wins.dat", O_RDWR | O_CREAT, 0666);
    err(bytes, "failed to read"); 
    lseek(recordingFile, sizeof(struct writeFile) * i, 0); 

    if (totalWins != 0 ) {
        strcpy (reader->name, user); 
        reader->wins = totalWins; 
        write(recordingFile, reader, sizeof(struct writeFile)); 

        
    }
    else {
        strcpy (reader->name, user); 
        reader->wins = currentWins; 
        write(recordingFile, reader, sizeof(struct writeFile)); 
        
    }
    close(recordingFile);

} 

void serverConnection (int i, char * message) {
    if (i == 0) {
        printf("Client lost connection with the server!\n"); 
    }
    else if (i < 0) {
        printf("Error: %s - %s\n", message, strerror(errno));
        exit(1); 
    }

}


struct clientDetails* createClient(int connection, char * buff){
    struct clientDetails* p = malloc(sizeof(struct clientDetails));
    p -> connection = connection;
    p -> guess = 0;
    p -> wins = 0;
    p -> isAlive = 1;
    strcpy(p -> identifier, buff); 
    return p;
}

int client_handling (struct clientDetails* client1, struct clientDetails* client2, int whichGame) {
    int playing = 1;
    while(playing){
        printf("Sending message to start game\n");
        int writeBytes;
        char startingMessage[BUFFER_SIZE] = "The match is beginning get ready.\0";
        int connection1 = client1 -> connection;
        int connection2 = client2 -> connection;
        
        writeBytes = write(client1 -> connection, startingMessage, BUFFER_SIZE);
        serverConnection(writeBytes, "failed to write to the client"); 

        writeBytes = write(client2 -> connection, startingMessage, BUFFER_SIZE);
        serverConnection(writeBytes, "failed to write to the client"); 
        
        struct clientDetails* winner = malloc(sizeof(struct clientDetails));
        if (whichGame == 0) {
        winner = game(client1, client2);
        }
        else if (whichGame == 1) {
        winner = rockPaperScissors(client1, client2);
        }
        char* loseFlag = malloc(BUFFER_SIZE); 
        char* winFlag = malloc(BUFFER_SIZE); 
        char* tieFlag = malloc(BUFFER_SIZE);
        winFlag[0] = '1';
        loseFlag[0] = '0';
        tieFlag[0] = '3';
        if(winner == NULL){
            write(connection1, tieFlag, BUFFER_SIZE);
            write(connection2, tieFlag, BUFFER_SIZE);
        }
        else if(winner -> connection == client1 -> connection){
            write(connection2, loseFlag, BUFFER_SIZE);
            write(connection1, winFlag, BUFFER_SIZE);
            playing = 0;
            free(winner);
            return 0;
        } else if(winner -> connection == client2 -> connection){
            write(connection1, loseFlag, BUFFER_SIZE);
            write(connection2, winFlag, BUFFER_SIZE);
            free(winner);
            playing = 0;
            return 1;
        }
    }
}

// AUTOMATICALLY GIVE THE WIN IF SOMEONE LOSES CONNECTION

int main(){
    printf("Which game would you like to play? Enter 0 for file size guessing game or 1 for rock paper scissors: ");
    char buff[BUFFER_SIZE];
    fgets(buff, BUFFER_SIZE, stdin);
    int whichGame;
    sscanf(buff, "%d", &whichGame);

    // INIT ALL VARIABLES 
    int matchStarted = 0;
    int numOfPlayers = 0;
    int playersJoined = 0;
    int maxPlayerCount = 16;
    pid_t p;

    int playerConnections[maxPlayerCount];
    struct clientDetails* players[maxPlayerCount];
    int listen_socket = server_setup();

    // THIS LOOP IS TO GET OBTAIN PLAYERS 
    while(!matchStarted && numOfPlayers < maxPlayerCount){
        fd_set read_fds;
        char buff[BUFFER_SIZE];
        printf("The current number of players is %d\n", numOfPlayers);
        printf("Type in start to start\n");


        FD_ZERO(&read_fds);
        FD_SET(STDIN_FILENO, &read_fds);
        FD_SET(listen_socket, &read_fds);
        int j = select(listen_socket + 1, &read_fds, NULL, NULL, NULL);
        
        if (FD_ISSET(STDIN_FILENO, &read_fds)) {
            fgets(buff, sizeof(buff), stdin);
            buff[strlen(buff)-1]=0;
            if(strcmp(buff, "start") == 0){
                matchStarted = 1;
            }
        }

        if(FD_ISSET(listen_socket, &read_fds)){

            playerConnections[numOfPlayers] = server_tcp_handshake(listen_socket);

            //THIS READ IS TO READ THE USERNAMES 
            int readBytes = read(playerConnections[numOfPlayers], buff, sizeof(buff));
            if (readBytes <= 0) {
                perror("could not create the connection\n"); 
            }

            //CREATE THE CLIENTS WITH USERNAME + SERVER SOCKET
            players[numOfPlayers] = createClient(playerConnections[numOfPlayers], buff);
            
            printf("%s joined\n", buff ); 

            numOfPlayers++; // create the amount of numPlayers needed 
        }

    }


    printf("There are currently %d player(s)... game is starting\n", numOfPlayers);
    playersJoined = numOfPlayers; 
    while(numOfPlayers > 1){
        int numberOfServers = numOfPlayers / 2;
        int playerPosInArray = 0;
        struct clientDetails* alivePlayers[numOfPlayers];
        for(int i = 0; i < playersJoined; i++){
            if(players[i] -> isAlive){
                // printf("Player is still connnected %d\n", playerConnections[i]);
                alivePlayers[playerPosInArray] = players[i];
                playerPosInArray++;
            }
        }
        for(int i = 0; i < numberOfServers; i++){
            p = fork();
            if(p == 0){
                int exiting = client_handling(alivePlayers[2 * i], alivePlayers[2 * i + 1], whichGame); 
                if(exiting == 0){
                    exit(alivePlayers[2 * i + 1] -> connection);
                } else{
                    exit(alivePlayers[2 * i] -> connection);
                }
            }
        }
        if(p != 0){
            for(int i = 0; i < numberOfServers; i++){
                int status;
                wait(&status);
                for(int i = 0; i < playersJoined; i++){
                    if(playerConnections[i] == WEXITSTATUS(status)){
                        players[i] -> isAlive = 0;
                    }
                }
            }
        }
        numOfPlayers -= numberOfServers;
    }
    printf("Game over!\n");
    for(int i = 0; i < playersJoined; i++){
        if(players[i] -> isAlive){
            printf("The winning player is %s, congratulations %s!\n", players[i] -> identifier, players[i] -> identifier);
            char* winFlag = malloc(BUFFER_SIZE);
            strcpy(winFlag, "you are the winner!");
            write(players[i] -> connection, winFlag, BUFFER_SIZE);
            recordWins(players[i]->identifier, 1); // add 1 win 
        }
    }
    printf("-----LIFETIME WINS------\n"); 
    readWins(); 
}

// choose the amount of users that you want for this function 
//----------------- ENDED UP NOT USING THESE FUNCTIONS------------------//
// int chooseUser () {
//     char * buff = malloc(sizeof (char) * BUFFER_SIZE); 
//     printf("do you want to use the default usernames? yes or no: ");
//     fflush (stdout); 

//     while (1) {
//     fgets(buff, BUFFER_SIZE, stdin);
//     buff = strsep(&buff, "\n");
//     if (strcmp (buff, "yes") == 0 ){
//         free(buff);
//         return 1; 

//     }
//     else if (strcmp (buff, "no") == 0){
//         free(buff); 
//         return 2; 

//     }
//     else {
//         printf("please write yes or no "); 
//         fflush(stdout);
    
//     }

//     }
 

// }

// int numUsers () {
//     char * buff = malloc(sizeof(char) * BUFFER_SIZE);
//     printf("please enter the number of users: ");
//     fflush(stdout); 

//     fgets(buff, BUFFER_SIZE, stdin); 
//     int numOfPlayers; 
//     sscanf(buff, "%d", &numOfPlayers);

//     free(buff); 
//     return numOfPlayers; 
// }
// ----------------- ENDED UP NOT USING THESE FUNCTIONS------------------//
