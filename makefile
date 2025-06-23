
compile: networking.o client.o server.o game.o
	@gcc -o cli networking.o client.o
	@gcc -o ser networking.o server.o game.o

cli: networking.o client.o game.o
	@gcc networking.o client.o -o cli

ser: networking.o server.o game.o
	@gcc networking.o server.o game.o -o ser

client: cli 
	@./cli 

server: ser
	@./ser

networking.o: networking.c networking.h 
	@gcc -c networking.c 

server.o: server.c 
	@gcc -c server.c 

game.o: game.c 
	@gcc -c game.c  

clean: 
	@rm -f wins.dat
	@rm -f ser
	@rm -f cli 
	@rm -f *.o 
