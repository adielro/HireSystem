// Adiel Rozenfeld - 208349019
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 20

int employeesSize = 0, candidatesSize = 0, exitProg = 0;

// Recommender struct, contains first name, last name and email.
typedef struct recommender {
    char firstName[N];
    char lastName[N];
    char email[N];
}Recommender;

// Developer struct, contains first name, last name, degree, 2 recommenders from inside the company and 2 recommenders outside the company.
typedef struct developer {
    char firstName[N];
    char lastName[N];
    char degree[N];
    Recommender* outsideRecA;
    Recommender* outsideRecB;
    struct developer* recommenderA;
    struct developer* recommenderB;
}Developer;
void printCandidates(Developer*[]);
void printWorkers(Developer*[]);
void addCandidate(Developer*[], Developer*[]);
int validString(char[]);
int validWorker(Developer*[], char[], char[]);
void hireCandidate(Developer*[], Developer*[]);
void freeAll(Developer*[], Developer*[]);
int validCandidate(Developer*[], char[], char[]);
int main() {
    candidatesSize = 0;
    Developer* employees[N], *candidates[N];


            printf("Welcome, what do you want to do?\n");
            while(!exitProg){
    printf("1. Print candidates.\n");
    printf("2. Print workers.\n");
    printf("3. insert new candidate.\n");
    printf("4. Hire candidate.\n");
    printf("5. Exit.\n");
    int userChoice = 0;
    scanf("%d", &userChoice);
    switch (userChoice){
        case 1:
            printCandidates(candidates);
            break;
        case 2:
            printWorkers(employees);
            break;
        case 3:
            addCandidate(candidates, employees);
            break;
        case 4:
            hireCandidate(employees, candidates);
            break;
        case 5:
            exitProg = 1;
            printf("Good bye.");
            freeAll(candidates, employees);
            break;
        default:
            printf("Invalid choice.\nSystem shut down.");
            exitProg = 1;
    }}
    return 0;
}
// Method goes through the candidates array printing all the candidates.
void printCandidates(Developer* candidates[]){
    for (int i = 0; i < candidatesSize;i++){
        printf("Candidate number %d\n", i+1);
        printf("Full name: %s %s\n", candidates[i]->firstName, candidates[i]->lastName);
        printf("Degree: %s\n", candidates[i]->degree);
        printf("Employees recommenders:\n");
        if (candidates[i] -> recommenderA != NULL)
            printf("Full name: %s %s\n", candidates[i] -> recommenderA -> firstName, candidates[i] -> recommenderA ->lastName);
        if (candidates[i] -> recommenderB != NULL)
            printf("Full name: %s %s\n", candidates[i] -> recommenderB -> firstName, candidates[i] -> recommenderB ->lastName);
        if (candidates[i] -> recommenderA == NULL && candidates[i] -> recommenderB == NULL)
            printf("None.\n");
        printf("Outside recommenders:\n");
        if (candidates[i] -> outsideRecA != NULL)
            printf("Full name:  %s %s\nEmail: %s\n", candidates[i] -> outsideRecA -> firstName, candidates[i] -> outsideRecA ->lastName, candidates[i] -> outsideRecA -> email);
        if (candidates[i] -> outsideRecB != NULL)
            printf("Full name:  %s %s\nEmail: %s\n", candidates[i] -> outsideRecB -> firstName, candidates[i] -> outsideRecB ->lastName, candidates[i] -> outsideRecB -> email);
        if (candidates[i] -> outsideRecA == NULL && candidates[i] -> outsideRecB == NULL)
            printf("None.\n");
    }
    if (candidatesSize == 0)
        printf("None\n-----------------------------------\n");
}
// Method goes through the employees array printing all the workers.
void printWorkers(Developer* employees[]){
    printf("Workers list:\n");
    for (int i = 0; i < employeesSize; i++) {
        printf("%d: %s %s\n", i+1, employees[i] -> firstName, employees[i] -> lastName);
    }
    if (employeesSize == 0)
        printf("None\n-----------------------------------\n");
    else
        printf("-----------------------------------\n");
}
// Method receives from the user a new candidate info: full name, degree, recommenders from inside the company and outside the company (2 max of each, may take 1 or none).
// Method is making sure the received strings are all valid (string max length is 20) and also making sure the recommenders from inside the company are valid (listed in the employees array).
// If everything checks out, the candidate will be added to the candidate array.
void addCandidate(Developer* candidates[], Developer* employees[]){
    if (candidatesSize>N){
        printf("Candidate list is full.");
        return;
    }
    candidates[candidatesSize] = (Developer*)malloc(sizeof(Developer));
    char temp[100];
    char first[100];
    char last[100];
    char mail[100];
    tryAgain:
    printf("First name: ");
    scanf("%s", temp);
    if (!validString(temp)){
            goto tryAgain;
    }
    strcpy(candidates[candidatesSize] -> firstName, temp);

    printf("Last name: ");
    scanf("%s", temp);
    if (!validString(temp)){
        goto tryAgain;
    }
    strcpy(candidates[candidatesSize] -> lastName, temp);
    printf("Degree: ");
    scanf("%s", temp);
    if (!validString(temp)){
        goto tryAgain;
    }
    strcpy(candidates[candidatesSize] -> degree, temp);
    printf("If there is a recommender inside the company, please enter his details, if not, type 0.\n");
    printf("First name: ");
    scanf("%s", first);
    if (strcmp(first, "0") == 0)
        goto outsideRecommenders;
    if (!validString(first))
        goto tryAgain;
    printf("Last name: ");
    scanf("%s", last);
    if (!validString(last))
        goto tryAgain;
    int workerNum = validWorker(employees, first, last);
    if (workerNum!=-1)
        candidates[candidatesSize] -> recommenderA = employees[workerNum];
    else
        candidates[candidatesSize] -> recommenderA = NULL;
    printf("if there is a second recommender inside the company, please enter his details, if not, type 0.\n");
    printf("First name: ");
    scanf("%s", first);
    if (strcmp(first, "0") == 0)
        goto outsideRecommenders;
    if (!validString(first))
        goto tryAgain;
    printf("Last name: ");
    scanf("%s", last);
    if (!validString(last))
        goto tryAgain;
    workerNum = validWorker(employees, first, last);
    if (workerNum!=-1)
        candidates[candidatesSize] -> recommenderB = employees[workerNum];
    else
        candidates[candidatesSize] -> recommenderB = NULL;
    outsideRecommenders:
    printf("If there is a recommender outside of the company, please enter his details, if not, type 0.\n");
    printf("First name: ");
    scanf("%s", first);
    if (strcmp(first, "0") == 0){
        candidates[candidatesSize] -> outsideRecA = candidates[candidatesSize] ->outsideRecB = NULL;
        goto end;}
    if (!validString(first))
        goto tryAgain;
    printf("Last name: ");
    scanf("%s", last);
    if (!validString(last))
        goto tryAgain;
    printf("Email: ");
    scanf("%s", mail);
    if (!validString(mail))
        goto tryAgain;
    candidates[candidatesSize] -> outsideRecA = (Recommender*)malloc(sizeof(Recommender));
    strcpy(candidates[candidatesSize] -> outsideRecA -> firstName ,first);
    strcpy(candidates[candidatesSize] -> outsideRecA -> lastName, last);
    strcpy(candidates[candidatesSize] -> outsideRecA -> email, mail);
    printf("If there is a second recommender outside of the company, please enter his details, if not, type 0.\n");
    printf("First name: ");
    scanf("%s", first);
    if (strcmp(first, "0") == 0){
        candidates[candidatesSize] -> outsideRecB = NULL;
        goto end;}
    if (!validString(first))
        goto tryAgain;
    printf("Last name: ");
    scanf("%s", last);
    if (!validString(last))
        goto tryAgain;
    printf("Email: ");
    scanf("%s", mail);
    if (!validString(mail))
        goto tryAgain;
    candidates[candidatesSize] -> outsideRecB = (Recommender*)malloc(sizeof(Recommender));
    strcpy(candidates[candidatesSize] -> outsideRecB -> firstName ,first);
    strcpy(candidates[candidatesSize] -> outsideRecB -> lastName, last);
    strcpy(candidates[candidatesSize] -> outsideRecB -> email, mail);
    end:
    candidatesSize++;
}
// Method receives a string and making sure it's no longer then 20 chars, return 1 if valid, 0 if invalid.
int validString(char s[]){
    if (strlen(s)>N){
        printf("Maximum length is 20, please try again.\n");
        return 0;
    }
    return 1;
}
// Method receives first and last name and check if there is a valid worker in the employees array answering that name.
int validWorker(Developer* employees[], char first[], char last[]){
    int addFlag = 0;
    for (int i = 0; i < employeesSize; i++)
        if (strcmp(employees[i]->firstName, first) == 0)
            if (strcmp(employees[i]->lastName, last) == 0){
                return i;
            }
    return -1;
}
// Method asks from the user for the candidate name he would like to hire, sending it to validCandidate to make sure it's a valid candidate.
// then add it to the employees array and deleting it from the candidate array.
void hireCandidate(Developer* employees[], Developer* candidates[]){
    if (employeesSize>N){
        printf("Workers list is full.");
        return;
    }
    char first[N];
    char last[N];
    typeAgain:
    printf("First name: ");
    scanf("%s", first);
    if (!validString(first)){
        printf("Maximum length is 20, please try again.\n");
        goto typeAgain;}
    printf("Last name: ");
    scanf("%s", last);
    if (!validString(last)){
        printf("Maximum length is 20, please try again.\n");
        goto typeAgain;}
    int candidateIndex = validCandidate(candidates, first, last);
    if(candidateIndex == -1){
        printf("Invalid candidate!\n");
        return;}
    employees[employeesSize] = candidates[candidateIndex];
    free(employees[employeesSize] -> outsideRecA);
    free(employees[employeesSize] -> outsideRecB);
    employees[employeesSize] -> recommenderA = employees[employeesSize] -> recommenderB = NULL;
    employees[employeesSize] -> outsideRecA= employees[employeesSize] -> outsideRecB = NULL;
    candidates[candidateIndex] = candidates[candidatesSize];
    candidates[candidatesSize--] = NULL;
    employeesSize++;
}
// Method check if the candidate details (first and last name) represent a listed candidate in the candidates array, if it is, return the index of the candidate, else return -1.
int validCandidate(Developer* candidates[], char first[], char last[]){
    for (int i = 0; i < candidatesSize; ++i) {
        if (strcmp(candidates[i] -> firstName, first) == 0)
            if (strcmp(candidates[i] -> lastName, last) == 0)
                return i;
    }
    return -1;
}
// Method going through all candidates and employees arrays and free them one by one, if there are outside recommenders, free them first.
void freeAll(Developer* candidates[], Developer* employees[]){
    for (int i = 0; i < candidatesSize; i++) {
        if (candidates[i] -> outsideRecA != NULL){
            free(candidates[i] -> outsideRecA);
            candidates[i] -> outsideRecA = NULL;
        }
        if (candidates[i] -> outsideRecB != NULL){
            free(candidates[i] -> outsideRecB);
            candidates[i] -> outsideRecB = NULL;
        }
        free(candidates[i]);
        candidates[i] = NULL;
    }
    for (int i = 0; i < employeesSize; i++) {
        free(employees[i]);
        employees[i] = NULL;
    }
}
