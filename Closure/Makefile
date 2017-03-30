PROG = main
PRODNAME = closure
# Variables pour la compilation des fichiers
CC        =  clang++
CFLAGS    =  -g -Wall
CPPFLAGS  =  -DDEBUG -I$(INCDIR)
LDFLAGS   =  -g
STD = -std=c++14
OBJECTS = functions.o Attribute.o FD.o FDSet.o AttSet.o


all : $(PROG)

%.o : %.cpp
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $(STD) $< -o $@

$(PROG): % : %.o $(OBJECTS)
	$(CC) $(LDFLAGS) $(STD) -o $(PRODNAME) $< $(OBJECTS) -lm

cleanall : clean
	rm -f $(PRODNAME)

clean :
	rm -f *.o


