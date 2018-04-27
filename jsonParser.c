#include "jsonParser.h"





//Auxilalry  functions
void print_table(jtable jsonTab)
{
    int i = 0;
    while(i < jsonTab.count)
    {
        printf("\n%s\n", jsonTab.jsonTable[i++]); 
    }
}

void print_weather(wdata wda)
{
    //Will soon change to work on assumption of receiving Farenheigt
    printf("\nThe weather is %s\nThe temperature is %s\n", wda.weather, wda.temp);
}

///Useful functions
int jsonParse(jtable jsonTab, wdata *wdat)
{
    int dlength = strlen("\"description\":\"");
    int mlength = strlen("\"main\":{\"temp\":");
    //printf("%d", mlength);
    for(int i = 0; i < jsonTab.count; i++)
    {         
       if(!strncmp(jsonTab.jsonTable[i], "\"description\":\"", dlength))
       {            
            for(int j = dlength; j < strlen(jsonTab.jsonTable[i])-1; j++)
            {
                wdat->weather[j-dlength] = jsonTab.jsonTable[i][j]; 
            }          
            for(int k = (strlen(jsonTab.jsonTable[i])-1); k < 50; k++)
            {
                wdat->weather[k-dlength] = '\0';

            }
            //wdat->weather[(strlen(jsonTab.jsonTable[i])-dlength)] = '\0';          
       }       
        if(!strncmp(jsonTab.jsonTable[i], "\"main\":{\"temp\":", mlength))
       {            

            for(int j = mlength; j < strlen(jsonTab.jsonTable[i]); j++)
            {
                wdat->temp[j-mlength] = jsonTab.jsonTable[i][j]; 
            }               
            for(int k = (strlen(jsonTab.jsonTable[i])-1); k < 50; k++)
            {
                wdat->temp[k-mlength] = '\0';

            }
            //wdat->temp[(strlen(jsonTab.jsonTable[i])-mlength)] = '\0';          
       }
    }

    return 0;
}


void free_jTable(jtable *jsonTab)
{
    for(int i=0; i <= jsonTab->count; i++)
    {
        free(jsonTab->jsonTable[i]);
    }
    free(jsonTab->jsonTable);
    free(jsonTab);
}

void clean_Weather(wdata * wda)
{
    for(int i = 0; i < 20; i++)
    {
        wda->weather[i] = '\0';
        wda->temp[i] = '\0';
    }
}

void free_Weather(wdata* wda)
{
    free(wda);

}
jtable * split_a_string(char *jsonStr)
{
    int length = strlen(jsonStr)+1;
    char *jstr = malloc(sizeof(char)*length);
    jtable *jsonTab = (jtable *)malloc(sizeof(jtable));
    jsonTab->jsonTable = (char **)malloc(sizeof(char *)*length);
    char *tokenized;
    const char t[] = ",";
    int  i = 0; 
    strcpy(jstr, jsonStr);    
    //printf("\n%s\n", jsonStr); 
    tokenized = strtok(jstr, t);
    while(tokenized != NULL)
    {   
        //printf("\n-----------------------------------------------------\n");

        jsonTab->jsonTable[i] =  (char *)malloc(sizeof(char)*(strlen(tokenized)+1));
        strcpy(jsonTab->jsonTable[i], tokenized);
        tokenized = strtok(NULL, t); 
        i++;
    }
    jsonTab->count = i-1;
    free(jstr);

    return jsonTab;
}
