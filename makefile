CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g
TARGET = fourmiliere_simulation

SRC = main.c \
      fourmi.c \
      reine.c \
      fourmiliere.c \
      liste_fourmis.c \
      animation.c \
      environnement.c


OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJ) $(TARGET)
