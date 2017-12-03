/*
	Cerinta: Inserati rezervari de bilete de tren folosind optiunile oferite.
	Fiecare bilet contine informatii despre:
	Pasager: Prenume, Nume, Varsta
	Data plecarii: zz/ll/aaaa hh:mm
	Data sosirii: zz/ll/aaaa hh:mm
	Ruta: Statie plecare, Via, Statie sosire
	Tren: Cod tren, cod vagon, nr. loc

	Cerinta: Stergeti doua inregistrari, dupa care reconstruiti id-urile astfel
	incat sa nu lipseasca nici un ID intermediar.

	Cerinta: Modificati o inregistrare complet.

	Cerinta: Afisati inregistrarile sortate alfabetic dupa prenume.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>

#define DIM 30
#define DATE_LEN 16
#define VOID_LIST "Nu exista nici o rezervare!\n"
#define PRICE_PER_MIN 15 / 210
#define MINS_IN_YEAR 535680
#define MINS_IN_MONTH 44640
#define MINS_IN_DAY 1440
#define THIS_YEAR 2016
#define NEXT_YEAR 2017






/*
 *
 * STRUCT REGION
 *
*/

typedef struct date {
	int year;
	unsigned int month:4, day:5, hour:5, min:6;
} date;

typedef struct route {
	char dep_station[DIM], arr_station[DIM], via[DIM];
} route;

typedef struct passanger {
	char f_name[DIM], s_name[DIM];
	int age;
} passanger;

typedef struct train {
	int place;
	char code[DIM], wagon[DIM];
} train;

typedef struct booking {
	int id;
	double price;
	date dep_date, arr_date;
	route route;
	train train;
	passanger psg;
} booking;

typedef struct node {
	booking bk;
	struct node *next;
} node;

typedef struct list {
    node *first;
} list;






// Array of function pointers defines
typedef void (*generic_fp)(void);
typedef booking (*single_int)(int x);
typedef void (*list_int)(list *x, int y);
typedef void (*single_list)(list *x);
typedef void (*f_f_list_int)(generic_fp x, generic_fp y, list *z, int w);

#define FUNC_INT(f, p1) ((single_int)(f))(p1)
#define FUNC_LIST_INT(f, p1, p2) ((list_int)(f))(p1, p2)
#define FUNC_LIST(f, p1) ((single_list)(f))(p1)
#define FUNC_MODIFY(f, p1, p2, p3, p4) ((f_f_list_int)(f))(p1, p2, p3, p4)





/*
 *
 * CHECK FUNCTION REGION
 *
*/


/*
 * Function: only_alpha
 **********************
 * Verifica daca toate caracterele unui string sunt litere
 * Returns: 1 - valid
 *			0 - invalid
*/
int only_alpha(char *string) {
	int i, len = strlen(string);

	for (i = 0; i < len - 1; ++i) {
		if (!isalpha(string[i])) {
			return 0;
		}
	}
	return 1;
}

/*
 * Function: only_digit
 **********************
 * Verifica daca toate caracterele unui string sunt cifre
 * Returns: 1 - valid
 *			0 - invalid
*/
int only_digits(char *string) {
	int len = strlen(string) - 1, i;

	string[len] = '\0';
	for (i = 0; i < len; ++i) {
		if (!isdigit(string[i])) {
			return 0;
		}
	}
	return 1;
}

/*
 * Function: only_alpha_digit
 ****************************
 * Verifica daca un string contine doar litere si cifre
 * Returns: 1 - valid
 *          0 - invalid
*/
int only_alpha_digit(char *string) {
	int len = strlen(string) - 1, i;

	for (i = 0; i < len; ++i) {
		if (!isdigit(string[i]) && !isalpha(string[i])) {
			return 0;
		}
	}
	return 1;
}

