/////////////////////////////////////////////////////////////////////////////
/////////                    PROGRAMME C AGENDA                     ////////
////////  AUTEUR : Mehadhebi Ines et Franja Bastien et Bail Lisa  /////////
///////                        VERSION : 6                       /////////
/////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <string.h>
#include "allfunction.h"
#include <time.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>


// creer une cellule : on donne sa valeur et le nombre de niveaux que possède
// cette cellule, pour obtenir un pointeur vers cette cellule
t_d_cell *create_cell(int value, int n_levels) {
    t_d_cell *cell = malloc(sizeof(t_d_cell)); // alloue de la memoire
    cell->value = value;        // cell pointe value qui prendra la valeur
    cell->max_level = n_levels; // le nombre de niveau de la cellule
    cell->next = malloc(
            n_levels * sizeof(t_d_cell *)); // alloue la memoire des pointeur suivant
    for (int i = 0; i < n_levels; i++) {
        cell->next[i] = NULL; // les pointeur  a null
    }
    return cell;
}

// create une liste a niveau vide : on donnera le nombre maximal de niveaux que
// possède cette liste
t_d_list *create_list(int max_level) {
    t_d_list *list = malloc(sizeof(t_d_list));
    list->head = malloc(max_level * sizeof(t_d_cell *)); // aloue la memoire
    for (int i = 0; i < max_level; i++) {
        list->head[i] = NULL; // met les pointeur a null
    }
    list->max_level = max_level; //a la list on lui met le nombre de niveau total
    return list;
}

// Inserer une cellule a niveaux en tête de liste (attention a bien tenir compte
// du nombre de niveaux de la cellule)
void insert_list(t_d_list *list, t_d_cell *cell) {
    for (int i = 0; i < cell->max_level && i < list->max_level; i++) {
        cell->next[i] =
                list->head[i]; // il prend l'adresse de la cellule et pour chaque niveau
        // chaque cellule egale a tel adresse
    }
    for (int i = cell->max_level - 1; i >= 0 && i < list->max_level; i--) {
        list->head[i] = cell; // chaque cellule devient la cellule de tête de liste
    }
}

// Afficher l’ensembles des cellules de la liste pour un niveau donne alligne
void display_one_level(t_d_list *list, int level) {
    t_d_cell *cell = list->head[level]; // on commence par la tête de la liste
    printf("[list head_%d @-]", level);
    if (cell == NULL) {
        printf("NULL\n"); // si la cellule est nulle on affiche NULL (fonctionne que
        // si la liste est vide)
        return;
    }
    t_d_cell *cell0;       // valeur 1er cellule de la liste du niveau 0
    int old = cell->value; // la valeur de la cellule courante
    int cpt = 0;           // un compteur
    if (list->head[0]->value !=
        list->head[level]->value) { // si la tête de la liste n'est pas la même
        // que la 1er cellule trouve
        cell0 = list->head[0];
        while (cell0 != NULL) {
            if (cell0->value < cell->value) {
                cpt++;
            }
            cell0 = cell0->next[0]; // on passe a la suivante
        }
        for (int i = 0; i < cpt; i++) {
            printf(
                    "-----------"); // boucle sur le nombre de fois puis on met les tiret
        }
    }

    while (cell != NULL) { // on parcourt le niveau, on refait la même chose
        cell0 = list->head[0];
        cpt = 0;
        while (cell0 != NULL) {
            if (cell0->value > old && cell0->value < cell->value) {
                cpt++;
            }
            cell0 = cell0->next[0];
        }
        for (int i = 0; i < cpt; i++) {
            printf("-----------");
        }
        // nombre de cellule entre old et new
        printf("-->[%3d|@-]", cell->value); // affiche la valeur de la cellule
        old = cell->value;
        cell = cell->next[level]; // on passe a la suivante
    }
    cpt = 0;
    int last0;
    cell0 = list->head[0];
    while (cell0 != NULL) { // on compte le nombre de cellule en fin de liste
        last0 = cell0->value;
        cell0 = cell0->next[0];
    }
    if (last0 != old) {
        cell0 = list->head[0];
        while (cell0 != NULL) {
            if (cell0->value > old) {
                cpt++;
            }
            cell0 = cell0->next[0];
        }
        for (int i = 0; i < cpt; i++) {
            printf("-----------");
        }
    }
    printf("-->NULL\n");
}

// Afficher tous les niveaux de la liste
void display_all_levels(t_d_list *list) {
    for (int i = 0; i < list->max_level; i++) {
        display_one_level(
                list, i); // on appelle la fonction pour afficher un niveau de la liste
        // autant de fois qu'il a de niveau a a l'aide du for
    }
}

// Inserer une cellule a niveau dans la liste, au bon endroit, de manière a ce
// que la liste reste triee par ordre croissant
void insert_cell(t_d_list *list, t_d_cell *cell) {
    int level;
    t_d_cell *current;
    for (level = 0; level < cell->max_level; level++) { // on parcourt les niveaux
        if (list->head[level] == NULL) {
            list->head[level] = cell; // si la liste est vide on y insère la cellule
        } else if (cell->value < list->head[level]->value) {
            t_d_cell *temp = list->head[level]; // on cree une cellule temporaire
            list->head[level] = cell;           // on y insère la cellule
            cell->next[level] = temp;
        } else { // on insère la cellule car le bon niveau est trouve
            current = list->head[level];
            while (current->next[level] != NULL &&
                   current->next[level]->value <
                   cell->value) { // cherche la bonne position
                current = current->next[level];
            }
            cell->next[level] = current->next[level]; // insère a la bonne position
            current->next[level] = cell;
        }
    }
}

int classical_search(t_d_list *list, int value, int level) {
    t_d_cell *current;
    current = list->head[level];     // variable temporaire
    while (current != NULL) {        // on boucle tant que la fin de la liste
        if (current->value == value) { // valeur trouvee
            return 0;
        } else { // valeur non trouvee on passe a la suivante
            current = current->next[level];
        }
    }
    return 1; // valeur non trouve
}

