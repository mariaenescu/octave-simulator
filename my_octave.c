// Copyright Maria Enescu 311CAa 2022-2023
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define N 100

/**
	Structura folosita pentru memorarea informatiilor despre o matrice
**/
typedef struct {
	int *a;	// a = matricea sub forma unui vector
	int m;	// m = numar linii
	int n;	// n = numar coloane
	int s;	// s = suma elementelor din matrice
} elem;

/**
	Functie folosita pentru validarea numărului cu privire la overflow-ul
	ce ar putea aparea in fuctiile de calcul.
	* Parametrul s de tip long reprezintă numărul ce se valideaza
**/
int valideaza(long s)
{
	int nr = s % 10007;
	if (nr < 0)
		nr += 10007;
	return nr;
}

/**
	Functie folosita pentru afisarea elementelor unei matrici.
	* Parametrul item reprezintă matricea ce se va afisa.
**/
void afiseaza(elem *item)
{
	for (int i = 0; i < item->m; i++) {
		for (int j = 0; j < item->n; j++)
			printf("%d ", item->a[i * item->n + j]);
		printf("\n");
	}
}

/**
	Functie folosita pentru citirea elementelor unei matrice și alocarea
	memoriei necesare pentru aceasta.
	* Parametrii m și n reprezintă numărul de linii și coloane ale matricei
	* Returneaza informațiile matricei citite sub forma unei structuri
	de tip elem
**/
elem *citire_matrice(int m, int n)
{
	elem *item = malloc(sizeof(elem));
	if (!item)
		return NULL;
	item->a = malloc(m * n * sizeof(int));
	if (!item->a) {
		free(item);
		return NULL;
	}
	item->m = m;
	item->n = n;
	long s = 0;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			item->a[i * n + j] = 0;
			scanf("%d", &item->a[i * n + j]);
			s += item->a[i * n + j];
		}
	}
	item->s = valideaza(s);
	return item;
}

/**
	Functie folosita pentru calcularea sumei elementelor unei matrice.
	* Parametru A reprezintă matricea data sub forma unei structuri
	de tip elem.
	* Returnează suma elementelor metricei date ca parametru
**/
int suma_elemente(elem *A)
{
	long s = 0;
	for (int i = 0; i < A->m; i++)
		for (int j = 0; j < A->n; j++)
			s += A->a[i * A->n + j];
	return valideaza(s);
}

/**
	Functie folosita pentru calculul înmulțiri a doua matrici.
	* Parametrii A și B de tip elem reprezintă matricile ce se vor înmulți
	* Returneaza matricea rezultata din înmulțirea celor doua matrici
**/
elem *inmultire_matrici(elem *A, elem *B)
{
	elem *rez = malloc(sizeof(elem));
	if (!rez)
		return NULL;
	rez->a = malloc(A->m * B->n * sizeof(int));
	if (!rez->a) {
		free(rez);
		return NULL;
	}
	for (int x = 0; x < A->m; x++)
		for (int i = 0; i < B->n; i++)
			rez->a[x * B->n + i] = 0;
	for (int x = 0; x < A->m; x++) {
		for (int i = 0; i < B->n; i++) {
			for (int j = 0; j < A->n; j++) {
				long nr = rez->a[x * B->n + i];
				nr += A->a[x * A->n + j] * B->a[j * B->n + i];
				nr = valideaza(nr);
				rez->a[x * B->n + i] = (int)nr;
			}
		}
	}
	rez->m = A->m;
	rez->n = B->n;
	rez->s = suma_elemente(rez);
	return rez;
}

