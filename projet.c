#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "projet.h"

typedef struct aux
{
    char ide[7];
    int car;
    char heu[4];
    int tt2;
    int con;
    char nom[25];
    int tt;
    char acr[3];
}Aux;

void creer_liste(struct liste* ll)
{
    ll->premier = NULL;
    ll->dernier = NULL;
}

unsigned liste_vide(struct liste ll)
{
    return (ll.premier == NULL);
}

unsigned taille_liste_av(struct liste  ll)
{
    noeud* p = ll.premier;
    unsigned nb = 0;
    while (p)
    {
        nb++;
        p = p->suivant;
    }
    return nb;

}
avion * recherche_av(struct liste ll, char id[])
{
    //supposant la liste n'est pas vide
    noeud* p;
    p = ll.premier;
    while ((p) && (strcmp(p->info.identifiant, id) != 0))
    {
        p = p->suivant;
    }
    if(!p)
        return NULL;
    else
        return &(p->info);
}


unsigned recherche_comp(struct liste ll, char nom_comp[])
{
    //supposant la liste n'est pas vide
    noeud* p;
    p = ll.premier;
    while ((p) && (strcmp(p->info.compagnie->nom,nom_comp) != 0))
    {
        p = p->suivant;
    }
    if (!p)
        return 0;
    else
        return 1;

}

unsigned recherche_heure_decollage(struct liste ll, char heure_decollage[])
{
    //supposant la liste n'est pas vide
    noeud* p;
    p = ll.premier;
    while ((p) && (strcmp(p->info.heure_decollage,heure_decollage) != 0))
    {
        p = p->suivant;
    }
    if (!p)
        return 0;
    else
        return 1;

}

void insere_tete_av(struct liste* ll, avion av)
{
    noeud* q;
    q = (noeud*)malloc(sizeof(noeud));
    q->info = av;
    q->suivant = ll->premier;
    if (liste_vide(*ll))
        ll->dernier = q;
    ll->premier = q;

}

void insere_queue_av (struct liste * ll, avion av)
{
    noeud* q;
    q = (noeud*)malloc(sizeof(noeud));
    q->info = av;
    q->suivant = NULL;
    if (liste_vide(*ll))
    {
        ll->premier = q;
        ll->dernier = q;
    }
    else
    {
        ll->dernier->suivant = q;
        ll->dernier = q;
    }

}

void insere_pos_av(struct liste* ll, avion av, unsigned pos)
{
    //supposons la postion de l'insertion est valide
    noeud* q, *p=ll->premier;
    q = (noeud*)malloc(sizeof(noeud));
    q->info = av;
    unsigned i=1;
    while ((p) && (i + 1 < pos))
    {
        p = p->suivant;
        i++;
    }
    if (i + 1 == pos)
    {
        q->suivant = p->suivant;
        p->suivant = q;
    }
}

void supprimer_tete_av(struct liste* ll)
{
    //supposons la liste n'est pas vide
    noeud* q;
    q = ll->premier;
    ll->premier = ll->premier->suivant;
    free(q);
}

void supprimer_queue_av(struct liste* ll)
{
    //supposons la liste n'est pas vide
    noeud *p, *prec;
    p = ll->premier;
    if (!p->suivant)
    {
        ll->premier = NULL;
        ll->dernier = NULL;
        free(p);
    }
    while (p->suivant)
    {
        prec = p;
        p = p->suivant;
    }
    prec->suivant = NULL;
    ll->dernier = prec;
    free(p);
}

void supprimer_pos_av(struct liste* ll, unsigned pos)
{
    //supposons la postion de la suppression est valide
    noeud* q, * p = ll->premier;
    unsigned i = 1;
    while ((p) && (i + 1 < pos))
    {
        p = p->suivant;
        i++;
    }
    if (i + 1 == pos)
    {
        q = p->suivant;
        p->suivant = p->suivant->suivant;
        free(q);
    }

}

void supprimer_av_donne(struct liste* ll, char id[])
{
    //supposons la postion de l'insertion est valide
    noeud* p = ll->premier, * prec = NULL;
    while ((p) && (strcmp(p->info.identifiant, id) != 0))
    {
        prec = p;
        p = p->suivant;
    }
    if ((p)&&(strcmp(p->info.identifiant, id) == 0))
    {
        if (prec == NULL)
            supprimer_tete_av(ll);
        else if (p->suivant == NULL)
            supprimer_queue_av(ll);
        else
        {
            prec->suivant = prec->suivant->suivant;
            free(p);
        }

    }

}