/*
 * Function: is_empty
 ********************
 * Verifica daca un string nu contine nici un caracter
 * Verifica pentru \n citit prin fgets
 * Returns: 1 - valid
 *			0 - invalid
*/
int is_empty(char *string) {
	if (string[0] == '\n') {
		return 1;
	}
	return 0;
}

/*
 * Function: valid_date
 **********************
 * Verifica daca o data introdusa reprezinta o data valida
 * Returns: 1 - valid
 *			0 - invalid
*/
int valid_date(char *string) {
	int len = strlen(string) - 1, i;
	char *copy = malloc(4 * sizeof(char));
	int nr;

	// Verifica sa aibe lungimea minima conform formatului ZZ/LL/AAAA HH:MM
	if (len < DATE_LEN) {
        free(copy);
		return 0;
	}

    // Verifica string-ul sa aibe cifre pe toate pozitiile corespunzatoare
	for (i = 0; i < len; ++i) {
		if (i != 2 && i != 5 && i != 10 && i != 13) {
			if (!isdigit(string[i])) {
                free(copy);
				return 0;
			}
		}
	}

	// Verifica ziua
    strncpy(copy, string, 2);
    nr = atoi(copy);
    if (!nr || nr > 31) {
        free(copy);
        return 0;
    }

    // Verifica luna
    strncpy(copy, string + 3, 2);
    nr = atoi(copy);
    if (!nr || nr > 12) {
        free(copy);
        return 0;
    }

    // Verifica anul
    strncpy(copy, string + 6, 4);
    nr = atoi(copy);
    if (nr < THIS_YEAR || nr > NEXT_YEAR) {
        free(copy);
        return 0;
    }

    // Verifica ora
    copy[2] = '\0';
    strncpy(copy, string + 11, 2);
    nr = atoi(copy);
    if (nr > 23) {
        free(copy);
        return 0;
    }

    // Verifica minutele
    strncpy(copy, string + 14, 2);
    nr = atoi(copy);
    if (nr > 59) {
        free(copy);
        return 0;
    }
    free(copy);
	return 1;
}

/*
 * Function: following_date
 **************************
 * Verifica daca prima data o succede pe a doua cronologic
 * Returns: 1 - valid
 *          0 - invalid
*/
int following_date(date arr_date, date dep_date) {
    if (arr_date.year < dep_date.year) {
        return 0;
    }
    if (arr_date.year == dep_date.year && arr_date.month < dep_date.month) {
        return 0;
    }
    if (arr_date.year == dep_date.year && arr_date.month == dep_date.month
        && arr_date.day < dep_date.day) {
        return 0;
    }
    if (arr_date.year == dep_date.year && arr_date.month == dep_date.month
        && arr_date.day == dep_date.day && arr_date.hour < dep_date.hour) {
        return 0;
    }
    if (arr_date.year == dep_date.year && arr_date.month == dep_date.month
        && arr_date.day == dep_date.day && arr_date.hour == dep_date.hour
        && arr_date.min <= dep_date.min) {
        return 0;
    }
    return 1;
}

/*
 * Function: valid_id
 ********************
 * Verifica daca id-ul unei rezervari citit de la tastatura exista in lista
 * Returns: 1 - exista
 *          0 - nu exista
*/
int valid_id(int id, node *head) {
    while (head != NULL) {
        if (head->bk.id == id) {
            return 1;
        }
        head = head->next;
    }
    return 0;
}







/*
 *
 * COMPUTE FUNCTION REGION
 *
*/

/*
 * Function: calculate_price
 ***************************
 * Calculeaza pretul calatoriei in functie de numarul de minute de calatorie
*/
double calculate_price(date dep_date, date arr_date) {
	int mins = 0;

	mins += arr_date.min - dep_date.min;
	mins += (arr_date.hour - dep_date.hour) * 60;
	mins += (arr_date.day - dep_date.day) * MINS_IN_DAY;
	mins += (arr_date.month - dep_date.month) * MINS_IN_MONTH;
	mins += (arr_date.year - dep_date.year) * MINS_IN_YEAR;

	return (double)mins * PRICE_PER_MIN;
}

