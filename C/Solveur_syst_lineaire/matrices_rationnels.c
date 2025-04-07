#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>

//////////////////////////////////////////////////
/* STRUCTURES */
//////////////////////////////////////////////////

typedef struct rationnel {
    int n;
    int d;
} rat;

typedef struct matrice {
	rat*** coef;
	int l;
	int c;
} mat;

//////////////////////////////////////////////////
/* PROTOTYPES */
//////////////////////////////////////////////////

// Renvoie le maximum entre a et b.
int max(int a, int b);
// Renvoie le minimum entre a et b.
int min(int a, int b);
// Renvoie le pgcd de a et b.
int pgcd(int a, int b);
// Affiche un booleen en chaine de caracteres
void affBool(bool b);

// Renvoie le rationnel a/b
rat* creerRat(int a, int b);
// Genere un rationnel tel que : 0 < n <= 10, 0 <= d <= 10
rat* genRatAlea();
// Modifie (par adresse) le rationnel ainsi :
// - (0, 1) si n est nul.
// - Sinon (u, v) avec v > 0 et u et v premiers entre eux.
void irreductible(rat* r);
// Renvoie true si les rationnels sont egaux, false sinon.
bool egauxRat(rat* r1, rat* r2);
// Affiche un rationnel sous la forme "(n/d)" si d != 1, et "n" sinon.
void affRat(rat* r);
// Affiche l'operation specifiee et son resultat entre deux rationnels
// '+' pour addition
// '*' pour produit
// '/' pour quotient
void affOpeRat(rat* r1, rat* r2, char ope);
// Affiche Le Produit d'un Rationnel Par un Entier
void affProdRatParEntier(rat* r, int a);

// Effectue la somme de deux rationnels
rat* sommeRat(rat* r1, rat* r2);
// Effectue la soustraction de r1 par r2
rat* soustractionRat(rat* r1, rat* r2);
// Effectue le produit de deux rationnels
rat* produitRat(rat* r1, rat* r2);
// Effectue le quotient de r1 par r2
rat* quotientRat(rat* r1, rat* r2);
// Renvoie le produit d'un rationnel et d'un entier
rat* produitRatParEntier(rat* r, int a);
// Unleashes the rat power
void demoRationnels();


// Cree et renvoie une matrice nulle de l lignes et c colonnes
mat* creerMat(int l, int c);
// Renvoie la matrice identite de taille souhaitee
mat* creerMatId(int taille);
// Affiche la matrice m
void affMat(mat* m);
// Attribue les valeurs d'un tableau a deux dimensions a une matrice
// Le tableau et la matrice doivent etre de memes dimensions
void ecrireTabMat(rat*** t, mat* m);
// Remplit la matrice avec de coefficients rationnels aleatoires
void remplitMatAlea(mat* m);
// Renvoie true si les deux matrices sont egales, false sinon
bool egalesMat(mat* m1, mat* m2);
// Renvoie l'addition de deux matrices

mat* sommeMat(mat* m1, mat* m2);
// Renvoie le produit de deux matrices
// (le nombre de colonnes de la premiere matrice doit etre egal au nombre de lignes de la seconde)
mat* produitMat(mat* m1, mat* m2);
// Renvoie l'inverse d'une matrice carree si celle-ci est inversible, sinon A DEFINIR.
mat* inverseMat(mat* m, bool* succes);
// Unleashes the mat power
void demoMatrices();


//////////////////////////////////////////////////
/* FONCTIONS RATIONNELS */
//////////////////////////////////////////////////
int max(int a, int b) {
    if (a > b) return a;
    return b;
}
int min(int a, int b) {
    if (a < b) return a;
    return b;
}
int pgcd(int a, int b) {
    a = abs(a);
    b = abs(b);
    int m = max(a, b);
    int n = min(a, b);
    if (n == 0) return max(a, b); // cas de base: l'algorithme d'Euclide
    while (n != 0) {
        int r = m % n;
        m = n;
        n = r;
    }
    return m;
}
void affBool(bool b) {
    if (b) printf("true");
    else printf("false");
}

