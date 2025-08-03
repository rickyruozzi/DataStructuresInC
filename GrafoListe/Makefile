# Nome del file sorgente senza estensione
SRC = Grafo

# Nome eseguibile (stesso nome del sorgente per default)
EXEC = $(SRC)

# Compilatore e flags
CC = gcc
CFLAGS = -Wall -g

# File oggetto
OBJ = $(SRC).o

all: $(EXEC)

# Regola per creare l'eseguibile a partire dall'oggetto
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Regola per creare il file oggetto a partire dal sorgente
$(OBJ): $(SRC).c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all clean