int expert_search(t_d_list *list, t_d_cell *first, t_d_cell *last, int value,
                  int level) {

    t_d_cell *current = first;
    t_d_cell *prec = first;

    while (current != last && current != NULL) { // on boucle tant que list!=NULL
        if (current->value > value) {
            if (level == 0) {
                return 1;
            } else {
                return expert_search(list, prec, current, value, level - 1);
            }
        } else if (current->value < value) { // on cherche la bonne position
            prec = current;
            current = current->next[level]; // on passe a la suivante
        } else {
            return 0; // valeur trouvee
        }
    }
    if (level == 0) {
        return 1; // valeur non trouvee
    } else {
        if (prec == first) {//jamais trouve de valeur plus petite
            return expert_search(list, list->head[level - 1], NULL, value, level - 1);//on cherche dans le niveau precedent en commencant a la 1er valeur du niveau precedent
        } else {
            return expert_search(list, prec, NULL, value, level - 1);
        }
    }
}

const int *LOG = "../log3.txt";// nom du fichier des log (temps)
const int *SAV = "../sauvegarde.txt";// nom du fichier de sauvegarde

int nbcontact=0, nbrdv=0; // Variables globales, communes a toutes les fonction si ajouter a un ajouter a tous

// Fonction effectuant la saisie, retournant un tableau dynamique stockant
// uniquement les caractères jusqu'a touche Entree
char *scanString(char *question) {
    char *texte = NULL;
    int taille = 0;
    char caractere;

    printf("%s", question);
    while ((caractere = getchar()) != '\n' || taille < 3) {
        if ((caractere >= 'a' && caractere <= 'z') ||
            (caractere >= 'A' && caractere <= 'Z') ||
            caractere == ' ' || caractere == '\'' || caractere == '-') {
            taille++;
            texte = (char *)realloc(texte, taille * sizeof(char));
            if (texte == NULL) {
                printf("Erreur d'allocation de memoire.\n");
                exit;
            }
            texte[taille - 1] = caractere;
        }
        else {
            printf("\b");
        }
    }
    texte = (char *)realloc(texte, (taille + 1) * sizeof(char)); // Ajout de memoire pour le caractère de fin de chaine
    texte[taille] = '\0';  // caractère de fin de chaine

    return texte;
}

// fonction pour renvoyer chaine en minuscule
char *minuscule(char *nom_prenom) {
    char *result = (char *)malloc(strlen(nom_prenom) + 1);
    if (result == NULL) {
        printf("Allocation de memoire a echoue.");
        exit;
    }
    for (int i = 0; nom_prenom[i] != '\0'; i++) {
        result[i] = tolower(nom_prenom[i]);
    }
    result[strlen(nom_prenom)] = '\0';

    return result;
}

// fonction pour renvoyer chaine concatener
/*char *concatener(char *chaine1, char *chaine2) {
  char *resultat = (char *)malloc(strlen(chaine1) + strlen(chaine2) + 1);
  if (resultat == NULL) {
    printf("Allocation de memoire a echoue.");
    exit;
  }
  strcpy(resultat, chaine1); // Copiez la première chaîne
  strcat(resultat, chaine2); // Concatenez la deuxième chaîne
  return resultat;
}*/

// fonction de creation d'agenda
t_agenda *createAgenda(void) {
    t_agenda *agenda = (t_agenda *)malloc(sizeof(t_agenda));
    agenda->contacts =
            (t_contact *)malloc(4 * sizeof(t_contact)); // aloue la memoire
    for (int i = 0; i < 4; i++) {
        agenda->contacts[i] = NULL; // met les pointeur a null
    }
    agenda->max_level = 4; //a la list on lui met le nombre de niveau total
    return agenda;
}

// Afficher l’ensembles des cellules de la liste pour un niveau donne alligne
void afficher1niveau(t_agenda *agenda, int level) {
    t_contact *contact =
            agenda->contacts[level]; // on commence par la tête de la liste
    printf("[Agenda_%d @-]", level);
    if (contact == NULL) {
        printf("-->NULL\n"); // si la cellule est nulle on affiche NULL (fonctionne
        // que si la liste est vide)
        return;
    }

    while (contact != NULL) { // on parcourt le niveau, on refait la même chose
        printf("-->[%s|@-]",
               contact->nom_prenom);    // affiche la valeur de la cellule
        contact = contact->next[level]; // on passe a la suivante
    }
    printf("-->NULL\n");
}

// Afficher tous les niveaux de la liste
void afficherAgenda(t_agenda *agenda) {
    for (int i = 0; i < agenda->max_level; i++) {
        afficher1niveau(
                agenda, i); // on appelle la fonction pour afficher un niveau de la
        // liste autant de fois qu'il a de niveau a a l'aide du for
    }
}

// Fonction pour create un contact
t_contact *createContact(char *nom, char *prenom, int max_level) {
    t_contact *contact = (t_contact *)malloc(
            sizeof(t_contact)); // allocation de memoire pour contact
    contact->nom =
            (char *)malloc(strlen(nom) + 1); // allocation de memoire pour le nom plus
    // 1 pour le caractère de fin de chaine
    strcpy(contact->nom, nom); // on copie le nom
    contact->prenom = (char *)malloc(
            strlen(prenom) + 1); // allocation de memoire pour le prenom plus 1 pour
    // le caractère de fin de chaine
    strcpy(contact->prenom, prenom); // on copie le prenom
    contact->nom_prenom =
            (char *)malloc(strlen(nom) + strlen(prenom) +
                           2); // allocation de memoire pour le nom_prenom plus 1 et
    // pour le caractère de fin plus 1
    strcpy(contact->nom_prenom, minuscule(nom));
    strcat(contact->nom_prenom,
           "_"); // ajoute la chaine a la suite a l'aide de strcat
    strcat(contact->nom_prenom, minuscule(prenom));
    contact->rendezvous = NULL;
    contact->max_level = max_level;
    contact->next = (t_contact *)malloc(
            max_level * sizeof(t_contact)); // alloue la memoire des pointeur suivant
    for (int i = 0; i < max_level; i++) {
        contact->next[i] = NULL; // met les pointeur a null
    }
    return contact;
}

