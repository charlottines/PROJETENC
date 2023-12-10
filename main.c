/////////////////////////////////////////////////////////////////////////////
////////  AUTEUR : Mehadhebi Ines et Franja Bastien et Bail Lisa  /////////
///////                        VERSION : 6                       /////////
/////////////////////////////////////////////////////////////////////////


#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <locale.h>
#include "allfunction.h"



int main(void) {
    setlocale(LC_ALL, "fr_FR.UTF-8"); // Défint locale: UTF-8
    //créer agenda
    t_agenda *agenda = createAgenda();
    t_Searchcontact search;
    char *nom;
    char *prenom;
    int jour, month, year, hour, minutes, hour2, minutes2;
    char *objet;
    t_contact *contact;
    t_rendezvous *rdv;
    int choice;
    char c, t[60], t1[60];
    char date[10], time[5], chx[5];
    char aff=' ';
    int nbc, nbr;

    t[0]='\0'; t1[0]='\0';
    // sauvegarde existe ?. Si oui :charger/non : afficher menu
    if (ExisteSauvegarde() == 0) {
        MenuHeader(1);
        MenuBody("           ATTENTION une sauvegarde existe deja!", "           Voulez-vous la telecharger ? [O]ui[N]on", NULL);
        MenuFeet();
        while (c = getchar()) {
            while (getchar() != '\n') { } // vider le buffer dans le cas ou  saisie de plusieurs caracteres
            if (c == 'o' || c == 'O'){
                ImportContactRdv(agenda);
                break;
            }
            else if (c == 'n' || c == 'N') {
                break;
            }
            else {
                printf("Saisie attendue : O ou N ");
            }
        }
    }
    // Affiche le menu while pas quitter
    strcpy(t, "           Choissisez une lettre  : R , S , D, C , Q");


    //char str[4]; for (int j = 0; j < 50000; ++j) { for (int i = 0; i < 3; ++i) { str[i] = (char)(rand() % 26 + 'a'); } str[3] = '\0'; Search(agenda, str, "", 0); } //Génération aléatoire de 50000 chaines de 3 caractères pour remplir les logs pour avoir un graph cg TpsMoy.xls
// enlever les "//" pour faire le fichier log sinon pertre de temps de la faire tourner a chaque fois
    while (1 == 1) {
        MenuHeader(0);
        switch (aff) {
            case 'R': // affichage rdv
                MenuBodyR(search.current, 1, "");
                aff=' ';
                break;
            default:
                if (t1[0]=='\0') {
                    MenuBody(t, NULL, NULL);
                }
                else {
                    MenuBody(t, t1, NULL);
                }
                break;
        }
        MenuFeet();
        c = getchar();
        while (getchar() != '\n') { } // vider le buffer dans le cas ou  saisie de plusieurs caracteres
        switch (c) {
            case 'c':
            case 'C':
                MenuHeader(1);
                MenuBody("           Saisir un nom (min 3 car.) :", NULL, NULL);
                MenuFeet();
                nom = scanString("");
                MenuHeader(1);
                MenuBody("           Saisir un prenom (min 3 car.) :", NULL, NULL);
                MenuFeet();
                prenom = scanString("");
                search = Search(agenda, nom, prenom, 0);
                strcpy(t1, "           Choissisez une lettre  : R , S , D, C , Q");
                strcpy(t, prenom);
                strcat(t, " ");
                strcat(t, nom);
                if (search.niveau == -1) {
                    strcat(t, "            existe deja");
                }
                else {
                    contact = createContact(nom, prenom, search.niveau);
                    addContactTri(agenda, contact, search.prec, search.current);
                    strcat(t, "            a ete ajoute");
                }
                break;
            case 'r':
            case 'R':
                MenuHeader(1);
                MenuBody("           Saisir les 3 premiers caractere d'un nom :", NULL, NULL);
                MenuFeet();
                nom = scanString("");
                nom[3]='\0';
                search = Search(agenda, nom, "", 0);
                MenuHeader(1);
                nbc=MenuBodyC(search.current, 0, nom, "");
                MenuFeet();
                if (nbc=='0') { // Pas de choix
                    sprintf(t, "           Aucun nom ne correspond à \"%s\"", nom);
                    t1[0]='\0';
                    break;
                }
                else {
                    do {
                        fgets(chx, sizeof(chx), stdin);
                        if (sscanf(chx, "%d", &choice) == 1) {
                            if (choice == 0) { // Nouveau contact
                                MenuHeader(1);
                                MenuBody("           Saisir un nom (min 3 car.) :", NULL, NULL);
                                MenuFeet();
                                nom = scanString("");
                                MenuHeader(1);
                                MenuBody("           Saisir un prenom (min 3 car.) :", NULL, NULL);
                                MenuFeet();
                                prenom = scanString("");
                                break;
                            }
                            else if (choice > 0 && choice <= nbc) { // création rdv pour le contact
                                for (int i = 0; i < choice - 1; i++) { search.current = search.current->next[0];}
                                nom = (char *)malloc(strlen(search.current->nom) + 1);
                                strcpy(nom, search.current->nom);
                                prenom = (char *)malloc(strlen(search.current->prenom) + 1);
                                strcpy(prenom, search.current->prenom);
                                break;
                            }
                            else if (choice == 999) { // Abandon
                                strcpy(t, "           Abandon");
                                t1[0]='\0';
                                break;
                            }
                        }
                        printf("Saisie attendue : un nombre entre 0 et %d ou 999 : ",nbc);
                    } while (1==1);
                }
                if (choice == 999) { // Abandon
                    break;
                }
                MenuHeader(1);
                MenuBody("           Saisir la date (jj/mm/aaaa) :", NULL, NULL);
                MenuFeet();
                do {
                    fgets(date, sizeof(date), stdin);
                    if (sscanf(date, "%d/%d/%d", &jour, &month, &year) == 3) {
                        if (DateValide(jour, month, year) == 0) {
                            break;
                        }
                    }
                    printf("Saisie attendue : une date valide au format jj/mm/aaaa : ");
                } while (1==1);
                MenuHeader(1);
                MenuBody("           Saisir l'heure (hh:mm) :", NULL, NULL);
                MenuFeet();
                do {
                    fgets(time, sizeof(time), stdin);
                    if (sscanf(time, "%d:%d", &hour, &minutes) == 2) {
                        if (hourValide(hour, minutes) == 0) {
                            break;
                        }
                    }
                    printf("Saisie attendue : une heure valide au format hh:mm : ");
                } while (1==1);
                MenuHeader(1);
                MenuBody("           Saisir la durée d(hh:mm) :", NULL, NULL);
                MenuFeet();
                do {
                    fgets(time, sizeof(time), stdin);
                    if (sscanf(time, "%d:%d", &hour, &minutes) == 2) {
                        if (DureeValide(hour, minutes) == 0) {
                            break;
                        }
                    }
                    printf("Saisie attendue : une heure valide au format hh:mm : ");
                } while (1==1);
                MenuHeader(1);
                MenuBody("           Saisir l'objet du rendez-vous (min 3 car.) :", NULL, NULL);
                MenuFeet();
                objet = scanString("");

                search = Search(agenda, nom, prenom, 0);
                strcpy(t, "           Le rendez-vous a ete ajoute pour  ");
                strcpy(t1, "           Choissisez une lettre  : R , S , D, C , Q");
                strcat(t, prenom);
                strcat(t, " ");
                strcat(t, nom);
                if (search.niveau != -1) {
                    contact = createContact(nom, prenom, search.niveau);
                    addContactTri(agenda, contact, search.prec, search.current);
                    search.current=contact;
                }
                rdv = createRendezVous(jour, month, year, hour, minutes, hour2, minutes2, objet);
                ajouterRendezVous(search.current, rdv);
                break;
            case 'd':
            case 'D':
                MenuHeader(1);
                MenuBody("           Saisir les 3 premiers caractere d'un nom :", NULL, NULL);
                MenuFeet();
                nom = scanString("");
                nom[3]='\0';
                search = Search(agenda, nom, "", 0);
                MenuHeader(1);
                nbc=MenuBodyC(search.current, 1, nom, "");
                MenuFeet();
                if (nbc=='0') { // Pas de choix
                    sprintf(t, "           Aucun nom ne correspond à \"%s\"", nom);
                    t1[0]='\0';
                    break;
                }
                else {
                    do {
                        fgets(chx, sizeof(chx), stdin);
                        if (sscanf(chx, "%d", &choice) == 1) {
                            if (choice > 0 && choice <= nbc) {
                                for (int i = 0; i < choice - 1; i++) { search.current = search.current->next[0];}
                                MenuHeader(1);
                                nbr=MenuBodyR(search.current, 0, "           Choisissez un nombre pour le supprimer ");
                                MenuFeet();
                                do {
                                    fgets(chx, sizeof(chx), stdin);
                                    if (sscanf(chx, "%d", &choice) == 1) {
                                        if (choice > 0 && choice <= nbr) {
                                            SupRendezVous(search.current, choice);
                                            t1[0]='\0';
                                            strcpy(t, "           Le rendez-vous de ");
                                            strcat(t, search.current->prenom);
                                            strcat(t, " ");
                                            strcat(t, search.current->nom);
                                            strcat(t, "            a ete supprime");
                                            break;
                                        }
                                        else if (choice == 999) { // Abandon
                                            strcpy(t, "           Abandon");
                                            t1[0]='\0';
                                            break;
                                        }
                                    }
                                    printf("Saisie attendue : un entier entre 1 et %d ou 999 : ", nbr);
                                } while (1==1);
                                break;
                            }
                            else if (choice == 999) {  // Abandon
                                break;
                            }
                        }
                        printf("Saisie attendue : un entier entre 1 et %d ou 999 : ", nbc);
                    } while (1==1);
                }
                break;
            case 's':
            case 'S':
                MenuHeader(1);
                MenuBody("           Saisir les 3 premiers caractere d'un nom :", NULL, NULL);
                MenuFeet();
                nom = scanString("");
                nom[3]='\0';
                search = Search(agenda, nom, "", 0);
                MenuHeader(1);
                nbc=MenuBodyC(search.current, 1, nom, "");
                MenuFeet();
                if (nbc=='0') { // Pas de choix
                    sprintf(t, "           Aucun nom ne correspond à \"%s\"", nom);
                    t1[0]='\0';
                    break;
                }
                else {
                    do {
                        fgets(chx, sizeof(chx), stdin);
                        if (sscanf(chx, "%d", &choice) == 1) {
                            if (choice > 0 && choice <= nbc) {
                                for (int i = 0; i < choice - 1; i++) { search.current = search.current->next[0];}
                                t[0]='\0';
                                t1[0]='\0';
                                aff='R';
                                break;
                            }
                            else if (choice == 999) { // Abandon
                                strcpy(t, "            Abandon");
                                strcpy(t1, "           Choissisez une lettre  : R , S , D, C , Q");
                                break;
                            }
                        }
                        printf("Saisie attendue : un nombre entre 1 et %d ou 999 : ",nbc);
                    } while (1==1);
                }
                break;
            case 'q':
            case 'Q':
                if (SauvegardePossible() == 0) {
                    MenuHeader(1);
                    MenuBody("           Voulez-vous sauvegarder ? [O]ui [N]on ", NULL, NULL);
                    MenuFeet();
                    while (c = getchar()) {
                        while (getchar() != '\n') { } // vider le buffer dans le cas ou saisie de plusieurs caracteres
                        if (c == 'o' || c == 'O'){
                            ExportContactRdv(agenda);
                            break;
                        }
                        else if (c == 'n' || c == 'N') {
                            break;
                        }
                        else {
                            printf("Saisie attendue : O ou N ");
                        }
                    }
                }
                exit(0);
                break;
            default:
                strcpy(t,"          Choissisez une lettre  : R , S , D, C , Q");
                break;
        }
    }

    free(agenda);// Libération mémoire

    return 0;
}

