#Les variables automatiques :
#$@ valeur du  target
#$< nom du premier pré-requis associé au target
#$? nom des pré-requis plus récent que le target
#$^ liste sans répétition des pré-requis
#$+ comme $^ mais avec les répétitions
#$* nom du target avec le suffix tronqué

#Variables pour faciliter la saisie et les modifications dans le Makefile :
#Variable pour le compilateur
CC ?= gcc
GW ?= i586-mingw32msvc-gcc

#Variable où aller chercher les fichiers
VPATH = lib:build:bin:src:include:src/tests

#Variables pour la confection de la librairie :
#Options pour les lignes de code faites pour la confection des fichiers objets
DIROBJ := bin/
CFLAGS += -g -lm -lpthread -Wall -I./include -I./src# -std=c99 -Wall -I./include -I./src
#-L./lib/SDL/lib -I./lib/SDL/include -lSDL2 -lSDL2_ttf -lSDL2_mixer -lSDL2_image -fPIC -Wall -std=c99
OBJETS = hadamard.o matrice.o etalement.o codeur.o pseudo_aleatoire.o binaire_formate.o agent_life_cycle.o
FICHIERSC = $(OBJETS:.o=.c)

#Nom du programme principal
DIRMAIN := src/targets/
#NOMPROGPRINC = tp1_A
PROGRPRINC = $(NOMPROGPRINC).o
PATHMAIN := $(DIRMAIN)$(PROGRPRINC)

#Dossier de  l'exécutable
DIRBUILD := build/

#Noms des librairies statiques et dynamiques
DIRLIB := lib/
LINKNAME ?= $(NOMPROGPRINC)
libSTATIC := $(DIRLIB)lib$(LINKNAME).a
MAJEUR ?= .0
MINEUR ?= .1
CORRECTION ?= .0
SONAMECOURT := lib$(LINKNAME).so
SONAME := $(SONAMECOURT)$(MAJEUR)
REALNAME := $(SONAME)$(MINEUR)$(CORRECTION)

#Variables pour la confection des executables de test :
TESTDIR := $(DIRBUILD)test/
TESTDIRC := src/tests/
TESTOBJETS = test_matrice.o test_pseudo_aleatoire.o test_binaire_formate.o test_codeur_artm.o test_codeur_hdbn.o test_compression_arithmetique.o test_agent_life_cycle.o test_etalement.o
TESTFICHIERSC = $(TESTOBJETS:.o=.c)
TESTEXEC = $(TESTOBJETS:%.o=%)
#TESTSTATIC = test_blokus.static
TESTlibSTATIC := test_lib$(LINKNAME).a
TESTstaticLDLIBS := -l:$(TESTlibSTATIC)

#Options pour les librairies
libCFLAGS = -shared -fPIC ,-soname,
libLDFLAGS = -L.
libLDLIBS = -lc

#Options pour l'archive
ARFLAGS = rcs -U

#Options des programmes en statique et dynamique
STATIC = $(NOMPROGPRINC).static
DYNAMIC = $(NOMPROGPRINC).shared
EXE = $(NOMPROGPRINC).exe
sharedLDFLAGS := $(CFLAGS)
sharedLDLIBS := -l:$(LINKNAME)
#staticLDFLAGS := $(CFLAGS)
staticLDLIBS := -l:$(libSTATIC)
staticLDLIBS := $(libSTATIC)

#Conception du Makefile :
#Execution du programme en entier
all: | MKDIR MOVE

#Création des dossiers
MKDIR: $(DIRMAIN)$(PROGRPRINC)
	-mkdir $(DIRLIB) $(DIROBJ) $(DIRBUILD)

#Fabrication des fichiers objet .o
$(OBJETS): CFLAGS := $(CFLAGS)
$(OBJETS): $(FICHIERSC)

#Fabrication du fichier objet main.o
$(PROGRPRINC): LDFLAGS := $(CFLAGS)

#Conception de l'archive pour la bibliothèque statique
$(libSTATIC)($(OBJETS)): ARFLAGS := $(ARFLAGS)
$(libSTATIC)($(OBJETS)): $(OBJETS)

