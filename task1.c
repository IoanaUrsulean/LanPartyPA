#include"task1.h"

void readPlayerArray(Player *array, int intValue, FILE *read_file)
{
    char charBuff1[20], charBuff2[20];
    int intBuff;
	for(int j=0; j<intValue; j++)
    {
        fscanf(read_file, "%s%s%d", charBuff1, charBuff2, &intBuff);
        charBuff1[strlen(charBuff1)]='\0';
        charBuff2[strlen(charBuff2)]='\0';
        array[j].firstName = (char *)malloc(strlen(charBuff1)*sizeof(char));
        array[j].secondName = (char *)malloc(strlen(charBuff2)*sizeof(char));
        strcpy(array[j].firstName, charBuff1);
        strcpy(array[j].secondName, charBuff2);
        array[j].points = intBuff;
    }
}

void readTeamNode(teamNode **head, int intValue, char *charValue, FILE *read_file)
{
	teamNode *newNode = (teamNode*)malloc(sizeof(teamNode));
	newNode->val.numberOfPlayers = intValue;
    newNode->val.teamName = (char *)malloc(strlen(charValue)*sizeof(char));
    strcpy(newNode->val.teamName, charValue);
    newNode->val.playersArray = (Player *)malloc(intValue*sizeof(Player));
    readPlayerArray(newNode->val.playersArray, intValue, read_file );
	
    newNode->next = *head;
	*head = newNode;
}

void readList(char *caleDate, teamNode **head, int *numberOfTeams)
{
    FILE *read_file = fopen(caleDate, "rt");
    if(read_file == NULL){
        printf("ErRoR! CoUlD nOt OpEn ReAd_FiLe."); 
        exit(1);
    }

    fscanf(read_file, "%d", numberOfTeams);
    int intBuff;
    char charBuff[100];
    for(int i=0; i<(*numberOfTeams); i++)
    {
        fscanf(read_file, "%d", &intBuff);
        fgets(charBuff, 100, read_file);
        charBuff[strlen(charBuff)-1]='\0';
        strcpy(charBuff, charBuff+1);
        readTeamNode(&*head, intBuff, charBuff, read_file);
    }
    
    fclose(read_file);
}

void displayList(char *outputFilePath, teamNode *head, int numberOfTeams)
{
    FILE *display_file = fopen(outputFilePath, "wt");
    if(display_file == NULL){
        printf("ErRoR! CoUlD nOt OpEn ReAd_FiLe."); 
        exit(1);
    }

    for(int i=0; i<numberOfTeams; i++)
    {
        //printf("%d %s\n", head->val.numberOfPlayers, head->val.teamName);
        //for(int j=0; j<head->val.numberOfPlayers; j++)
        //    printf("%s %s %d\n", head->val.playersArray[j].firstName, head->val.playersArray[j].secondName, head->val.playersArray[j].points);
        fprintf(display_file, "%s\n", head->val.teamName);
        //getchar();
        head = head->next;
    }
    fclose(display_file);
}

void freeNodeList(teamNode **head)
{
   
    for(int i=0; i<(*head)->val.numberOfPlayers; i++)
    {
        free((*head)->val.playersArray[i].firstName);
        free((*head)->val.playersArray[i].secondName);    
    }
    free(((*head)->val.playersArray));
    free(((*head)->val.teamName));
    free(*head);
        
}

void deleteList(teamNode **head)
{
    teamNode *headcopy;
    while (* head != NULL )
    {
         
        headcopy =(*head)->next ;
        freeNodeList(&*head);
        *head = headcopy ;
    }
    * head = NULL ;
}

void freeMemory(teamNode **head, int *numberOfTeams, int *taskArray)
{ 
    deleteList(&*head);
    free(numberOfTeams);
    free(taskArray);
}   