# SlideOut 


## Par: 

**

* ABDRABO Khaled	     - p1713323 
* BASSIOUNY Mohamed 	 - p1707606
* GHANDOURI Feras      - p1601442
* MESSOUD Salem        - p1714033


**

## Structure de l’archive

 - Dossier ./src : contient les fichiers sources (.cpp) et entêtes (.h) 
 -         ./src/core : modules principaux du jeu (Terrain, Player, Game)
 -         ./src/grapic : modules pour l'affichage Grapic
 -         ./src/sdl : modules pour l'affichage SDL
 -         ./src/txt : modules pour l'affichage Txt
 -         
 - Dossier ./bin: contient les exécutables du jeu.
 - Dossier ./data: contient les assets (images, polices, sons) du jeu.
 - Dossier ./obj: contient les fichiers .o générés lors de la compilation du jeu.
 - Dossier ./doc: contient la documentation du code source du jeu.
 - 
 - Fichier ./Makefile qui permet la compilation (cf plus bas section compilation)
   Fichier ./Readme.md : Informations sur l'application

## Instructions :



### Dépendances Pour compiler

1. Il faudra la librairie SDL2 pour l'affichage: [http://wiki.libsdl.org/Installation](http://wiki.libsdl.org/Installation)
2. La librarie Box2D pour le moteur physique
Sous ubuntu/debian  ``` sudo apt-get install libbox2d2.3.0 ```
sous fedora/centos  vous pouvez utlisez la version pré-compilé en changeant ``INCLUDE_DIR = -IBox2D`` par ``INCLUDE_DIR = -I$(CORE_DIR)Box2D``
et ``LIBS_BOX2D = -LBox2D -lBox2D`` par ``LIBS_BOX2D = -L$(CORE_DIR)Box2D -lBox2D``

ce jeu est destiné au système d’exploitation Unix, il vous faudra des étapes supplémentaire pour la compilation sous Windows/linux.

### Étapes
1. Extraire l’archive.  
2. naviguer dans votre Shell vers le répertoire d’extraction. 

     > cd SlideOut


####  Commande de compilation

A la racine du répertoire : 

3. ``` make ```: créé les éxécutables pour les 3 versions (Texte, Grapic, SDL) dans ./bin, les fichier .o dans ./obj
    ``` make clean ```: vide les dossiers obj et bin.
NB: Make clean : vide les dossiers obj et bin.

#### Exemple d'utilisation
4. Exécutez le jeu depuis le répertoire racine d'extraction comme ceci:
 

 ```sh
 `myuser@machine $ ./bin/mainSdl` #lancer le jeu     
```
  
##### Options:

> appliquer plus de force avec la fléche du bas

 `myuser@machine $ firefox doc/html/index.html` # Pour consulter la documentation
 Ou vous pouvez visitez la version en-ligne 