/*
 * Function: int_cmp
 *******************
 * Functia de comparare pentru qsort realizata pe structura booking in functie
 * de ID
*/
int int_cmp(const void *a, const void *b) {
	booking bookA = *(booking *)a;
	booking bookB = *(booking *)b;

	return (bookA.id - bookB.id);
}

/*
 * Function: str_cmp
 *******************
 * Functia de comparare pentru qsort realizata pe structura booking in functie
 * de prenume
*/
int str_cmp(const void *a, const void *b) {
	booking bookA = *(booking *)a;
	booking bookB = *(booking *)b;

	return strcmp(bookA.psg.f_name, bookB.psg.f_name);
}








/*
 *
 * FORMAT FUNCTION REGION
 *
*/

/*
 * Function: c(haracter) to d(igit)
 **********************************
 * Returns: valoarea integerei a cifrei data ca si caracter
*/
int ctod(char c) {
    return c - '0';
}

/*
 * Function: strtoupper
 **********************
 * Schimba toate litere unui string in uppercase
*/
void strtoupper(char *string) {
	int len = strlen(string) - 1, i;

	string[len] = '\0';
	for (i = 0; i < len; ++i) {
		if (isalpha(string[i])) {
			string[i] = toupper(string[i]);
		}
	}
}

/*
 * Function: format_string
 *************************
 * Schimba caracterul \n citit prin fgets in \0 si schimba toate literele in
 * lowercase, cu exceptia primei litere care va fi uppercase
*/
void format_string(char *string) {
	int len = strlen(string) - 1, i;

	string[len] = '\0';
	for (i = 0; i < len; ++i) {
		string[i] = tolower(string[i]);
	}
	string[0] -= 32;
}

/*
 * Function: format_date
 ***********************
 * Transforma formatul date dintr-un string in valori integer ce sunt salvate
 * intr-o structura de tip date
 *
 * Returns: date - structura de tip date
*/
date format_date(char *string) {
    date date;

	date.day = ctod(string[0]) * 10 + ctod(string[1]);
	date.month = ctod(string[3]) * 10 + ctod(string[4]);
	date.year = ctod(string[6]) * 1000 + ctod(string[7]) * 100 + ctod(string[8])
				* 10 + ctod(string[9]);
	date.hour = ctod(string[11]) * 10 + ctod(string[12]);
	date.min = ctod(string[14]) * 10 + ctod(string[15]);

	return date;
}

/*
 * Function: format_number
 *************************
 * Transforma un numar din string in integer
*/
int format_number(char *string) {
	char *ptr;

	return (int)strtol(string, &ptr, 10);
}










/*
 *
 * READ FUNCTION REGION
 *
*/

/*
 * Function: read_string
 ***********************
 * Citeste si verifica un string ce ar trebui sa contina doar litere si il verifica
 * Va cere reintroducerea datelor pana la introducerea unui string valid
 *
 * Paramteres: *string - pointer catre string-ul de citit
 *			   *text - mesajul de introducere a datelor
 *			   *err_text - mesaj in caz de introducere invalida
*/
void read_string(char *string, char *text, char *err_text) {
	printf("%s", text);
	fgets(string, DIM, stdin);
	if (*string == '\n') {
        fgets(string, DIM, stdin);
	}
	// Cat timp string-ul introdus este invalid citeste iar
	while (!only_alpha(string) || is_empty(string)) {
		printf("%s", err_text);
		fgets(string, DIM, stdin);
	}
}

/*
 * Function: read_date
 *********************
 * Citeste si verifica un string ce ar trebui sa contina formatul unei date
 * Va cere reintroducerea datelor pana la introducerea unui string valid
 *
 * Paramteres: *string - pointer catre string-ul de citit
 *			   *text - mesajul de introducere a datelor
 *			   *err_text - mesaj in caz de introducere invalida
*/
void read_date(char *string, char *text, char *err_text) {
	printf("%s", text);
	fgets(string, DIM, stdin);
	// Cat timp string-ul introdus este invalid citeste iar
	while (!valid_date(string) || is_empty(string)) {
		printf("%s", err_text);
		fgets(string, DIM, stdin);
	}
}

