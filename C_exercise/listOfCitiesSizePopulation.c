// listOfCitiesSizePopulation.cpp 
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ROW 127
#define MAX_LEN 63
#define POPULATION 0
#define SIZE 1

// Node structure for a capital city
struct Capital {
    //char name[MAX_LEN+1];
    char* name;
    double size; // in square kilometers
    int population;
    struct Capital* next;
};

// Function prototypes
void addCapital(struct Capital** head);
struct Capital* addCapitalSizePopulation(struct Capital* head, char *name, double size, long population);
void displayCapitals(struct Capital* head);
void findLargestCapital(struct Capital* head);
void findMostPopulatedCapital(struct Capital* head);
void deleteCapital(struct Capital** head, char* name);
struct Capital* read_cities(FILE* fi);
int bubbleSort(struct Capital** ptr, unsigned int order);
int bubbleSortSize(struct Capital** ptr);

int main(int argc, char *argv[]) {
    struct Capital* head = NULL;
    int choice;
    char name[MAX_LEN+1];

    if (argc != 2)
    {
        printf("Error: usage %s cities_size_population_filename\n", argv[0]);
        return(1);
    }
    FILE* fi = fopen(argv[1], "r");
    if (fi == NULL)
    {
        perror("Error opening input file\n");
        return(2);
    }

    head = read_cities(fi);
    if (head == NULL)
    {
        perror("Error reading input file\n");
        return(3);
    }
    fclose(fi);

    while (1) {
        // Display menu
        printf("\nMenu:\n");
        printf("1. Add a city\n");
        printf("2. Display all cities\n");
        printf("3. Find the largest city\n");
        printf("4. Find the most populated city\n");
        printf("5. Delete a city\n");
        printf("6. Order list in ascending order of population\n");
        printf("7. Order list in ascending order of size\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character

        switch (choice) {
        case 1:
            addCapital(&head);
            break;

        case 2:
            displayCapitals(head);
            break;

        case 3:
            findLargestCapital(head);
            break;

        case 4:
            findMostPopulatedCapital(head);
            break;

        case 5:
            printf("Enter capital name to delete: ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = '\0'; // Remove newline character
            deleteCapital(&head, name);
            break;

        case 6:
            bubbleSort(&head, POPULATION);
            break;

        case 7:
            bubbleSort(&head, SIZE);
            break;

        case 8:
            printf("Exiting...\n");
            return 0;

        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
}

// Function to add a new capital
void addCapital(struct Capital** head) {
    char cityName[MAX_LEN + 1];
    struct Capital* newCapital = (struct Capital*)malloc(sizeof(struct Capital));
    if (newCapital != NULL)
    {
        printf("Enter city name: ");
        fgets(cityName, sizeof(cityName), stdin);
        //fgets(newCapital->name, sizeof(newCapital->name), stdin);
        cityName[strcspn(cityName, "\n")] = '\0'; // Remove newline character
        newCapital->name = (char*)malloc(strlen(cityName) + 1);
        if (newCapital->name != NULL)
        {
            strcpy(newCapital->name, cityName);
            printf("Enter size (in km^2): ");
            scanf("%lf", &newCapital->size);
            printf("Enter population: ");
            scanf("%d", &newCapital->population);
            getchar(); // Consume newline character

            newCapital->next = *head;
            *head = newCapital;
        }
        else
        {
            free(newCapital);
            perror("Error adding new city");
        }
    }
    else
        perror("Error adding new city");
}

// Function to add a new capital
struct Capital* addCapitalSizePopulation(struct Capital* head, char* name, double size, long population)
{
    struct Capital* newCapital = (struct Capital*)malloc(sizeof(struct Capital));
    if (newCapital != NULL)
    {
        newCapital->name = (char*)malloc(strlen(name) + 1);
        if (newCapital->name != NULL)
        {
            strcpy(newCapital->name, name);
            newCapital->size = size;
            newCapital->population = population;
            newCapital->next = head;
        }
        else
        {
            free(newCapital);
            newCapital = NULL;
        }
    }
    return(newCapital);
}

// Function to display all capitals
void displayCapitals(struct Capital* head) {
    if (head == NULL) {
        printf("No cities in the list.\n");
        return;
    }

    printf("Cities:\n");
    while (head != NULL) {
        printf("%s: Size: %.2f km^2, Population: %d\n", head->name, head->size, head->population);
        head = head->next;
    }
}

// Function to find the largest capital
void findLargestCapital(struct Capital* head) {
    if (head == NULL) {
        printf("No cities in the list.\n");
        return;
    }

    struct Capital* largest = head;
    while (head != NULL) {
        if (head->size > largest->size) {
            largest = head;
        }
        head = head->next;
    }
    printf("The largest city is %s with a size of %.2f km^2.\n", largest->name, largest->size);
}

// Function to find the most populated capital
void findMostPopulatedCapital(struct Capital* head) {
    if (head == NULL) {
        printf("No cities in the list.\n");
        return;
    }

    struct Capital* mostPopulated = head;
    while (head != NULL) {
        if (head->population > mostPopulated->population) {
            mostPopulated = head;
        }
        head = head->next;
    }
    printf("The most populated city is %s with a population of %d.\n", mostPopulated->name, mostPopulated->population);
}

// Function to delete a capital by name
void deleteCapital(struct Capital** head, char* name) {
    struct Capital* temp = *head;
    struct Capital* prev = NULL;

    // Check if the head node is the one to delete
    if (temp != NULL && strcmp(temp->name, name) == 0) {
        *head = temp->next;
        free(temp->name);
        free(temp);
        printf("%s has been deleted.\n", name);
        return;
    }

    // Search for the node to delete
    while (temp != NULL && strcmp(temp->name, name) != 0) {
        prev = temp;
        temp = temp->next;
    }

    // If the capital was not found
    if (temp == NULL) {
        printf("%s not found in the list.\n", name);
        return;
    }

    // Unlink the node and free memory
    prev->next = temp->next;
    free(temp->name);
    free(temp);
    printf("%s has been deleted.\n", name);
}

struct Capital* read_cities(FILE* fi)
{
    char row[MAX_ROW + 1];
    struct Capital* head = NULL;

    while (!feof(fi))
    {
        if (fgets(row, MAX_ROW, fi) != row)
        {
            if (feof(fi))
            {
                break;
            }
            else
            {
                perror("Error reading file input");
                return(NULL);
            }
        }
        char capitalName[MAX_LEN + 1];
        unsigned long capitalPopulation = 0;
        double capitalSize = 0.0;
        char* t;
        if ((t = strtok(row, ";")) != NULL)
        {
            strcpy(capitalName, t);
            if ((t = strtok(NULL, ";")) != NULL)
            {
                char* endptr;
                capitalSize = strtod(t, &endptr);
                if ((t = strtok(NULL, ";")) != NULL)
                {
                    capitalPopulation = strtol(t, &endptr, 10);
                }
                else
                {
                    perror("Error converting city population");
                    return(NULL);
                }
            }
            else
            {
                perror("Error converting city size");
                return(NULL);
            }
        }
        else
        {
            perror("Error reading tokens from cities size/population file");
            return(NULL);
        }
        //printf("Capital %s - size %lf - population %d\n", capitalName, capitalSize, capitalPopulation);
        head = addCapitalSizePopulation(head, capitalName, capitalSize, capitalPopulation);
        if (head == NULL)
        {
            printf("Error adding new node");
            return(NULL);
        }
    }
    return(head);
}

int bubbleSort(struct Capital** ptr, unsigned int order)
{
    struct Capital* prev;
    struct Capital* current;
    struct Capital* tmp;
    bool swapped = true;
    bool toBeSwapped = false;

    if (*ptr == NULL || (*ptr)->next == NULL)
        return(0);
    while (swapped)
    {
        swapped = false;
        toBeSwapped = false;
        current = (*ptr)->next;
        if (order == POPULATION && (*ptr)->population > current->population)
            toBeSwapped = true;
        if (order == SIZE && (*ptr)->size > current->size)
            toBeSwapped = true;
        if (toBeSwapped)
        {
            swapped = true;
            prev = *ptr;
            *ptr = current;
            prev->next = current->next;
            current->next = prev;
        }
        prev = *ptr;
        current = prev->next->next;
        while (current != NULL)
        {
            toBeSwapped = false;
            if (order == POPULATION && prev->next->population > current->population)
                toBeSwapped = true;
            if (order == SIZE && prev->next->size > current->size)
                toBeSwapped = true;
            if (toBeSwapped)
            {
                swapped = true;
                tmp = prev->next;
                prev->next = current;
                tmp->next = current->next;
                current->next = tmp;
            }
            prev = prev->next;
            current = current->next;
        }
        if (!swapped)
            break;
    }
    if (order == POPULATION)
        printf("Ordering per population completed\n");
    else if (order == SIZE)
        printf("Ordering per size completed\n");
    return(0);
}

int bubbleSortSize(struct Capital** ptr)
{
    struct Capital* prev;
    struct Capital* current;
    struct Capital* tmp;
    bool swapped = true;

    if (*ptr == NULL || (*ptr)->next == NULL)
        return(0);
    while (swapped)
    {
        swapped = false;
        current = (*ptr)->next;
        if ((*ptr)->size > current->size)
        {
            swapped = true;
            prev = *ptr;
            *ptr = current;
            prev->next = current->next;
            current->next = prev;
        }
        prev = *ptr;
        current = prev->next->next;
        while (current != NULL)
        {
            if (prev->next->size > current->size)
            {
                swapped = true;
                tmp = prev->next;
                prev->next = current;
                tmp->next = current->next;
                current->next = tmp;
            }
            prev = prev->next;
            current = current->next;
        }
        if (!swapped)
            break;
    }
    printf("Ordering per size completed\n");
    return(0);
}
