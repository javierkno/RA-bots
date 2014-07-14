GCC=g++
CFLAGS=-c -static

INC_DIR=include
LIB_DIR=lib
SRC_DIR=src

_OBJ= utils.o perceptron.o logisticRegression.o baseBot.o
OBJ= $(patsubst %,$(LIB_DIR)/%,$(_OBJ))
MAINFILE=bot
EXEC=javierkno.10.robot

LIBS=-llbfgs

all : $(SRC_DIR)/$(MAINFILE).cpp $(OBJ)
	$(GCC) -I $(INC_DIR) -L$(LIB_DIR) $< -o $(EXEC) $(OBJ)  $(LIBS)

$(LIB_DIR)/%.o : $(LIB_DIR)/%.cpp $(INC_DIR)/%.h
	$(GCC) $(CFLAGS) $< -o $@ -I$(INC_DIR)

clean:
	rm -Rf $(OBJ) $(EXEC)

