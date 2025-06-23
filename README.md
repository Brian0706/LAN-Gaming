# Bunch Of Random Games 

### Brian and Friends

Aareeb Jamil, Brian Chau, Jason Ng
       
### Project Description:

Explain what is this project.
The server hosts up to 16 clients and makes them play in a tournament, with the game being chosen by the host (either the file size guessing game or rock paper scissors). The server forks off a subserver for each game played between a pair of clients. The file size guessing game is when two players compete to guess the size of a file (chosen randomly from the gamefiles directory) based on the name of the file. Whoever is closest to the actual size wins. Rock paper scissors is the usual, with the two players entering 0, 1, or 2 corresponding to rock, paper, or scissors. After each win, the server updates the lifetime wins of the players in a data file. At the end of the tournament, the server prints the data file.

### Instructions:

How does the user install/compile/run the program.
We do not use any new libraries. Compile using "make compile". The server user will run make server. For clients they have to connect with a command. For example, if the server has to be run from homer and the client users will need to run ./cli *homer's ip*. 

How does the user interact with this program?

One user hosts the program (in this case, it needs to be on homer [because of the funny business with ports]/home computer if all the clients are playing from the home computer). The user who control the server can pick the game (either rock, paper, scissors or guess the file size). After an instance of the server is created, the clients can start connecting to the server. The max number of players is 16, but the server user can start whenever they want. 
After the server starts the game, the clients are prompte for an input. If they lose, they will see a message saying they lost. 