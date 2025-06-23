# Final Project Proposal

## Group Members:

Aareeb Jamil, Brian Chau, Jason Ng

# Intentions:

A file guessing tournament of 16 players where the match log is recorded in a best of 1

# Intended usage:

A server hosts the main game with clients connecting to the server. The server picks a random file and chooses one and records the size. The clients then guess the size of the file is and depending whoever has the cloest guess, they move on, play again in a tie or the program exits. Then the winners of the game are rematched with each other until a winner of the whole tournament is decided. The server then records the match results of each game.

# Technical Details:

Topics we will use:
Working with files - We will have the server write to a file to record the match history of the tournmanet

Processes - The server will fork a bunch of subservers to actually manage the games

Finding infomation about files - The server needs to determine the size of the files being guessed

Networking - The server will connect the clients and organize them into 1v1 matches

Division of Labor - Aareeb works on the game. Jason works on server forking and client management. Brian works on networking. 

A description of your technical design. This should include:

How you are breaking down the project and who is responsible for which parts.

What data structures you will be using and how.

What algorithms and /or data structures you will be using, and how.

# Intended pacing:

01/08 - Networking between two players and the server is functioning
01/10 - File guessing game between two players completed
01/11 - Forking server completed
01/12 - Client reassignment completed
01/15 - Dynamic tournament sizing completed
01/16 - Full program completed
