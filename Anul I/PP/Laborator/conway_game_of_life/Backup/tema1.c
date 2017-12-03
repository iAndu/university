/*
   * Program ce realizeaza un simulator pentru Conway's Game of Life
   * Documentatie: https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
   * Tema 1 laborator PP pentru data de 9/11/2016
   * Autor: Banu Alexandru
*/

#include <stdio.h>
#define NMAX 1000
#define DIRECTIONS 8
#define MAX(a, b) (a > b) ? a : b

int matrix[NMAX][NMAX];
short friends[NMAX][NMAX];

/*
 * Functie: ReadMatrix
 * -------------------
 * citeste o matrice de noOfLines linii si noOfColumns coloane de la tastatura
 *
 * noOfLines: numarul de linii al matricei
 * noOfColumns: numarul de coloane al matricei
 *
 * nu returneaza nimic
*/

void ReadMatrix(int noOfLines, int noOfColumns) {
	int i, j;

	for (i = 0; i < noOfLines; ++i) {
		for (j = 0; j < noOfColumns; ++j) {
			scanf("%d", &matrix[i][j]);
		}
	}
}

/*
 * Functie: NumberOfCells
 * ----------------------
 * calculeaza numarul de celule din matrice
 *
 * noOfLines: numarul de linii al matriceia
 * noOfColumns: numarul de coloane al matricei
 *
 * returneaza: numarul de celule din matrice
*/

int NumberOfCells(int noOfLines, int noOfColumns) {
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
 			   0 daca elementul nu se afla in matrice
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
 * option: optiunea aleasa pentru reprezentare: planara(P) sau toroidala(T)
 * noOfLines: numarul de linii al matricei
 * noOfColumns: nnumarul de coloane al matricei
 *
 * nu returneaza nimic
*/

void ComputeFriends(char option, int noOfLines, int noOfColumns) {
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
                        if (line != -1 && col != -1) {
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
 * noOfLines: numarul de linii al matricei
 * noOfColumns: nnumarul de coloane al matricei
 *
 * nu returneaza nimic
*/

void ReinitializeFriends(int noOfLines, int noOfColumns) {
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
 * noOfLines: numarul de linii al matricei
 * noOfColumns: numarul de coloane al matricei
 *
 * nu returneaza nimic
*/

void NextStage(int noOfLines, int noOfColumns) {
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

int main() {
    int noOfLines, noOfColumns, noOfSteps, nrCells = 0, i, j;
    int nrMaxCells = 0;
    char option;

    scanf("%c %d %d %d", &option, &noOfColumns, &noOfLines, &noOfSteps);
    ReadMatrix(noOfLines, noOfColumns);

    nrCells = NumberOfCells(noOfLines, noOfColumns);
    nrMaxCells = MAX(nrCells, nrMaxCells);

    int step;
    for (step = 0; step < noOfSteps; ++step) {
        ComputeFriends(option, noOfLines, noOfColumns);
        NextStage(noOfLines, noOfColumns);
        ReinitializeFriends(noOfLines, noOfColumns);
        nrCells = NumberOfCells(noOfLines, noOfColumns);
        nrMaxCells = MAX(nrCells, nrMaxCells);
    }

    printf("\n");
    for (i = 0; i < noOfLines; ++i) {
        for (j = 0; j < noOfColumns; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("%0.3f%%\n", (float)nrMaxCells / (noOfLines * noOfColumns) * 100);

    return 0;
}
