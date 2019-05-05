# SlideOut 


## Par: 

**
ABDRABO Khaled	     - p1713323 
BASSIOUNY Mohamed 	 - p1707606
GHANDOURI Feras      - p1601442
MESSOUD Salem        - p1714033
**

## Structure de l’archive

 - Dossier ./src : contient le code source en .cpp et les entêtes des fonctions en .h pour les modules principales ainsi que le module d'affichage
 - Dossier ./bin: contient les exécutables du jeu.
 - Dossier ./data: contient les fichiers nécessaire(font/images) pour le jeu.
 - Dossier ./obj: contient les fichiers .o générer lors de la compilation du jeu.
 - Dossier ./doc: contient la documentation du code source du jeu.
 - Fichier ./makefile qui permet la compilation (cf plus bas section compilation)
   Fichier ./readme.md : explication brève pour commencer (ce fichier actuelle.)

## Instructions :



### Dépendances Pour compiler

1. La librairie SDL2,Il faudra l’installer: [http://wiki.libsdl.org/Installation](http://wiki.libsdl.org/Installation)
2. La librarie (moteur physique) Box2D 
Sous ubuntu/debian  ``` sh sudo apt-get install libbox2d2.3.0```
sous fedora/centos  vous pouvez utlisez la version pré-compilé en changeant ``INCLUDE_DIR = -IBox2D`` par ``INCLUDE_DIR = -I$(CORE_DIR)Box2D``
et ``LIBS_BOX2D = -LBox2D -lBox2D`` par ``LIBS_BOX2D = -L$(CORE_DIR)Box2D -lBox2D``





ce jeu est destiné au système d’exploitation Unix, il vous faudra des étapes supplémentaire pour la compilation sous Windows/linux.

### Étapes
1. Télécharger le module en format archive. Extraire l’archive.  
2. naviguer dans votre Shell vers le répertoire d’extraction. 

     > cd SlideOut


 

####  Commande de compilation

3. Make : créer tous les fichiers exécutables dans le répertoire bin ainsi que les objets dans le dossier obj

NB: Make clean : vide les dossiers obj et bin.

#### Exemple d'utilisation
4. Exécutez le jeu depuis le répertoire racine d'extraction comme ceci:
 

 ```sh
 `myuser@machine $ ./bin/mainSdl`#lancer le jeu     
```
  
##### Options:

> appliquer plus de force avec la fléche du bas

 `myuser@machine $ firefox doc/html/index.html` # Pour consulter la documentation
 Ou vous pouvez visitez la version en-ligne 
