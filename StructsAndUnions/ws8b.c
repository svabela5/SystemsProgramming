#include <stdio.h>
#include <string.h>

struct Persons {
    char id[10];
    short yob;
    char name[50];
};

int main(void)
{
    struct Persons p1, p2;

    // 1. Fill the first person with hardcoded values
    strcpy(p1.id, "A12345");
    p1.yob = 2005;
    strcpy(p1.name, "Sven Goran");

    // 2. Fill the second person with user input
    printf("Enter ID for person 2: ");
    scanf("%9s", p2.id); // limit to 9 characters

    printf("Enter year of birth for person 2: ");
    scanf("%hd", &p2.yob);

    printf("Enter name for person 2 (no spaces): ");
    scanf("%49s", p2.name); // limit to 49 characters (no spaces)

    // 3. Determine the older person (smaller year of birth)
    struct Persons older = (p1.yob < p2.yob) ? p1 : p2;

    // 4. Print the details of the older person
    printf("\n--- Older Person ---\n");
    printf("ID: %s\n", older.id);
    printf("Name: %s\n", older.name);
    printf("Year of Birth: %hd\n", older.yob);

    return 0;
}