// fonction ajouter contact en tête d'agenda
/*void addContact(t_agenda *agenda, t_contact *contact) {
  for (int i = 0; i < contact->max_level && i < agenda->max_level; i++) {
    contact->next[i] =
        agenda->contacts[i]; // il prend l'adresse de la cellule et pour chaque
                             // niveau chaque cellule egale a tel adresse
  }
  for (int i = contact->max_level - 1; i >= 0 && i < agenda->max_level; i--) {
    agenda->contacts[i] =
        contact; // chaque cellule devient la cellule de tête de liste
  }
  nbcontact++;
}*/
// fonction ajouter contact au bon endroit dans la liste
void addContactTri(t_agenda *agenda, t_contact *contact, t_contact *prec, t_contact *suiv) {
    if (prec != NULL) {
        for (int i = 0; i < contact->max_level && i < agenda->max_level; i++) {
            contact->next[i] = prec->next[i]; // il prend l'adresse de la cellule et pour chaque niveau chaque cellule egale a tel adresse
        }
        for (int i = contact->max_level - 1; i >= 0 && i < agenda->max_level; i--) {
            prec->next[i] = contact; // chaque cellule devient la cellule de tête de liste
        }
        if (strcmp(prec->nom_prenom, contact->nom_prenom) > 0) {
            char *t_c;
            t_rendezvous *t_r;
            t_c = prec->nom;
            prec->nom = contact->nom;
            contact->nom = t_c;
            t_c = prec->prenom;
            prec->prenom = contact->prenom;
            contact->prenom = t_c;
            t_c = prec->nom_prenom;
            prec->nom_prenom = contact->nom_prenom;
            contact->nom_prenom = t_c;
            t_r=prec->rendezvous;
            prec->rendezvous=contact->rendezvous;
            contact->rendezvous=t_r;
        }
    }
    else {
        for (int i = 0; i < contact->max_level && i < agenda->max_level; i++) {
            contact->next[i] =
                    agenda->contacts[i]; // il prend l'adresse de la cellule et pour chaque
            // niveau chaque cellule egale a tel adresse
        }
        for (int i = contact->max_level - 1; i >= 0 && i < agenda->max_level; i--) {
            agenda->contacts[i] =
                    contact; // chaque cellule devient la cellule de tête de liste
        }
    }
    nbcontact++;
}


t_Searchcontact Search(t_agenda *agenda, char *nom, char *prenom, int log) {//paramètre int log pour savoir si enregistrer log ou pas dans la Search
    t_Searchcontact r; // structure de retour de la fonction pour avoir les bornes pour ajouter le contact en cas de valeur non trouvee et e niveau pour create le contact
    r.current = agenda->contacts[0];
    r.prec = agenda->contacts[0];
    r.niveau = 4;

    char *nom_prenom;
    int comp;

    clock_t debut, fin; // Variable pour stocker les temps d'ececution des Searchs
    char time_lvl0[15];
    char time_all_levels[15];
    FILE *log_file = NULL;
    char format[] = "%c\t%s\t%s\n";

    if (log == 0) { // Pas d"enregistrement des log si Log different(<>) 0
        log_file = fopen(LOG, "a"); // fichier des logs des temps

        debut = clock(); // Enregistrez le temps de debut
    }
    nom_prenom = (char *)malloc(strlen(nom) + strlen(prenom) + 2); // allocation de memoire pour le nom_prenom plus 1 et pour le caractère de fin plus 1
    strcpy(nom_prenom, minuscule(nom));
    strcat(nom_prenom, "_"); // ajoute la chaine a la suite a l'aide de strcat
    strcat(nom_prenom, minuscule(prenom));

    // Search directe au niveau 0
    while (r.current != NULL) {        // on boucle tant que la fin de la liste
        comp=strcmp(r.current->nom_prenom, nom_prenom); // comparaison de 2 chaines de caractères
        if (comp == 0) { // valeurs identiques, on indique trouvee avec niveau=-1 et on sort de la boucle
            r.niveau=-1;
            break;
        } else if (comp < 0){ // valeur courante plus petite que valeur cherchee, on passe a la suivante en sauvegardant la valeur courante dans prec avant
            r.prec=r.current;
            r.current = r.current->next[0];
        }
        else if (comp > 0) { //valeur courante plus grande que valeur cherchee, on arrête la Search
            break;
        }
    }

    if (log == 0) {
        fin = clock(); // Enregistrez le temps de fin
        sprintf(time_lvl0,"%.6f",((double)(fin - debut)) / CLOCKS_PER_SEC * 1000000);


        debut = clock(); // Enregistrez le temps de debut
    }
    // Search au niveau 4
    r.niveau = 4;
    r.current = agenda->contacts[3];
    r.prec = agenda->contacts[2];
    char *val = malloc(sizeof(char) * 3);
    char *cur = malloc(sizeof(char) * 3);
    val[0] = nom_prenom[0];
    val[1] = '\0';
    while (r.current != NULL) {        // on boucle tant que la fin de la liste
        cur[0] = r.current->nom_prenom[0];
        cur[1] = '\0';
        comp=strcmp(cur, val); // comparaison de 2 chaines de caractères
        if (comp == 0) { // valeurs identiques, on indique trouvee avec niveau=-1 et on sort de la boucle
            r.niveau=3;
            break;
        } else if (comp < 0){ // valeur courante plus petite que valeur cherchee, on passe a la suivante en sauvegardant la valeur courante dans prec avant
            r.prec=r.current;
            r.current = r.current->next[0];
        }
        else if (comp > 0) { //valeur courante plus grande que valeur cherchee, on arrête la Search
            break;
        }
    }
    free(val);
    free(cur);
    // Search au niveau 3
    r.current = r.prec;
    r.prec = agenda->contacts[1];
    val = malloc(sizeof(char) * 3);
    cur = malloc(sizeof(char) * 3);
    val[0] = nom_prenom[0];
    val[1] = nom_prenom[1];
    val[2] = '\0';
    while (r.current != NULL) {        // on boucle tant que la fin de la liste
        cur[0] = r.current->nom_prenom[0];
        cur[1] = r.current->nom_prenom[1];
        cur[2] = '\0';
        comp=strcmp(cur, val); // comparaison de 2 chaines de caractères
        if (comp == 0) { // valeurs identiques, on indique trouvee avec niveau=-1 et on sort de la boucle
            r.niveau=2;
            break;
        } else if (comp < 0){ // valeur courante plus petite que valeur cherchee, on passe a la suivante en sauvegardant la valeur courante dans prec avant
            r.prec=r.current;
            r.current = r.current->next[0];
        }
        else if (comp > 0) { //valeur courante plus grande que valeur cherchee, on arrête la Search
            break;
        }
    }
    free(val);
    free(cur);
    // Search au niveau 2
    r.current = r.prec;
    r.prec = agenda->contacts[0];
    val = malloc(sizeof(char) * 4);
    cur = malloc(sizeof(char) * 4);
    val[0] = nom_prenom[0];
    val[1] = nom_prenom[1];
    val[2] = nom_prenom[2];
    val[3] = '\0';
    while (r.current != NULL) {        // on boucle tant que la fin de la liste
        cur[0] = r.current->nom_prenom[0];
        cur[1] = r.current->nom_prenom[1];
        cur[2] = r.current->nom_prenom[2];
        cur[3] = '\0';
        comp=strcmp(cur, val); // comparaison de 2 chaines de caractères
        if (comp == 0) { // valeurs identiques, on indique trouvee avec niveau=-1 et on sort de la boucle
            r.niveau=1;
            break;
        } else if (comp < 0){ // valeur courante plus petite que valeur cherchee, on passe a la suivante en sauvegardant la valeur courante dans prec avant
            r.prec=r.current;
            r.current = r.current->next[0];
        }
        else if (comp > 0) { //valeur courante plus grande que valeur cherchee, on arrête la Search
            break;
        }
    }
    free(val);
    free(cur);
    // Search au niveau 1
    r.current = r.prec;
    r.prec = agenda->contacts[0];
    while (r.current != NULL) {        // on boucle tant que la fin de la liste
        comp=strcmp(r.current->nom_prenom, nom_prenom); // comparaison de 2 chaines de caractères
        if (comp == 0) { // valeurs identiques, on indique trouvee avec niveau=-1 et on sort de la boucle
            r.niveau=-1;
            break;
        } else if (comp < 0){ // valeur courante plus petite que valeur cherchee, on passe a la suivante en sauvegardant la valeur courante dans prec avant
            r.prec=r.current;
            r.current = r.current->next[0];
        }
        else if (comp > 0) { //valeur courante plus grande que valeur cherchee, on arrête la Search
            break;
        }
    }
    if (log == 0) {
        fin = clock(); // Enregistrez le temps de fin

        sprintf(time_all_levels,"%.6f",((double)(fin - debut)) / CLOCKS_PER_SEC * 1000000);//permet d'ecrire dans une chaine de caractère, printf ca ecrit a l'ecran, sprintf ecrit dans la varianle time_all_levels

        fprintf(log_file, format, nom[0], time_lvl0, time_all_levels);//fprintf ecrit dans le fichier log_file
        fclose(log_file); // fermeture du fichier log_file
    }
    return r;
}



