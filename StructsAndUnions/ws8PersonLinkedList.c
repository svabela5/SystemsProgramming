#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

typedef struct Persons
{
    char name[50];
    char surname[50];
    char address[100];
    int  yob;
    struct Persons* next;
} person;

/* Head of the list. NULL means empty list */
person *list_head = NULL;

/* Retrieves the list head record or NULL if list is empty */
person* get_list_head(void) {
    return list_head;
}

/* Set first element of the list */
void set_list_head(person* new_head) {
    list_head = new_head;
}

//     _               _      
//    | |__   __ _ ___(_) ___ 
//    | '_ \ / _` / __| |/ __|
//    | |_) | (_| \__ \ | (__ 
//    |_.__/ \__,_|___/_|\___|

/* Finds the last allocation entry in list, or returns NULL if list is empty */
person* find_last(void) {
    if (get_list_head == NULL)
    {
        return NULL;
    }
    person* current = get_list_head();
    while (current->next != NULL)
    {
        current = current->next;
    }    
    return current;
}

/* Add a person to the end of the list */
void add_person_at_end(person* new_person) {
    if (new_person == NULL) return;

    if (get_list_head() == NULL) {
        set_list_head(new_person);
    } else {
        person* last = find_last();
        last->next = new_person;
    }
}

/* Prints a string representation of a person */
void print_person(person* p) {
    if (p == NULL) return;
    printf("Name: %s %s, Address: %s, Year of Birth: %d\n",
           p->name, p->surname, p->address, p->yob);
}

void print_list(void) {
    person* current = get_list_head();
    while (current != NULL)
    {
        print_person(current);
        current = current->next;
    }
}

/* Returns a pointer to the person at the specified index or NULL if nothing is there */
person* get_person_at_index(int index) {
    int i = 0;
    person* current = get_list_head();
    while (current != NULL)
    {
        if (i == index) {
            return current;
        }
        current = current->next;
        i++;
    }
    return NULL;
}

/* Remove a person from list and free memory. Return true if successful */
bool remove_person(person* p) {
    person* current = get_list_head();
    person* previous = NULL;
    while (current != NULL)
    {
        if (current == p) {
            if (previous == NULL) {
                // removing head
                set_list_head(current->next);
            } else {
                previous->next = current->next;
            }
            free(current);
            return true;
        }
        previous = current;
        current = current->next;
    }
    return false;
}

/* Remove the person at index from list and free memory. Return true if successful */
bool remove_person_at_index(int index) {
    person* current = get_list_head();
    person* previous = NULL;
    int i = 0;
    while (current != NULL)
    {
        if (i == index)
        {
            /* code */
            if (index == 0) {
            if (previous == NULL) {
                // removing head
                set_list_head(current->next);
            } else {
                previous->next = current->next;
            }
            free(current);
            return true;
        }
        }

        previous = current;
        current = current->next;
        index--;
    }
}

/* Frees all the persons in the list */
void free_list(void) {
    person* current = get_list_head();
    while (current != NULL)
    {
        person* next = current->next;
        free(current);
        current = next;
    }
    set_list_head(NULL);
}

/* Calculate the total number of persons in the list */
int count_list_size(void) {
    int total = 0;
    person* current = get_list_head();
    while (current != NULL)
    {
        total++;
        current = current->next;
    }
    return total;
}

//               _                               _ 
//      __ _  __| |_   ____ _ _ __   ___ ___  __| |
//     / _` |/ _` \ \ / / _` | '_ \ / __/ _ \/ _` |
//    | (_| | (_| |\ V / (_| | | | | (_|  __/ (_| |
//     \__,_|\__,_| \_/ \__,_|_| |_|\___\___|\__,_|

/* Add a person to the list at a specific index */
void add_person_at_index(person* new_person, int index) {
    if (new_person == NULL) return;

    if (index == 0) {
        new_person->next = get_list_head();
        set_list_head(new_person);
        return;
    }

    person* current = get_list_head();
    person* previous = NULL;
    int i = 0;
    while (current != NULL)
    {
        if (i == index)
        {
            previous->next = new_person;
            new_person->next = current;
            return;
        }
        
        previous = current;
        current = current->next;
        i++;
    }
}

/* Search the list for a particular name, return NULL if not found */
person* search_by_name(const char* name) {
    return NULL;
}

//     _            _   _             
//    | |_ ___  ___| |_(_)_ __   __ _ 
//    | __/ _ \/ __| __| | '_ \ / _` |
//    | ||  __/\__ \ |_| | | | | (_| |
//     \__\___||___/\__|_|_| |_|\__, |
//                              |___/ 

/* Generate an amount of identical persons - for testing purposes */
void generate_persons(int amount) {
    for (int i=0; i < amount; i++)
    {
        person* p = (person*)malloc(sizeof(person));
        sprintf (p->name, "John %d", i);
        strcpy(p->surname, "Doe");
        strcpy(p->address, "unknown");
        p->yob = 2000+i;
        add_person_at_end(p);
    }
}

int main (void) {
    
    //confirm that the list is empty when we start
    // assert (count_list_size() == 0);

    // //generate 10 persons and check that the count is 10
    // generate_persons(10);
    // assert (count_list_size() == 10);

    // //confirm that there is a person at index 0 and 9
    // assert (get_person_at_index(0) != NULL);
    // assert (get_person_at_index(9) != NULL);

    // //get the last person (index 9) and confirm yob
    // person *last = get_person_at_index(9);
    // assert (last->yob == 2009);

    // //remove last person and confirm it was successful
    // assert (remove_person_at_index(9) == true);
    // assert (count_list_size() == 9);

    // //free list and confirm count is zero
    // free_list();
    // assert (count_list_size() == 0);

    generate_persons(5);
    print_list();
    
    
    return 0;
}
