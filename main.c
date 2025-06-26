#include <stdio.h>
#include "projet.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>



//controle de saisie :

unsigned verif_heure_decollage(char ch[])
{
    unsigned i = 0;
    unsigned test=0;



    if(ch[1]=='h')
    {
        while((i<strlen(ch)) && (isdigit(ch[i])))
        {
            i++;
            if(ch[i]=='h')
                i++;
        }

        if(((i==strlen(ch))&&(ch[2]<='5'))&&(ch[2]>='0'))
            test=1;
    }
    return test;
}


unsigned saisie_position(struct liste ll)
{
    unsigned position ;
    do
    {
        printf("\nSaisir la position : ");
        scanf("%u",&position);
    }
    while((position<1)||(position>(taille_liste_av(ll)+1)));
    return position;
}

unsigned verif_id(char ch[],char ch2[])
{
    unsigned i = 0;
    while((i<strlen(ch2))&&(ch[i]==ch2[i]))
        i++;

    if(i==strlen(ch2))
    {
        while((i<strlen(ch))&&(isdigit(ch[i])))
            i++;
        return i==strlen(ch);
    }
    else
        return 0 ;
}

unsigned est_numerique(char ch[])
{
    unsigned i = 0;
    while ((i<strlen(ch))&&(isdigit(ch[i])))
        i++;
    return i==strlen(ch);
}

unsigned est_alphabetique(char ch[])
{
    unsigned i = 0;
    while ((i<strlen(ch))&&(isalpha(ch[i])))
        i++;
    return i==strlen(ch);
}

unsigned est_majuscule(char ch[])
{
    unsigned i = 0;
    while (((i<strlen(ch))&&(isalpha(ch[i])))&&(isupper(ch[i])))
        i++;
    return i==strlen(ch);
}
unsigned verif_format_id (char ch [])
{
    unsigned i=0;
    unsigned test = 1 ;
    while((i<strlen(ch))&&(test==1))
    {
        if(i<3)
        {
            if((!isalpha(ch[i])) || (!isupper(ch[i])))
                test=0;
        }
        else
        {
            if(!isdigit(ch[i]))
                test=0;
        }
        i++;
    }
    return test;
}

//modification :

void mod_par_compagnie_donne(struct noeud * p,char nom_comp[])
{
    char c;
    //unsigned i;
    if(strcmp(p->info.compagnie->nom,nom_comp)==0)
    {
        do
        {
            printf("Saisir le nouveau niveau de carburant : ");
            scanf("%d",&p->info.carburant);
        }
        while(p->info.carburant<0);
        do
        {
            printf("Saisir la nouvelle valeur de la consommation de carburant par minute : ");
            scanf("%d",&p->info.consommation);
        }
        while(p->info.consommation<0);
        scanf("%c",&c);

        do
        {
            printf("Saisir le nouveau heure de d'collage prevue : ");
            /*for(i=0; i<4; i++)
                scanf("%c",&(av.heure_decollage[i]));
            av.heure_decollage[i]='\0';*/
            gets(p->info.heure_decollage);
        }
        while((strlen(p->info.heure_decollage)!=4)||(!verif_heure_decollage(p->info.heure_decollage)));
    }
}

void mod_par_id(avion * av)
{
    char c ;
    //unsigned i;
    do
    {
        printf("Saisir le nouveau niveau de carburant : ");
        scanf("%d",&(*av).carburant);
    }
    while((*av).carburant<0);
    do
    {
        printf("Saisir la nouvelle valeur de la consommation de carburant par minute : ");
        scanf("%d",&(*av).consommation);
    }
    while((*av).consommation<0);


    scanf("%c",&c);

    do
    {
        printf("Saisir le nouveau heure de d'collage prevue : ");
        /*for(i=0; i<4; i++)
            scanf("%c",&(av.heure_decollage[i]));
        av.heure_decollage[i]='\0';*/
        gets((*av).heure_decollage);
    }
    while((strlen((*av).heure_decollage)!=4)||(!verif_heure_decollage((*av).heure_decollage)));

}