#Règle pour appeler la conception de l'archive
$(libSTATIC): $(libSTATIC)($(OBJETS))

#Conception de la bibliothèque dynamique avec ses 2 liens symboliques
$(REALNAME): $(OBJETS)
	$(CC) $(libCFLAGS)$(SONAME) -o $@ $^
	ln -sf $@ $(SONAMECOURT)
	ln -sf $@ $(SONAME)

#Génération du programme static
$(STATIC): LDFLAGS := $(staticLDFLAGS)
$(STATIC): LDLIBS := $(staticLDLIBS)
$(STATIC): $(DIRMAIN)$(PROGRPRINC) $(libSTATIC)
	$(CC) -o $@ $(DIRMAIN)$(PROGRPRINC) $(staticLDFLAGS) $(staticLDLIBS) $(CFLAGS)

#Génération du programme dynamique
#$(DYNAMIC): LDFLAGS := $(sharedLDFLAGS)
#$(DYNAMIC): LDLIBS := $(sharedLDLIBS)
#$(DYNAMIC): $(DIRMAIN)$(PROGRPRINC) $(REALNAME)
#	$(CC) -o $@ $(DIRMAIN)$(PROGRPRINC) $(sharedLDFLAGS) $(sharedLDLIBS)

#Move les fichiers dans leur dossier respectif : .so .a dans le dossier lib. .o dans le dossier bin. L'exécutable dans le dossier build
#MOVE: $(DYNAMIC) $(STATIC)
MOVE: $(STATIC)
	-mv *.a* *.so* ./$(DIRLIB)
#	-mv *$(LINKNAME)* ./$(DIRBUILD)
	-mv *$(NOMPROGPRINC)* ./$(DIRBUILD)
	-mv $(DIRMAIN)*.o $(DIRLIB)*.o *.o ./$(DIROBJ)

#Nettoie les fichiers créés dans le current directory
clean:
	-rm *.o *Tp1_A* *tp1_A*
	-rm -R $(DIRBUILD)

#Nettoie les dossiers créés et leur contenu
mrProper: clean clearScreen
	-rm -R $(DIRLIB)*lib* $(DIROBJ)

#Nettoie l'écran
clearScreen:
	-clear

#Mets à jour et la push sur le git distant
majDoc:
	-git pull
	-doxygen
	-git add docs/*
	-git commit -m "Maj doc le $(shell date "+%d/%m/%y à %H:%M:%S")"
	-git push origin master


##################### FICHIERS DE TEST #####################

#Lancement des directives pour la création des TEST
test: | TESTMOVE

#Move les fichiers dans leur dossier respectif : .so .a dans le dossier lib. .o dans le dossier bin. Les exécutables de test dans le dossier build
TESTMOVE: $(TESTEXEC)
	-mv $(DIRMAIN)*/*.o $(DIRLIB)*.o *.o ./$(DIROBJ)
	-mv *test* *Test* ./$(TESTDIR)/

TESTMKDIR:
	-mkdir $(DIRLIB) $(DIROBJ) $(DIRBUILD)
	-mkdir $(TESTDIR)

#Fabrication des executables de TEST
$(TESTOBJETS): CFLAGS := $(CFLAGS)
$(TESTOBJETS): $(TESTDIRC)$(TESTFICHIERSC) TESTMKDIR

#Fabrication du fichier objet main.o
#$(TESTOBJETS): LDFLAGS := $(CFLAGS)

#Règle pour appeler la conception de l'archive de TEST
$(TESTlibSTATIC): $(TESTlibSTATIC)($(OBJETS))

#Conception de l'archive pour la bibliothèque statique de TEST
#$(TESTlibSTATIC)($(OBJETS)): ARFLAGS := $(ARFLAGS)
#$(TESTlibSTATIC)($(OBJETS)): $(OBJETS) $(TESTOBJETS)

#Génération des exécutables de TEST
$(TESTEXEC): LDFLAGS := $(staticLDFLAGS)
$(TESTEXEC): LDLIBS := $(staticLDLIBS)
$(TESTEXEC): $(TESTOBJETS) $(libSTATIC)
	$(CC) -o $@ $@.o $(staticLDFLAGS) $(staticLDLIBS) $(CFLAGS)
