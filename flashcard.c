#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void add();
void review();

struct qna {
    char ques[100];
    char ans[100];
};

int main() {
    int choose;
    while (1) {
        printf("Enter 1 to add flashcards, 2 to review them, 0 to exit: ");
        scanf("%d", &choose);
        switch (choose) {
            case 1:
                add();
                break;
            case 2:
                review();
                break;
            case 0:
                return 0; 
            default:
                printf("Invalid choice! Please try again.\n");
                break;
        }
    }
}

void add() {
    char subject[50];
    int i, n;
    char filename[60];
    FILE *file;
    
    printf("Enter the name of the subject: ");
    scanf("%s", subject);
    strcat(subject, ".txt");
    file = fopen(subject, "w");
    if (file != NULL) {
        printf("Enter the number of questions to add: ");
        scanf("%d", &n);
        struct qna ques[n];
        for (i = 0; i < n; i++) {
            printf("Enter question %d: \n", i + 1);
            scanf(" %[^\n]", ques[i].ques); // Read entire line for question
            fputs("Q: ", file);
            fputs(ques[i].ques, file);
            fputs("\n", file);
            
            printf("Enter the answer: \n");
            scanf(" %[^\n]", ques[i].ans); // Read entire line for answer
            fputs("A: ", file);
            fputs(ques[i].ans, file);
            fputs("\n", file);
            printf("\t*FLASHCARD SAVED SUCCESSFULLY*\n");
        }
        fclose(file);
    }
}

void review() {
    char subject[50];
    FILE *file;
    int i, c = 0;
    printf("Enter the name of the subject you want to review flashcards for: ");
    scanf("%s", subject);
    strcat(subject, ".txt");
    file = fopen(subject, "r");
    if (file != NULL) {
        char line[200];
        while (fgets(line, sizeof(line), file) != NULL) {
            printf("%s", line);
            if (line[0] == 'Q') {
                printf("Press Enter to see the answer...\n");
                while (getchar() != '\n'); // Wait for Enter key
            }
            else if (line[0] == 'A') {
                char ch[10];
                printf("Did you get that right (yes/no)? ");
                scanf("%s", ch);
                if (strcmp(ch, "yes") == 0) {
                    c++;
                }
            }
            while (getchar() != '\n');
        }
        printf("\t\t you got %d questions rightc\n\n",c);
    }
    fclose(file); 
}