//saisie de l'avion :

avion saisie_avion(struct liste ll)
{
    Compagnie * comp;
    avion av ;
    char ch1[10], ch2[10] ;
    char c;
    //unsigned i;
    printf("\n\t\tLes informations liees a la compagnie : \n\n");
    scanf("%c",&c);
    do
    {
        printf("Saisir le nom de la compagnie : ");
        gets(ch1);
    }
    while(!est_alphabetique(ch1));
    do
    {
        printf("Saisir l'acronyme de la compagnie : ");
        gets(ch2);
    }
    while((strlen(ch2)!=3)||(!est_majuscule(ch2)));
    comp=(Compagnie * )malloc(sizeof(Compagnie));
    strcpy(comp->nom,ch1);
    strcpy(comp->acronyme,ch2);
    av.compagnie=comp;
    printf("\n\t\tLes informations liees a l'avion : \n\n");
    do
    {
        printf("Saisir l'identifiant de l'avion : ");
        gets(av.identifiant);
    }
    while(((strlen(av.identifiant)!=6)||(!verif_id(av.identifiant,av.compagnie->acronyme)))||(recherche_av(ll,av.identifiant)!=NULL));
    do
    {
        printf("Saisir son niveau de carburant : ");
        scanf("%d",&av.carburant);
    }
    while(av.carburant<0);
    do
    {
        printf("Saisir sa consommation de carburant par minute : ");
        scanf("%d",&av.consommation);
    }
    while(av.consommation<0);
    scanf("%c",&c);

    do
    {
        printf("Saisir son heure de d'collage prevue : ");
        /*for(i=0; i<4; i++)
            scanf("%c",&(av.heure_decollage[i]));
        av.heure_decollage[i]='\0';*/
        gets(av.heure_decollage);
    }
    while((strlen(av.heure_decollage)!=4)||(!verif_heure_decollage(av.heure_decollage)));
    return av;

}

//affichage

void affichage_av_compagnie_donne(noeud * p, char nom_comp[] )
{
    if(strcmp(p->info.compagnie->nom,nom_comp)==0)
    {
        printf("\nL'identifiant de l'avion : %s\n",(p->info).identifiant);
        printf("Son niveau de carburant : %d\n",(p->info).carburant);
        printf("Sa consommation de carburant par minute : %d\n",(p->info).consommation);
        printf("Son heure de decollage prevue : %s\n",(p->info).heure_decollage);
        printf("Sa compagnie de rattachement : \n");
        printf("Le nom de la compagnie : %s\n",((p->info).compagnie)->nom);
        printf("L'acronyme de la compagnie : %s\n",((p->info).compagnie)->acronyme);
        printf("---------------------------------------------------------------------\n");
    }
}

void affichage_av_heure_decollage(noeud * p, char heure_decollage[] )
{
    if(strcmp(p->info.heure_decollage,heure_decollage)==0)
    {
        printf("\nL'identifiant de l'avion : %s\n",(p->info).identifiant);
        printf("Son niveau de carburant : %d\n",(p->info).carburant);
        printf("Sa consommation de carburant par minute : %d\n",(p->info).consommation);
        printf("Son heure de decollage prevue : %s\n",(p->info).heure_decollage);
        printf("Sa compagnie de rattachement : \n");
        printf("Le nom de la compagnie : %s\n",((p->info).compagnie)->nom);
        printf("L'acronyme de la compagnie : %s\n",((p->info).compagnie)->acronyme);
        printf("---------------------------------------------------------------------\n");
    }
}

void affichage_av_donne(avion av )
{
    printf("\nL'identifiant de l'avion : %s\n",av.identifiant);
    printf("Son niveau de carburant : %d\n",av.carburant);
    printf("Sa consommation de carburant par minute : %d\n",av.consommation);
    printf("Son heure de decollage prevue : %s\n",av.heure_decollage);
    printf("Sa compagnie de rattachement : \n");
    printf("Le nom de la compagnie : %s\n",(av.compagnie)->nom);
    printf("L'acronyme de la compagnie : %s\n",(av.compagnie)->acronyme);
    printf("---------------------------------------------------------------------\n");
}

