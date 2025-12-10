#include <stdio.h>

// Define the structure for a Person
struct Person {
    char name[50];
    int age;
    float height; // in meters
    char city[50];
};

int main() {
    // Declare a variable of type 'struct Person'
    struct Person p1;

    // Read the person's details
    printf("Enter name: ");
    scanf("%49s", p1.name); // Read string up to 49 chars
    printf("Enter age: ");
    scanf("%d", &p1.age);
    printf("Enter height (in meters): ");
    scanf("%f", &p1.height);
    printf("Enter city: ");
    scanf("%49s", p1.city); // Read string up to 49 chars

    // Print the person's details
    printf("\n--- Person Details ---\n");
    printf("Name: %s\n", p1.name);
    printf("Age: %d years\n", p1.age);
    printf("Height: %.2f m\n", p1.height);
    printf("City: %s\n", p1.city);

    return 0;
}