rat* creerRat(int a, int b) {
    rat* r = malloc(sizeof(rat));
    r->n = a;
    r->d = b;
    return r;
}
rat* genRatAlea() {
    return creerRat(rand() % 11, rand() % 3 + 1);
}
void irreductible(rat* r) {
    if (r->n == 0) {
        r->d = 1;
    } else {
        // Reduction de la fraction
        int p = pgcd(r->n, r->d);
        r->n /= p;
        r->d /= p;
        // S'assurer que le denominateur est positif
        if (r->d < 0) {
            r->n = -r->n;
            r->d = -r->d;
        }
    }
}
bool egauxRat(rat* r1, rat* r2) {
    return r1->n * r2->d == r1->d * r2->n;
}
void affRat(rat* r) {
    if (r->d == 1 || r->d == -1) {
        printf("%d", r->n * r->d);
    } else if (r->n == 0 && r->d != 0) {
        printf("0");
    } else {
        printf("%d/%d", r->n, r->d);
    }
}

void affOpeRat(rat* r1, rat* r2, char ope) {
    affRat(r1);
    printf(" %c ", ope);
    affRat(r2);
    printf(" = ");
    if (ope == '+') affRat(sommeRat(r1, r2));
    if (ope == '-') affRat(soustractionRat(r1, r2));
    else if (ope == '*') affRat(produitRat(r1, r2));
    else if (ope == '/') affRat(quotientRat(r1, r2));
    printf("\n");
}
void affProdRatParEntier(rat* r, int a) {
    affRat(r);
    printf(" * %d = ", a);
    affRat(produitRatParEntier(r, a));
    printf("\n");
}
rat* sommeRat(rat* r1, rat* r2) {
    int n = (r1->n * r2->d) + (r2->n * r1->d);
    int d = r1->d * r2->d;
    rat* q = creerRat(n, d);
    irreductible(q);
    return q;
}
rat* soustractionRat(rat* r1, rat* r2) {
    int n = (r1->n * r2->d) - (r2->n * r1->d);
    int d = r1->d * r2->d;
    rat* q = creerRat(n, d);
    irreductible(q);
    return q;
}
rat* produitRat(rat* r1, rat* r2) {
    int n = r1->n * r2->n;
    int d = r1->d * r2->d;
    rat* p = creerRat(n, d);
    irreductible(p);
    return p;
}
rat* quotientRat(rat* r1, rat* r2) {
    int n = r1->n * r2->d;
    int d = r1->d * r2->n;
    rat* q = creerRat(n, d);
    irreductible(q);
    return q;
}
rat* produitRatParEntier(rat* r, int a) {
    rat* p = creerRat(r->n * a, r->d);
    irreductible(p);
    return p;
}
void demoRationnels() {
    int nb_rats = 9;
    rat** rats = malloc(sizeof(rat*) * nb_rats);
    printf("Quelques rationnels :\t");
    for (int i = 0; i < nb_rats; i++) {
        rats[i] = genRatAlea();
        affRat(rats[i]);
        printf("\t");
    }
    printf("\n\n");

    affOpeRat(rats[0], rats[1], '+');
    affOpeRat(rats[2], rats[3], '-');
    affOpeRat(rats[4], rats[5], '*');
    affOpeRat(rats[6], rats[7], '/');
    affProdRatParEntier(rats[8], rand() % 10);

    for (int i = 0; i < nb_rats; i++) free(rats[i]);
}

//////////////////////////////////////////////////
/* FONCTIONS MATRICES */
//////////////////////////////////////////////////
mat* creerMat(int l, int c) {
	mat* m = (mat*) malloc(sizeof(mat));
	m->l = l;
	m->c = c;
	m->coef = (rat***) malloc(sizeof(rat**) * l);
	for (int i = 0; i < l; i++) {
		m->coef[i] = (rat**) malloc(sizeof(rat*) * c);
		for (int j = 0; j < c; j++) {
			m->coef[i][j] = creerRat(0, 1);
		}
	}
	return m;
}
mat* creerMatId(int taille) {
	mat* m = (mat*) malloc(sizeof(mat));
	m->l = taille;
	m->c = taille;
	m->coef = (rat***) malloc(sizeof(rat**) * taille);
	for (int i = 0; i < taille; i++) {
		m->coef[i] = (rat**) malloc(sizeof(rat*) * taille);
		for (int j = 0; j < taille; j++) {
		    if (i == j) {
		        m->coef[i][j] = creerRat(1, 1);
		    }
		    else {
		        m->coef[i][j] = creerRat(0, 1);
		    }
		}
	}
	return m;
}
void affMat(mat* m) {
	for (int i = 0; i < m->l; i++) {
		printf("[");
		for (int j = 0; j < m->c; j++){
			printf("\t");
            affRat(m->coef[i][j]);
		}
		printf("\t]\n");
	}
	printf("\n");
}
void ecrireTabMat(rat*** t, mat* m) {
	// Fonction a developper.
}
void remplitMatAlea(mat* m) {
	for (int i = 0; i < m->l; i++) {
		for (int j = 0; j < m->c; j++) {
			m->coef[i][j] = genRatAlea();
		}
	}
}
bool egalesMat(mat* m1, mat* m2) {
    if (m1->l != m2->l || m1->c != m2->c) {
        return false;
    }
    for (int i = 0; i < m1->l; i++) {
        for (int j = 0; j < m1->c; j++) {
            if (!egauxRat(m1->coef[i][j], m2->coef[i][j])) {
                return false;
            }
        }
    }
    return true;
}