void affichage_av(noeud * p )
{
    printf("\nL'identifiant de l'avion : %s\n",(p->info).identifiant);
    printf("Son niveau de carburant : %d\n",(p->info).carburant);
    printf("Sa consommation de carburant par minute : %d\n",(p->info).consommation);
    printf("Son heure de decollage prevue : %s\n",(p->info).heure_decollage);
    printf("Sa compagnie de rattachement : \n");
    printf("Le nom de la compagnie : %s\n",((p->info).compagnie)->nom);
    printf("L'acronyme de la compagnie : %s\n",((p->info).compagnie)->acronyme);
    printf("---------------------------------------------------------------------\n");
}


void CREATION (struct liste * ll)
{
    avion av ;
    unsigned rep=1,position;
    do
    {
        av=saisie_avion(*ll);
        position=saisie_position(*ll);
        if (position==1)
            insere_tete_av(ll,av);
        else if((taille_liste_av(*ll)+1)==position)
            insere_queue_av(ll,av);
        else
            insere_pos_av(ll,av,position);
        do
        {
            printf("\nVoulez vous ajouter un autre avion O/N ? ");
            scanf("%u",&rep);
        }
        while((rep!=1)&&(rep!=0));
    }
    while(rep==1);
}


// les menus
void menu_ajout(struct liste * ll,  unsigned * quiter)
{
    unsigned rep,pos;
    avion av;
    do
    {
        printf("\n  Menu Ajouter \n\n\t1_Ajout en tete \n\t2_Ajout en queue \n\t3_Ajout dans une position \n\t4_Retour au menu MAJ \n\n\tDonner votre choix SVP :");
        scanf("%d",&rep);
        while((rep<1)||(rep>4))
        {
            printf("\n___Verifier votre choix SVP !___ \n\n ");
            printf("\n  Menu Ajouter \n\n\t1_Ajout en tete \n\t2_Ajout en queue \n\t3_Ajout dans une position \n\t4_Retour au menu MAJ \n\n\tDonner votre choix SVP :");
            scanf("%d",&rep);
        }

        switch(rep)
        {
        case 1:
            av=saisie_avion(*ll);
            insere_tete_av(ll,av);
            printf("\nL'ajout en tete effectue avec succes !!!\n\n");
            break;
        case 2:
            av=saisie_avion(*ll);
            insere_queue_av(ll,av);
            printf("\nL'ajout en queue effectue avec succes !!!\n\n");
            break;
        case 3:
            pos=saisie_position(*ll);
            if(pos==1)
            {
                printf("\nChoisir la premiere option dans le menu d'ajout SVP !\n");
                break;
            }
            else if(pos==taille_liste_av(*ll)+1)
            {
                printf("\nChoisir la deusieme option dans le menu d'ajout SVP !\n");
                break;
            }
            else
            {
                av=saisie_avion(*ll);
                insere_pos_av(ll,av,pos);
                printf("\nL'ajout a la %ueme position effectue avec succes !!!\n\n",pos);
                break;
            }
        case 4:
            break;
        }
    }
    while(rep!=4);
    menu_maj(ll,quiter);
}