// Fonction pour create un rendez-vous
t_rendezvous *createRendezVous(int day, int month, int year, int hour,int minute, int duree_hour, int duree_minute, char *object) {
    t_rendezvous *rdv = (t_rendezvous *)malloc(sizeof(t_rendezvous));
    rdv->day = day;
    rdv->month = month;
    rdv->year = year;
    rdv->hour = hour;
    rdv->minute = minute;
    rdv->duree_hour = duree_hour;
    rdv->duree_minute = duree_minute;
    rdv->object = (char *)malloc(strlen(object) + 1);
    strcpy(rdv->object, object);
    rdv->next = NULL;
    return rdv;
}


// Fonction pour ajouter un rendez-vous a un contact
void ajouterRendezVous(t_contact *contact, t_rendezvous *rdv) {
    rdv->next = contact->rendezvous;
    contact->rendezvous = rdv;
    nbrdv++;
}

// Fonction pour supprimer le nième rendez-vous dun contact
void SupRendezVous(t_contact *contact, int nb) {
    t_rendezvous *rdv=contact->rendezvous;//quelle contact le rdv appartient
    t_rendezvous *rdv_prec=contact->rendezvous;//numero du rdv
    if (nb == 1) {
        contact->rendezvous = rdv->next;//l'adresse de contact devient celle de next(rdv que l'on va supprimer)
    }
    else {//superieur a1
        for (int i=0; i<nb-1; i++) {
            rdv_prec=rdv;//rdv devient rdv prec
            rdv=rdv->next;//rdv devient rdv suivant lui celui qu'on veut supprimer après toutes les iteration
        }
        rdv_prec->next=rdv->next;  //on met l'adresse de celui que l'on veut supprimer
    }
    nbrdv--;
    free(rdv->object);//on libère l'espace memoire de l'object
    free(rdv);//on libère l'espace memoire de rdv
}


// Fonction pour afficher un rendez-vous
void afficherRendezVous(t_rendezvous *rendez_vous) {
    t_rendezvous *rdv = rendez_vous;
    if (rdv == NULL) {
        printf("            Pas de rendez vous\n");
        return;
    }

    while (rdv != NULL) {
        // On affiche la date du rendez-vous
        printf("            Date : %02d/%02d/%04d\n", rdv->day, rdv->month, rdv->year);

        // On affiche l'hour du rendez-vous
        printf("            hour : %02d:%02d\n", rdv->hour, rdv->minute);

        // On affiche la duree du rendez-vous
        printf("            Duree : ");
        if (rdv->duree_hour !=0) {
            printf("            %d hours ",rdv->duree_hour);
        }
        if (rdv->duree_hour !=0 && rdv->duree_minute != 0) {
            printf("et ");
        }
        if (rdv->duree_minute != 0) {
            printf("            %d minutes", rdv->duree_minute);
        }
        printf("\n");
        // On affiche l'object du rendez-vous
        printf("            object : %s\n", rdv->object);
        printf("            -------------\n");
        rdv = rdv->next;
    }
}

// fonction pour supprimer le rendez vous d'un contact