/*
 * Function: read_number
 ***********************
 * Citeste si verifica un string ce ar trebui sa contina doar cifre si il verifica
 * Va cere reintroducerea datelor pana la introducerea unui string valid
 *
 * Paramteres: *string - pointer catre string-ul de citit
 *			   *text - mesajul de introducere a datelor
 *			   *err_text - mesaj in caz de introducere invalida
*/
void read_number(char *string, char *text, char *err_text) {
	printf("%s", text);
	fgets(string, DIM, stdin);
	// Cat timp string-ul introdus este invalid citeste iar
	while (is_empty(string) || !only_digits(string)) {
		printf("%s", err_text);
		fgets(string, DIM, stdin);
	}
}

/*
 * Function: read_mixed_string
 *****************************
 * Citeste si verifica un string ce ar trebui sa contina doar cifre si litere
 * si il verifica Va cere reintroducerea datelor pana la introducerea unui string
 * valid
 *
 * Paramteres: *string - pointer catre string-ul de citit
 *			   *text - mesajul de introducere a datelor
 *			   *err_text - mesaj in caz de introducere invalida
*/
void read_mixed_string(char *string, char *text, char *err_text) {
	printf("%s", text);
	fgets(string, DIM, stdin);
	// Cat timp string-ul introdus este invalid citeste iar
	while (is_empty(string) || !only_alpha_digit(string)) {
		printf("%s", err_text);
		fgets(string, DIM, stdin);
	}
}









/*
 *
 * PRINT FUNCTION REGION
 *
*/

/*
 * Function: main_menu
 *********************
 * Goleste ecranul si afiseaza meniul de optiuni
*/
void main_menu() {
    system("cls");
    printf(" ------------------------------------ \n");
	printf("| A - adauga rezervare               |\n");
	printf("| M - modifica rezervare             |\n");
	printf("| S - sterge rezervare               |\n");
	printf("| L - listeaza rezervarile existente |\n");
	printf("| O - listeaza ordonat dupa prenume  |\n");
	printf("| C - copiaza rezerare               |\n");
	printf("| R - reactualizeaza id-urile        |\n");
	printf("| T - inchide aplicatia              |\n");
	printf(" ------------------------------------ \n");
}

/*
 * Function: print_date
 **********************
 * Afiseaza in format ZZ/LL/AAAA HH:MM data primita ca parametru, tratand cazurile
 * de exceptie cauzate de retinerea ca valoare integer a componentelor
*/
void print_date(date date) {
    char *hour = malloc(3 * sizeof(char)), *min = malloc(3 * sizeof(char));

    if (!date.hour) { // Daca valoarea este 0 se va afisa 00
        hour = "00";
    } else if (date.hour < 10) { // Daca este o cifra, se va afisa ca 0C
        hour[0] = '0';
        hour[1] = date.hour+ '0';
        hour[2] = '\0';
    } else {
        itoa(date.hour, hour, 10);
    }

    if (!date.min) {
        min = "00";
    } else if (date.min < 10) {
        min[0] = '0';
        min[1] = date.min + '0';
        min[2] = '\0';
    } else {
        itoa(date.min, min, 10);
    }

	printf("\t%d/%d/%d ", date.day, date.month, date.year);
	printf("%s:%s", hour, min);

	free(hour);
	free(min);
}

/*
 * FUnction: print_booking
 *************************
 * Afiseaza o rezervare cu toate componentele sale
*/
void print_booking(booking book) {
	printf("%d\t%s\t%s\t%d\t%s\t%s\t%s", book.id, book.psg.f_name, book.psg.s_name,
		   book.psg.age, book.route.dep_station, book.route.via,
		   book.route.arr_station);
	print_date(book.dep_date);
	print_date(book.arr_date);
	printf("\t%s\t%s\t%d\t%.2f RON", book.train.code, book.train.wagon,
		   book.train.place, book.price);
	printf("\n");
}

