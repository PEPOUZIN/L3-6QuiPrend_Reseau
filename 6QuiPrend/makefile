CC = gcc
CFLAGS = -std=c11
SRC = main.c Joueur.c Ordi.c OrdiAmeliorer.c GestionJoueur.c GestionOrdi.c GestionOrdiAmeliorer.c Manche.c Paquet.c Carte.c Partie.c Affichage.c Plateau.c 
OBJ = $(SRC:.c=.o)
EXEC = 6Quiprend3.exe

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

clean:
	del $(OBJ) $(EXEC)