// Fonction pour verifier l'existance de la sauvegarde
int ExisteSauvegarde() {
    FILE *fichier = fopen(SAV, "r");

    if (fichier != NULL) {
        fclose(fichier);
        return 0; // Succès : Le fichier existe et on peut le lire
    }
    else {
        return 1; // Echec : // Le fichier n'existe pas ou on ne peut pas le lire
    }
}
// Fonction pour verifier si la sauvegarde est possible
int SauvegardePossible() {
    FILE *fichier = fopen(SAV, "a");

    if (fichier != NULL) {
        fclose(fichier);
        return 0; // Succès : Le fichier existe et on peut ecrire
    }
    else {
        return 1; // Echec : // Le fichier n'existe pas ou on ne peut pas ecrire
    }
}

// Fonction pour importer un fichier de rendez-vous
void ImportContactRdv(t_agenda *agenda) {
    FILE *f = fopen(SAV, "r");//defini fichier
    char l[256];
    char *nom = NULL, *prenom = NULL, *object = NULL;
    int day, month, year, hour, minutes, hour2, minutes2;
    t_contact *contact;
    t_rendezvous *rdv;
    t_Searchcontact search;


    size_t s = 0;
    while (fgets (l,sizeof(l),f) != NULL) //recupere une ligne du fichier -1 fin du fichier
    {
        for (int i = 0; i < strlen(l); i++) {
            if (l[i] == '\n') {
                // Remplacer le caractère
                l[i] = '\0';
            }
        }
        nom = strtok(l, "\t");//permet de recuperer premier terme jusqu'a la tabulation
        prenom = strtok(NULL, "\t");
        day = atoi(strtok(NULL, "\t"));//atoi permet de transformer en entier
        month = atoi(strtok(NULL, "\t"));
        year = atoi(strtok(NULL, "\t"));
        hour = atoi(strtok(NULL, "\t"));
        minutes = atoi(strtok(NULL, "\t"));
        hour2 = atoi(strtok(NULL, "\t"));
        minutes2 = atoi(strtok(NULL, "\t"));
        object = strtok(NULL, "\t");

        //recuperer nom prenom rdv  1 ligne 1 rdv

        search = Search(agenda, nom, prenom, 1);//Search du contact
        if (search.niveau != -1) {//contact non trouvee
            contact = createContact(nom, prenom, search.niveau);//creation du contact
            addContactTri(agenda, contact, search.prec, search.current);//ajout du contact dans l'agenda
            if (day != 0) {
                rdv = createRendezVous(day, month, year, hour, minutes, hour2, minutes2, object);//creation du rendez-vous
                ajouterRendezVous(contact, rdv);// ajout du rendez vous au contact
            }
        }
        else {
            if (day != 0) {
                rdv = createRendezVous(day, month, year, hour, minutes, hour2, minutes2, object);//creation du rendez-vous
                ajouterRendezVous(search.current, rdv);//ajout du rendez-vous au contact
            }
        }
    }
}


void ExportContactRdv(t_agenda *agenda) {//sauvegarde du fichier
    FILE *f = fopen(SAV, "w");//defini fichier
    t_contact *contact = agenda->contacts[0]; // on commence par la tête de la liste

    t_rendezvous *rdv = NULL; // on commence par la tête de la liste
    while (contact != NULL) { // on parcourt le niveau, on refait la même chose
        rdv = contact->rendezvous;
        if (rdv == NULL) {
            fprintf(f, "%s\t%s\t0\t0\t0\t0\t0\t0\t0\t0\n", contact->nom, contact->prenom);//on ecrit dans le fichier
        }
        else {
            while (rdv != NULL) { // on parcourt le niveau, on refait la même chose
                fprintf(f, "%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%s\n", contact->nom, contact->prenom, rdv->day, rdv->month, rdv->year, rdv->hour, rdv->minute, rdv->duree_hour, rdv->duree_minute, rdv->object);
                rdv = rdv->next;
            }
        }
        contact = contact->next[0];
    }
    fclose(f);//ferme le fichier
}