/**
	Functie folosita pentru calculul transpusei unei matrice.
	* Parametrii A și B de tip elem reprezintă matricile ce se vor înmulți
	* Returneaza matricea rezultata din înmulțirea celor doua matrici
**/
elem *transpusa_matrice(elem *A)
{
	elem *rez1 = malloc(sizeof(elem));
	if (!rez1)
		return NULL;
	rez1->a = malloc(A->m * A->n * sizeof(int));
	if (!rez1->a) {
		free(rez1);
		return NULL;
	}
	for (int i = 0; i < A->m; i++) {
		for (int j = 0; j < A->n; j++) {
			rez1->a[j * A->m + i] = 0;
			rez1->a[j * A->m + i] = A->a[i * A->n + j];
		}
	}
	rez1->m = A->n;
	rez1->n = A->m;
	rez1->s = A->s;
	return rez1;
}

/**
	Functie folosita pentru ridicarea la puterea p a unei matrici.
	* Parametrul A de tip elem reprezintă matricea ce se va ridica la putere
	* Parametrul p de tip int reprezintă puterea la care se ridica matricea
	* Returneaza matricea rezultata din ridicarea la putere a matricei
**/
elem *ridicare_putere(elem *A, long p)
{
	long n = p - 1;
	elem *B = malloc(sizeof(elem));
	B->a = malloc(A->m * A->n * sizeof(int));
	B->m = A->m;
	B->n = A->n;
	B->s = A->s;
	for (int i = 0; i < A->m; i++)
		for (int j = 0; j < A->n; j++)
			B->a[i * A->n + j] = A->a[i * A->n + j];
	while (n > 0) {
		if (n & 1) {
			elem *temp = A;
			A = inmultire_matrici(A, B);
			free(temp->a);
			free(temp);
			n--;
		}
		if (n > 0) {
			elem *temp = B;
			B = inmultire_matrici(B, B);
			free(temp->a);
			free(temp);
			n = n >> 1;
		}
	}
	free(B->a);
	free(B);
	return A;
}

/**
	Functie folosita pentru alocarea de memorie pentru o matrice patratica
	de n x n elemente de tip int
	* Parametrul n de tip int reprezintă numărul de linii/coloane ale matricei
	* Returneaza matricea alocată sub forma unui vector de elemente de tip int
**/
int *initializare_matrice(int n)
{
	int *temp = malloc(n * n * sizeof(int));
	return temp;
}

/**
	Funcție folosita pentru calculul sumei elementelor a doua matrici
	patratice.
	* Parametrii M1 și M2 reprezintă cele doua matrici folosite în calcul
	* Parametrul n reprezintă numărul de linii și coloane ale matricelor
	* Returneaza matricea suma rezultata sub forma unui vector de
	elemente de tip int în care fiecare element este validat
**/
int *suma(int *M1, int *M2, int n)
{
	int *rez = initializare_matrice(n);
	if (!rez)
		return NULL;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			rez[i * n + j] = valideaza(M1[i * n + j] + M2[i * n + j]);
	return rez;
}

/**
	Funcție folosita pentru calculul diferentei elementelor a doua matrici
	patratice.
	* Parametrii M1 și M2 reprezintă cele doua matrici folosite în calcul
	* Parametrul n reprezintă numărul de linii și coloane ale matricelor
	* Returneaza matricea diferenta rezultata sub forma unui vector de
	elemente de tip int în care fiecare element este validat
**/
int *diferenta(int *M1, int *M2, int n)
{
	int *rez = initializare_matrice(n);
	if (!rez)
		return NULL;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			rez[i * n + j] = valideaza(M1[i * n + j] - M2[i * n + j]);
	return rez;
}

/**
	Funcție folosita pentru împărțirea matricilor A și B în submatrici
	necesare calculului inmultirii a doua matrici prin algoritmul lui Strassen
**/
void creare_parti_matrici(int *A11, int *A12, int *A21, int *A22,
						  int *B11, int *B12, int *B21, int *B22,
						  int *A, int *B, int n, int k)
{
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			A11[i * k + j] = A[i * n + j];
			A12[i * k + j] = A[i * n + (k + j)];
			A21[i * k + j] = A[(k + i) * n + j];
			A22[i * k + j] = A[(k + i) * n + (k + j)];
			B11[i * k + j] = B[i * n + j];
			B12[i * k + j] = B[i * n + (k + j)];
			B21[i * k + j] = B[(k + i) * n + j];
			B22[i * k + j] = B[(k + i) * n + (k + j)];
		}
	}
}