void menu_supprimer(struct liste * ll,  unsigned * quiter)
{
    unsigned rep=0,pos;
    char id[7];
    char nom_comp[25];
    char c;
    if(taille_liste_av(*ll)!=0)
    {
        do
        {
            printf("\n  Menu Suppression \n\n\t1_Suppression en tete \n\t2_Suppression en queue \n\t3_Suppression a partir d'une position \n\t4_Suppression d'un avion donne \n\t5_Suppression des avions d'une compagnie donnee \n\t6_Retour au menu MAJ \n\n\tDonner votre choix SVP :");
            scanf("%d",&rep);
            while((rep<1)||(rep>6))
            {
                printf("\n___Verifier votre choix SVP !___ \n\n ");
                printf("\n  Menu Suppression \n\n\t1_Suppression en tete \n\t2_Suppression en queue \n\t3_Suppression a partir d'une position \n\t4_Suppression d'un avion donne \n\t5_Suppression des avions d'une compagnie donnee \n\t6_Retour au menu MAJ \n\n\tDonner votre choix SVP :");
                scanf("%d",&rep);
            }
            switch(rep)
            {
            case 1:
                supprimer_tete_av(ll);
                printf("\nLa suppression en tete effectuee avec succes !!!\n\n");
                break;
            case 2:
                supprimer_queue_av(ll);
                printf("\nLa suppression en queue effectuee avec succes !!!\n\n");
                break;
            case 3:
                pos=saisie_position(*ll);
                if(pos==1)
                {
                    printf("\nChoisir la premiere option dans le menu de suppression SVP !\n");

                    break;
                }
                else if(pos==taille_liste_av(*ll)+1)
                {
                    printf("\nChoisir la deusieme option dans le menu de suppression SVP !\n");
                    break;
                }
                else
                {
                    supprimer_pos_av(ll,pos);
                    printf("\nLa suppression a partir de la %ueme position est effectuee avec succes !!!\n\n",pos);
                    break;
                }
                break;
            case 4:
                scanf("%c",&c);
                do
                {
                    printf("Saisir l'identifiant de l'avion : ");
                    gets(id);
                }
                while((strlen(id)!=6)||(!verif_format_id(id)));
                if(recherche_av(*ll,id)==NULL)
                    printf("\nAvion inexistant !!! \n");
                else
                {
                    supprimer_av_donne(ll,id);
                    printf("\nLa suppression de l'avion de l'identificateur '%s' est effectuee avec succes !!!\n\n",id);
                }
                break;
            case 5:
                scanf("%c",&c);
                do
                {
                    printf("Saisir le nom de la compagnie : ");
                    gets(nom_comp);
                }
                while(!est_alphabetique(nom_comp));
                if(recherche_comp(*ll,nom_comp)==0)
                {
                    printf("\nCompagnie inexistante !!! \n\n");
                }
                else if(recherche_comp(*ll,nom_comp)==1)
                {
                    supprimer_av_compagnie_donne(ll,nom_comp);
                    printf("\nLa suppression des avions d'origine de la compagnie '%s' est effectuee avec succes !!!\n\n",nom_comp);
                }
                break;
            case 6:
                break;
            }
        }
        while((rep!=6)&&(taille_liste_av(*ll)!=0));
        if(taille_liste_av(*ll)==0)
            printf("\nLe repertoire d'avion est vide !!!\n\n");
    }
    else
        printf("\nLe repertoire d'avion est vide !!!\n\n");
    menu_maj(ll,quiter);
}