void MenuHeader(int on) {//le paramètre on signigie que le menu est actif sinon on ne peux pas retaper dessus
    system("clear"); //system("clear"); // Clear screan
    printf("           ———————————————————————————————————————————————————————————————————————————\n");
    printf("                                         AGENDA PROJET C                              \n");
    printf("                                                                                    \n");
    printf("                         Ines MEHADHEBI     Bastien FRANJA    Lisa BAIL                \n");
    printf("                                                                                   \n");
    printf("                                           GROUPE BN                               \n");
    printf("           ————————————————————————————————————————————————————————————————————————————\n");
    if (on == 0) {
        printf("              ADD [R]DV   | [S]how RDV  | [D]elete RDV  | [C]ontact  | [Q]uitter    \n");
    }
    else {
        printf("              ADD [R]DV   | [S]how RDV  | [D]elete RDV  | [C]ontact  | [Q]uitter                                                                            \n");
    }
}
void MenuFeet() {//s'affiche en bas contact et rdv nombre chacun
    float v0=0, vall=0, min_0['z'-'a'+2], max_0['z'-'a'+2], moy_0['z'-'a'+2], min_all['z'-'a'+2], max_all['z'-'a'+2], moy_all['z'-'a'+2], moy_max=0;//v0 vall valeur que l'on lit, min max permet d'avoir la plus petite/grande valeur pour la lettre des code Ascii 1 indice car 1 valeur en plus plus 1
    int nbl['z'-'a'+2];//nombre de ligne
    size_t s = 0;
    char l[256], *t=NULL;//pointeur vers ligne

    printf("\n");
    printf("                   l'agenda  contient : %6d contact(s)  &   %6d Rendez-vous                      \n",nbcontact, nbrdv);
    printf("\n");

    // lecture des temps dans le fichier des log
    FILE *f = fopen(LOG, "r");//defini fichier
    if (f == NULL) {
        printf("2\n");
        f = fopen(LOG, "w");//defini fichier
    }

    // Initialisation des variables (les min a 9999 une grande valeur...)
    for (int i=0; i<'z'-'a'+2; i++) {
        max_0[i]=moy_0[i]=max_all[i]=moy_all[i]=0.0;
        min_all[i]=min_0[i]=9999.99;
        nbl[i]=0;
    }

    while (fgets (l,sizeof(l),f) != NULL) { //recupere une ligne du fichier -1 fin du fichier
        for (int i = 0; i < strlen(l); i++) {
            if (l[i] == '\n') {
                // Remplacer le caractère
                l[i] = '\0';
            }
        }
        t = strtok(l, "\t");//permet de recuperer premier terme jusqu'a la tabulation
        v0 = atof(strtok(NULL, "\t"));//atof transformer en float et strtok recupère tout ce qui dans la variable jusqu'a la tab
        vall = atof(strtok(NULL, "\t"));

        // indice 0 : global
        nbl[0]++;
        if (min_0[0] > v0) {min_0[0]=v0;}//commence première valeur
        if (max_0[0] < v0) {max_0[0]=v0;}
        moy_0[0]+=v0;//somme de toute les valeurs
        if (min_all[0] > vall) {min_all[0]=vall;}
        if (max_all[0] < vall) {max_all[0]=vall;}
        moy_all[0]+=vall;
        // Indice de 1 (t-'a'+1) a 26 (t-'z'+1) pour chaque lettre
        nbl[t[0]-'a'+1]++;
        if (min_0[t[0]-'a'+1] > v0) {min_0[t[0]-'a'+1]=v0;}//t -> caractère qui est lu dans le fichier attention chaine de caractère donc prendre le premier element
        if (max_0[t[0]-'a'+1] < v0) {max_0[t[0]-'a'+1]=v0;}
        moy_0[t[0]-'a'+1]+=v0;
        if (min_all[t[0]-'a'+1] > vall) {min_all[t[0]-'a'+1]=vall;}
        if (max_all[t[0]-'a'+1] < vall) {max_all[t[0]-'a'+1]=vall;}
        moy_all[t[0]-'a'+1]+=vall;
    }

    // Calcul de de la moyenne max pour des lettres pour optimiser l'affichage
    for (int i=1; i<'z'-'a'+2; i++) {
        if (moy_max<(moy_0[i]/nbl[i])) {moy_max=moy_0[i]/nbl[i];}
        if (moy_max<(moy_all[i]/nbl[i])) {moy_max=moy_all[i]/nbl[i];}
    }
    fclose(f);//ferme le fichier

    int j=10;//le graphisque 10 ligne en hauteur
    printf("                                                    %3d ",(int)round(moy_max/(10.0/j)));
    for (int i='a'; i<='z'; i++) {
        if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j && (int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
            printf("■");//si la moyenne est egale a j et la moyenne de tous les niveau est egale a j alors on affiche
        }
        else if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
            printf("□");//si la moyenne au niveau 0 est j on affiche
        }
        else if ((int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
            printf("-");//si la moyenne de tous les niveau c'est j (donc on en a qu'un) on affiche
        }
        else {
            printf(" "); //si aucun de ces cas on affiche
        }
    }
    j--;//on passe a la ligne suivante du hauut vers le bas
    printf("  \n");
    printf("                                                    %3d ",(int)round(moy_max/(10.0/j)));
    for (int i='a'; i<='z'; i++) {
        if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j && (int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
            printf("■");
        }
        else if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
            printf("□");
        }
        else if ((int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
            printf("-");
        }
        else {
            printf(" ");
        }
    }
    j--;// dès 3e ligne debut affichage avec tableau egalement
    printf("  \n");
    printf("             ┌————————————————————————————————————┐ %3d ",(int)round(moy_max/(10.0/j)));
    for (int i='a'; i<='z'; i++) {
        if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j && (int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
            printf("■");
        }
        else if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
            printf("□");
        }
        else if ((int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
            printf("-");
        }
        else {
            printf(" ");
        }
    }
    j--;
    printf("   \n");
    printf("             | Temps (µs) |  min  |  max  |  moy  | %3d ",(int)round(moy_max/(10.0/j)));
    for (int i='a'; i<='z'; i++) {
        if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j && (int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
            printf("■");
        }
        else if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
            printf("□");
        }
        else if ((int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
            printf("-");
        }
        else {
            printf(" ");
        }
    }
    j--;
    printf("  \n");
    printf("             ├————————————┼———————┼———————┼———————┤ %3d ",(int)round(moy_max/(10.0/j)));
    for (int i='a'; i<='z'; i++) {
        if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j && (int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
            printf("■");
        }
        else if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
            printf("□");
        }
        else if ((int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
            printf("-");
        }
        else {
            printf(" ");
        }
    }
    j--;
    printf("  \n");
    if (nbl==0) {//zi nb ligne = 0 peux pas affiche de moyenne donc cas particulier on calcule rien
        printf("  | Niveau 0   |  N/A  |  N/A  |  N/A  | %3d ",(int)round(moy_max/(10.0/j)));
        for (int i='a'; i<='z'; i++) {
            if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j && (int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
                printf("■");
            }
            else if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
                printf("□");
            }
            else if ((int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
                printf("-");
            }
            else {
                printf(" ");
            }
        }
        j--;
        printf("  \n");
        printf("             ├————————————┼———————┼———————┼———————┤ %3d ",(int)round(moy_max/(10.0/j)));
        for (int i='a'; i<='z'; i++) {
            if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j && (int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
                printf("■");
            }
            else if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
                printf("□");
            }
            else if ((int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
                printf("-");
            }
            else {
                printf(" ");
            }
        }
        j--;
        printf("  \n");
        printf("O"
               "| Tous niveau|  N/A  |  N/A  |  N/A  | %3d ",(int)round(moy_max/(10.0/j)));//N/A = non applicable
        for (int i='a'; i<='z'; i++) {
            if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j && (int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
                printf("■");
            }
            else if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
                printf("□");
            }
            else if ((int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
                printf("-");
            }
            else {
                printf(" ");
            }
        }
        j--;
        printf("  \n");
    }
    else {
        printf("             | Niveau 0   |%7.3f|%7.3f|%7.3f| %3d ",min_0[0], max_0[0], moy_0[0]/nbl[0], (int)round(moy_max/(10.0/j)));//affiche la moyenne sur 7 caractère avec 3 decimal
        for (int i='a'; i<='z'; i++) {
            if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j && (int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
                printf("■");
            }
            else if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
                printf("□");
            }
            else if ((int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
                printf("-");
            }
            else {
                printf(" ");
            }
        }
        j--;
        printf("  \n");
        printf("             ├————————————┼———————┼———————┼———————┤ %3d ",(int)round(moy_max/(10.0/j)));
        for (int i='a'; i<='z'; i++) {
            if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j && (int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
                printf("■");
            }
            else if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
                printf("□");
            }
            else if ((int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
                printf("-");
            }
            else {
                printf(" ");
            }
        }
        j--;
        printf("  \n");
        printf("             | Tous niveau|%7.3f|%7.3f|%7.3f| %3d ", min_all[0], max_all[0], moy_all[0]/nbl[0],(int)round(moy_max/(10.0/j)));
        for (int i='a'; i<='z'; i++) {
            if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j && (int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
                printf("■");
            }
            else if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
                printf("□");
            }
            else if ((int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
                printf("-");
            }
            else {
                printf(" ");
            }
        }
        j--;
        printf("  \n");
    }

    printf("             └————————————————————————————————————┘ %3d ",(int)round(moy_max/(10.0/j)));
    for (int i='a'; i<='z'; i++) {
        if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j && (int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
            printf("■");
        }
        else if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
            printf("□");
        }
        else if ((int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
            printf("-");
        }
        else {
            printf(" ");
        }
    }
    j--;
    printf("  \n");

    printf("                                                    %3d ",(int)round(moy_max/(10.0/j)));
    for (int i='a'; i<='z'; i++) {
        if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j && (int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
            printf("■");
        }
        else if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
            printf("□");
        }
        else if ((int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
            printf("-");
        }
        else {
            printf(" ");
        }
    }
    printf("  \n");
    printf("                                                    tps ");
    for (int i='a'; i<='z'; i++) {
        printf("%c",i);
    }
    printf("  \n");
    printf("                                                   (µs)  □ Niveau 0 - Tous niveaux  \n");
    printf("             ————————————————————————————————————————————————————————————————————————\n");
}