/**
	Funcție folosita pentru reconstructia matricei rezultat din blocurile
	matricei calculate prin algoritmul lui Strassen
**/
void reconstructie_matrice(int *rez, int *C11, int *C12,
						   int *C21, int *C22, int k, int n)
{
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			rez[i * n + j] = C11[i * k + j];
			rez[i * n + (j + k)] = C12[i * k + j];
			rez[(k + i) * n + j] = C21[i * k + j];
			rez[(k + i) * n + (k + j)] = C22[i * k + j];
		}
	}
}

/**
	Funcție folosita pentru calculul inmultirii a doua matrici patratice prin
	algoritmul Strassen.
	* Parametrii A și B reprezintă cele doua matrici folosite în calcul
	* Parametrul n reprezintă numărul de linii și coloane ale matricelor
	* Returneaza matricea rezultata sub forma unui vector de elemente
	de tip int în care fiecare element este validat
**/
int *inmultire_strassen(int *A, int *B, int n)
{
	int *rez = initializare_matrice(n);
	if (!rez)
		return NULL;
	if (n == 1) {
		rez[0] = A[0] * B[0];
		return rez;
	}
	int k = n / 2;
	int *A11 = initializare_matrice(k), *A12 = initializare_matrice(k);
	int *A21 = initializare_matrice(k), *A22 = initializare_matrice(k);
	int *B11 = initializare_matrice(k), *B12 = initializare_matrice(k);
	int *B21 = initializare_matrice(k), *B22 = initializare_matrice(k);
	creare_parti_matrici(A11, A12, A21, A22, B11, B12, B21, B22, A, B, n, k);
	// Calculez 7 matrici auxiliare prin aplicarea recursiva a metodei Strassen
	int *t = diferenta(B12, B22, k);
	int *P1 = inmultire_strassen(A11, t, k); // Se calculeaza P1=A11*(B12-B22)
	free(t);
	t = suma(A11, A12, k);
	int *P2 = inmultire_strassen(t, B22, k); // Se calculeaza P2=(A11+A12)*B22
	free(t);
	t = suma(A21, A22, k);
	int *P3 = inmultire_strassen(t, B11, k); // Se calculeaza P3=(A21+A22)*B11
	free(t);
	t = diferenta(B21, B11, k);
	int *P4 = inmultire_strassen(A22, t, k); // Se calculeaza P4=A22*(B21-B11)
	free(t);
	t = suma(A11, A22, k);
	int *t1 = suma(B11, B22, k);
	int *P5 = inmultire_strassen(t, t1, k); // P5=(A11+A22)*(B11+B22)
	free(t);
	free(t1);
	t = diferenta(A12, A22, k);
	t1 = suma(B21, B22, k);
	int *P6 = inmultire_strassen(t, t1, k); // P6=(A12-A22)*(B21+B22)
	free(t);
	free(t1);
	t = diferenta(A11, A21, k);
	t1 = suma(B11, B12, k);
	int *P7 = inmultire_strassen(t, t1, k); // P7=(A11-A21)*(B11+B12)
	// Eliberam memoria dupa calculul cele 7 matrici intermediare
	free(t);
	free(t1);
	free(A11);
	free(A12);
	free(A21);
	free(A22);
	free(B11);
	free(B12);
	free(B21);
	free(B22);
	// Calculam blocurile matricei rezultat C11, C12, C21, C22
	t = suma(P5, P4, k);
	t1 = suma(t, P6, k);
	int *C11 = diferenta(t1, P2, k); // Calculam blocul C11=((P5+P4)+P6)-P2;
	free(t);
	free(t1);
	int *C12 = suma(P1, P2, k);	// Calculam blocul C12=P1+P2;
	int *C21 = suma(P3, P4, k); // Calculam blocul C21=P3+P4;
	t = suma(P5, P1, k);
	t1 = diferenta(t, P3, k);
	int *C22 = diferenta(t1, P7, k); // Calculam blocul C22=((P5+P1)-P3)-P7;
	// Eliberam memoria dupa ce am terminat de calculat cele 4 blocuri
	free(t);
	free(t1);
	free(P1);
	free(P2);
	free(P3);
	free(P4);
	free(P5);
	free(P6);
	free(P7);
	reconstructie_matrice(rez, C11, C12, C21, C22, k, n);
	// Eliberam memoria dupa ce am obtinut matricea rezultat
	free(C11);
	free(C12);
	free(C21);
	free(C22);
	return rez;
}