/*
 * Function: modify_menu
 ***********************
 * Afiseaza meniul cu optiunile de modificat
*/
void modify_menu() {
	printf("\n1. Prenume\n2. Nume\n3. Varsta\n");
	printf("4. Statie plecare\n5. Via\n6. Statie sosire\n");
	printf("7. Data plecare\n8. Data sosire\n");
	printf("9. Cod tren\n10. Cod vagon\n11. Loc\n");
	printf("12. Total\n\n");
}









/*
 *
 * OPERATII LISTA
 *
*/

/*
 * Function: add_to_list
 ***********************
 * Adauga o structura de tip booking la lista de rezervari ce incepe la *head
*/
void add_to_list(list *head, booking book) {
	node *new_node = malloc(sizeof(node));

	new_node->bk = book;
	new_node->next = NULL;
	if (head->first == NULL) { // Daca lista este vida nodul nou va fi capul listei
		head->first = new_node;
	} else { // Altfel lista este parcursa pana la ultimul nod si va fi anexat in
			 // continuare
	    node *tail = head->first;
		while (tail->next != NULL) {
			tail = tail->next;
		}
		tail->next = new_node;
	}
}

/*
 * Function: deconstruct_list
 ****************************
 * Transforma lista simplu inlantuita intr-un vector de structuri aflat la
 * adresa *book
*/

void deconstruct_list(booking *book, list *head) {
	node *active = head->first;
	int i = -1;

	while (active != NULL) {
		book[++i] = active->bk;
		active = active->next;
	}
}

/*
 * Function: reconstruct_list
 ****************************
 * Transforma vectorul de structuri aflat la adresa *book intr-o lista simplu
 * inlantuita
*/
void reconstruct_list(list *head, booking *book) {
	node *active = head->first;
	int i = -1;

	while (active != NULL) {
		active->bk = book[++i];
		active = active->next;
	}
}











/*
 *
 * MAIN FUNCTIONS REGION
 *
*/

/*
 * Function: add_booking
 ***********************
 * Creaza un booking nou cu date introduse de la tastatura si il returneaza
*/
booking add_booking(int last_id) {
	booking book;
	char *string = malloc(DIM * sizeof(char));

	// Passanger info
	read_string(book.psg.f_name, "Introduceti prenumele: ",
				"Prenumele poate contine doar litere!\n");
	format_string(book.psg.f_name);
	read_string(book.psg.s_name, "Introduceti numele: ",
				"Numele poate contine doar litere!\n");
	format_string(book.psg.s_name);
	read_number(string, "Introduceti varsta in ani impliniti: ",
			  "Varsta invalida!\n");
	book.psg.age = format_number(string);

	// Route info
	read_string(book.route.dep_station, "Introduceti statia de plecare! Pentru statiile ce contin spatiu, scrieti cuvintele legat!: ",
				"Statiile pot contine doar litere!\n");
    format_string(book.route.dep_station);
    read_string(book.route.via, "Introduceti statia intermediara sau ""NA"" daca nu exista! Pentru statiile ce contin spatiu, scrieti cuvintele legat!: ",
				"Statiile pot contine doar litere!\n");
    format_string(book.route.via);
	read_string(book.route.arr_station, "Introduceti statia de sosire! Pentru statiile ce contin spatiu, scrieti cuvintele legat!: ",
				"Statiile pot contine doar litere!\n");
    format_string(book.route.arr_station);

    // Dates info
	read_date(string, "Introduceti data si ora plecarii dupa formatul dd/mm/yyyy hh:mm: ",
              "Data invalida!\n");
	book.dep_date = format_date(string);
	read_date(string, "Introduceti data si ora sosirii dupa formatul dd/mm/yyyy hh:mm: ",
              "Data invalida!\n");
	book.arr_date = format_date(string);
	while (!following_date(book.arr_date, book.dep_date)) {
        printf("Data sosirii nu poate fi anterioara sau asemenea celei de plecare!\n");
        read_date(string, "", "Data invalida!\n");
        book.arr_date = format_date(string);
	}

	// Train info
	read_mixed_string(book.train.code, "Introduceti codul trenului: ",
					  "Codul trenului poate contine doar litere si cifre!\n");
	strtoupper(book.train.code);
	read_mixed_string(book.train.wagon, "Introduceti codul corespunzatoare vagonului: ",
					  "Codul vagonului poate contine doar litere si cifre!\n");
	strtoupper(book.train.wagon);
	read_number(string, "Introduceti numarul locului: ",
				"Numar invalid!\n");
	book.train.place = format_number(string);

	book.id = last_id + 1;
	book.price = calculate_price(book.dep_date, book.arr_date);
    free(string);

    return book;
}

