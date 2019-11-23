// ************** P2 **************
// Algoritmo de evolução
// Aluno: Hugo Espinelli Amorim
// Professor: João

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_FILE_LENGTH 100

typedef struct skiplistnode{
    char *string;
    struct skiplistnode *next;
} skiplistnode;

skiplistnode *createNodeSkiplist(char *string) {
    skiplistnode *node = (skiplistnode *) malloc(sizeof(skiplistnode));
    node->next = NULL;
    node->string = string;
    return node;
};

char getRandAlpha() {
    char alpha[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
    int size = strlen(alpha);
    int n = rand() % size;
    return alpha[n];
}

int shouldBeMutated(int mutationRate) {
    int n = rand() % 100;
    return n <= mutationRate ? 1 : 0;
}

char *mutatePhrase(char *phrase, int mutationRate) {
    char *randomPhrase = (char *) malloc (sizeof(char) * (strlen(phrase)));
    strcpy(randomPhrase, phrase);
    for (int i = 0; phrase[i] != '\0'; i++) {
        randomPhrase[i] = shouldBeMutated(mutationRate) ? getRandAlpha() : phrase[i];
    }
    return randomPhrase;
}

char *generateRandomPhrase(char *phrase) {
    char *randomPhrase = (char *) malloc (sizeof(char) * (strlen(phrase)));
    int i;
    for (i = 0; phrase[i] != '\0'; i++) {
        randomPhrase[i] = getRandAlpha();
    }
    randomPhrase[i] = '\0';
    return randomPhrase;
}

int scorePopulation(char *phraseToBeScored, char *template) {
    int score = 0;
    for (; *phraseToBeScored != '\0'; template++, phraseToBeScored++) {

        if (*phraseToBeScored == *template) {
            score++;
        }

    }
    return score;
}

skiplistnode *createGeneration(skiplistnode *previousNode, char *basePhrase, int mutationRate, int organisms, int maxOrganism) {

    if (organisms == maxOrganism) {
        return NULL;
    }

    char *phrase = mutatePhrase(basePhrase, mutationRate);
    skiplistnode *node = createNodeSkiplist(phrase);
    previousNode->next = node;
    return createGeneration(node, basePhrase, mutationRate, organisms + 1, maxOrganism);
}

char *highestGene(skiplistnode *head, char *basePhrase) {
    skiplistnode *node = head;
    int score;
    char *bestPhrase;
    for (int maxScore = scorePopulation(head->string, basePhrase); node != NULL; node = node->next) {

        if (maxScore < (score = scorePopulation(node->string, basePhrase))) {
            maxScore = score;
            bestPhrase = node->string;
        }

    }
    return bestPhrase;
}

int isInvolved(skiplistnode *node, skiplistnode *nextnode, char *template) {
    if (nextnode != NULL) {
        int nextScore = scorePopulation(node->next->string, template);
        int score = scorePopulation(node->string, template);
        return score > nextScore;
    }

    return 0;
}

void printSkiplistContent(skiplistnode *node, char *template) {
    if (node == NULL) {
        return;
    }

    printSkiplistContent(node->next, template);
    printf("frase: %s ", node->string);
    printf("%s \n", isInvolved(node, node->next, template) ? "Oh, nao! Houve uma involucao!" : "");
}

void evolution(skiplistnode *node, char *template, int generations, int mutationRate) {
    skiplistnode *head = createNodeSkiplist("");
    createGeneration(head, node->string, mutationRate, 0, generations);
    char *s = highestGene(head, template);
    printf("A frase selecionada foi %s \n", s);

    skiplistnode *newNode = createNodeSkiplist(s);
    node->next = newNode;

    if (strcmp(template, s) == 0) {
        return;
    }

    evolution(newNode, template, generations, mutationRate);
}

char *fileRead(char *fileName) {
    char c, fileContent[MAX_FILE_LENGTH];
    int i = 0;
    FILE *fp = fopen(fileName, "r");
    while ((c = getc(fp)) != EOF && i < MAX_FILE_LENGTH) {
        fileContent[i++] = c;
    }
    fileContent[i] = '\0';
    fclose(fp);
    return strdup(fileContent);
}

int main(int argc, char *argv[]) {

    srand(time(NULL));

//  Default params
    char *template = "CELACANTO PROVOCA MAREMOTO";
    int generations = 100;
    int mutationRate = 5;

// Search script params
    char c, inTemplate[MAX_FILE_LENGTH] = {'\0'};
    int hasFile = 0, hasInTemplate = 0;
    while (--argc > 0 && (*++argv)[0]) {

        if ((*argv)[0] == '-') {
            c = *++argv[0];
            switch (c) {
                case 'p':
                    mutationRate = atoi(*argv+1);
                    break;
                case 'g':
                    generations = atoi(*argv+1);
                    break;
                case 'f':
                    hasFile = 1;
                    break;
                default:
                    printf("O argumento especificado nao foi encontrado.");
            }
            continue;
        }

        if (hasFile) {
            template = fileRead(*argv);
            hasFile = 0;
            continue;
        }

        hasInTemplate = 1;
        strcat(inTemplate, *argv);
        if (argc > 1) {
            strcat(inTemplate, " ");
        }

    }

    if (hasInTemplate) {
        template = inTemplate;
    }

    char *begin = generateRandomPhrase(template);
    printf("Frase final: %s \n", template);
    printf("Frase inicial: %s \n", begin);
    printf("mutacao %d \n", mutationRate);
    printf("geracao %d \n", generations);

//  Generate Evolution
    skiplistnode *head = createNodeSkiplist(begin);
    evolution(head, template, generations, mutationRate);
    printSkiplistContent(head, template);
    return 0;
}