/**
	Funcție folosita pentru încărcarea în memorie a unei matrice
	(comanda L).
	Dacă operația de citire matrice se face cu succes atunci vectorul v
	va conține nr_matrici + 1 elemente
	* Parametrul v reprezintă vectorul de matrici alocate
	* Parametrul nr_matrici reprezintă numărul total de matrici conținute în
	vectorul v
	* Returneaza noul număr de matrici continute de vectorul v
**/
int functie_L(elem **v, int nr_matrici)
{
	int n, m;
	scanf("%d %d", &m, &n);
	elem *o = citire_matrice(m, n);
	if (o) {
		v[nr_matrici] = o;
		return nr_matrici + 1;
	}
	return nr_matrici;
}

/**
	Funcție folosita pentru afisarea dimensiunilor unei matrice (comanda D).
	* Parametrul v reprezintă vectorul de matrici alocate
	* Parametrul nr_matrici reprezintă numărul total de matrici conținute în
	vectorul v
**/
void functie_D(elem **v, int nr_matrici)
{
	int index_dat;
	scanf("%d", &index_dat);
	if (index_dat >= 0 && index_dat < nr_matrici) {
		elem *e = v[index_dat];
		printf("%d %d\n", (*e).m, (*e).n);
	} else {
		printf("No matrix with the given index\n");
	}
}

/**
	Funcție folosita pentru afisearea elementelor unei matrice (comanda P).
	* Parametrul v reprezintă vectorul de matrici alocate
	* Parametrul nr_matrici reprezintă numărul total de matrici conținute în
	vectorul v
**/
void functie_P(elem **v, int nr_matrici)
{
	int index_dat;
	scanf("%d", &index_dat);
	if (index_dat >= 0 && index_dat < nr_matrici) {
		elem *e = v[index_dat];
		afiseaza(e);
	} else {
		printf("No matrix with the given index\n");
	}
}

/**
	Funcție folosita pentru redimensionarea unei matrice (comanda C).
	* Parametrul v reprezintă vectorul de matrici alocate
	* Parametrul nr_matrici reprezintă numărul total de matrici conținute în
	vectorul v
**/
void functie_C(elem **v, int nr_matrici)
{
	int index_dat, l = 0, k = 0;
	scanf("%d %d", &index_dat, &l); // l = indici linii
	int *linii = malloc(l * sizeof(int));
	if (linii) {
		for (int i = 0; i < l; i++)
			scanf("%d", &linii[i]);
	}
	scanf("%d", &k); // k = indici coloane
	int *coloane = malloc(k * sizeof(int));
	if (coloane) {
		for (int i = 0; i < k; i++)
			scanf("%d", &coloane[i]);
	}
	if (index_dat >= 0 && index_dat < nr_matrici) {
		elem *e = v[index_dat];
		int *b = malloc(l * k * sizeof(int));
		long s = 0;
		for (int i = 0; i < l; i++) {
			for (int j = 0; j < k; j++) {
				b[i * k + j] = e->a[(linii[i]) * e->n + (coloane[j])];
				s += b[i * k + j];
			}
		}
		v[index_dat] = malloc(sizeof(elem));
		v[index_dat]->a = b;
		v[index_dat]->m = l;
		v[index_dat]->n = k;
		v[index_dat]->s = valideaza(s);
		free(e->a);
		free(e);
	} else {
		printf("No matrix with the given index\n");
	}
	free(linii);
	free(coloane);
}

