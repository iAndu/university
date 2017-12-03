/*
   * Program ce realizeaza un simulator pentru Conway's Game of Life
   * Documentatie: https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
   * Tema 1 laborator PP pentru data de 9/11/2016
   * Autor: Banu Alexandru
*/

#include <stdio.h>
#include <stdlib.h>
#define DIRECTIONS 8
#define MAX(a, b) (a > b) ? a : b

/*
 ***********************************************************
 *********************|------------|************************
 *********************|ZONA FUNCTII|************************
 *********************|------------|************************
 ***********************************************************
*/

/*
 * Functie: ReadMatrix
 * -------------------
 * citeste o matrice de noOfLines linii si noOfColumns coloane de la tastatura
 *
 * **matrix: pointer catre matricea de celule
 * noOfLines: numarul de linii al matricei
 * noOfColumns: numarul de coloane al matricei
 *
 * nu returneaza nimic
*/

void ReadMatrix(int **matrix, int noOfLines, int noOfColumns) {
	int i, j;

	for (i = 0; i < noOfLines; ++i) {
		for (j = 0; j < noOfColumns; ++j) {
			scanf("%d", &matrix[i][j]);
		}
	}
}

/*
 * Functie: AllocateMemory
 * -----------------------
 * aloca memorie dinamic celor doua matrici
 *
 * **matrix: pointer catre matricea de celule
 * **friends: pointer catre matricea de vecini
 * noOfLines: numarul de linii al matricei
 * noOfColumns: numarul de coloane al matricei
 *
 * nu returneaza nimic
*/

void AllocateMemory(int **matrix, short **friends, int noOfLines, int noOfColumns) {
    int i;

    for (i = 0; i < noOfLines; ++i) {
        matrix[i] = (int *)malloc(noOfColumns * sizeof(int));
        friends[i] = (short *)calloc(noOfColumns, sizeof(short));
    }
}

void DiposeMemory(int **matrix, short **friends, int noOfLines, int noOfColumns) {
    int i;

    for (i = 0; i < noOfLines; ++i) {
        free(matrix[i]);
        free(friends[i]);
    }
    free(matrix);
    free(friends);
}

/*
 * Functie: NumberOfCells
 * ----------------------
 * calculeaza numarul de celule din matrice
 *
 * **matrix: pointer catre matricea de celule
 * noOfLines: numarul de linii al matricei
 * noOfColumns: numarul de coloane al matricei
 *
 * returneaza: numarul de celule din matrice
*/

int NumberOfCells(int **matrix, int noOfLines, int noOfColumns) {
	int i, j, nrCells = 0;

	for (i = 0; i < noOfLines; ++i) {
		for (j = 0; j < noOfColumns; ++j) {
			nrCells += matrix[i][j];
		}
	}

	return nrCells;
}

/*
 * Functie: IsInMatrix
 * -------------------
 * verifica daca un element caracterizat prin indicii de linie
 * si de coloana se afla in interiorul matricei
 *
 * line: indicele liniei al elementului din matrice
 * noOfLines: numarul de linii al matricei
 * col: indicele de coloana al elementului din matrice
 * noOfColumns: numarul de coloane al matricei
 *
 * returneaza: 1 daca elementul se afla in matrice
 *			   0 daca elementul nu se afla in matrice
*/

short IsInMatrix(int line, int noOfLines, int col, int noOfColumns) {
    if (line >= 0 && line < noOfLines && col >= 0 && col < noOfColumns) {
        return 1;
    }
    return 0;
}

/*
 * Functie: ComputeFriends
 * -----------------------
 * calculeaza numarul de celule vecine al fiecarui element din matrice
 * in functie de tipul reprezentarii: planara(P) sau toroidala
 * sunt folositi doi vectori di si dj pentru determinarea pozitiei
 * vecinilor unui element
 *
 * **matrix: pointer catre matricea de celule
 * **friends: pointer catre matricea de vecini
 * option: optiunea aleasa pentru reprezentare: planara(P) sau toroidala(T)
 * noOfLines: numarul de linii al matricei
 * noOfColumns: nnumarul de coloane al matricei
 *
 * nu returneaza nimic
*/

