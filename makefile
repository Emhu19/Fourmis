CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g
TARGET = fourmiliere_simulation

SRC = main.c \
      fourmi_creation.c \
      fourmi_deplacement.c \
      fourmi_list.c \
      fourmi_role.c \
      fourmi_update.c \
      reine.c \
      animation.c \
      environnement.c \
      larve.c


OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJ) $(TARGET)
