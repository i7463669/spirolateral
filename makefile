# make file for spirolateral
# spirolateral.o
OBJECTS = UIspirolateral.o
PROGNAME = UIspirolateral
OUTPUT =-l SDL2 -l SDL2_ttf -lm -o
OPTIONS = -std=c89 -c
COMPILER = clang

$(PROGNAME) : $(OBJECTS)
	$(COMPILER) $(OBJECTS) $(OUTPUT) $(PROGNAME)
	
	
	
#-L /usr/local/lib 
#spirolateral.o: spirolateral.c
#$(COMPILER) $(OPTIONS) spirolateral.c
	
	
UIspirolateral.o: UIspirolateral.c
	$(COMPILER) $(OPTIONS) UIspirolateral.c

clean:
	@echo remove object files
	@rm $(OBJECTS)
