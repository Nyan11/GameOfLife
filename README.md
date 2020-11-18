# GameOfLife

Par Yann LE GOFF
En L3 CDA UBO


## Comment compiler ?

Compiler:

`make`

Pour changer les régle du plateau de jeu:

  - Dans le fichier `conway.h`
  - Changer la variable `N` [0..1000] pour changer la taille du plateau
  - Changer la variable `TOR` [0..1] pour rendre le plateau torique.
  - Recompiler

Clean:

`make clean`

## Lancer le code

Une fois compiler, vous pouvez l'utiliser avec les options suivantes:

Version simple:

`./prog`

Version avec choix du seed
`./prog [seed]`

exemple:

`./prog 404`

Version avec un glider: (fonctionne avec TOR = 1 et N >= 10)

`./prog glider`

Version avec un Middle Ship: (fonctionne avec TOR = 1 et N >= 13)

`./prog ship`

Version avec un Gosper Gun: (fonctionne avec TOR = 0 et N >= 36)

`./prog gun`



