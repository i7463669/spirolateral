# make file for spirolateral
# spirolateral.o
OBJECTS = UIspirolateral.c
PROGNAME = spirolateral
OUTPUT =-lm -l SDL2 -o
OPTIONS = -std=c89 -c
COMPILER = clang

$(PROGNAME) : $(OBJECTS)
	$(COMPILER) $(OBJECTS) $(OUTPUT) $(PROGNAME)
	
	
#spirolateral.o: spirolateral.c
#$(COMPILER) $(OPTIONS) spirolateral.c
	
	
UIspirolateral.o: UIspirolateral.c
	$(COMPILER) $(OPTIONS) UIspirolateral.c

clean:
	@echo remove object files
	@rm $(OBJECTS)
