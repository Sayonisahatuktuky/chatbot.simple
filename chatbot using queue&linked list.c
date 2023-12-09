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
    ResponseNode* front;
    ResponseNode* rear;
} ResponseQueue;

void enqueue(ResponseQueue* queue, const char* keyword, const char* response, int transfer) {
    ResponseNode* newNode = (ResponseNode*)malloc(sizeof(ResponseNode));
    if (!newNode) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    newNode->keyword = keyword;
    newNode->response = response;
    newNode->transfer = transfer;
    newNode->next = NULL;

    if (queue->rear == NULL) {
        // If the queue is empty, set both front and rear to the new node
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        // Otherwise, add the new node to the rear of the queue
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

ResponseNode* dequeue(ResponseQueue* queue) {
    if (queue->front == NULL) {
        return NULL;  // Queue is empty
    }

    ResponseNode* frontNode = queue->front;
    queue->front = queue->front->next;

    if (queue->front == NULL) {
        // If the queue becomes empty after dequeue, set rear to NULL
        queue->rear = NULL;
    }

    return frontNode;
}

const char* getResponse(const char* userInput, ResponseQueue* queue) {
    char* lowercaseInput = strdup(userInput);
    if (!lowercaseInput) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; lowercaseInput[i]; i++) {
        lowercaseInput[i] = tolower(lowercaseInput[i]);
    }

    const char* result = "Chatbot: I'm sorry, I didn't understand that. Can you provide more information?";

    ResponseNode* current = queue->front;
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

void freeQueue(ResponseQueue* queue) {
    while (queue->front != NULL) {
        ResponseNode* temp = dequeue(queue);
        free(temp);
    }
}

int main() {
    char userInput[100];

    ResponseQueue responses;
    responses.front = NULL;
    responses.rear = NULL;

    // Enqueue responses
    enqueue(&responses, "hello", "Hello there!", 0);
    enqueue(&responses, "hi", "Hi! How can I assist you?", 0);
    enqueue(&responses, "how are you", "I'm just a computer program, but thanks for asking!", 0);
    enqueue(&responses, "transfer to support", "Sure! Transferring you to an official member. Please wait...", 1);
    enqueue(&responses, "goodbye", "Goodbye! Have a great day!", 0);
    enqueue(&responses, "what is your name", "I don't have a personal name. You can call me Chatbot.", 0);
    enqueue(&responses, "my name is shayoni", "Hello Shayoni! Nice to meet you.", 0);
    enqueue(&responses, "e-commerce", "For e-commerce related queries, you can check the specific online platform or contact their support.", 0);
    enqueue(&responses, "weather", "I'm sorry, I don't have real-time weather information. You may check a weather website or app.", 0);
    enqueue(&responses, "education", "For educational questions, you can refer to online educational resources or ask your teachers for assistance.", 0);
    // Add more responses as needed

    printf("Chatbot: Hello! How can I help you today?\n");

    while (1) {
        printf("User: ");
        fgets(userInput, sizeof(userInput), stdin);

        userInput[strcspn(userInput, "\n")] = 0;

        if (strcasecmp(userInput, "exit") == 0 || strcasecmp(userInput, "quit") == 0) {
            printf("Chatbot: Goodbye! Have a great day!\n");
            freeQueue(&responses);  // Free allocated memory before exiting
            break;
        }

        const char* response = getResponse(userInput, &responses);

        printf("Chatbot: %s\n", response);

        printf("Chatbot: Would you find this helpful? (yes/no): ");

        fgets(userInput, sizeof(userInput), stdin);
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