void menu_mod(struct liste * ll,  unsigned * quiter)
{
    unsigned rep=0;
    char id [7],nom_comp[25];
    char c ;
    if(taille_liste_av(*ll)!=0)
    {
        do
        {
            printf("\n  Menu Modification \n\n\t1_Identifiant \n\t2_Compagnie \n\t3_Retour au menu MAJ \n\n\tDonner votre choix SVP :");
            scanf("%d",&rep);
            while((rep<1)||(rep>3))
            {
                printf("\n___Verifier votre choix SVP !___ \n\n ");
                printf("\n  Menu Modification \n\n\t1_Identifiant \n\t2_Compagnie \n\t3_Retour au menu MAJ \n\n\tDonner votre choix SVP :");
                scanf("%d",&rep);
            }
            switch(rep)
            {
            case 1:
                scanf("%c",&c);
                do
                {
                    printf("Saisir l'identifiant de l'avion : ");
                    gets(id);
                }
                while((strlen(id)!=6)||(!verif_format_id(id)));
                if(recherche_av(*ll,id)==NULL)
                    printf("\nAvion inexistant !!! \n");
                else
                {
                    mod_par_id(recherche_av(*ll,id));
                    printf("\nLa modification des donnees de l'avion de l'identificateur '%s' est effectuee avec succes !!!\n\n",id);
                }
                break;
            case 2:
                scanf("%c",&c);
                do
                {
                    printf("Saisir le nom de la compagnie : ");
                    gets(nom_comp);
                }
                while(!est_alphabetique(nom_comp));
                if(recherche_comp(*ll,nom_comp)==0)
                {
                    printf("\nCompagnie inexistante !!! \n\n");
                }
                else if(recherche_comp(*ll,nom_comp)==1)
                {
                    parcours_2(ll,mod_par_compagnie_donne,nom_comp);
                    printf("\nLa modification des donnees des avions d'origine de la compagnie '%s' est effectue avec succes !!!\n\n",nom_comp);
                }
                break;
            case 3:
                break;
            }
        }
        while(rep!=3);
    }
    else
        printf("\nLe repertoire d'avion est vide !!!\n\n");
    menu_maj(ll,quiter);
}

void menu_maj(struct liste * ll, unsigned * quiter)
{
    unsigned rep=0;
    printf("\n  MENU MAJ \n\n\t1_Ajouter un nouvel avion \n\t2_Supprimer un avion \n\t3_Modifier les donnees d'un avion \n\t4_Retour Menu generale \n\n\tDonner votre choix SVP : ");
    scanf("%d",&rep);
    while((rep<1)||(rep>4))
    {
        printf("\n___Verifier votre choix SVP !___ \n\n ");
        printf("\n  MENU MAJ \n\n\t1_Ajouter un nouvel avion \n\t2_Supprimer un avion \n\t3_Modifier les donnees d'un avion \n\t4_Retour Menu generale \n\n\tDonner votre choix SVP : ");
        scanf("%d",&rep);
    }
    switch(rep)
    {
    case 1:
        menu_ajout(ll,quiter);
        break;
    case 2:
        menu_supprimer(ll,quiter);
        break;
    case 3:
        menu_mod(ll,quiter);
        break;
    case 4:
        menu_general(ll,quiter);
        break;
    }

}

void menu_rech_aff(struct liste * ll, unsigned * quiter)
{
    unsigned rep=0;
    char c ;
    char nom_comp[25],id [7],heure_decollage [4];
    if(taille_liste_av(*ll)!=0)
    {
        do
        {
            printf("\n  Menu Recherche et affichage \n\n\t1_Contenu de la liste des avions \n\t2_Recherche par identifiant avion \n\t3_Recherche par compagnie \n\t4_Recherche par heure de decollage \n\t5_Tri 1 \n\t6_Retour au menu general \n\n\tDonner votre choix SVP :");
            scanf("%d",&rep);
            while((rep<1)||(rep>6))
            {
                printf("\n___Verifier votre choix SVP !___ \n\n ");
                printf("\n  Menu Recherche et affichage \n\n\t1_Contenu de la liste des avions \n\t2_Recherche par identifiant avion \n\t3_Recherche par compagnie \n\t4_Recherche par heure de decollage \n\t5_Tri 1 \n\t6_Retour au menu general \n\n\tDonner votre choix SVP :");
                scanf("%d",&rep);
            }
            switch(rep)
            {
            case 1:
                parcours(*ll,affichage_av);
                break;
            case 2:
                scanf("%c",&c);
                do
                {
                    printf("Saisir l'identifiant de l'avion : ");
                    gets(id);
                }
                while((strlen(id)!=6)||(!verif_format_id(id)));
                if(recherche_av(*ll,id)==NULL)
                    printf("\nAvion inexistant !!! \n");
                else
                    affichage_av_donne(*(recherche_av(*ll,id)));
                break;
            case 3:
                scanf("%c",&c);
                do
                {
                    printf("Saisir le nom de la compagnie : ");
                    gets(nom_comp);
                }
                while(!est_alphabetique(nom_comp));
                if(recherche_comp(*ll,nom_comp)==0)
                {
                    printf("\nCompagnie inexistante !!! \n\n");
                }
                else if(recherche_comp(*ll,nom_comp)==1)
                {
                    parcours_2(ll,affichage_av_compagnie_donne,nom_comp);
                }
                break;
            case 4:
                scanf("%c",&c);
                do
                {
                    printf("\nSaisir l'heure de decollage : ");
                    gets(heure_decollage);
                }
                while((strlen(heure_decollage)!=4)||(!verif_heure_decollage(heure_decollage)));
                if(recherche_heure_decollage(*ll,heure_decollage)==0)
                {
                    printf("\nHeure de decollage prevue inexistante !!! \n\n");
                }
                else if(recherche_heure_decollage(*ll,heure_decollage)==1)
                {
                    parcours_2(ll,affichage_av_heure_decollage,heure_decollage);
                }
                break;
            case 5:
                tri_1(ll);
                parcours(*ll,affichage_av);
                break;
            case 6:
                break;
            }
        }
        while(rep!=6);
    }
    else
        printf("\nLe repertoire d'avion est vide !!!\n\n");
    menu_general(ll,quiter);

}

