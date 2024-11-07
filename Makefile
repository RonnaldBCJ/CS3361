CC		= gcc
TARGET	= cooke_analyzer
SRC		= Persertest2.c
OBJ		= Persertest2.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) ${CFLAGS} -o $@ $(OBJ)

clean:
	rm -f $(TARGET) $(OBJ)