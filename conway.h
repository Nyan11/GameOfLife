/*
 * Author: Yann LE GOFF <y.legoff97@gmail.com>
 * Date:   07/11/2020 17:16:11
 */
#ifndef _H_YLG_CONWAY_
#define _H_YLG_CONWAY_

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

int N = 36;
int TOR = 0;

#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))

enum {DEAD, ALIVE};

/* 
 * Initialize conway matrice. M[N+2][N+2]
 *   size: size of the matrice
 *   return: pointer on first position of the matrice
 */
int** init_mat(const unsigned int size);

/*
 * Free memory of a matrice
 *   m: matrice
 *   size: size of the matrice
 */
void free_mat(int **m, const unsigned int size);


/*
 * Print the matrice of size(N) on the screen.
 *   m: matrice
 *   size: size of the matrice
 */
void print_mat(int **m, const unsigned int size);

/*
 * Set value to ALIVE in the matrice.
 *   m: matrice
 *   size: size of the matrice
 *   p: arrays of positions to initialize the matrice
 *   p_size: total of position to set
 *   return: if 0 all position have been set else the number of position set
 */
int set_mat(int **m, const unsigned int size, int *p, const unsigned int p_size, int value);

/*
 * Set one cell of the matrice
 * m: matrice
 * size: size of the matrice
 * x: x position
 * y: y position
 * value: DEAD or ALIVE
 * return 0 if ok
 */
int set_one_cell(int **m, const unsigned int size, int x, int y, int value);

/*
 * Apply function to the matrice
 *   m: pointer of matrice
 *   size: size of the matrice
 *   func: function to apply
 */
int apply_function(int ***m, const unsigned size, int (*func)());

/*
 * Find the number of neighbor for a given cell.
 *   m: matrice
 *   size: size of the matrice
 *   x: x position
 *   y: y position
 *   return: number of neighbor
 */
int nb_neighbor(int **m, const unsigned size, unsigned int x, unsigned int y);


/*
 * Find the next cell status.
 * if the cell is DEAD and has only 3 neighbors -> ALIVE
 * if the cell is ALIVE and has 2 or 3 neighbors -> ALIVE
 * if the cell is ALIVE and has less than 2 or more than 3 neighbors -> DEAD
 *   m: matrice
 *   size: size of the matrice
 *   x: x position
 *   y: y position
 *   return: DEAD or ALIVE
 */
int find_next_status(int **m, const unsigned size, unsigned int x, unsigned int y);

/*
 * Generate a random number between 0 and 1.
 * Use it to generate random matrice.
 *   return: 0 or 1
 */
int randomize_mat();


#endif
