#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef enum boolean{FALSE,TRUE}boolean;

typedef struct TDate{
    int jj;
    int mm ;
    int aa;
}TDate;

typedef struct TArticle{
    int idArticle ;
    char designtation[100];
    int quantite;
    TDate da;
    float pua;
    float puv;
}TArticle;

typedef struct LArticle{
    TArticle a;
    struct LArticle*suiv;
}LArticle;

typedef LArticle*ptr;

// Les  Prototypes
TArticle saisirUnArticle();
void ajouterUnArticleEnTete(ptr *tete, TArticle a);
void saisirDesArticles(ptr *tete);
char menuPrincipal(void);
void afficherUnArticle(TArticle a);
void afficherDesArticles(ptr tete );
ptr rechercheUnArticle(ptr tete , int codeArt);
void rechercheAfficherUnArticle(ptr tete);
void modifierUnArticle(ptr tete );
void trierArticlesParCode(ptr tete);
void insertionTrieeUnArticleParCode(ptr *tete , TArticle nva );
void enregistrerListeVersFichier(ptr tete);
void chargeFichierVersListe(ptr *tete);
void libererListeDesArticles(ptr * tete);
float totalValeursEnStock(ptr tete);

float totalValeursEnStock(ptr tete) {
    if (tete == NULL) {
        return 0.0;
    }else {
        float total = tete->a.quantite * tete->a.pua;
        return total + totalValeursEnStock(tete->suiv);
    }
}

void libererListeDesArticles(ptr * tete){
    ptr p;
    while (*tete !=NULL) {
            p=(*tete);
            (*tete)=(*tete)->suiv;
            free(p);
    }
    *tete=NULL;
}


void insertionTrieeUnArticleParCode(ptr *tete , TArticle nva ){
    ptr l = (ptr)malloc(sizeof(struct LArticle));
    l->a = nva;
    l->suiv = NULL;
    ptr pred =*tete;
    ptr cour=*tete;
    while(cour->a.idArticle  < nva.idArticle || cour !=NULL){
        pred=cour;
        cour=cour->suiv;
    }
    pred->suiv = l;
    l->suiv = cour;
}


void trierArticlesParCode(ptr tete)
{
    boolean trie;
    ptr p;
    TArticle a;
    if(tete->suiv !=NULL){
        do{
            trie=TRUE;
            for (p=tete ; p->suiv!=NULL ; p=p->suiv){
                if(p->a.idArticle  > (p->suiv)->a.idArticle){
                    a=p->a;
                    p->a=(p->suiv)->a;
                    (p->suiv)->a=a;
                    trie=FALSE;
                }
            }
        }while(!(trie==FALSE));
        printf("la liste est triee avec succes");
    }

}

void supprimerUnArticle(ptr *tete){
    ptr p ,pred;
    int codeAsupp;
    if(tete == NULL){
        printf("Liste Vide ");
    }
    else{
        printf("veuillez saisir le code d'Art a Supprimer");
        scanf("%d",&codeAsupp);
        p=rechercheUnArticle(*tete,codeAsupp);
        if(p==NULL){
            printf("Article Introuvable");
        }else{
            if(p==*tete){
                *tete=(*tete)->suiv;
                free(p);
            }
            else{
                pred=*tete;
                while(pred->suiv !=p){
                    pred=pred->suiv;

                }
                pred->suiv=p->suiv;
                free(p);
            }

        }
    }
}
void modifierUnArticle(ptr tete){
    ptr p;
    int codeAModifier;
    if(tete == NULL){
        printf("Liste Vide ");
    }
    else{
        printf("veuillez saisir le code d'Art a modifier");
        scanf("%d",&codeAModifier);
        p=rechercheUnArticle(tete,codeAModifier);
        if(p==NULL){
            printf("Article Introuvable");
        }else{
            printf("Anciennes données de l'article : \n ");
            afficherUnArticle(p->a);
            printf("veuillez saisir les nouvelle modification \n ");
            p->a=saisirUnArticle();
            printf("Modification effectue avec succes ");
        }
    }
}
void rechercheAfficherUnArticle(ptr tete){
    ptr p;
    int codeArt;
    if(tete == NULL){
        printf("Liste Vide ");
    }
    else{
        printf("veuillez saisir le code d'Art a rechercher");
        scanf("%d",&codeArt);
        p=rechercheUnArticle(tete,codeArt);
        if(p==NULL){
            printf("Article Introuvable");
        }else{
            afficherUnArticle(p->a);
        }
    }
}

ptr rechercheUnArticle(ptr tete, int codeArt) {
    if (tete == NULL) {
        return NULL ;
    } else {
        if (tete->a.idArticle ==codeArt) {
            return tete;
        } else {
            return rechercheUnArticle(tete->suiv, codeArt);
        }
    }
}