void ComputeFriends(int **matrix, short **friends, char option, int noOfLines, int noOfColumns) {
    int i, j, line, col;
    short di[] = {-1, -1, 0, 1, 1, 1, 0, -1}, dj[] = {0, 1, 1, 1, 0, -1, -1, -1}, k;

    if (option == 'P') {
        for (i = 0; i < noOfLines; ++i) {
            for (j = 0; j < noOfColumns; ++j) {
                for (k = 0; k < DIRECTIONS; ++k) {
                    if (IsInMatrix(i + di[k], noOfLines, j + dj[k], noOfColumns)) {
                        friends[i][j] += matrix[i + di[k]][j + dj[k]];
                    }
                }
            }
        }
    } else { /* pentru reprezentarea toroidala */
        for (i = 0; i < noOfLines; ++i) {
            for (j = 0; j < noOfColumns; ++j) {
                for (k = 0; k < DIRECTIONS; ++k) {
                    line = i + di[k];
                    col = j + dj[k];
                    if (IsInMatrix(line, noOfLines, col, noOfColumns)) {
                        friends[i][j] += matrix[line][col];
                    } else { /* daca celula se afla in afara matricei */
                        if (line == -1 && col == -1  && noOfLines > 2 && noOfColumns > 2) {
                            line = noOfLines - 1;
                            col = noOfColumns - 1;
                        } else if (line == - 1 && col == noOfColumns && noOfLines > 2 && noOfColumns > 2) {
                            line = noOfLines - 1;
                            col = 0;
                        } else if (line == noOfLines && col == -1 && noOfLines > 2 && noOfColumns > 2) {
                            line = 0;
                            col = noOfColumns - 1;
                        } else if (line == noOfLines && col == noOfColumns && noOfLines > 2 && noOfColumns > 2) {
                            line = col = 0;
                        } else if (line == -1 && noOfLines > 2) {
                            line = noOfLines - 1;
                        } else if (line == noOfLines && noOfLines > 2) {
                            line = 0;
                        } else if (col == -1 && noOfColumns > 2) {
                            col = noOfColumns - 1;
                        } else if (col == noOfColumns && noOfColumns > 2) {
                            col = 0;
                        }
                        if (IsInMatrix(line, noOfLines, col, noOfColumns)) {
                            friends[i][j] += matrix[line][col];
                        }
                    }
                }
            }
        }
    }
}

/*
 * Functie: ReinitializeFriends
 * ----------------------------
 * reinitializeaza matricea de vecini cu 0
 *
 * **friends: pointer catre matricea de vecini
 * noOfLines: numarul de linii al matricei
 * noOfColumns: nnumarul de coloane al matricei
 *
 * nu returneaza nimic
*/

void ReinitializeFriends(short **friends, int noOfLines, int noOfColumns) {
	int i, j;

	for (i = 0; i < noOfLines; ++i) {
		for (j = 0; j < noOfColumns; ++j) {
			friends[i][j] = 0;
		}
	}
}

/*
 * Functie: NextStage
 * ------------------
 * realizeaza trecerea la urmatorul stagiu al evolutiei celulelor urmand un set de reguli:
 * - daca celula are mai putin de doi vecini, moare de singuratate
 * - daca celula are mai mult de trei vecini, aceasta moare de supraaglomerare
 * - daca un element din matrice are exact trei celule vecine, va fi creata o celula noua
 *   in acel loc
 * - daca o celula are intre doi si trei vecini, aceasta supravietuieste
 *
 * **matrix: pointer catre matricea de celule
 * **friends: pointer catre matricea de vecini
 * noOfLines: numarul de linii al matricei
 * noOfColumns: numarul de coloane al matricei
 *
 * nu returneaza nimic
*/

void NextStage(int **matrix, short **friends, int noOfLines, int noOfColumns) {
    int i, j;

    for (i = 0; i < noOfLines; ++i) {
        for (j = 0; j < noOfColumns; ++j) {
            if (friends[i][j] < 2 || friends[i][j] > 3) {
                matrix[i][j] = 0;
            } else if (friends[i][j] == 3) {
                matrix[i][j] = 1;
            }
        }
    }
}

/*
 * Functie: Print
 * --------------
 * afiseaza matricea de celule finala si procentul maxim de populatie
 *
 * **matrix: pointer catre matricea de celule
 * noOfLines: numarul de linii al matricei
 * noOfColumns: numarul de coloane al matricei
 * nrMaxCells: numarul maxim de celule vii pe parcursul etapelor
 *
 * nu returneaza nimic
*/

void Print(int **matrix, int noOfLines, int noOfColumns, int nrMaxCells) {
    int i, j;

    printf("\n");
    for (i = 0; i < noOfLines; ++i) {
        for (j = 0; j < noOfColumns; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("%0.3f%%\n", (float)nrMaxCells / (noOfLines * noOfColumns) * 100);
}

/*
 ***********************************************************
 *******************|--------------------|******************
 *******************|SFARSIT ZONA FUNCTII|******************
 *******************|--------------------|******************
 ***********************************************************
*/

int main() {
    int noOfLines, noOfColumns, noOfSteps, nrCells = 0, nrMaxCells = 0, **matrix;
    short **friends;
    char option;

    scanf("%c %d %d %d", &option, &noOfColumns, &noOfLines, &noOfSteps);

    matrix = (int **)malloc(noOfLines * sizeof(int *));
    friends = (short **)calloc(noOfLines, sizeof(short *));
    AllocateMemory(matrix, friends, noOfLines, noOfColumns);

    ReadMatrix(matrix, noOfLines, noOfColumns);

    nrCells = NumberOfCells(matrix, noOfLines, noOfColumns);
    nrMaxCells = MAX(nrCells, nrMaxCells);

    int step;
    for (step = 0; step < noOfSteps; ++step) {
        ComputeFriends(matrix, friends, option, noOfLines, noOfColumns);
        NextStage(matrix, friends, noOfLines, noOfColumns);
        ReinitializeFriends(friends, noOfLines, noOfColumns);
        nrCells = NumberOfCells(matrix, noOfLines, noOfColumns);
        nrMaxCells = MAX(nrCells, nrMaxCells);
    }

    Print(matrix, noOfLines, noOfColumns, nrMaxCells);
    DiposeMemory(matrix, friends, noOfLines, noOfColumns);

    return 0;
}