/*
 * Function: delete_booking
 **************************
 * Sterge rezervarea cu ID-ul dat ca parametru sau citit de la tastatura din lista
*/
void delete_booking(list *head, int id) {
	char *string = malloc(DIM * sizeof(char));
	node *tail = head->first;

    if (tail == NULL) {
        printf(VOID_LIST);
    } else {
        if (id == 0) { // Daca ID-ul nnu a fost dat este citit de la tastatura
            read_number(string, "Introduceti ID-ul rezervarii de sters: ", "ID invalid\n");
            id = format_number(string);
            while (!valid_id(id, tail)) {
                printf("ID invalid!\n");
                read_number(string, "Introduceti ID-ul rezervarii de sters: ", "ID invalid\n");
                id = format_number(string);
            }
        }

        if (tail->bk.id == id) { // Daca ID-ul de sters este primul nod din lista
            head->first = tail->next; // Capul listei se muta pe urmatorul nod
        } else {
        	// Parcurge lista pana cand urmatorul nod contine ID-ul de sters
            while (tail->next != NULL && tail->next->bk.id != id) {
                tail = tail->next;
            }
            node *save = tail; // Sare peste nodul de sters
            tail = tail->next;
            save->next = tail->next;
        }
        free(tail); // Elibereaza nodul sters din memorie
    }
    free(string);
}

