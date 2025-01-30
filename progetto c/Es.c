#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        if (strcmp(current->tax_id, tax_id) == 0) return current;
        current = current->next;
    }
    return NULL;
}

struct department* searchDByName(struct DList* list, const char* name) {
    struct department* current = list->head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) return current;
        current = current->next;
    }
    return NULL;
}

// Inserimento
void Einsert(struct EList* list, const char* name, const char* surname, const char* tax_id, int salary, int vacation_days, const char* department, int level) {
    if (searchEByTaxID(list, tax_id) != NULL) {
        return;
    }
    struct employee* newNode = (struct employee*)malloc(sizeof(struct employee));
    strcpy(newNode->name, name);
    strcpy(newNode->surname, surname);
    strcpy(newNode->tax_id, tax_id);
    newNode->salary = salary;
    newNode->vacation_days = vacation_days;
    newNode->sick_days = 0;
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
void modifyDepartment(struct DList* list, const char* old_name, const char* new_name) {
    struct department* dept = searchDByName(list, old_name);
    if (dept != NULL) {
        strcpy(dept->name, new_name);
    }
}

void deleteEmployee(struct EList* list, const char* tax_id) {
    struct employee* current = list->head;
    struct employee* prev = NULL;
    while (current != NULL && strcmp(current->tax_id, tax_id) != 0) {
        prev = current;
        current = current->next;
    }
    if (current == NULL) return;
    if (prev == NULL) {
        list->head = current->next;
    } else {
        prev->next = current->next;
    }
    free(current);
    list->size--;
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
    struct employee temp;

    for (i = list->head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->salary > j->salary) {
                temp = *i;
                *i = *j;
                *j = temp;
            }
        }
    }
}

void sortEmployeesByLevel(struct EList* list) {
    if (list->size < 2) return;

    struct employee* i;
    struct employee* j;
    struct employee temp;

    for (i = list->head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->level > j->level) {
                temp = *i;
                *i = *j;
                *j = temp;
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

void loadData(struct EList* employees, struct DList* departments) {
    FILE* fp = fopen("data.txt", "r");
    if (!fp) {
        printf("Impossibile aprire il file per il caricamento\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        char* token = strtok(line, ";");
        if (token[0] == 'E') {
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

            Einsert(employees, name, surname, tax_id, salary, vacation_days, department, level);
        } else if (token[0] == 'D') {
            char name[MAX_DEPARTMENT+1];
            token = strtok(NULL, ";");
            strcpy(name, token);
            Dinsert(departments, name);
        }
    }

    fclose(fp);
}

void menu() {
    printf("1. Aggiungi o modifica un nome di dipartimento\n");
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
    printf("13. Esci\n");
}

int main() {
    struct EList* employees = initEList();
    struct DList* departments = initDList();

    loadData(employees, departments);

    int choice;
    char name[MAX_NAME+1];
    char surname[MAX_SURNAME+1];
    char tax_id[MAX_TAX_ID+1];
    int salary;
    int vacation_days;
    int level;
    char department[MAX_DEPARTMENT+1];
    char old_name[MAX_DEPARTMENT+1];
    char new_name[MAX_DEPARTMENT+1];
    int amount;
    int days;

    while (1) {
        menu();
        printf("Scegli un'opzione: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Inserisci il nome del dipartimento da modificare: ");
                scanf("%s", old_name);
                printf("Inserisci il nuovo nome del dipartimento: ");
                scanf("%s", new_name);
                modifyDepartment(departments, old_name, new_name);
                break;
            case 2:
                printf("Inserisci il nome del dipendente: ");
                scanf("%s", name);
                printf("Inserisci il cognome del dipendente: ");
                scanf("%s", surname);
                printf("Inserisci il codice fiscale del dipendente: ");
                scanf("%s", tax_id);
                printf("Inserisci il salario annuale del dipendente: ");
                scanf("%d", &salary);
                printf("Inserisci i giorni di vacanza del dipendente: ");
                scanf("%d", &vacation_days);
                printf("Inserisci il dipartimento del dipendente: ");
                scanf("%s", department);
                printf("Inserisci il livello del dipendente: ");
                scanf("%d", &level);
                Einsert(employees, name, surname, tax_id, salary, vacation_days, department, level);
                break;
            case 3:
                printf("Inserisci il codice fiscale del dipendente da eliminare: ");
                scanf("%s", tax_id);
                deleteEmployee(employees, tax_id);
                break;
            case 4:
                printf("Inserisci il codice fiscale del dipendente: ");
                scanf("%s", tax_id);
                printf("Inserisci l'importo dell'aumento: ");
                scanf("%d", &amount);
                increaseSalary(employees, tax_id, amount);
                break;
            case 5:
                printf("Inserisci il codice fiscale del dipendente: ");
                scanf("%s", tax_id);
                printf("Inserisci i giorni di vacanza da assegnare: ");
                scanf("%d", &days);
                assignVacationDays(employees, tax_id, days);
                break;
            case 6:
                printf("Inserisci il codice fiscale del dipendente: ");
                scanf("%s", tax_id);
                printf("Inserisci i giorni di malattia da assegnare: ");
                scanf("%d", &days);
                assignSickDays(employees, tax_id, days);
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
                printEmployeesByDepartment(employees, department);
                break;
            case 11:
                printRemainingVacationDays(employees);
                break;
            case 12:
                printf("Inserisci il codice fiscale del dipendente: ");
                scanf("%s", tax_id);
                printf("Inserisci il nuovo dipartimento del dipendente: ");
                scanf("%s", department);
                moveEmployee(employees, tax_id, department);
                break;
            case 13:
                saveData(employees, departments);
                return 0;
            default:
                printf("Opzione non valida\n");
        }
    }

    return 0;
}
