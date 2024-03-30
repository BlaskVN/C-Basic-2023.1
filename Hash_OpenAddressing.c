#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 128

typedef struct {
    int id;
    char name[MAX_LEN];
} Student;

int linear_probe(int id, int m, int i) {
    return ((id + i) % m);
}

int quadratic_probe(int id, int m, int c1, int c2, int i) {
    return (id + c1 * i + c2 * i * i) % m;
}

int double_hashing(int id, int i, int m) {
    int h1 = id % 13;
    int h2 = 7 - (id % 7);
    return (h1 + i * h2) % m;
}

void insert_student(Student** arr, int id, char* name, char* probing_type, int m, int c1, int c2) {
    int index;
    int i = 0;
    do {
        if (strcmp(probing_type, "linear") == 0) {
            index = linear_probe(id, m, i);
        } else if (strcmp(probing_type, "quadratic") == 0) {
            index = quadratic_probe(id, m, c1, c2, i);
        } else if (strcmp(probing_type, "double") == 0) {
            index = double_hashing(id, i, m);
        } else {
            printf("Invalid probing type.\n");
            return;
        }
        i++;
    } while (arr[index] != NULL && i < m);

    if (i == m) {
        printf("Hash table is full.\n");
        return;
    }

    Student* student = (Student*)malloc(sizeof(Student));
    student->id = id;
    strcpy(student->name, name);
    arr[index] = student;
}

void search_student(Student** arr, int id, char* probing_type, int m, int c1, int c2) {
    int index;
    if (strcmp(probing_type, "linear") == 0) {
        index = linear_probe(id, m, 0);
    } else if (strcmp(probing_type, "quadratic") == 0) {
        index = quadratic_probe(id, m, c1, c2, 0);
    } else if (strcmp(probing_type, "double") == 0) {
        index = double_hashing(id, 0, m);
    } else {
        printf("Invalid probing type.\n");
        return;
    }

    int i = 0;
    while (arr[index] != NULL && i < m) {
        if (arr[index]->id == id) {
            printf("Found student name %s id %d at position %d.\n", arr[index]->name, arr[index]->id, index);
            return;
        }
        if (strcmp(probing_type, "linear") == 0) {
            index = linear_probe(id, m, i);
        } else if (strcmp(probing_type, "quadratic") == 0) {
            index = quadratic_probe(id, m, c1, c2, i);
        } else if (strcmp(probing_type, "double") == 0) {
            index = double_hashing(id, i, m);
        }
        i++;
    }

    printf("Id %d not found.\n", id);
}

void print_students(Student** arr, int m) {
    for (int i = 0; i < m; i++) {
        if (arr[i] != NULL) {
            printf("%s ", arr[i]->name);
        }
    }
    printf("\n");
}

int main() {
    int m, c1 = 0, c2 = 0;
    char probing_type[10];
    scanf("%d %s", &m, probing_type);

    if (strcmp(probing_type, "quadratic") == 0) {
        scanf("%d %d", &c1, &c2);
    } else if (strcmp(probing_type, "linear") != 0 && strcmp(probing_type, "double") != 0 && strcmp(probing_type, "quadratic") != 0) {
        printf("Invalid probing type.\n");
        return 0;
    }

    Student** arr = (Student**)malloc(m * sizeof(Student*));
    for (int i = 0; i < m; i++) {
        arr[i] = NULL;
    }

    for (int i = 0; i < m; i++) {
        int id;
        char name[MAX_LEN];
        scanf("%d %s", &id, name);
        insert_student(arr, id, name, probing_type, m, c1, c2);
    }

    char command[MAX_LEN];
    while (scanf("%s", command) != EOF) {
        if (strcmp(command, "Search") == 0) {
            int id;
            if (scanf("%d", &id) != 1) {
                printf("Invalid command.\n");
                scanf("%*[^\n]");
                getchar();
                continue;
            }
            search_student(arr, id, probing_type, m, c1, c2);
        } else if (strcmp(command, "Print") == 0) {
            print_students(arr, m);
        } else if (strcmp(command, "Quit") == 0) {
            break;
        } else {
            printf("Invalid command.\n");
            scanf("%*[^\n]");
            getchar();
        }
    }

    for (int i = 0; i < m; i++) {
        if (arr[i] != NULL) {
            free(arr[i]);
        }
    }
    free(arr);

    return 0;
}