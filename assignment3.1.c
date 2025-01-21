#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Finds a specific name in the array that the user entered
int findName(char **nameList, int nameCount, char *searchName) {
    for (int i = 0; i < nameCount; ++i) {
        //Compares each index of the array with the name the user entered to find
        if (strcmp(nameList[i], searchName) == 0) {
            return i;
        }
    }
return -1;
}

//Removes a specific name that the user entered
int removeName(char ***nameList, int *nameCount, char *removeName) {
    int index = findName(*nameList, *nameCount, removeName);
    if (index != -1) {
        free((*nameList)[index]);
        //Moves all elemets to the correct positions after removing the specified
        //name
        for (int i = index; i < (*nameCount) - 1; ++i) {
            (*nameList)[i] = (*nameList)[i + 1];
        }
        (*nameCount)--;
        *nameList = realloc(*nameList, (*nameCount) * sizeof(char*));
    }
}

//Expands the array once the maximum ammount of names has been entered
int expandArray(char ***nameList, int *arraySize) {
    *arraySize *= 2;
    *nameList = realloc(*nameList, (*arraySize) * sizeof(char*));
}

//Prints out the array of the names the user entered
int printListwhich(char **nameList, int nameCount) {
    printf("List has %d names: ", nameCount);
    for (int i = 0; i < nameCount; ++i) {
        printf("\n%s ", nameList[i]);
    }
    printf("\n");
}

int main() {
    //Initializes the dynamic array
    char **nameList = malloc(4 * sizeof(char*));
    int arraySize = 4;
    int nameCount = 0;
    //Prompts the user to enter a name
    printf("Please enter a name: ");
    char userInput[1000];
    //Prompts the user to enter names to add to the array until they enter "Done"
    //into the prompt
    while (scanf("%s", userInput) == 1 && strcmp(userInput, "Done") != 0) {
        //Doubles the array size if more than 4 names are entered
        if (nameCount >= arraySize) {
            expandArray(&nameList, &arraySize);
        }
        nameList[nameCount] = malloc((strlen(userInput) + 1) * sizeof(char));
        //Copies the user input to the index in nameList
        strcpy(nameList[nameCount], userInput);
        nameCount++;
        printf("Please enter a name to add: ");
    }
    //Prints the first list of names entered by the user
    printListwhich(nameList, nameCount);
    //Prompts the user to enter a name to find in the array
    printf("Please enter the name you want to find: ");
    scanf("%s", userInput);
    int foundIndex = findName(nameList, nameCount, userInput);
    //Prints the location of the specified name in the index
    if (foundIndex != -1) {
        printf("Found that name at index %d\n", foundIndex);
    }
    //Prints that the name couldn't be found if the user enters a name that isn't
    //present in the array
    else {
        printf("Name is not in array\n");
    }
    //Prompts the user to enter a name they wish to remove from the array
    printf("Please enter the name you want to remove: ");
    scanf("%s", userInput);
    //Removes the name from the array and re-prints the list with the updated array
    removeName(&nameList, &nameCount, userInput);
    printListwhich(nameList, nameCount);
    for (int i = 0; i < nameCount; ++i) {
        free(nameList[i]);
    }
    free(nameList);
    return 0;
}

//Assignment 3.1
//2024 Logan Kerner <lo660771@ucf.edu>