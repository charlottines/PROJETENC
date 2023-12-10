/////////////////////////////////////////////////////////////////////////////
/////////                    PROGRAMME C AGENDA                     ////////
////////  AUTEUR : Mehadhebi Ines et Franja Bastien et Bail Lisa  /////////
///////                        VERSION : 6                       /////////
/////////////////////////////////////////////////////////////////////////

#ifndef UNTITLED6_ALLFUNCTION_H
#define UNTITLED6_ALLFUNCTION_H


#include <sys/times.h>

typedef struct s_d_cell {
    int value;
    int max_level;
    struct s_d_cell **next;
} t_d_cell;

t_d_cell *create_cell(int, int);

//  a n niveau pour un tableau de n ligne avec val max
// tableau de pointeur
typedef struct s_d_list {
    t_d_cell **head;
    int max_level;
} t_d_list;

t_d_list *create_list(int);
void insert_list(t_d_list *, t_d_cell *);
void insert_cell(t_d_list *, t_d_cell *);
void display_one_level(t_d_list *, int);
void display_all_levels(t_d_list *);
int classical_search(t_d_list *, int, int);
int expert_search(t_d_list *, t_d_cell *, t_d_cell *, int, int);

// stocker un rendez-vous
typedef struct s_rendezvous {
    int day, month, year;
    int hour, minute;
    int duree_hour, duree_minute;
    char *object;
    struct s_rendezvous *next;
} t_rendezvous;

//  stocker un contact
typedef struct s_contact {
    char *nom;
    char *prenom;
    char *nom_prenom;
    struct s_rendezvous *rendezvous; // Un tableau dynamique de rendez-vous
    struct s_contact **next;
    int max_level;
} t_contact;

// l'agenda
typedef struct s_agenda {
    t_contact **contacts; // Un tableau dynamique de contacts
    int max_level;        // nombre de niveau de la liste
} t_agenda;


typedef struct s_Searchcontact {
    t_contact *prec;
    t_contact *current;
    int niveau;
}t_Searchcontact;


char *scanString(char *);
char *minuscule(char *);
char *concatener(char *, char *);

t_agenda *createAgenda(void);
void afficher1niveau(t_agenda *, int);
void afficherAgenda(t_agenda *);

t_contact *createContact(char *, char *, int);
void addContact(t_agenda *, t_contact *);
void addContactTri(t_agenda *, t_contact *, t_contact *, t_contact *);
t_Searchcontact Search(t_agenda *, char *, char *, int log);

t_rendezvous *createRendezVous(int, int, int, int, int, int, int, char *);
void ajouterRendezVous(t_contact *, t_rendezvous *);
void SupRendezVous(t_contact *, int );
void afficherRendezVous(t_rendezvous *);

void ImportContactRdv(t_agenda *);
void ExportContactRdv(t_agenda *);
int ExisteSauvegarde();
int SauvegardePossible();


void MenuHeader(int );
void MenuFeet();
void MenuBody(char *, char*, char *);
int MenuBodyR(t_contact *, int, char *);
int MenuBodyC(t_contact *, int, char *, char *);

int DateValide(int ,int ,int );
int hourValide(int ,int );
int DureeValide(int ,int );

// timer structure
typedef struct s_timer {
    clock_t _start; // start time
    clock_t _end;   // end time
    double _msecs;  // duration in milliseconds
} t_timer;

static t_timer _timer;

/**
 * @brief start the timer
 * @param none
 * @return none
 */
void startTimer();

/**
 * @brief stop the timer
 * @param none
 * @return none
 */
void stopTimer();

/**
 * @brief display the time
 * @param none
 * @return none
 */
void displayTime();

/**
 * @brief return a string with the time in seconds and milliseconds
 * @param none
 * @return a string with the time in seconds and milliseconds
 */
char *getTimeAsString();



#endif //UNTITLED6_ALLFUNCTION_H