void menu_enrg(struct liste * ll, unsigned * quiter)
{
    unsigned rep=0;
    do
    {
        printf("\n  Menu Enregistrement et chargement \n\n\t1_Enregistrement \n\t2_Chargement \n\t3_Retour au menu general \n\n\tDonner votre choix SVP : ");
        scanf("%d",&rep);

        while((rep<1)||(rep>3))
        {
            printf("\n___Verifier votre choix SVP !___ \n\n ");
            printf("\n  Menu Enregistrement et chargement \n\n\t1_Enregistrement \n\t2_Chargement \n\t3_Retour au menu general \n\n\tDonner votre choix SVP : ");
            scanf("%d",&rep);
        }
        switch(rep)
        {
        case 1:
            if(taille_liste_av(*ll)!=0)
            {
                ENREGISTREMENT(ll);
                printf("\nL'enregistrement du contenu de la liste dans le fichier est effectue avec succes !!! \n\n ");
            }
            else
            {
                printf("\nLe repertoire d'avion est vide !!!\n\n");
            }
            break;
        case 2:
            CHARGEMENT(ll);
            break;
        case 3:
            menu_general(ll,quiter);
            break;
        }
    }
    while(rep!=3);
}

void menu_general(struct liste * ll, unsigned * quiter)
{
    unsigned rep=0;
    printf("\nMENU GENERAL \n\n\t1_Creation du repertoire Avion \n\t2_Mise a jour des Avions \n\t3_Recherche , Affichage et Tri \n\t4_Enregistrement et chargement dans un fichier \n\t5_Quitter \n\n\tDonner votre choix SVP : ");
    scanf("%u",&rep);
    while((rep<1)||(rep>5))
    {
        printf("\n___Verifier votre choix SVP !___ \n\n ");
        printf("\nMENU GENERAL \n\n\t1_Creation du repertoire Avion \n\t2_Mise a jour des Avions \n\t3_Recherche ,affichage et Tri \n\t4_Enregistrement et chargement dans un fichier \n\t5_Quitter \n\n\tDonner votre choix SVP : ");
        scanf("%u",&rep);
    }

    switch(rep)
    {
    case 1 :
        CREATION(ll);
        break;
    case 2:
        menu_maj(ll, quiter);
        break;
    case 3:
        menu_rech_aff(ll,quiter);
        break;
    case 4:
        menu_enrg(ll,quiter);
        break;
    case 5:
        *quiter=1;
        break;

    }

}


void main()
{
    struct liste ll;
    creer_liste(&ll);
    unsigned quiter=0;
    do
    {
        menu_general(&ll,&quiter);
    }
    while(quiter==0);
}
