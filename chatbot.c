#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* keyword;
    const char* response;
    int transfer;
} Response;

const char* getResponse(const char* userInput, const Response responses[], int numResponses) {

    char lowercaseInput[100];
    strcpy(lowercaseInput, userInput);
    for (int i = 0; lowercaseInput[i]; i++) {
        lowercaseInput[i] = tolower(lowercaseInput[i]);
    }

    for (int i = 0; i < numResponses; i++) {

        char lowercaseKeyword[100];
        strcpy(lowercaseKeyword, responses[i].keyword);
        for (int j = 0; lowercaseKeyword[j]; j++) {
            lowercaseKeyword[j] = tolower(lowercaseKeyword[j]);
        }

        if (strstr(lowercaseInput, lowercaseKeyword) != NULL) {
            if (responses[i].transfer) {

                printf("Chatbot: Transferring you to an official member. Please wait...\n");

                printf("Chatbot: You are now connected to an official member.\n");
                exit(0);
            } else {
                return responses[i].response;
            }
        }
    }


    if (strstr(userInput, "do you know shayoni") != NULL) {
        return "Oh, shayoni! That's a lovely name. I'm pleased to inform you that I was created by her and her friend!She is a student of Daffodil International University of CSE department.";
    }
        if (strstr(userInput, "do you know debangshu") != NULL) {
        return "Oh, debangshu! That's a lovely name. I'm pleased to inform you that I was created by him with his friend Shayoni!";
    }

    return "I'm sorry, I didn't understand that. An official member will assist you.";
}

int main() {
    char userInput[100];

    Response responses[] = {
        {"hello", "hello there!", 0},
        {"hi", "hi! how can i assist you?", 0},
        {"how are you", "i'm just a computer program, but thanks for asking!", 0},
        {"transfer to support", "sure! transferring you to an official member. please wait...", 1},
        {"goodbye", "goodbye! have a great day!", 0},
        {"how are you going", "i'm doing well, thank you!",0},
        {"what is your name", "I don't have a personal name. You can call me Chatbot.", 0},
        {"what’s up", "not much, just here to help!",0},
        {"good morning", "good morning! how can i assist you today?",0},
        {"good evening", "good evening! how can i assist you right now?",0},
        {"good afternoon", "good afternoon! how can i assist you at the moment?",0},
        {"good night", "good night! if you have more questions, feel free to ask tomorrow!",0},
        {"tell me something", "sure! did you know that the world's largest desert is antarctica?",0},
        {"ok", "alright! if you have any more questions, feel free to ask.",0},
        {"yes", "great! how can i assist you further?",0},
        {"i’ll do that now", "thank you! if you have any issues, feel free to ask for help.",0},
        {"thank you", "you're welcome! if you have more questions, feel free to ask.",0},
        {"goodbye", "goodbye! have a great day!",0},
        {"how can you help me", "i can provide information and answer your questions. how can i assist you today?",0},
        {"what can you do", "i can provide information, answer questions, and have general conversations. how can i assist you?",0},
        {"do you have girlfriend", "no, i am a AI Assistant i don't have girlfriend but my creater has girlfriend, she is devi and he loves her so much",0},
        {"hi, my name is", "nice to meet you, [user's name]! how can i assist you today?",0},
        {"happy birthday", "happy birthday! wishing you a fantastic day!",0},
        {"i have a question", "sure, go ahead! what would you like to know?",0},
        {"can you help me", "of course! what do you need assistance with?",0},
        {"what is your mother’s name", "i don't have a mother, as i am a computer program.",0},
        {"where do you live", "i exist in the digital world and don't have a physical location.",0},
        {"how many people can you speak to at once", "i can interact with multiple users simultaneously.",0},
        {"what’s the weather like today", "i'm sorry, i don't have real-time information. you may check a weather website or app.",0},
        {"do you have a job for me", "i don't have job opportunities, but you can explore job websites or check with local companies.",0},
        {"where can i apply", "you can apply for jobs on various online platforms or directly on company websites.",0},
        {"are you expensive", "i'm a free service! you don't need to pay anything to interact with me.",0},
        {"who’s your boss", "i don't have a boss or master. i'm a program created to assist users.",0},
        {"do you get smarter", "i don't inherently get smarter, but updates may improve my functionality over time.",0},
        {"e-commerce", "For e-commerce questions, please specify your inquiry, such as product information, order status, or assistance with the website.", 0},
        {"weather", "I'm sorry, I don't have real-time weather information. You may check a weather website or app for the latest updates.", 0},
        {"educational", "For educational queries, feel free to ask about specific topics, courses, or learning resources.", 0},


    };

    int numResponses = sizeof(responses) / sizeof(responses[0]);
    printf("Chatbot: Hello! How can I help you today?\n");

    while (1) {
        printf("User: ");
        fgets(userInput, sizeof(userInput), stdin);

        userInput[strcspn(userInput, "\n")] = 0;

        if (strcmp(userInput, "exit") == 0 || strcmp(userInput, "quit") == 0) {
            printf("Chatbot: Goodbye! Have a great day!\n");
            break;
        }

        const char* response = getResponse(userInput, responses, numResponses);
        printf("Chatbot: %s\n", response);
        printf("Chatbot: Would you find this helpful? (yes/no): ");


        fgets(userInput, sizeof(userInput), stdin);
        userInput[strcspn(userInput, "\n")] = 0;


        if (strcmp(userInput, "yes") == 0) {
            printf("Chatbot: That's great to hear! If you have more questions, feel free to ask.\n");
        } else if (strcmp(userInput, "no") == 0) {
            printf("Chatbot: I'm sorry to hear that. Please provide feedback on how I can improve.\n");
        } else {
            printf("Chatbot: I didn't understand your feedback. If you have more information, please let me know.\n");
        }
    }

    return 0;
}
