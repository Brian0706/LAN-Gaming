# Dev Log:

## Player 1

### 2024-01-02 - Brief description

Expanded description including how much time was spent on task.

### 2024-01-03 - Brief description

Expanded description including how much time was spent on task.

## Player 2

### 2024-01-02 - Brief description

Expanded description including how much time was spent on task.

### 2024-01-03 - Brief description

Expanded description including how much time was spent on task.

```
Brian Chau:

2024-01-03 Started working on proposal
I added names of group members, our idea and how the user would use the program I worked on it with group members for roughly 30 minutes. At home I started on the technical details by determing which topics we were going to use for our project which took another 20 minutes. ~50 minutes

2024-01-04 Finished proposal and began work on networking
I modified our intended project usage and topics we added because of the change in the type of game
we wanted. I worked on this with my group for 30 minutes. At home I copied over a bunch of the networking code from lab to be modified and added main to server and made sure that it worked properly which took 10 minutes. Then, I decided to make the server an array to hold all the connections and then put the connections into the array. This took 20 minutes with most of the time spent coming with the idea. ~1 hour

2024-01-05 Started work on a way to listen to multiple clients
Spent the 40 minutes at school working on the first itieration of the retrieveNumber function which was a copy of the select demo with some changes to fit the project. Then I created a struct to be used to hold both the guess and client metadata to be able to determine which client was communicating. At home, I fixed the struct and then added the struct to the function and fixed all the compiling issues which took 20 minutes. ~1 hour

2024-01-05 Started work on a way to listen to multiple clients
Spent the 40 minutes at school working on the first itieration of the retrieveNumber function which was a copy of the select demo with some changes to fit the project. Then I created a struct to be used to hold both the guess and client metadata to be able to determine which client was communicating. At home, I fixed the struct and then added the struct to the function and fixed all the compiling issues which took 30 minutes. ~1 hour, 10 minutes

2024-01-06 Fixing bugs on retrieveNumber and server creates structs
Made a function to create structs based on the connections from clients to store the guesses from retrieveNumber. Then I fixed some bugs so that retrieveNumber works fully with the clientData struct rather than an int. ~40 minutes

2024-01-07 Started implementation of dynamic starts
Allowed the server to start a match whenever it wanted even if max number of players was not reached. Also continued working on retrieveNumber to fix some bugs. ~30 minutes

2024-01-08 Completed work on starting match and couldn't fix bug with retrieveNumber
I merge all of the changes from the weekend in class as well as worked on a way to prevent the client from prompting for an answer before the match started. At home, I completed this and started work on what the forking server would do but not the actual forking. I spent a large amount of time fixing a bug with socket but could not fix retrieveNumber. ~3 hours 30 minutes

2024-01-09 Started work on forking server
I fixed all the small problems with server and client due to extra reads and writes. Then I worked on the subserver, first creating the subserver logic then creating the forking. I created a way to find all the players still playing and put them into an array so that it was easier to fork. Then I worked on forking and fixed problems due to bad connection errnos. ~2 hours 15 minutes

2024-01-10 Finished making server
I completed the subserver so that it could send a message telling the client when it lost the game. I also created a way for the server to send a message to the client telling it when they were the winner of the whole tournament. Then I spent the rest of the time debugging the server and client. ~1 hour 30 minutes

2024-01-11 Server now runs with odd number of player
I changed out the isPlaying function for a attributes in the clientDetails to make it easier to detect defeated players. I suffered through a lot of bugs but I eventually got it working. ~2 hour 30 minutes

2024-01-12 Fixed problem with players tying and the server breaking
I fixed a problem where if the players tied, the game broke and fixed it but could not fix the problem with the winner losing connection although I identified it as the strcmp if statement not working for some reason. ~1 hour

Aareeb Jamil:

2024-01-04 Edited proposal and brainstormed
Came up with ideas for implementation of project. Added the intended pacing of our project and our planned division of labor to PROPOSAL.md. Total time: ~30 minutes

2024-01-05 Writing helper functions for game.c
In the morning (before school), I planned the overall structure of game.c by adding some function headers to game.c (and game.h). Spent about 20 minutes. In class, I created a directory called gamefiles with some random files for our file size guessing game. I also started working on countFiles() and randFile(), which are helper functions in game.c. Spent about 30 minutes. After school, I finished writing countFiles() and randFile(), and I tested them by creating a dummy main in game.c. Spent about 30 minutes. Total time: ~1 hour 30 minutes

2024-01-08 Writing main game function
In class, I worked on the structure of the main game function and used the retrieveNumber helper function that Brian wrote. Spent about 30 minutes. At home, I tried testing but had issues on the networking side. Now that's fine but I need to make randFile() not produce "." and ".." as results. Spent about 30 minutes. Total time: ~1 hour

2024-01-09 Fixing randFile
I was absent today due to being sick. randFile had a bug where it would sometimes return the "." or ".." entry.I spent a lot of time researching ways to get a list of directory entries that didn't include "." or ".." but just settled on changing the game function such that randFile is called until it doesn't return those entries. Messy solution but it works. Total time: ~40 minutes

2024-01-10 Tested randFile and adding RPS
I hadn't tested randFile so now I have. It works as intended. I also started implementing rock paper scissors since the file guessing game code is done. Total time: ~40 minutes

2024-01-11 Finished Rock Paper Scissors
In class, I finished writing the rock paper scissors function. I also edit some things server-side in order to be able to run rock paper scissors, but I didn't finish. Spent 30 minutes. At home, I finished editing the server and started thinking of more games to possibly implement. Spent 20 minutes. Total time: ~50 minutes

2024-01-14 Removed unnecessary code/comments
I cleaned up some stuff that was unnecessary for the final version, like comments that were just personal notes. I also added more files to the gamefiles directory. Total time: ~30 minutes

Jason Ng:

2024-01-03 11:32 PM Reformatted devlog
Created this entire textbox for greater organization ~5 minutes

2024-01-04 2:32 PM Created files
Planned and created the structure of our project. Worked on making a skeleton for networking and added make commands to the make file. Worked on the input logic for client.c total time: ~30 minutes

2024-01-04 9:01 PM Client logic
Worked on client-side logic again (planning out client-server communication and how they will communicate); primarly worked on server_handling() function ~20 minutes

2024-01-05 2:05 PM Client
Worked on a way to distinguish clients between each other by adding usernames; added logic for communication with server; mostly in the main() function of the client program ~40 minutes

2024-01-07 7:48 PM Client finished + Networking needs restructing
Finished client input logic; worked on debugging and testing; tested the server and client connection and realized we need to completely scrap our previous networking. Need to talk to Brian about this --- need to put the accept function into the server.c or else bad things will happen (error: connection reset by peer); also need to include <sys/select.h> for fd_set function ~1 hour

2024-01-08 2:10 PM Working on choosing usernames
Wrote function chooseUser() in server.c and added communication between server and client... fixing a ton of merge conflicts

2024-01-08 8:35 PM Fixing bugs --- took way longer than necessary
Wrote a helper function for future use (numUsers); tried fixing bugs where the server and client could not communicate properly; TOOK WAYY TOO MUCH TIME ON THAT; ~1 hour (it's because we read in 256 bytes when reading in BUFFER_SIZE was the problem here). Will communicate with group about this

2024-01-09 2:20 PM Finished basic work on game
Finished up and cleaned up the code for game; still need to work on the case where they are equal and we should just play again ~30 minutes

2024-01-10 12:59 AM Exit status and error messaging
Added a bunch of error messages and figured out a way to return the right exit status; most of the time spent was on debugging a bunch of random stuff ~30 minutes

2024-01-10 2:20 PM Commenting code + check connection function
Worked on documenting code ; created function check connection and tested server and client; server works with different users connecting onto homer.stuy.edu ; GOOD SIGN ~30 mins

2024-01-10 7:19 PM More documentation
Continued to document everything and try to trace through all of our code; LINE 41 code takes from where???? Need to ask them about it 40 minutes

2024-01-11 2:05 PM Semaphores
Working on sem.c to add the use of semaphores to our project ~30 minutes

2024-01-11 10:16 PM No Semaphores
Realized that semaphores would be useless here because we would not be using the same machine ~20 minutes
Worked on a way to add storing data to the project; storing wins after every single iteration! ~40 minutes

2024-01-12 2:05 PM Update ReadMe + makefile
Update makefile to remove the dat file + add update to dat file + update ReadMe.md 40 minutes 

2024-01-14 11:57 PM Comment out code + organize things
Commented out excess statements; ended up not using chooseUser() and numUser() ~10 minutes
```