/**
	Funcție folosita pentru înmulțirea a doua matrici (comanda M).
	Dacă operația de inmultire se face cu succes atunci vectorul v va conține
	nr_matrici + 1 elemente si pe poziția nr_matrici se va adauga noua matrice.
	* Parametrul v reprezintă vectorul de matrici alocate
	* Parametrul nr_matrici reprezintă numărul total de matrici conținute în
	vectorul v
	* Returneaza noul număr de matrici continute de vectorul v
**/
int functie_M(elem **v, int nr_matrici)
{
	int index1, index2;
	scanf("%d %d", &index1, &index2);
	if (index1 >= 0 && index1 < nr_matrici &&
		index2 >= 0 && index2 < nr_matrici) {
		elem *e1 = v[index1]; // Retin in *e1 de tip elem matricea de la index1
		elem *e2 = v[index2]; // Retin in *e2 de tip elem matricea de la index2
		if (e1->n != e2->m) {
			printf("Cannot perform matrix multiplication\n");
		} else {
			elem *rez = inmultire_matrici(e1, e2);
			if (rez) {
				v[nr_matrici] = rez;
				return nr_matrici + 1;
			}
		}
	} else {
		printf("No matrix with the given index\n");
	}
	return nr_matrici;
}

/**
	Funcție folosita pentru realizarea transpusei unei matrice (comanda T).
	Dacă operația se face cu succes atunci noua matrice obținuta va înlocui
	matricea sursa în vectorul v.
	* Parametrul v reprezintă vectorul de matrici alocate
	* Parametrul nr_matrici reprezintă numărul total de matrici conținute în
	vectorul v
**/
void functie_T(elem **v, int nr_matrici)
{
	int index_dat;
	scanf("%d", &index_dat);
	if (index_dat >= 0 && index_dat < nr_matrici) {
		elem *e3 = v[index_dat];
		elem *rez1 = transpusa_matrice(e3);
		if (rez1) {
			v[index_dat] = rez1;
			free(e3->a);
			free(e3);
		}
	} else {
		printf("No matrix with the given index\n");
	}
}

/**
	Funcție folosita pentru realizarea ordonarii matricilor din vectorul v
	pe baza sumei elementelor acestora(comanda O).
	* Parametrul v reprezintă vectorul de matrici alocate
	* Parametrul nr_matrici reprezintă numărul total de matrici conținute în
	vectorul v
**/
void functie_O(elem **v, int nr_matrici)
{
	for (int i = 0; i < nr_matrici - 1; i++) {
		int index = i;
		int min = v[i]->s;
		for (int j = i + 1; j < nr_matrici; j++) {
			if (min > v[j]->s) {
				min = v[j]->s;
				index = j;
			}
		}
		elem *t = v[i];
		v[i] = v[index];
		v[index] = t;
	}
}

/**
	Funcție folosita pentru realizarea ridicării la putere a unei matrice
	în timp logaritmic (comanda R). Dacă operația se face cu succes
	atunci noua matrice obținuta va înlocui matricea sursa în vectorul v.
	* Parametrul v reprezintă vectorul de matrici alocate
	* Parametrul nr_matrici reprezintă numărul total de matrici conținute în
	vectorul v
**/
void functie_R(elem **v, int nr_matrici)
{
	int index;
	long putere;
	scanf("%d %ld", &index, &putere);
	if (index < 0 || index >= nr_matrici) {
		printf("No matrix with the given index\n");
	} else if (putere < 0) {
		printf("Power should be positive\n");
	} else {
		elem *A = v[index];
		if (A->n != A->m) {
			printf("Cannot perform matrix multiplication\n");
		} else {
			elem *rez = ridicare_putere(A, putere);
			v[index] = rez;
		}
	}
}