/*
 int main(void) {
  //main2  attention sur replit ca enregistre mais pas CLION jsp prk
  time_t t;
  time(&t);
  srand(t);
  int n = rand() % 12 + 1;
  int size = pow(2, n) - 1;
  int tab[size];
  for (int i = 0; i < size; i++) { // initialisation  des niveau à 0 des tableaus
    tab[i] = 0;
  }
  int a = 1;
  for (int k = 0; k < size; k++) { // pour l'afficher le tableau
    // printf("%d", tab[k]);
  }
  // printf("\n");
  for (int i = 1; i < n; i++) { // parcours le tableau de niveau
    a = a * 2;                  // on double l'incrémentation du tableau

    for (int j = a - 1; j < size; j += a) { // pour chaque niveau on ajoute 1
      tab[j]++;
    }
    for (int k = 0; k < size; k++) { // pour l'affichage
      // printf("%d", tab[k]);
    }
    // printf("\n");
  }

  t_d_list *list = create_list(n); // on crée la liste vide
  t_d_cell *cell[size];
  for (int i = 0; i < size; i++) {
    cell[i] = create_cell(i + 1, tab[i] + 1); // on crée les cellules
    insert_cell(list, cell[i]);               // on les insère dans la liste
  }
  //  display_all_levels(list); // on affiche la liste

  clock_t debut, fin;
  double temps;

  FILE *log_file = fopen("log.txt", "a");
  char format[] = "%d\t%s\t%s\n";
  int level = n;
  char time_lvl0[15];
  char time_all_levels[15];

  printf("niveau\tSearch\ttps\titérations\n");
  for (int j = 2; j < 3; j++) {
    // startTimer();
    debut = clock(); // Enregistrez le temps de début
    for (int i = 0; i < pow(10, j + 3); i++) {
      classical_search(list, rand() % size + 1, 0);
    }
    // stopTimer();
    fin = clock(); // Enregistrez le temps de fin
    // displayTime();
    sprintf(time_lvl0,"%f",((double)(fin - debut)) / CLOCKS_PER_SEC * 1000);
    //time_lvl0 = ((char)(((double)(fin - debut)) / CLOCKS_PER_SEC * 1000)) +
'\0';

    // printf("%d\tstandard\t%f\t%.0f\n", n,
    //   ((double)(fin - debut)) / CLOCKS_PER_SEC * 1000, pow(10, j + 3));
    // time_lvl0 = getTimeAsString(); // fonction du module timer

    // startTimer();
    debut = clock(); // Enregistre le temps de début
    for (int i = 0; i < pow(10, j + 3); i++) {
      expert_search(list, list->head[n - 1], NULL, rand() % size + 1, n - 1);
    }
    // stopTimer();
    fin = clock(); // Enregistre le temps de fin
    // displayTime();
    // time_all_levels = getTimeAsString();
    sprintf(time_all_levels,"%f",((double)(fin - debut)) / CLOCKS_PER_SEC *1000);
    //time_all_levels = ((char)(((double)(fin - debut)) / CLOCKS_PER_SEC *1000)) + '\0';

    //  printf("%d\tavancée\t%f\t%.0f\n", n,
    //       ((double)(fin - debut)) / CLOCKS_PER_SEC * 1000, pow(10, j + 3));
   fprintf(log_file, format, level, time_lvl0, time_all_levels);
  }

  fclose(log_file);
  return 0;
}
*/
/*
int main(void) {
// main1
  t_d_list *list = create_list(5);
  display_all_levels(list);
  t_d_cell *cell1 = create_cell(56, 3);
  t_d_cell *cell2 = create_cell(31, 2);
  t_d_cell *cell3 = create_cell(32, 5);
  t_d_cell *cell4 = create_cell(18, 4);
  t_d_cell *cell5 = create_cell(25, 1);
  t_d_cell *cell6 = create_cell(59, 1);
  t_d_cell *cell7 = create_cell(58, 5);
  t_d_cell *cell8 = create_cell(91, 3);
  insert_cell(list, cell1);
  insert_cell(list, cell2);
  insert_cell(list, cell3);
  insert_cell(list, cell4);
  insert_cell(list, cell5);
  insert_cell(list, cell6);
  insert_cell(list, cell7);
  insert_cell(list, cell8);
  printf(".........................\n");
  display_all_levels(list);
  return 0;
}
*/
