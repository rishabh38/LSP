libraryLoc = ./lib/
objects = opcodegenerator.o word_utility.o fileHandler.o instructure.o

opcgen : $(objects)
	g++ $(objects) -o opcgen
	

opcodegenerator.o : lib/fileHandler.h lib/instructure.h \
	lib/word_utility.h opcodegenerator.cc 
	g++ -c -iquote $(libraryLoc) opcodegenerator.cc

word_utility.o : lib/word_utility.h lib/word_utility.cc
	g++ -c -iquote $(libraryLoc) lib/word_utility.cc

fileHandler.o : lib/fileHandler.h lib/fileHandler.cc
	g++ -c -iquote $(libraryLoc) lib/fileHandler.cc

instructure.o : lib/instructure.h lib/word_utility.h \
	lib/instructure.cc
	g++ -c -iquote $(libraryLoc) lib/instructure.cc

.PHONY : clean

clean : 
	rm $(objects)
