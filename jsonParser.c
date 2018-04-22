#include "jsonParser.h"


/*int pullInfo(char *smallStr)
{
    //printf("%s\n", smallStr);
    int length = strlen(smallStr)+1;
    char *tmp = malloc(sizeof(char)*length);
    strncpy(tmp, smallStr, length); 
    //printf("\nInside\n");         
    //printf("\n%s\n", smallStr); 
    const char ma[] = ":";
    char *toked;
    toked = strtok(tmp, ma);

    while(toked != NULL)
    {   
        //printf("%s\n", toked);
        if(toked != NULL)
        {
            toked = strtok(NULL, ma);
            ///printf("\n%s\n",toked);
        }
    }

    free(tmp);
    printf("\n%s\n",smallStr);
    return 0;

}*/

int jsonParse(char *jsonStr)
{
    int length = strlen(jsonStr)+1;
    char *jstr = malloc(sizeof(char)*length);
    strcpy(jstr, jsonStr);    
    printf("\n%s\n", jsonStr); 
    char *tokenized;
    const char t[] = ",";
    tokenized = strtok(jstr, t);
    while(tokenized != NULL)
    {   
        //printf("\n-----------------------------------------------------\n");
        printf("%s    %d\n", tokenized, strlen(tokenized));
        if(!strncmp(tokenized, "\"main\"", 6))
        {            
            //printf("\nBefore\n");    
            //printf(tokenized);            
            //pullInfo(tokenized);  
            //printf("\nAfter\n");      
            printf(tokenized);
        }
        tokenized = strtok(NULL, t);
        
    }
    free(jstr);

    return 0;
}
