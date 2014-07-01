.PHONY= clean execute

CC=g++
OPTIONS= #-g 
DEBUG= #-D DEBUG
LIBDIR=lib
INCLUDEDIR=include
_OBJ= MessageListener.o TemplateBot.o Pathfinding.o FuzzyControl.o Rule.o Variable.o LeftRange.o RightRange.o AND.o OR.o TriangleRange.o SetRange.o BotStates.o
OBJ = $(patsubst %,$(LIBDIR)/%,$(_OBJ))

bot:    src/main.cpp $(OBJ)
	$(CC) $(OPTIONS) $(DEBUG) -I $(INCLUDEDIR) src/main.cpp $(OBJ) -o /usr/lib/realtimebattle/Robots/javierkno.10.robot

$(LIBDIR)/%.o : $(LIBDIR)/%.cpp $(INCLUDEDIR)/%.h
	$(CC) $(OPTIONS) $(DEBUG) -c -I $(INCLUDEDIR) -o $@ $<

clean:
	rm -f $(OBJ)

execute:
	/usr/games/realtimebattle --tournament_file t1
