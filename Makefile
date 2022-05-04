####################################
###      PROGRAMA PRINCIPAL      ###
####################################

program.exe: program.o jugador.o mapa_categorias.o mapa_jugadores.o mapa_torneos.o torneo.o
	g++ -o program.exe program.o mapa_categorias.o mapa_jugadores.o mapa_torneos.o jugador.o torneo.o

program.o: program.cc 
	g++ -c program.cc

#####################################
###        CLASES CONJUNTO        ###
#####################################

mapa_categorias.o: mapa_categorias.cc
	g++ -c mapa_categorias.cc

mapa_jugadores.o: mapa_jugadores.cc jugador.o
	g++ -c mapa_jugadores.cc

mapa_torneos.o: mapa_torneos.cc torneo.o
	g++ -c mapa_torneos.cc

#####################################
###     CLASES INDEPENDIENTES     ###
#####################################

jugador.o: jugador.cc
	g++ -c jugador.cc

torneo.o: torneo.cc
	g++ -c torneo.cc

####################################
###           LIMPIEZA           ###
####################################

clean:
	rm -r *.o
	rm -r *.exe
	rm -r *.tar

####################################
###          COMPRIMIR           ###
####################################

tar: program.cc mapa_torneos.hh mapa_torneos.cc mapa_jugadores.hh mapa_jugadores.cc mapa_categorias.hh mapa_categorias.cc jugador.hh jugador.cc torneo.hh torneo.cc Makefile BinTree.hh
	tar -cvf practica.tar program.cc mapa_torneos.hh mapa_torneos.cc mapa_jugadores.hh mapa_jugadores.cc mapa_categorias.hh mapa_categorias.cc jugador.hh jugador.cc torneo.hh torneo.cc Makefile BinTree.hh
