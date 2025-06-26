typedef struct compagnie
{
    char nom[25];
    char acronyme[3];
} Compagnie;

typedef struct avion
{
    char identifiant[7];
    int carburant;
    int consommation;
    char heure_decollage[4];
    int tt;
    Compagnie* compagnie;
} avion;

typedef struct noeud
{
    avion info;
    struct noeud* suivant;
} noeud;

struct liste
{
    noeud* premier;
    noeud* dernier;
};


void creer_liste(struct liste*);
unsigned liste_vide(struct liste);
unsigned taille_liste_av(struct liste);
avion * recherche_av(struct liste, char []);
unsigned recherche_comp(struct liste, char[]);
unsigned recherche_heure_decollage(struct liste, char[]);
void insere_tete_av(struct liste*, avion);
void insere_queue_av(struct liste*, avion);
void insere_pos_av(struct liste*, avion, unsigned);
void supprimer_tete_av(struct liste*);
void supprimer_queue_av(struct liste*);
void supprimer_pos_av(struct liste*,unsigned);
void supprimer_av_donne(struct liste*, char []);
void supprimer_av_compagnie_donne(struct liste*, char []);
void parcours(struct liste, void (*oper)(noeud*));
void parcours_2(struct liste *, void (*oper)(noeud*,char []),char []);
void tri_1(struct liste *);
void ENREGISTREMENT(struct liste *);
void CHARGEMENT (struct liste *);


