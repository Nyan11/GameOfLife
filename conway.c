/*
 * Author: Yann LE GOFF <y.legoff97@gmail.com>
 * Date:   07/11/2020 17:16:11
 */
#include "conway.h"

int** init_mat(const unsigned int size)
{
	int i, j;
	int **ptr;
	int **matrice = (int**) malloc((size + 2) * sizeof(int*));
	
	if(matrice == NULL)
	{
		fprintf(stderr, "[ERROR] init_mat: can't allocate memory\n");
		return NULL;
	}
	
	ptr = matrice;
	for(int i = 0; i < (size + 2); i++)
	{
		*ptr = malloc((size + 2) * sizeof(int));
		if(matrice == NULL)
		{
			ptr--;
			for(int j = i; j > 0; j--)
			{ 
				free(*ptr);
				ptr--;
			}
			free(ptr);
			fprintf(stderr, "[ERROR] init_mat: can't allocate memory\n");
			return NULL;
		}
		for(int j = 0; j < (size + 2); j++)
			(*ptr)[j] = DEAD;
		ptr++;
	}
	return matrice;
}

void free_mat(int **m, const unsigned int size)
{
	for(int i = 0; i < (size + 2); i++)
		free(m[i]);
	free(m);
}


void print_mat(int **m, const unsigned int size)
{
	int *ptr;
	for(int i = 0; i < (size + 2); i++)
	{
		ptr = *m;
		for(int j = 0; j < (size + 2); j++)
		{
			if(i == 0 && j == 0)
				printf("╔");
			else if(i == 0 && j == (size + 1))
				printf("╗");
			else if(i == (size + 1) && j == 0)
				printf("╚");
			else if(i == (size + 1) && j == (size + 1))
				printf("╝");
			else if(i == 0 || i == (size + 1))
				printf("══");
			else if(j == 0 || j == (size + 1))
				printf("║");
			else if(*ptr == ALIVE)
				printf("██");
			else
				printf("  ");
			ptr++;
		}
		printf("\n");
		m++;
	}
}

int set_one_cell(int **m, const unsigned int size, int x, int y, int value)
{
	if(x >= (size + 2) || y >= (size + 2))
	{
		fprintf(stderr, "[ERROR] set_one_cell: [x:%d, y:%d] for a size of %d\n", x, y, size + 2);
		return -1;
	}
	if(value)
		m[x][y] = ALIVE;
	else
		m[x][y] = DEAD;
	return 0;
}


int set_mat(int **m, const unsigned int size, int *p, const unsigned int p_size, int value)
{
	for(int i = 0; i < p_size; i +=2)
		if(set_one_cell(m, size, p[i], p[i+1], value))
			return i;
	return 0;
}


int apply_function(int ***m, const unsigned size, int (*func)())
{
	int **m_bis = init_mat(size);
	for(int i = 1; i < (size + 1); i++)
		for(int j = 1; j < (size + 1); j++)
			if(set_one_cell(m_bis, size, i, j, (*func)(*m, size, i, j)))
			{
				fprintf(stderr, "[ERROR] apply_function: something went wrong ?\n");
				free_mat(m_bis, size);
				return -1;
			}
	free_mat(*m, size);
	*m = m_bis;
	return 0;
}


int nb_neighbor(int **m, const unsigned size, unsigned int x, unsigned int y)
{
	if(x >= (size + 2) || y >= (size + 2))
	{
		fprintf(stderr, "[ERROR] nb_neighbor: [x:%d, y:%d] for a size of %d\n", x, y, size + 2);
		return -1;
	}
	int res = 0;
	switch(TOR)
	{
		case 1:
			if(x == 1)
			{
				res += m[size][y-1];
				res += m[size][y];
				res += m[size][y+1];
			}
			if(x == size)
			{
				res += m[1][y-1];
				res += m[1][y];
				res += m[1][y+1];
			}
			if(y == 1)
			{
				res += m[x-1][size];
				res += m[x][size];
				res += m[x+1][size];
			}
			if(y == size)
			{
				res += m[x-1][1];
				res += m[x][1];
				res += m[x+1][1];
			}
				
		case 0:
			res += m[x-1][y-1];
			res += m[x-1][y];
			res += m[x-1][y+1];
			res += m[x][y-1];
			res += m[x][y+1];
			res += m[x+1][y-1];
			res += m[x+1][y];
			res += m[x+1][y+1];
	}
	return res;
}

int find_next_status(int **m, const unsigned size, unsigned int x, unsigned int y)
{
	if(x >= (size + 2) || y >= (size + 2))
	{
		fprintf(stderr, "[ERROR] find_next_status: [x:%d, y:%d] for a size of %d\n", x, y, size + 2);
		return -1;
	}
	int neighbors = nb_neighbor(m, size, x, y);
	if(neighbors < 0)
		return -1;
	switch(m[x][y])
	{
		case DEAD:
			if(neighbors == 3)
				return ALIVE;
			else
				return DEAD;
		case ALIVE:
			if(neighbors < 2)
				return DEAD;
			else if(neighbors < 4)
				return ALIVE;
			else
				return DEAD;
	}
}
			

int randomize_mat()
{
	return (int)((rand()-1) / (double)RAND_MAX * 2) - 1;
}

int main(int argc, char *argv[])
{
	int seed = 1;
	int **matrice = init_mat(N);
	int glider[10] = {4,8,4,9,4,10,5,10,6,9}; // TOR=1 and N=10
	int ship[18] = {1,11,1,13,2,10,3,10,4,10,4,13,5,10,5,11,5,12};  // TOR=1 and N=13
	int gospergun[72] = {1,10,1,11,2,10,2,11,11,9,11,10,11,11,12,8,12,12,13,7,13,13,14,7,14,13,15,10,16,8,16,12,17,9,17,10,17,11,18,10,21,7,21,8,21,9,22,7,22,8,22,9,23,6,23,10,25,5,25,6,25,10,25,11,35,8,35,9,36,8,36,9}; // TOR=0 and N=36
	
	if(argc == 2)
	{
		seed = strtoul(argv[1], 0L, 10);
		if(seed != 0)
		{
			srand(seed);
			apply_function(&matrice, N, &randomize_mat);
		}
		else
		{
			if(!strcmp(argv[1], "glider") && TOR == 1 && N >=10)
				set_mat(matrice, N, glider, 72, ALIVE);
			else if(!strcmp(argv[1], "ship") && TOR == 1 && N >= 13)
				set_mat(matrice, N, ship, 72, ALIVE);
			else if(!strcmp(argv[1], "gun") && TOR == 0 && N >= 36)
				set_mat(matrice, N, gospergun, 72, ALIVE);
			else
				apply_function(&matrice, N, &randomize_mat);
		}
	}
	else
		apply_function(&matrice, N, &randomize_mat);

	int i = 1;
	while(1)
	{
		clear();
		gotoxy(0, 0);
		printf("Rang : %20d", i++);
		printf("\t\tSeed: %20d\n", seed);
		apply_function(&matrice, N, &find_next_status);
		print_mat(matrice, N);
		printf("Press enter to continue\n");
		printf("Press ctrl+C to quit\n");
		getchar();
	}
	free_mat(matrice, N);
	
	return 1;
}




















