vpath %.h  ./lib/
vpath %.cc ./lib/
objects = opcodegenerator.o word_utility.o fileHandler.o instructure.o

opcgen : $(objects)
	g++ $(objects) -o opcgen
	

opcodegenerator.o : opcodegenerator.cc fileHandler.h instructure.h       \
										word_utility.h  
	g++ -I./lib/ -c $< -o $@

word_utility.o : word_utility.cc word_utility.h 
	g++ -I./lib/ -c $<

fileHandler.o : fileHandler.cc fileHandler.h 
	g++ -I./lib/ -c $<

instructure.o : instructure.cc instructure.h word_utility.h 
	g++ -I./lib/ -c $<

.PHONY : clean cleanobj

clean : 
	rm $(objects) opcgen

cleanobj :
	rm $(objects)
