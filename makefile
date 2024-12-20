CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g
TARGET = fourmiliere_simulation

SRC = main.c \
      fourmi.c \
      reine.c \
      animation.c \
      environnement.c \
      liste_fourmis.c


OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJ) $(TARGET)
