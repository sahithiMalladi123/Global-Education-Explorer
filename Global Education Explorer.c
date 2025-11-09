#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct Course {
    char name[100];
    char institutes[5][100];
    int numInstitutes;
    char fee[50];
    char jobMarket[200];
};
struct Country {
    char name[100];
    char currency[50];
    float conversionRate;
    struct Course courses[5];
    int numCourses;
};
struct Country countries[50];
int totalCountries = 0;
void saveToFile() {
    FILE *fp = fopen("education_database.txt", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(fp, "TotalCountries: %d\n\n", totalCountries);
    for (int i = 0; i < totalCountries; i++) {
        fprintf(fp, "Country: %s\n", countries[i].name);
        fprintf(fp, "Currency: %s\n", countries[i].currency);
        fprintf(fp, "Conversion: %.4f\n", countries[i].conversionRate);
        fprintf(fp, "Courses: %d\n", countries[i].numCourses);

        for (int j = 0; j < countries[i].numCourses; j++) {
            fprintf(fp, " Course: %s\n", countries[i].courses[j].name);
            fprintf(fp, " Institutes: %d\n", countries[i].courses[j].numInstitutes);
            for (int k = 0; k < countries[i].courses[j].numInstitutes; k++) {
                fprintf(fp, "  %s\n", countries[i].courses[j].institutes[k]);
            }
            fprintf(fp, " Fee: %s\n", countries[i].courses[j].fee);
            fprintf(fp, " JobMarket: %s\n", countries[i].courses[j].jobMarket);
        }
        fprintf(fp, "-----------------------------\n\n");
    }
    fclose(fp);
}
void loadFromFile() {
    FILE *fp = fopen("education_database.txt", "r");
    if (fp == NULL)
        return;
    fscanf(fp, "TotalCountries: %d\n", &totalCountries);
    for (int i = 0; i < totalCountries; i++) {
        fscanf(fp, "Country: %[^\n]\n", countries[i].name);
        fscanf(fp, "Currency: %[^\n]\n", countries[i].currency);
        fscanf(fp, "Conversion: %f\n", &countries[i].conversionRate);
        fscanf(fp, "Courses: %d\n", &countries[i].numCourses);
        for (int j = 0; j < countries[i].numCourses; j++) {
            fscanf(fp, " Course: %[^\n]\n", countries[i].courses[j].name);
            fscanf(fp, " Institutes: %d\n", &countries[i].courses[j].numInstitutes);
            for (int k = 0; k < countries[i].courses[j].numInstitutes; k++) {
                fscanf(fp, "  %[^\n]\n", countries[i].courses[j].institutes[k]);
            }

            fscanf(fp, " Fee: %[^\n]\n", countries[i].courses[j].fee);
            fscanf(fp, " JobMarket: %[^\n]\n", countries[i].courses[j].jobMarket);
        }
        fscanf(fp, "-----------------------------\n\n");
    }

    fclose(fp);
}
void listCountries() {
    if (totalCountries == 0) {
        printf("\nNo countries available.\n");
        return;
    }
    printf("\nAvailable Countries:\n");
    for (int i = 0; i < totalCountries; i++) {
        printf("%d. %s\n", i + 1, countries[i].name);
    }
}
void addCountry() {
    if (totalCountries >= 50) {
        printf("Cannot add more countries.\n");
        return;
    }
    struct Country c;
    printf("Enter country name: ");
    scanf(" %[^\n]", c.name);
    printf("Enter local currency: ");
    scanf(" %[^\n]", c.currency);
    printf("Enter conversion rate to INR: ");
    scanf("%f", &c.conversionRate);
    printf("Enter number of popular courses: ");
    scanf("%d", &c.numCourses);
    for (int i = 0; i < c.numCourses; i++) {
        printf("\nCourse %d name: ", i + 1);
        scanf(" %[^\n]", c.courses[i].name);
        printf("Enter number of top institutes: ");
        scanf("%d", &c.courses[i].numInstitutes);
        for (int j = 0; j < c.courses[i].numInstitutes; j++) {
            printf("Institute %d name: ", j + 1);
            scanf(" %[^\n]", c.courses[i].institutes[j]);
        }
        printf("Enter fee in %s: ", c.currency);
        scanf(" %[^\n]", c.courses[i].fee);
        printf("Enter job market info: ");
        scanf(" %[^\n]", c.courses[i].jobMarket);
    }
    countries[totalCountries++] = c;
    saveToFile();
    printf("\nCountry added successfully!\n");
}
void displayCountry(struct Country c) {
    printf("\n--- %s ---\n", c.name);
    printf("Currency: %s (1 %s = %.2f INR)\n", c.currency, c.currency, c.conversionRate);
    printf("Courses: %d\n", c.numCourses);
    for (int i = 0; i < c.numCourses; i++) {
        printf("\nCourse %d: %s\n", i + 1, c.courses[i].name);
        printf("Institutes:\n");
        for (int j = 0; j < c.courses[i].numInstitutes; j++) {
            printf("  - %s\n", c.courses[i].institutes[j]);
        }
        printf("Fee: %s %s\n", c.courses[i].fee, c.currency);
        printf("Job Market: %s\n", c.courses[i].jobMarket);
    }
}
void searchCountry() {
    listCountries();
    if (totalCountries == 0) return;
    char name[100];
    printf("\nEnter country name to search: ");
    scanf(" %[^\n]", name);
    for (int i = 0; i < totalCountries; i++) {
        if (strcmp(name, countries[i].name) == 0) {
            displayCountry(countries[i]);
            return;
        }
    }

    printf("Country not found.\n");
}
void updateCountry() {
    listCountries();
    if (totalCountries == 0) return;
    char name[100];
    printf("\nEnter country name to update: ");
    scanf(" %[^\n]", name);
    for (int i = 0; i < totalCountries; i++) {
        if (strcmp(name, countries[i].name) == 0) {
            printf("\n1. Update currency\n2. Update conversion rate\n3. Update course info\nEnter choice: ");
            int ch;
            scanf("%d", &ch);
            if (ch == 1) {
                printf("Enter new currency: ");
                scanf(" %[^\n]", countries[i].currency);
            } else if (ch == 2) {
                printf("Enter new conversion rate: ");
                scanf("%f", &countries[i].conversionRate);
            } else if (ch == 3) {
                for (int j = 0; j < countries[i].numCourses; j++) {
                    printf("%d. %s\n", j + 1, countries[i].courses[j].name);
                }
                printf("Choose course to update: ");
                int ci;
                scanf("%d", &ci);
                ci--;
                printf("\n1. Update course name\n2. Update institutes\n3. Update fee\n4. Update job market\nEnter choice: ");
                int sub;
                scanf("%d", &sub);
                if (sub == 1) {
                    printf("Enter new course name: ");
                    scanf(" %[^\n]", countries[i].courses[ci].name);
                } else if (sub == 2) {
                    printf("Enter number of institutes: ");
                    scanf("%d", &countries[i].courses[ci].numInstitutes);
                    for (int j = 0; j < countries[i].courses[ci].numInstitutes; j++) {
                        printf("Institute %d name: ", j + 1);
                        scanf(" %[^\n]", countries[i].courses[ci].institutes[j]);
                    }
                } else if (sub == 3) {
                    printf("Enter new fee: ");
                    scanf(" %[^\n]", countries[i].courses[ci].fee);
                } else if (sub == 4) {
                    printf("Enter new job market info: ");
                    scanf(" %[^\n]", countries[i].courses[ci].jobMarket);
                }
            }

            saveToFile();
            printf("Updated successfully!\n");
            return;
        }
    }

    printf("Country not found.\n");
}
void deleteCountry() {
    listCountries();
    if (totalCountries == 0) return;
    char name[100];
    printf("\nEnter country name to delete: ");
    scanf(" %[^\n]", name);
    for (int i = 0; i < totalCountries; i++) {
        if (strcmp(name, countries[i].name) == 0) {
            for (int j = i; j < totalCountries - 1; j++)
                countries[j] = countries[j + 1];
            totalCountries--;
            saveToFile();
            printf("Deleted successfully!\n");
            return;
        }
    }

    printf("Country not found.\n");
}
int main() {
    loadFromFile();
    int choice;
    do {
        printf("\n---- Global Education Explorer ----\n");
        printf("1. Add Country\n2. Search Country\n3. Update Country\n4. Delete Country\n5. Exit\n6. List All Countries\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: addCountry(); break;
            case 2: searchCountry(); break;
            case 3: updateCountry(); break;
            case 4: deleteCountry(); break;
            case 5: saveToFile(); printf("Exiting...\n"); break;
            case 6: listCountries(); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 5);
    return 0;
}