//pour afficher les paramètre
void MenuBody(char *c1, char *c2, char *c3) {
    int sp=66;
    char sp1[sp];

    for (int i = 0; i < sp-strlen(c1); i++) { sp1[i]=' '; } sp1[sp-strlen(c1)]='\0';

    printf("             ———————————————————————————————————————————————————————————————————————— \n");
    printf("                                                                                \n");
    printf("                                                                                   \n");
    switch (c1[0]) {
        case '|': // Affichage des RDV

            break;
        default:
            printf("    %s %s \n",c1,sp1);
            break;
    }

    if (c2 != NULL) {
        for (int i = 0; i < sp-strlen(c2); i++) { sp1[i]=' '; } sp1[sp-strlen(c2)]='\0';
        printf("    %s %s \n",c2,sp1);
    }
    if (c3 != NULL) {
        sp=57-strlen(c3);
        for (int i = 0; i < sp-strlen(c3); i++) { sp1[i]=' '; } sp1[sp-strlen(c3)]='\0';
        printf("    %s %s \n",c3,sp1);
    }
    printf("                                                                        \n");
    printf("                                                                        \n");
}

//pour afficher les rdv
int MenuBodyR(t_contact *contact, int ab, char *Question) { // Si ab=0 on ajoute un menu pour abandonne l'operation
    int cpt=0;
    int sp=68;
    char sp1[sp], sp2[sp], ch[sp], l[sp+15];
    char h, m;

    printf("            ————————————————————————————————————————————————————————————————————————\n");
    printf("                                                                        \n");
    printf("                                                                        \n");
    t_rendezvous *rdv = contact->rendezvous;
    if (rdv == NULL) {
        sprintf(ch, "       Aucun rendez-vous pour %s %s",contact->prenom, contact->nom);
        for (int i = 0; i < sp-strlen(ch); i++) { sp1[i]=' '; } sp1[sp-strlen(ch)]='\0';
        printf("  %s %s \n",ch,sp1);

    }
    else {
        sprintf(ch,"        Rendez-vous de %s %s",contact->prenom, contact->nom);
        for (int i = 0; i < sp-strlen(ch); i++) { sp1[i]=' '; } sp1[sp-strlen(ch)]='\0';
        printf("            %s %s \n",ch,sp1);
        for (int i = 0; i < strlen(ch); i++) { sp2[i]='-'; } sp2[strlen(ch)]='\0';
        sprintf(l,"         %s%s  \n", sp2, sp1);
        printf("            %s", l);
        while (rdv != NULL) {
            cpt++;
// On affiche la date du rendez-vous
            sprintf(ch, "        %2d. Date : %02d/%02d/%04d", cpt, rdv->day, rdv->month, rdv->year);
            for (int i = 0; i < sp-strlen(ch); i++) { sp1[i]=' '; } sp1[sp-strlen(ch)]='\0';
            printf("             %s %s \n",ch,sp1);
            // On affiche l'hour du rendez-vous
            sprintf(ch, "             hour : %02d:%02d", rdv->hour, rdv->minute);
            for (int i = 0; i < sp-strlen(ch); i++) { sp1[i]=' '; } sp1[sp-strlen(ch)]='\0';
            printf("             %s %s\n",ch,sp1);
            // On affiche la duree du rendez-vous
            if (rdv->duree_hour > 1) { h='s'; } else { h=' ';}
            if (rdv->duree_minute > 1) { m='s'; } else { m=' ';}
            if ((rdv->duree_hour !=0) && (rdv->duree_minute !=0)) {
                sprintf(ch, "             Duree : %d hour%c et %d minute%c", rdv->duree_hour, h, rdv->duree_minute, m);
            }
            else if (rdv->duree_hour ==0) {
                sprintf(ch,"             Duree : %d minute%c", rdv->duree_minute, m);
            }
            else if (rdv->duree_minute ==0) {
                sprintf(ch, "             Duree : %d hour%c", rdv->duree_hour, h);
            }
            else {
                sprintf(ch, "             Duree : %d hour%c et %d minute%c", rdv->duree_hour, h, rdv->duree_minute, m);
            }
            for (int i = 0; i < sp-strlen(ch); i++) { sp1[i]=' '; } sp1[sp-strlen(ch)]='\0';
            printf("             %s %s \n",ch,sp1);
            // On affiche l'object du rendez-vous
            for (int i = 0; i < sp-strlen(rdv->object)-4; i++) { sp1[i]=' '; } sp1[sp-strlen(rdv->object)-4]='\0';
            printf("             %s %s \n",rdv->object,sp1);
            printf("             %s", l);
            rdv = rdv->next;
        }
    }
    if (ab==0){
        sprintf(ch, "                     999. <Abandon de l'operation>");
        for (int i = 0; i < sp-strlen(ch); i++) { sp1[i]=' '; } sp1[sp-strlen(ch)]='\0';
        printf("             %s %s \n",ch,sp1);
    }
    if (strcmp(Question,"")!=0){
        printf("                                                                        \n");
        for (int i = 0; i < sp-strlen(Question); i++) {  sp1[i]=' '; } sp1[sp-strlen(Question)]='\0';
        printf("             %s %s \n",Question,sp1);
    }
    printf("                                                                        \n");
    return(cpt);
}
//pour afficher les contact
int MenuBodyC(t_contact *contact, int new, char *rech, char *Question) {//Bodys pour le contact
    int cpt=0;
    int sp=68;
    char sp1[sp], ch[sp], n[4];
    printf("            ————————————————————————————————————————————————————————————————————————\n");//affichage du cadre
    printf("                                                                        \n");
    printf("                                                                        \n");
    t_contact *c = contact;
    if (c==NULL) { // pas de contact trouve
        sprintf(ch, "               Aucun contact correspondant a la Search : %s", rech);
        for (int i = 0; i < sp-strlen(ch); i++) { sp1[i]=' '; } sp1[sp-strlen(ch)]='\0';//pour create une chaine d'espace pour aligner la barre au fond
        printf("             %s %s\n",ch,sp1);
    }

    if (new==0) {//si new=0 alors affichier la ligne 0. <Nouveau contact>
        sprintf(ch, "         0. <Creation d'un nouveau contact>");
        for (int i = 0; i < sp-strlen(ch); i++) { sp1[i]=' '; } sp1[sp-strlen(ch)]='\0';
        printf("              %s %s \n",ch,sp1);
    }
    while (c != NULL) {//lire les contact
        for (int i=0; i<3; i++){ n[i]=c->nom_prenom[i];} n[3]='\0';//recupère les 3 première lettre de non prenom
        if (strcmp(n, minuscule(rech)) != 0) { // on est plus sur les 3 mêmes caractère
            break;
        }
        cpt++;//nom a 3 meme caractère que la Search faire plus 1
        sprintf(ch, "        %3d. %s %s", cpt, c->prenom, c->nom);
        for (int i = 0; i < sp-strlen(ch); i++) { sp1[i]=' '; } sp1[sp-strlen(ch)]='\0';
        printf("             %s %s \n",ch,sp1);
        c=c->next[0];
    }

    sprintf(ch, "                     999. <Abandon de l'operation>");//abandonner l'operation en cours
    for (int i = 0; i < sp-strlen(ch); i++) { sp1[i]=' '; } sp1[sp-strlen(ch)]='\0';
    printf("  %s %s \n",ch,sp1);
    //si Question<>"" alors afiicher un ligne vide + afficher Question
    if (strcmp(Question,"")!=0){
        printf("                                                                        \n");
        for (int i = 0; i < sp-strlen(Question); i++) { sp1[i]=' '; } sp1[sp-strlen(Question)]='\0';
        printf("  %s %s \n",Question,sp1);
    }
    printf("                                                                        \n");
    return cpt;
}