/**
	Funcție folosita pentru înmulțirea a doua matrici prin algoritmul
	lui Strassen (comanda S). Dacă operația de inmultire se face cu succes
	atunci vectorul v va conține nr_matrici + 1 elemente si pe poziția
	nr_matrici se va adauga noua matrice.
	* Parametrul v reprezintă vectorul de matrici alocate
	* Parametrul nr_matrici reprezintă numărul total de matrici conținute
	în vectorul v
	* Returneaza noul număr de matrici continute de vectorul v
**/
int functie_S(elem **v, int nr_matrici)
{
	int index1, index2;
	scanf("%d %d", &index1, &index2);
	if (index1 >= 0 && index1 < nr_matrici &&
		index2 >= 0 && index2 < nr_matrici) {
		elem *e1 = v[index1];
		elem *e2 = v[index2];
		if (e1->n != e2->m || e1->m != e1->n ||
			e2->m != e2->n || e1->n % 2 == 1) {
			printf("Cannot perform matrix multiplication\n");
		} else {
			// Calculam matricea p rezultata prin inmultirea matricelor dorite
			int *p = inmultire_strassen(e1->a, e2->a, e1->m);
			if (p) {
				// Construim elementul ce contine matricea produs, numarul de
				// linii, numarul de coloane si suma elementelor matricei
				elem *rez = malloc(sizeof(elem));
				rez->a = p;
				rez->m = e1->m;
				rez->n = e1->n;
				rez->s = suma_elemente(rez);
				v[nr_matrici] = rez;
				return nr_matrici + 1;
			}
		}
	} else {
		printf("No matrix with the given index\n");
	}
	return nr_matrici;
}

int main(void)
{
	char caracter;
	int n = 10, nr_matrici = 0;
	elem **v = malloc(n * sizeof(elem));
	while (1) {
		while (1) {
			scanf("%c", &caracter);
			if (isspace(caracter) == 0) // Elimin spatiile: space, enter, tab
				break;
		}
		if (caracter == 'L') {
			nr_matrici = functie_L(v, nr_matrici);
		} else if (caracter == 'D') {
			functie_D(v, nr_matrici);
		} else if (caracter == 'P') {
			functie_P(v, nr_matrici);
		} else if (caracter == 'C') {
			functie_C(v, nr_matrici);
		} else if (caracter == 'M') {
			nr_matrici = functie_M(v, nr_matrici);
		} else if (caracter == 'T') {
			functie_T(v, nr_matrici);
		} else if (caracter == 'O') {
			functie_O(v, nr_matrici);
		} else if (caracter == 'R') {
			functie_R(v, nr_matrici);
		} else if (caracter == 'F') {
			int index_dat;
			scanf("%d", &index_dat);
			if (index_dat >= 0 && index_dat < nr_matrici) {
				elem *e = v[index_dat];
				for (int i = index_dat; i < nr_matrici - 1; i++)
					v[i] = v[i + 1];
				free(e->a);
				free(e);
				nr_matrici--;
				// Redimensionam vectorul rezultat daca s-a eliberat jumatate
				// din memoria alocata vectorului
				if (nr_matrici + 1 < n / 2) {
					n = n / 2;
					v = realloc(v, n * sizeof(elem));
				}
			} else {
				printf("No matrix with the given index\n");
			}
		} else if (caracter == 'Q') {
			for (int i = 0; i < nr_matrici; i++) {
				if (v[i]) {
					if (v[i]->a)
						free(v[i]->a);
					free(v[i]);
				}
			}
			free(v);
			nr_matrici = 0;
			break;
		} else if (caracter == 'S') {
			nr_matrici = functie_S(v, nr_matrici);
		} else {
			printf("Unrecognized command\n");
		}
		// Realocam memorie pentru vectorul de matrici, daca am ajuns la final
		if (nr_matrici + 1 >= n) {
			n += 10;
			v = realloc(v, n * sizeof(elem));
		}
	}
	return 0;
}
