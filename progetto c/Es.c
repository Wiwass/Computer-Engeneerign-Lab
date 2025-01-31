/*
Questo programma è stato realizzato da: Freschet Simone 2066732

Il programma è un gestionale per la gestione di dipendenti e dipartimenti di un'azienda.
Tutte le funzioni del programma sono abbastanza standard, lascio solo una nota per quanto riguarda la correctness dei dati inseriti dagli utenti.
Il programma è stato realizzato così da poter essere più facilmente modulato nel futuro soprattutto per quanto riguarda l'inserimento dati:
- per il nome e il cognome non sono state implementate delle restrizioni, quindi è possibile inserire qualsiasi tipo di carattere
- per l'id fiscale non sono state implementate delle restrizioni se non che non sia di esattamente 16 caratteri
- per il salario non sono state implementate delle restrizioni se non che non sia un numero intero
ecc..
Visto che non era ben speficiata la consegna ho costruito delle funzioni di correctness, che al momento controllano solamente che i dati inseriti non siano negativi, ma che possono tranquillamente essere e modificate in base alle esigenze per aggiungere parametri di controllo.
Un esempio potrebbe essere un tetto massimo ai giorni di ferie, o di aumento di salario, ecc..




*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// le lunghezze dei parametri nomi cognomi e id fiscali sono scelti in maniera completamente arbitraria

#define MAX_NAME 20
#define MAX_SURNAME 20
#define MAX_DEPARTMENT 40
#define MAX_TAX_ID 16

struct employee {
    char name[MAX_NAME+1];
    char surname[MAX_SURNAME+1];
    char tax_id[MAX_TAX_ID+1];
    int salary;
    int vacation_days;
    int sick_days;
    char department[MAX_DEPARTMENT+1];
    int level;
    struct employee* next;
};

struct department {
    char name[MAX_DEPARTMENT+1];
    struct department* next;
};

struct EList {
    struct employee* head;
    int size;
};

struct DList {
    struct department* head;
    int size;
};

// Inizializzazione
struct EList* initEList() {
    struct EList* list = (struct EList*)malloc(sizeof(struct EList));
    list->head = NULL;
    list->size = 0;
    return list;
}

struct DList* initDList() {
    struct DList* list = (struct DList*)malloc(sizeof(struct DList));
    list->head = NULL;
    list->size = 0;
    return list;
}

// Ricerca
struct employee* searchEByTaxID(struct EList* list, const char* tax_id) {
    struct employee* current = list->head;
    while (current != NULL) {
        if (strcmp(current->tax_id, tax_id) == 0){return current;}
        current = current->next;
    }
    return NULL;
}

struct department* searchDByName(struct DList* list, const char* name) {
    struct department* current = list->head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0){
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Inserimento
void Einsert(struct EList* list, const char* name, const char* surname, const char* tax_id, int salary, int vacation_days, int sick_days, const char* department, int level) {
    if (searchEByTaxID(list, tax_id) != NULL) {
        return;
    }
    struct employee* newNode = (struct employee*)malloc(sizeof(struct employee));
    strcpy(newNode->name, name);
    strcpy(newNode->surname, surname);
    strcpy(newNode->tax_id, tax_id);
    newNode->salary = salary;
    newNode->vacation_days = vacation_days;
    newNode->sick_days = sick_days;
    strcpy(newNode->department, department);
    newNode->level = level;
    newNode->next = list->head;
    list->head = newNode;
    list->size++;
}

void Dinsert(struct DList* list, const char* name) {
    if (searchDByName(list, name) != NULL) {
        return;
    }
    struct department* newNode = (struct department*)malloc(sizeof(struct department));
    strcpy(newNode->name, name);
    newNode->next = list->head;
    list->head = newNode;
    list->size++;
}

// Modifica
void modifyDepartment(struct DList* list, struct EList* elist, const char* old_name, const char* new_name) { 
    struct department* dept = searchDByName(list, old_name);
    if (dept != NULL) {
        strcpy(dept->name, new_name);
    }

    struct employee* current = elist->head; // cambio il nome del dipartimento in tutti i dipendenti
    while (current != NULL) {
        if (strcmp(current->department, old_name) == 0) {
            strcpy(current->department, new_name);
        }
        current = current->next;
    }
}
void deleteEmployee(struct EList* list, const char* tax_id) {
    struct employee* current = list->head;
    struct employee* prev = NULL;
    while (current != NULL && strcmp(current->tax_id, tax_id) != 0) {
        prev = current;
        current = current->next;
    }
    if (current == NULL) return;  // dipendente non trovato
    if (prev == NULL) {   // se l'elemento da eliminare è il primo
        list->head = current->next;
    } else {
        prev->next = current->next;  // caso "base"
    }
    free(current);
    list->size--;
    printf("Dipendente eliminato con successo.\n");
}

void increaseSalary(struct EList* list, const char* tax_id, int amount) {
    struct employee* emp = searchEByTaxID(list, tax_id);
    if (emp != NULL) {
        emp->salary += amount;
    }
}

void assignVacationDays(struct EList* list, const char* tax_id, int days) {
    struct employee* emp = searchEByTaxID(list, tax_id);
    if (emp != NULL) {
        emp->vacation_days += days;
    }
}

void assignSickDays(struct EList* list, const char* tax_id, int days) {
    struct employee* emp = searchEByTaxID(list, tax_id);
    if (emp != NULL) {
        emp->sick_days += days;
    }
}

void moveEmployee(struct EList* list, const char* tax_id, const char* new_department) {
    struct employee* emp = searchEByTaxID(list, tax_id);
    if (emp != NULL) {
        strcpy(emp->department, new_department);
    }
}

// Stampa
void printDepartments(struct DList* list) {
    struct department* current = list->head;
    while (current != NULL) {
        printf("Department: %s\n", current->name);
        current = current->next;
    }
}

void printEmployees(struct EList* list) {
    struct employee* current = list->head;
    while (current != NULL) {
        printf("Name: %s, Surname: %s, Tax ID: %s, Salary: %d, Vacation Days: %d, Sick Days: %d, Department: %s, Level: %d\n",
               current->name, current->surname, current->tax_id, current->salary, current->vacation_days, current->sick_days, current->department, current->level);
        current = current->next;
    }
}

void printEmployeesByDepartment(struct EList* list, const char* department) {
    struct employee* current = list->head;
    while (current != NULL) {
        if (strcmp(current->department, department) == 0) {
            printf("Name: %s, Surname: %s, Tax ID: %s, Salary: %d, Vacation Days: %d, Sick Days: %d, Department: %s, Level: %d\n",
                   current->name, current->surname, current->tax_id, current->salary, current->vacation_days, current->sick_days, current->department, current->level);
        }
        current = current->next;
    }
}

void printRemainingVacationDays(struct EList* list) {
    struct employee* current = list->head;
    while (current != NULL) {
        printf("Name: %s, Surname: %s, Remaining Vacation Days: %d\n", current->name, current->surname, current->vacation_days);
        current = current->next;
    }
}

// Sorting
void sortEmployeesBySalary(struct EList* list) {
    if (list->size < 2) return;

    struct employee* i;
    struct employee* j;
    int temp_salary;
    int temp_vacation_days;
    int temp_sick_days;
    int temp_level;
    char temp_name[MAX_NAME+1];
    char temp_surname[MAX_SURNAME+1];
    char temp_tax_id[MAX_TAX_ID+1];
    char temp_department[MAX_DEPARTMENT+1];

    for (i = list->head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->salary > j->salary) {
                // Scambia salary
                temp_salary = i->salary;
                i->salary = j->salary;
                j->salary = temp_salary;

                // Scambia vacation_days
                temp_vacation_days = i->vacation_days;
                i->vacation_days = j->vacation_days;
                j->vacation_days = temp_vacation_days;

                // Scambia sick_days
                temp_sick_days = i->sick_days;
                i->sick_days = j->sick_days;
                j->sick_days = temp_sick_days;

                // Scambia level
                temp_level = i->level;
                i->level = j->level;
                j->level = temp_level;

                // Scambia name
                strcpy(temp_name, i->name);
                strcpy(i->name, j->name);
                strcpy(j->name, temp_name);

                // Scambia surname
                strcpy(temp_surname, i->surname);
                strcpy(i->surname, j->surname);
                strcpy(j->surname, temp_surname);

                // Scambia tax_id
                strcpy(temp_tax_id, i->tax_id);
                strcpy(i->tax_id, j->tax_id);
                strcpy(j->tax_id, temp_tax_id);

                // Scambia department
                strcpy(temp_department, i->department);
                strcpy(i->department, j->department);
                strcpy(j->department, temp_department);
            }
        }
    }
}

void sortEmployeesByLevel(struct EList* list) {
    if (list->size < 2) return;

    struct employee* i;
    struct employee* j;
    int temp_salary;
    int temp_vacation_days;
    int temp_sick_days;
    int temp_level;
    char temp_name[MAX_NAME+1];
    char temp_surname[MAX_SURNAME+1];
    char temp_tax_id[MAX_TAX_ID+1];
    char temp_department[MAX_DEPARTMENT+1];

    for (i = list->head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->level > j->level) {
                // Scambia salary
                temp_salary = i->salary;
                i->salary = j->salary;
                j->salary = temp_salary;

                // Scambia vacation_days
                temp_vacation_days = i->vacation_days;
                i->vacation_days = j->vacation_days;
                j->vacation_days = temp_vacation_days;

                // Scambia sick_days
                temp_sick_days = i->sick_days;
                i->sick_days = j->sick_days;
                j->sick_days = temp_sick_days;

                // Scambia level
                temp_level = i->level;
                i->level = j->level;
                j->level = temp_level;

                // Scambia name
                strcpy(temp_name, i->name);
                strcpy(i->name, j->name);
                strcpy(j->name, temp_name);

                // Scambia surname
                strcpy(temp_surname, i->surname);
                strcpy(i->surname, j->surname);
                strcpy(j->surname, temp_surname);

                // Scambia tax_id
                strcpy(temp_tax_id, i->tax_id);
                strcpy(i->tax_id, j->tax_id);
                strcpy(j->tax_id, temp_tax_id);

                // Scambia department
                strcpy(temp_department, i->department);
                strcpy(i->department, j->department);
                strcpy(j->department, temp_department);
            }
        }
    }
}

// Gestione file
void saveData(struct EList* employees, struct DList* departments) {
    FILE* fp = fopen("data.txt", "w");
    if (!fp) {
        printf("Impossibile aprire il file per il salvataggio\n");
        return;
    }

    struct employee* e = employees->head;
    while (e != NULL) {
        fprintf(fp, "E;%s;%s;%s;%d;%d;%d;%s;%d\n", e->name, e->surname, e->tax_id, e->salary, e->vacation_days, e->sick_days, e->department, e->level);
        e = e->next;
    }

    struct department* d = departments->head;
    while (d != NULL) {
        fprintf(fp, "D;%s\n", d->name);
        d = d->next;
    }

    fclose(fp);
}

void loadData(struct EList* employees, struct DList* departments) {  // carico i dati nelle rispettive liste dal file testuale data.txt che funziona da registro
    FILE* fp = fopen("data.txt", "r");
    if (!fp) {
        printf("Impossibile aprire il file per il caricamento\n");
        return;
    }

    char line[256];  // buffer per la lettura di una riga dal file di lunghezza massima 256 >> MAX_NAME+MAX_SURNAME+MAX_TAX_ID+MAX_DEPARTMENT+5
    while (fgets(line, sizeof(line), fp)) {
        char* token = strtok(line, ";");
        if (token[0] == 'E') { // se la prima lettera della riga è E allora è un dipendente
            char name[MAX_NAME+1];
            char surname[MAX_SURNAME+1];
            char tax_id[MAX_TAX_ID+1];
            int salary;
            int vacation_days;
            int sick_days;
            char department[MAX_DEPARTMENT+1];
            int level;

            token = strtok(NULL, ";");
            strcpy(name, token);
            token = strtok(NULL, ";");
            strcpy(surname, token);
            token = strtok(NULL, ";");
            strcpy(tax_id, token);
            token = strtok(NULL, ";");
            salary = atoi(token);
            token = strtok(NULL, ";");
            vacation_days = atoi(token);
            token = strtok(NULL, ";");
            sick_days = atoi(token);
            token = strtok(NULL, ";");
            strcpy(department, token);
            token = strtok(NULL, ";");
            level = atoi(token);

            Einsert(employees, name, surname, tax_id, salary, vacation_days, sick_days, department, level);

        } else if (token[0] == 'D') { // se la prima lettera della riga è D allora è un dipartimento
            char name[MAX_DEPARTMENT+1];
            token = strtok(NULL, ";");
            strcpy(name, token);
            name[strcspn(name, "\n")] = 0;
            Dinsert(departments, name);
        }
    }

    fclose(fp);
}
bool nameCorrectness(char* name) {
    if (strlen(name) > MAX_NAME) return false;
    return true;
}
bool departmentExists(char* department, struct DList* departments) {
    struct department* current =searchDByName(departments, department);
    if (current != NULL) {
        return true;
    }
    return false;
    
}
bool departmentCorrectness(char* department, struct DList* departments) {
    if (strlen(department) > MAX_DEPARTMENT) return false;
    struct department* current = departments->head;
    while (current != NULL) {
        if (strcmp(current->name, department) == 0) {  //se esiste un dipartimento con lo stesso nome allora restituisci false
            return false;
        }
        current = current->next;
    }
    return true;
}
bool surnameCorrectness(char* surname) {
    if (strlen(surname) > MAX_SURNAME) return false;
    return true;
}
bool taxIDExists(char* tax_id, struct EList* list) {
    if (strlen(tax_id) != MAX_TAX_ID) return false;
    struct employee* current = list->head;
    while (current != NULL) {
        if (strcmp(current->tax_id, tax_id) == 0) {
            return true;
        }
        current = current->next;
    }
    return false;
}
bool taxIDCorrectness(char* tax_id, struct EList* list) {
    if (strlen(tax_id) != MAX_TAX_ID) return false;
    struct employee* current = list->head;
    while (current != NULL) {
        if (strcmp(current->tax_id, tax_id) == 0) {
            return false;
        }
        current = current->next;
    }
    return true;
}
bool salaryCorrectness(int salary) {
    if (salary < 0) return false;
    return true;
}
bool vacationDaysCorrectness(int vacation_days) {
    if (vacation_days < 0) return false;
    return true;
}
bool sickDaysCorrectness(int sick_days) {
    if (sick_days < 0) return false;
    return true;
}

void menu() { // funzione che stampa il menu senza che sia inserito nel main per rendere le cose più ordinate
    printf("1. Modifica un nome di dipartimento\n");
    printf("2. Aggiungi un nuovo dipendente\n");
    printf("3. Elimina un dipendente\n");
    printf("4. Aumenta il salario di un dipendente\n");
    printf("5. Assegna giorni di vacanza a un dipendente\n");
    printf("6. Assegna giorni di malattia a un dipendente\n");
    printf("7. Stampa i dipartimenti esistenti\n");
    printf("8. Stampa i dipendenti in ordine di salario\n");
    printf("9. Stampa i dipendenti in ordine di livello\n");
    printf("10. Stampa i dipendenti di un certo dipartimento\n");
    printf("11. Stampa i giorni di vacanza rimanenti per dipendente\n");
    printf("12. Sposta un dipendente da un dipartimento a un altro\n");
    printf("13. Aggiungi un dipartimento\n");
    printf("14. Esci\n");
}

int main() {
    struct EList* employees = initEList();
    struct DList* departments = initDList();

    loadData(employees, departments); // ogni avvio del programma carica i dati dal file data.txt

    //inizializzazione delle variabili che potrebbero essere utilizzate nel programma
    int choice;
    char name[MAX_NAME+1];
    char surname[MAX_SURNAME+1];
    char tax_id[MAX_TAX_ID+1];
    char salary[20];
    char vacation_days[20];
    char sick_days[20];
    char level[20];
    char amount[20];
    char days[20];
    int salary_int;
    int vacation_days_int;
    int sick_days_int;
    int level_int;
    char department[MAX_DEPARTMENT+1];
    char old_name[MAX_DEPARTMENT+1];
    char new_name[MAX_DEPARTMENT+1];
    int amount_int;
    int days_int;
    char* endptr;
    //

    while (1) {
        printf("\n");
        printf("********** MENU **********\n");
        menu(); //stampa il menu
        printf("Scegli un'opzione: "); 
        scanf("%d", &choice); // legge la scelta dell'utente

        switch (choice) { //switch case per gestire le scelte dell'utente
            case 1:

                printf("Inserisci il nome del dipartimento da modificare: ");
                scanf("%s", old_name);
                if (!departmentExists(old_name,departments)) { printf("Nome del dipartimento non valido\n"); break; }

                printf("Inserisci il nuovo nome del dipartimento: ");
                scanf("%s", new_name);
                if (!departmentCorrectness(new_name,departments)) { printf("Nome del dipartimento non valido\n"); break; }

                modifyDepartment(departments,employees, old_name, new_name);
                break;
            case 2:
                printf("Inserisci il nome del dipendente: ");
                scanf("%s", name);
                if (!nameCorrectness(name)) { printf("Nome del dipendente non valido\n"); break; }

                printf("Inserisci il cognome del dipendente: ");
                scanf("%s", surname);
                if (!surnameCorrectness(surname)) { printf("Cognome del dipendente non valido\n"); break; }

                printf("Inserisci il codice fiscale del dipendente: ");
                scanf("%s", tax_id);
                if (!taxIDCorrectness(tax_id, employees)) { printf("Codice fiscale non valido o già esistente\n"); break; }

                printf("Inserisci il salario annuale del dipendente: ");
                scanf("%s", salary);
                salary_int = strtol(salary, &endptr, 10);
                if (*endptr != '\0') { printf("Salario non valido\n"); break; }
                if (!salaryCorrectness(salary_int)) { printf("Salario non valido\n"); break; }

                printf("Inserisci i giorni di vacanza del dipendente: ");
                scanf("%s", vacation_days);
                vacation_days_int = strtol(vacation_days, &endptr, 10);
                if (*endptr != '\0') { printf("Giorni di vacanza non validi\n"); break; }
                if (!vacationDaysCorrectness(vacation_days_int)) { printf("Giorni di vacanza non validi\n"); break; }

                printf("Inserisci i giorni di malattia del dipendente: ");
                scanf("%s", sick_days);
                sick_days_int = strtol(sick_days, &endptr, 10);
                if (*endptr != '\0') { printf("Giorni di malattia non validi\n"); break; }
                if (!sickDaysCorrectness(sick_days_int)) { printf("Giorni di malattia non validi\n"); break; }

                printf("Inserisci il dipartimento del dipendente: ");
                scanf("%s", department);
                if (!departmentExists(department,departments)) { printf("Nome del dipartimento non valido\n"); break; }

                printf("Inserisci il livello del dipendente: ");
                scanf("%s", level);
                level_int = strtol(level, &endptr, 10);
                if (*endptr != '\0') { printf("Livello non valido\n"); break; }

                Einsert(employees, name, surname, tax_id, salary_int, vacation_days_int, sick_days_int, department, level_int); 
                break;
            case 3:

                printf("Inserisci il codice fiscale del dipendente da eliminare: ");
                scanf("%s", tax_id);
                if(!taxIDExists(tax_id, employees)) { printf("Codice fiscale non valido o non esistente\n"); break; }
                deleteEmployee(employees, tax_id);
                break;

            case 4:

                printf("Inserisci il codice fiscale del dipendente: ");
                scanf("%s", tax_id);
                if(!taxIDExists(tax_id, employees)) { printf("Codice fiscale non valido\n"); break; }

                printf("Inserisci l'importo dell'aumento: ");
                scanf("%s", amount);
                amount_int = strtol(amount, &endptr, 10);
                if (*endptr != '\0') { printf("Importo non valido\n"); break; }
                if (!salaryCorrectness(amount_int)) { printf("Importo non valido\n"); break; }

                increaseSalary(employees, tax_id, amount_int);
                break;
            case 5:

                printf("Inserisci il codice fiscale del dipendente: ");
                scanf("%s", tax_id);
                if(!taxIDExists(tax_id, employees)) { printf("Codice fiscale non valido\n"); break; }

                printf("Inserisci i giorni di vacanza da assegnare: ");
                scanf("%s", days);
                days_int = strtol(days, &endptr, 10);
                if (*endptr != '\0') { printf("Giorni di vacanza non validi\n"); break; }
                if (!vacationDaysCorrectness(days_int)) { printf("Giorni di vacanza non validi\n"); break; }

                assignVacationDays(employees, tax_id, days_int);
                break;

            case 6:

                printf("Inserisci il codice fiscale del dipendente: ");
                scanf("%s", tax_id);
                if(!taxIDExists(tax_id, employees)) { printf("Codice fiscale non valido\n"); break; }

                printf("Inserisci i giorni di malattia da assegnare: ");
                scanf("%s", days);
                days_int = strtol(days, &endptr, 10);
                if (*endptr != '\0') { printf("Giorni di malattia non validi\n"); break; }
                if (!vacationDaysCorrectness(days_int)) { printf("Giorni di malattia non validi\n"); break; }

                assignSickDays(employees, tax_id, days_int);
                break;
            case 7:
                printDepartments(departments);
                break;
            case 8:
                sortEmployeesBySalary(employees);
                printEmployees(employees);
                break;
            case 9:
                sortEmployeesByLevel(employees);
                printEmployees(employees);
                break;
            case 10:
                printf("Inserisci il nome del dipartimento: ");
                scanf("%s", department);
                if (!departmentExists(department,departments)) { printf("Nome del dipartimento non valido\n"); break; }
                printEmployeesByDepartment(employees, department);
                break;
            case 11:
                printRemainingVacationDays(employees);
                break;
            case 12:
                printf("Inserisci il codice fiscale del dipendente: ");
                scanf("%s", tax_id);
                if(!taxIDExists(tax_id, employees)) { printf("Codice fiscale non valido\n"); break; }

                printf("Inserisci il nuovo dipartimento del dipendente: ");
                scanf("%s", department);
                if(!departmentExists(department,departments)) { printf("Nome del dipartimento non valido\n"); break; }
                

                moveEmployee(employees, tax_id, department);
                printf("Dipendente spostato con successo\n");
                break;
            case 13:
                printf("Inserisci il nome del nuovo dipartimento: ");
                scanf("%s", department);
                if(departmentExists(department,departments)) { printf("Nome del dipartimento non valido\n"); break; }
                Dinsert(departments, department);
                printf("Dipartimento creato con successo\n");
                break;
            case 14:
                saveData(employees, departments);
                printf("Dati salvati con successo\n");
                return 0;
            default:
                printf("Opzione non valida\n");
        }
    }

    return 0;
}