mat* sommeMat(mat* m1, mat* m2) {
	assert(m1->l == m2->l || m1->c == m2->c);
	mat* s = creerMat(m1->l, m1->c);
	
	for (int i = 0; i < s->l; i++) {
		for (int j = 0; j < s->c; j++){
			s->coef[i][j] = sommeRat(m1->coef[i][j], m2->coef[i][j]);
		}
	}
	
	return s;
}
mat* produitMat(mat* m1, mat* m2) {
	assert(m1->c == m2->l);
	mat* p = creerMat(m1->l, m2->c);
	for(int i = 0; i < m1->l; i++) {
		for(int j = 0; j < m2->c; j++){
			for(int k = 0; k < m1->c; k++) {
			    p->coef[i][j] = sommeRat(p->coef[i][j], produitRat(m1->coef[i][k], m2->coef[k][j]));
			}
		}
	}
	
	return p;
}
mat* inverseMat(mat* m, bool* succes) {
    assert(m->l == m->c);
    *succes = true;  // Supposons que l'inversion reussira
    
    mat* inv = creerMat(m->l, m->c);
    mat* augm = creerMat(m->l, m->c * 2);

    // Creation de la matrice augmentee [A | I]
    for (int i = 0; i < m->l; i++) {
        for (int j = 0; j < m->c; j++) {
            augm->coef[i][j] = m->coef[i][j];
            augm->coef[i][j + m->c] = (i == j) ? creerRat(1, 1) : creerRat(0, 1);
        }
    }

    // printf("Matrice augmentee :\n");
    // affMat(augm);
    
    // Appliquer Gauss-Jordan
    for (int colPivot = 0; colPivot < m->c; colPivot++) {
        // Pivotage partiel : Trouver le plus grand pivot
        int lPivot = colPivot;
        for (int i = colPivot + 1; i < m->l; i++) {
            if (abs(augm->coef[i][colPivot]->n) > abs(augm->coef[lPivot][colPivot]->n)) {
                lPivot = i;
            }
        }
        
        // Si le pivot est nul, la matrice n'est pas inversible
        if (augm->coef[lPivot][colPivot]->n == 0) {
            *succes = false;
            // printf("Matrice non inversible.\n");
            return NULL;
        }
        
        // echange des lignes si necessaire
        if (lPivot != colPivot) {
            rat** temp = augm->coef[colPivot];
            augm->coef[colPivot] = augm->coef[lPivot];
            augm->coef[lPivot] = temp;
        }

        // Normalisation du pivot (rendre le pivot egal a 1)
        rat* pivot = augm->coef[colPivot][colPivot];
        for (int j = 0; j < augm->c; j++) {
            augm->coef[colPivot][j] = quotientRat(augm->coef[colPivot][j], pivot);
        }

        // elimination des autres lignes
        for (int i = 0; i < m->l; i++) {
            if (i != colPivot) {
                rat* facteur = augm->coef[i][colPivot];
                for (int j = 0; j < augm->c; j++) {
                    augm->coef[i][j] = soustractionRat(augm->coef[i][j], produitRat(facteur, augm->coef[colPivot][j]));
                }
            }
        }
        // affMat(augm);
    }

    // Extraction de l'inverse (partie droite de la matrice augmentee)
    for (int i = 0; i < m->l; i++) {
        for (int j = 0; j < m->c; j++) {
            inv->coef[i][j] = augm->coef[i][j + m->c];
        }
    }

    if (egalesMat(produitMat(m, inv), creerMatId(m->l))) {
        *succes = true;
        return inv;
    } else {
        *succes = false;
        return NULL;
    }

}
mat* produitRatMat(rat* r, mat* m) {
    mat* p = creerMat(m->l, m->c);
    for (int i = 0; i < p->l; i++) {
        for (int j = 0; j < p->c; j++) {
            // affRat(m->coef[i][j]);
            p->coef[i][j] = produitRat(m->coef[i][j], r);
        }
    }
    return p;
}
void demoMatrices() {
    int nb_mats = 3;
	mat** mats = (mat**) malloc(sizeof(mat*) * nb_mats);
	for (int i = 0; i < 2; i++) {
		mats[i] = creerMat(2, 3);
		remplitMatAlea(mats[i]);
		// affMat(mats[i]);
	}
	mats[2] = creerMat(mats[1]->c, 3);
	remplitMatAlea(mats[2]);
	// affMat(mats[2]);

    // Somme de matrices
    affMat(mats[0]);
    printf("+\n\n");
    affMat(mats[1]);
    printf("=\n\n");
    mat* s = sommeMat(mats[0], mats[1]);
    affMat(s);
    printf("--------------------------------\n\n");

    // Produit de matrices
    affMat(s);
    printf("*\n\n");
    affMat(mats[2]);
    printf("=\n\n");
    affMat(sommeMat(s, mats[2]));

    // Produit d'une matrice par un rationnel
    mat* avantProdRat = creerMat(4, 4);
    remplitMatAlea(avantProdRat);
    affMat(avantProdRat); printf(" * \n");
    rat* theRat = genRatAlea();
    affRat(theRat);
    printf("\n = \n\n");
    mat* apresProdRat = produitRatMat(theRat, avantProdRat);
    affMat(apresProdRat);
}
void demoInversionMatrice() {
    // Test d'inversion de matrice
    mat* matriceTest = creerMat(4, 4);
    remplitMatAlea(matriceTest);
    // Coefficients choisis pour la matrice de test
    // matriceTest->coef[0][0] = creerRat(1, 1);
    // matriceTest->coef[0][1] = creerRat(0, 1);
    // matriceTest->coef[0][2] = creerRat(0, 1);
    // matriceTest->coef[0][3] = creerRat(0, 1);
    // matriceTest->coef[1][0] = creerRat(0, 1);
    // matriceTest->coef[1][1] = creerRat(1, 1);
    // matriceTest->coef[1][2] = creerRat(0, 1);
    // matriceTest->coef[1][3] = creerRat(0, 1);
    // matriceTest->coef[2][0] = creerRat(0, 1);
    // matriceTest->coef[2][1] = creerRat(0, 1);
    // matriceTest->coef[2][2] = creerRat(1, 1);
    // matriceTest->coef[2][3] = creerRat(0, 1);
    // matriceTest->coef[3][0] = creerRat(0, 1);
    // matriceTest->coef[3][1] = creerRat(0, 1);
    // matriceTest->coef[3][2] = creerRat(0, 1);
    // matriceTest->coef[3][3] = creerRat(1, 1);
    printf("Matrice de test :\n");
    affMat(matriceTest);

	printf("Inversion de la matrice -> ");
	bool* succesInv = (bool*) malloc(sizeof(bool));
	*succesInv = false;
	mat* inverseTest = inverseMat(matriceTest, succesInv);
    if (*succesInv && inverseTest != NULL) {
        printf("matrice inversee :\n");
        affMat(inverseTest);
        printf("\nProduit des deux matrices :\n");
        affMat(produitMat(matriceTest, inverseTest));
    } else {
        printf("La matrice n'est pas inversible.\n");
    }

    // Fin du test d'inversion
}

//////////////////////////////////////////////////
/* PROGRAMME PRINCIPAL */
//////////////////////////////////////////////////
int main(int argc, char* argv[]) {
	srand(time(NULL));
    // demoRationnels();
    // printf("\n--------------------------------\n\n");
    // demoMatrices();
    // printf("\n--------------------------------\n\n");
    // demoInversionMatrice();

    printf("\n");
	return 0;
}