TArticle saisirUnArticle(){
    TArticle ar;
    printf("ID article :");
    scanf("%d",&ar.idArticle);
    printf("Designtation :");
    scanf("%s",ar.designtation);
    printf("Quantite :");
    scanf("%d",&ar.quantite);
    printf("Date d'achat :");
    scanf("%d/%d/%d", &ar.da.jj, &ar.da.mm, &ar.da.aa );
    printf("PUA :");
    scanf("%f",&ar.pua);
    printf("PUV : ");
    scanf("%f",&ar.puv);
    return(ar);
}

void ajouterUnArticleEnTete(ptr *tete, TArticle a) {
    ptr aux;
    aux = (LArticle *)malloc(sizeof(LArticle));
    aux->a = a;
    aux->suiv = *tete;
    *tete = aux;
}
void saisirDesArticles(ptr *tete) {
    TArticle a;
    char rep;
    do {
        printf("Voulez-vous saisir un autre article ? (o/n): ");
        scanf(" %c", &rep);
        if(rep == 'o' || rep == 'O') {
            a = saisirUnArticle();

            ajouterUnArticleEnTete(tete, a);
        }
    } while (rep == 'o' || rep == 'O');
}


void afficherUnArticle(TArticle a){
    printf("ID Article: %d \n",a.idArticle);
    printf("Designtation :%s \n",a.designtation);
    printf("Quantite : %d \n",a.quantite);
    printf("Date Achat : %d/%d/%d \n", a.da.jj ,a.da.mm,a.da.jj);
    printf("PUA :  %f \n", a.pua);
    printf("PUV :  %f \n", a.puv);
}

void afficherDesArticles(ptr tete ){
    ptr p;
    p=tete;
    while(p!=NULL){
        afficherUnArticle(p->a);
        p=p->suiv;
    }
}


char menuPrincipal(void)
{
    char choix;
        printf("           ********************************************************\n");
        printf("           *                   MENU PRINCIPAL                     *\n");
        printf("           ********************************************************\n");
        printf("           *    S    *       Saisir des articles                  *\n");
        printf("           ********************************************************\n");
        printf("           *    A    *       Afficher les articles                *\n");
        printf("           ********************************************************\n");
        printf("           *    R    *       Recherche Article Par CodeART        *\n");
        printf("           ********************************************************\n");
        printf("           *    M    *       Modifier un article                  *\n");
        printf("           ********************************************************\n");
        printf("           *    T    *       Trier Article par code               *\n");
        printf("           ********************************************************\n");
        printf("           *    D    *       Supprimer Un article                 *\n");
        printf("           ********************************************************\n");
        printf("           *    V    *       Total Valeurs en Stock               *\n");
        printf("           ********************************************************\n");
        printf("           *    Q    *       Quitter l'application                *\n");
        printf("           ********************************************************\n");
        printf("           Donner votre choix :                                   *\n");
        scanf(" %c",&choix);
    return (choix);
}


int main() {
    TArticle a ;
    ptr tete = NULL;
    float total;
    char choix;
    chargeFichierVersListe(&tete);
    do {
        system("cls");
        choix = menuPrincipal();
        switch (choix) {
            case 'S':
                saisirDesArticles(&tete);
                getch();
                break;

            case 'A':
                afficherDesArticles(tete);
                getch();
                break;
            case 'R':
                rechercheAfficherUnArticle(tete);
                getch();
                break;
            case 'M':
                modifierUnArticle(tete);
                getch();
                break;
            case 'T':
                trierArticlesParCode(tete);
                getch();
                break;
            case'D':
                supprimerUnArticle(&tete);
                printf("Suppression effectue ");
                getch();
                break;
             case 'V':
                total=totalValeursEnStock(tete);
                printf("La valeur en stock est %f",total);
                getch();
                break;
            case 'Q':
                enregistrerListeVersFichier(tete);
                libererListeDesArticles(&tete);
                getch();
                break;
                }
    }while (choix != 'Q' && choix != 'q');
}

void chargeFichierVersListe(ptr *tete){
    FILE* f;
    TArticle ar;
    char *fichierArticle="C:\\TI\\C\\TP3\\article.dat";
    f = fopen(fichierArticle, "rb");
    while (fread(&ar, sizeof(TArticle), 1, f)){
        ajouterUnArticleEnTete(&(*tete),ar);
    }
    fclose(f);
}
void enregistrerListeVersFichier(ptr tete){
    FILE* f;
    ptr p;
    TArticle ar;
    f = fopen("article.dat", "wb");
    for (p=tete; p!=NULL ; p=p->suiv){
        fwrite(&p->a, sizeof(TArticle), 1, f);
        printf("Enregistrement effectue avec succes");
    }
    fclose(f);

}










