#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Feedback {
    int studentID;
    char courseCode[20];
    int rating;  // 1-5
    char comments[100];
    struct Feedback *next;
} Feedback;
Feedback* createNode(int studentID, char courseCode[], int rating, char comments[]) {
    Feedback* newNode = (Feedback*)malloc(sizeof(Feedback));
    newNode->studentID = studentID;
    strcpy(newNode->courseCode, courseCode);
    newNode->rating = rating;
    strcpy(newNode->comments, comments);
    newNode->next = NULL;
    return newNode;
}
void addFeedback(Feedback **head, int studentID, char courseCode[], int rating, char comments[]) {
    Feedback *newNode = createNode(studentID, courseCode, rating, comments);
    newNode->next = *head;
    *head = newNode;
}
void displayFeedbacks(Feedback *head) {
    if (!head) {
        printf("No feedback available.\n");
        return;
    }
    Feedback *temp = head;
    while (temp) {
        printf("Student ID: %d, Course: %s, Rating: %d, Comments: %s\n",
               temp->studentID, temp->courseCode, temp->rating, temp->comments);
        temp = temp->next;
    }
}
void searchFeedback(Feedback *head, int studentID, char courseCode[]) {
    Feedback *temp = head;
    int found = 0;
    while (temp) {
        if ((studentID != -1 && temp->studentID == studentID) ||
            (strlen(courseCode) > 0 && strcmp(temp->courseCode, courseCode) == 0)) {
            printf("Found -> Student ID: %d, Course: %s, Rating: %d, Comments: %s\n",
                   temp->studentID, temp->courseCode, temp->rating, temp->comments);
            found = 1;
        }
        temp = temp->next;
    }
    if (!found) printf("No feedback found.\n");
}
void averageRating(Feedback *head, char courseCode[]) {
    Feedback *temp = head;
    int sum = 0, count = 0;
    while (temp) {
        if (strcmp(temp->courseCode, courseCode) == 0) {
            sum += temp->rating;
            count++;
        }
        temp = temp->next;
    }
    if (count > 0)
        printf("Average rating for course %s = %.2f\n", courseCode, (float)sum / count);
    else
        printf("No feedback found for course %s\n", courseCode);
}
Feedback* reverseList(Feedback *head) {
    Feedback *prev = NULL, *curr = head, *next = NULL;
    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}
Feedback* cloneList(Feedback *head) {
    if (!head) return NULL;
    Feedback *cloneHead = createNode(head->studentID, head->courseCode, head->rating, head->comments);
    Feedback *currClone = cloneHead, *currOrig = head->next;
    while (currOrig) {
        currClone->next = createNode(currOrig->studentID, currOrig->courseCode, currOrig->rating, currOrig->comments);
        currClone = currClone->next;
        currOrig = currOrig->next;
    }
    return cloneHead;
}
int main() {
    Feedback *head = NULL;
    int choice, studentID, rating;
    char courseCode[20], comments[100];
    Feedback *clonedList = NULL;
    do {
        printf("\n--- Student Feedback Tracking System ---\n");
        printf("1. Add Feedback\n");
        printf("2. Display All Feedback\n");
        printf("3. Search Feedback\n");
        printf("4. Average Feedback Rating per Course\n");
        printf("5. Reverse Feedback Display\n");
        printf("6. Clone Feedback Data\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // clear buffer
        switch (choice) {
            case 1:
                printf("Enter Student ID: ");
                scanf("%d", &studentID);
                getchar();
                printf("Enter Course Code: ");
                scanf("%s", courseCode);
                printf("Enter Rating (1-5): ");
                scanf("%d", &rating);
                getchar();
                printf("Enter Comments: ");
                fgets(comments, sizeof(comments), stdin);
                comments[strcspn(comments, "\n")] = '\0'; // remove newline
                addFeedback(&head, studentID, courseCode, rating, comments);
                break;
            case 2:
                displayFeedbacks(head);
                break;
            case 3:
                printf("Search by Student ID (enter -1 to skip): ");
                scanf("%d", &studentID);
                getchar();
                printf("Search by Course Code (enter empty string to skip): ");
                fgets(courseCode, sizeof(courseCode), stdin);
                courseCode[strcspn(courseCode, "\n")] = '\0';
                searchFeedback(head, studentID, courseCode);
                break;
            case 4:
                printf("Enter Course Code: ");
                scanf("%s", courseCode);
                averageRating(head, courseCode);
                break;
            case 5:
                head = reverseList(head);
                printf("Feedback list reversed.\n");
                break;
            case 6:
                clonedList = cloneList(head);
                printf("Cloned Feedback Data:\n");
                displayFeedbacks(clonedList);
                break;
            case 7:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice>=1&&choice<=7);
    return 0;
}