/*
 * Function: modify_booking
 **************************
 * Ofera optiunea de a modifica o componenta sau o rezervare in totalitate
*/
void modify_booking(generic_fp func_delete, generic_fp func_add, list *head, int count) {
	char *string = malloc(DIM * sizeof(char)), *opt = malloc(DIM * sizeof(char));
	int id, nr;
	node *tail = head->first;
	booking book;

    if (tail == NULL) {
        printf(VOID_LIST);
    } else {
    	// Citeste ID-ul de modificat
        read_number(string, "Introduceti ID-ul rezervarii de modificat: ", "ID invalid\n");
        id = format_number(string);
        while (!valid_id(id, tail)) {
            printf("ID invalid!\n");
            read_number(string, "Introduceti ID-ul rezervarii de modificat: ", "ID invalid\n");
            id = format_number(string);
        }

        while (tail->bk.id != id) { // Parcurge lista pana la nodul cu ID citit
            tail = tail->next;
        }

        modify_menu(); // Afiseazaz meniul cu optiunile de modificat
        read_number(opt, "\nAlegeti ce doriti sa modificati: ", "Optiune invalida!\n");
        nr = format_number(opt);
        while (nr < 1 || nr > 12) {
        	printf("Optiune invalida!\n");
            read_number(opt, "Alegeti ce doriti sa modificati: ", "Optiune invalida!\n");
       		nr = format_number(opt);
        }

        switch (nr) { // Modifica in functie de optiune
            case 1: read_string(tail->bk.psg.f_name, "Introduceti prenumele: ",
                                "Prenumele poate contine doar litere!\n");
                    format_string(tail->bk.psg.f_name);
                    break;
            case 2: read_string(tail->bk.psg.s_name, "Introduceti numele: ",
                                "Numele poate contine doar litere!\n");
                    format_string(tail->bk.psg.s_name);
                    break;
            case 3: read_number(string, "Introduceti varsta in ani impliniti: ",
                                "Varsta invalida!\n");
                    tail->bk.psg.age = format_number(string);
                    break;
            case 4: read_string(tail->bk.route.dep_station, "Introduceti statia de plecare! Pentru statiile ce contin spatiu, scrieti cuvintele legat!: ",
                                "Statiile pot contine doar litere!\n");
                    format_string(tail->bk.route.dep_station);
                    break;
            case 5: read_string(tail->bk.route.via, "Introduceti statia intermediara! Pentru statiile ce contin spatiu, scrieti cuvintele legat!: ",
                                "Statiile pot contine doar litere!\n");
                    format_string(tail->bk.route.via);
                    break;
            case 6: read_string(tail->bk.route.arr_station, "Introduceti statia de sosire! Pentru statiile ce contin spatiu, scrieti cuvintele legat!: ",
                                "Statiile pot contine doar litere!\n");
                    format_string(tail->bk.route.arr_station);
                    break;
            case 7: read_date(string, "Introduceti data si ora plecarii dupa formatul dd/mm/yyyy hh:mm: ",
                                    "Data invalida!\n");
                    tail->bk.dep_date = format_date(string);
                    while (!following_date(tail->bk.arr_date, tail->bk.dep_date)) {
    				    printf("Data sosirii nu poate fi anterioara sau asemenea celei de plecare!\n");
        				read_date(string, "", "Data invalida!\n");
        				tail->bk.dep_date = format_date(string);
					}
                    tail->bk.price = calculate_price(tail->bk.dep_date, tail->bk.arr_date);
                    break;
            case 8: read_date(string, "Introduceti data si ora plecarii dupa formatul dd/mm/yyyy hh:mm: ",
                                    "Data invalida!\n");
                    tail->bk.arr_date = format_date(string);
                    while (!following_date(tail->bk.arr_date, tail->bk.dep_date)) {
    				    printf("Data sosirii nu poate fi anterioara sau asemenea celei de plecare!\n");
        				read_date(string, "", "Data invalida!\n");
        				tail->bk.arr_date = format_date(string);
					}
                    tail->bk.price = calculate_price(tail->bk.dep_date, tail->bk.arr_date);
                    break;
            case 9: read_mixed_string(tail->bk.train.code, "Introduceti codul trenului: ",
                                        "Codul trenului poate contine doar litere si cifre!\n");
                    strtoupper(tail->bk.train.code);
                    break;
            case 10: read_mixed_string(tail->bk.train.wagon, "Introduceti codul vagonului: ",
                                    "Codul vagonului poate contine doar litere si cifre!\n");
                    strtoupper(tail->bk.train.wagon);
                    break;
            case 11: read_number(string, "Introduceti numarul locului: ",
                                "Numar invalid!\n");
                    tail->bk.train.place = format_number(string);
                    break;
            /* Pentru modifiacri complete: sterge booking-ul cu ID-ul dat,
             * creaza o noua rezervare cu ID-ul celui sters, o adauga la lista,
             * construieste un vector de structuri booking identic liste,
             * sorteaza crescator dupa ID vectorul, dupa care reconstruieste lista */
            case 12: FUNC_LIST_INT(func_delete, head, id);
                     book = FUNC_INT(func_add, id - 1);
                     add_to_list(head, book);

                     booking array[count];
                     deconstruct_list(array, head);
                     qsort(array, count, sizeof(booking), int_cmp);
                     reconstruct_list(head, array);
                     break;
        }
    }
    free(string);
    free(opt);
}

