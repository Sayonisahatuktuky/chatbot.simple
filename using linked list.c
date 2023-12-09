#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct ResponseNode {
    const char* keyword;
    const char* response;
    int transfer;
    struct ResponseNode* next;
} ResponseNode;

typedef struct {
    ResponseNode* head;
} ResponseList;

void addResponse(ResponseList* list, const char* keyword, const char* response, int transfer) {
    ResponseNode* newNode = (ResponseNode*)malloc(sizeof(ResponseNode));
    if (!newNode) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    newNode->keyword = keyword;
    newNode->response = response;
    newNode->transfer = transfer;
    newNode->next = list->head;

    list->head = newNode;
}

const char* getResponse(const char* userInput, const ResponseList* list) {
    char* lowercaseInput = strdup(userInput);
    if (!lowercaseInput) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; lowercaseInput[i]; i++) {
        lowercaseInput[i] = tolower(lowercaseInput[i]);
    }

    const char* result = "Chatbot: I'm sorry, I didn't understand that. Can you provide more information?";

    ResponseNode* current = list->head;
    while (current != NULL) {
        if (strstr(lowercaseInput, current->keyword) != NULL) {
            if (current->transfer) {
                printf("Chatbot: Transferring you to an official member. Please wait...\n");
                printf("Chatbot: You are now connected to an official member.\n");
                free(lowercaseInput);
                exit(EXIT_SUCCESS);
            } else {
                result = current->response;
                break;
            }
        }
        current = current->next;
    }

    free(lowercaseInput);
    return result;
}

void freeList(ResponseNode* head) {
    while (head != NULL) {
        ResponseNode* temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    char userInput[100];

    ResponseList responses;
    responses.head = NULL;

    // Adding responses to the linked list
    addResponse(&responses, "hello", "Hello there!", 0);
    addResponse(&responses, "hi", "Hi! How can I assist you?", 0);
    addResponse(&responses, "how are you", "I'm just a computer program, but thanks for asking!", 0);
    addResponse(&responses, "transfer to support", "Sure! Transferring you to an official member. Please wait...", 1);
    addResponse(&responses, "goodbye", "Goodbye! Have a great day!", 0);
    addResponse(&responses, "what is your name", "I don't have a personal name. You can call me Chatbot.", 0);
    addResponse(&responses, "my name is shayoni", "Hello Shayoni! Nice to meet you.", 0);
    addResponse(&responses, "e-commerce", "For e-commerce related queries, you can check the specific online platform or contact their support.", 0);
    addResponse(&responses, "weather", "I'm sorry, I don't have real-time weather information. You may check a weather website or app.", 0);
    addResponse(&responses, "education", "For educational questions, you can refer to online educational resources or ask your teachers for assistance.", 0);
    // Add more responses as needed

    printf("Chatbot: Hello! How can I help you today?\n");

    while (1) {
        printf("User: ");
        fgets(userInput, sizeof(userInput), stdin);

        userInput[strcspn(userInput, "\n")] = 0;

        if (strcasecmp(userInput, "exit") == 0 || strcasecmp(userInput, "quit") == 0) {
            printf("Chatbot: Goodbye! Have a great day!\n");
            freeList(responses.head);  // Free allocated memory before exiting
            break;
        }

        const char* response = getResponse(userInput, &responses);

        printf("Chatbot: %s\n", response);

        printf("Chatbot: Would you find this helpful? (yes/no): ");

        fgets(userInput, sizeof(userInput), stdin);`
        userInput[strcspn(userInput, "\n")] = 0;

        if (strcasecmp(userInput, "yes") == 0) {
            printf("Chatbot: That's great to hear! If you have more questions, feel free to ask.\n");
        } else if (strcasecmp(userInput, "no") == 0) {
            printf("Chatbot: I'm sorry to hear that. Please provide feedback on how I can improve.\n");
        } else {
            printf("Chatbot: I didn't understand your feedback. If you have more information, please let me know.\n");
        }
    }

    return 0;
}