int DateValide(int day, int month, int year) {//valide une date
    if (month < 1 || month > 12) {//moi entre 1-12 sinon impossible
        return 1;
    }

    int Nbdaysparmonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};//par rapport au month on peux pas depasser pour chaque month
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) { // year bixestile
        Nbdaysparmonth[1] = 29;
    }

    if (day < 1 || day > Nbdaysparmonth[month - 1]) {//day entre 1 et le nombre de days du month
        return 1;//retourne faux
    }

    return 0;
}

int hourValide(int hour, int minute) {//hour valide
    if (hour < 0 || hour > 23) {//hour negative ou superieur a 23 impossible
        return 1;
    }
    if (minute < 0 || minute > 59) {//minute negative ou superieur a 59 impossible
        return 1;
    }

    return 0;
}

int DureeValide(int hour, int minute) {//renvoie si la duree est valide ou pas c'est a dire
    if (hour < 0 || hour > 23) {//hour negative ou superieur a 23 impossible
        return 1;
    }
    if (minute < 0 || minute > 59) {//minute negative ou superieur a 59 impossible
        return 1;
    }
    if (minute == 0 && hour == 0) {//impossible si 0h ou 0min
        return 1;
    }

    return 0;
}
//
// Created by flasque on 11/10/2023.
//



// start the timer
void startTimer() { _timer._start = clock(); }

// stop the timer and compute the duration in milliseconds
void stopTimer() {
    _timer._end = clock();
    // compute the duration in milliseconds wrt CLOCKS_PER_SEC
    _timer._msecs =
            (1000.0 * (double)(_timer._end - _timer._start)) / CLOCKS_PER_SEC;
}

// display the time
void displayTime() {
    // display the time using getTimeAsString()
    printf("%s\n", getTimeAsString());
    return;
}

// return a string with the time in seconds and milliseconds
char *getTimeAsString() {
    // return a string with the time in seconds and milliseconds
    // format : integers, with 3 digits, fill with 0
    // example : 001,123

    // use sprintf to write the string in a dynamically allocated buffer
    char *buffer = (char *)malloc(10 * sizeof(char));
    // use sprintf to write the string in a dynamically allocated buffer
    sprintf(buffer, "[%g] %03d,%03d", _timer._msecs, (int)(_timer._msecs) / 1000,
            (int)(_timer._msecs) % 1000);

    // return the buffer
    return buffer;
}