/*
 * Function: show_bookings
 *************************
 * Afiseaza toate rezervarile existente in lista
*/
void show_bookings(list *head) {
    node *tail = head->first;

	if (tail == NULL) {
		printf(VOID_LIST);
	} else {
		while (tail != NULL) {
			print_booking(tail->bk);
			tail = tail->next;
		}
	}
}

/*
 * Function: show_bookings
 *************************
 * Afiseaza toate rezervarile existente in lista ordonate alfabetic dupa prenume
*/
void ordered_bookings(list *head, int count) {
	booking array[count];
	int i;

	if (!count) {
        printf(VOID_LIST);
	} else {
		deconstruct_list(array, head);
		qsort(array, count, sizeof(booking), str_cmp);
		printf("Inregistrarile sortate in functie de prenume:\n");
		for (i = 0; i < count; ++i) {
			print_booking(array[i]);
		}
	}
}

/*
 * Function: copy_booking
 ************************
 * Creaza o copie a unei rezervari existente
*/
void copy_booking(list *head, int count) {
	char *string = malloc(DIM * sizeof(char));
	int id;
	node *aux = malloc(sizeof(node)), *tail = head->first;

    if (tail == NULL) {
        printf(VOID_LIST);
    } else {
        read_number(string, "Introduceti ID-ul rezervarii de copaiat: ", "ID invalid\n");
        id = format_number(string);
        while (!valid_id(id, tail)) {
            printf("ID invalid!\n");
            read_number(string, "Introduceti ID-ul rezervarii de copaiat: ", "ID invalid\n");
            id = format_number(string);
        }

        while (tail->bk.id != id) {
            tail = tail->next;
        }
        aux->bk = tail->bk;
        aux->next = NULL;
        aux->bk.id = count + 1;

        while (tail->next != NULL) {
            tail = tail->next;
        }
        tail->next = aux;
    }
    free(string);
}

/*
 * FUnction: rebuild_ids
 ***********************
 * Reconstruieste id-urile inregistrarilor astfel incat sa nu existe numere
 * intermediare lipsa
*/
void rebuild_ids(list *head) {
    int id = 1;
    node *active = head->first;

    if (active == NULL) {
        printf(VOID_LIST);
    } else {
        while (active != NULL) {
            if (active->bk.id != id) {
                active->bk.id = id;
            }
            ++id;
            active = active->next;
        }
        printf("ID-urile au fost reactualizate!\n");
    }
}










int main() {
    booking book;
    list bookings = {NULL};
    int count = 0, id = 0;
    char *opt = malloc(DIM * sizeof(char));
    generic_fp func_table[] = {(generic_fp)add_booking, (generic_fp)show_bookings,
    							(generic_fp)modify_booking, (generic_fp)delete_booking,
    							(generic_fp)copy_booking, (generic_fp)rebuild_ids,
    							(generic_fp)ordered_bookings};

    main_menu();
    fgets(opt, DIM, stdin);
    strtoupper(opt);
    while (strcmp(opt, "T") != 0) {
    	switch (*opt) {
    		case 'A': main_menu();
                      book = FUNC_INT(func_table[0], count++);
    				  add_to_list(&bookings, book);
    				  break;
    		case 'L': main_menu();
                      FUNC_LIST(func_table[1], &bookings);
    				  break;
    		case 'O': main_menu();
                      FUNC_LIST_INT(func_table[6], &bookings, count);
                      break;
    		case 'M': FUNC_MODIFY(func_table[2], func_table[3], func_table[0], &bookings, count);
    				  break;
    		case 'S': FUNC_LIST_INT(func_table[3], &bookings, id);
                      --count;
    				  break;
    		case 'C': FUNC_LIST_INT(func_table[4], &bookings, count++);
    				  break;
            case 'R': main_menu();
                      FUNC_LIST(func_table[5], &bookings);
                      break;
    		default: printf("Optiune invalida!\n");
    	}
    	fgets(opt, DIM, stdin);
    	strtoupper(opt);
	}

    return 0;
}