void supprimer_av_compagnie_donne(struct liste* ll, char nom_comp[])
{
    noeud* p = ll->premier, * prec = NULL;
    while ((taille_liste_av(*ll) != 0)&&(recherche_comp(*ll,nom_comp)!=0))
    {
        while ((p) && (strcmp(p->info.compagnie->nom,nom_comp) != 0))
        {
            prec = p;
            p = p->suivant;
        }
        if ((p) && (strcmp(p->info.compagnie->nom, nom_comp) == 0))
        {
            if (prec == NULL)
                supprimer_tete_av(ll);
            else if (p->suivant == NULL)
                supprimer_queue_av(ll);
            else
            {
                prec->suivant = prec->suivant->suivant;
                free(p);
            }
        }
    }
}

void parcours(struct liste ll, void (*oper)(noeud*))
{
    noeud* p;
    p = ll.premier;
    while (p)
    {
        (*oper)(p);
        p = p->suivant;
    }
}

void parcours_2(struct liste *ll, void (*oper)(noeud*,char []),char ch[])
{
    noeud* p;
    p = ll->premier;
    while (p)
    {
        (*oper)(p,ch);
        p = p->suivant;
    }
}

void tri_1(struct liste * ll )
{
    struct liste ll_aux;
    noeud * p;
    creer_liste(&ll_aux);
    p=ll->premier;
    while(p)
    {
        insere_tri(&ll_aux,p->info);
        p=p->suivant;
    }
    ll->premier=ll_aux.premier;
    ll->dernier=ll_aux.dernier;
}

void insere_tri(struct liste * ll, avion av)
{
    noeud * p1, * prec,*q;
    p1 = ll->premier;
    prec = NULL;
    while (p1 && p1->info.consommation > av.consommation)
    {
        prec = p1;
        p1 = p1->suivant;
    }
    q = (noeud *)malloc(sizeof(noeud));
    q->info = av;
    if(prec && !p1)
    {
        q->suivant =NULL;
        prec->suivant=q;
        ll->dernier=q;
    }
    else if (prec)
    {
        q->suivant= prec->suivant;
        prec->suivant = q;
    }
    else
    {
        q->suivant = ll->premier;
        ll->premier = q ;
    }
}
void stringcpy(char ch1[],char ch2[])
{

    unsigned i ;
    for(i=0;i<strlen(ch2);i++)
    {
        ch1[i]=ch2[i];
    }
    ch1[i]='\0';
}
void CHARGEMENT (struct liste * ll)
{
    FILE *f;
    avion av ;
    int i=0 ;
    Aux aux_av;
    Compagnie *comp;
    f=fopen("Repertoire_des_avions.dat","rb");
    while(fread(&aux_av,sizeof(aux_av),1,f))
    {
        strcpy(av.identifiant,aux_av.ide);
        av.carburant=aux_av.car;
        av.consommation=aux_av.con;
        strcpy(av.heure_decollage,aux_av.heu);
        comp=(Compagnie *)malloc(sizeof(Compagnie));
        strcpy(comp->acronyme,aux_av.acr);
        strcpy(comp->nom,aux_av.nom);
        av.compagnie=comp;
        insere_queue_av(ll,av);
        i++;
    }
    fclose(f);
    if(i==0)
        printf("\nLe fichier est vide  !!! \n\n");
    else
        printf("\nLe charger du contenu de la liste a partir du fichier est effectue avec succes !!! \n\n");
    /*f=fopen("Repertoire_des_avions.dat","wb");
    fclose(f);*/
}


void ENREGISTREMENT(struct liste * ll)
{
    FILE * f;
    struct noeud * p ;
    Aux aux_av;
    f=fopen("Repertoire_des_avions.dat","wb");
    p=ll->premier;
    while(p)
    {
        strcpy( aux_av.ide ,(p->info).identifiant);
        aux_av.car = p->info.carburant;
        aux_av.con = p->info.consommation;
        strcpy(aux_av.heu , p->info.heure_decollage);
        strcpy(aux_av.nom , p->info.compagnie->nom);
        strcpy(aux_av.acr , p->info.compagnie->acronyme);
        fwrite(&aux_av,sizeof(aux_av),1,f);
        supprimer_tete_av(ll);
        p=p->suivant;
    }
    fclose(f);
}




