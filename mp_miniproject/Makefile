OBJECT =  main.o step2.o step3.o helper.o expr.o

file: $(OBJECT)
	g++ -o numerics $(OBJECT)
%.o: %.cpp expr.hpp functions.hpp step2.hpp step3.hpp helper.hpp
	g++ -Wall -Werror -std=gnu++11 -pedantic -ggdb3 -c $<
clean:
	rm -f *~ *.o 
