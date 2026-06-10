#include "CLI.h"

FILE *fh_output;

void run(HashTable* HT){
    char input[256];
    FILE* fh_input = fopen("io.txt","r");
    if(fh_input!= NULL){

        while(fgets(input,sizeof(input),fh_input) != NULL){
            
            input[strcspn(input,"\r\n")] = '\0';
            
            char* command = strtok(input," ");
            
            // dechpiring the first word
            
            if(command == NULL) continue;
            
            else if (strcmp(command, "SET") == 0){
                char* key_input = strtok(NULL," ");
                char* value_input = strtok(NULL," ");
                if(key_input == NULL || value_input == NULL){
                    printf("missing arguments\n");
                    continue;
                }
                upsert(HT, key_input,atoi(value_input));
            }
            else if (strcmp(command, "DEL") == 0){
                char* key_input = strtok(NULL," ");
                if(key_input == NULL ){
                    printf("Missing arguments\n");
                    continue;
                }
                removeNode(HT,key_input);
            }
        }
        fclose(fh_input);
    }
        
        printf("Welcome to my Hashtable,\n"
            "enter SET, key(string) and a value(number) in order to insert elements\n"
        "enter GET and its key in order to retrieve a key\n"
        "enter DEL and a key in order to delete it\n"
        "enter PRINT in order to print all the elements you entered\n");
        while(1){
            printf("----------------------------------------\n");
            printf(">");
            //entering input
            fgets(input,sizeof(input),stdin);
            
            input[strcspn(input,"\r\n")] = '\0';

            char* command = strtok(input," ");

            // dechpiring the first word

            if(command == NULL) continue;

            else if (strcmp(command, "SET") == 0){
                char* key_input = strtok(NULL," ");
                char* value_input = strtok(NULL," ");
                if(key_input == NULL || value_input == NULL){
                    printf("missing arguments\n");
                    continue;
                }
                upsert(HT, key_input,atoi(value_input));
                fh_output = fopen("io.txt","a");
                if(fh_output == NULL) continue;
                fprintf(fh_output,"SET %s %s\n",key_input,value_input);
                fclose(fh_output);
            }

            else if (strcmp(command, "DEL") == 0){
                char* key_input = strtok(NULL," ");
                if(key_input == NULL ){
                    printf("Missing arguments\n");
                    continue;
                }
                removeNode(HT,key_input);
                fh_output = fopen("io.txt","a");
                if(fh_output == NULL) continue;
                fprintf(fh_output,"DEL %s\n",key_input);
                fclose(fh_output);
            }
            else if (strcmp(command, "GET") == 0){
                char* key_input = strtok(NULL," ");
                if(key_input == NULL ) {
                    printf("Missing arguments\n");
                    continue;
                }
                printf("the value of %s is:%d\n",key_input ,get(HT,key_input));
            }

            else if (strcmp(command, "EXIT") == 0){
                printf("Bye");
                break;
            }

            else if (strcmp(command, "PRINT") == 0){
                printAllElements(HT);
            }
            else{
                printf("Unknown input\n");
                continue;
            }
        }
}