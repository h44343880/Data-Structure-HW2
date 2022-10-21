#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
    int length, width, user, cnt = 0;
    scanf("%d %d %d", &length, &width, &user);

    int user_id, block_len, block_wid, current = 0;
    char * input = (char*)calloc(50, sizeof(char));
    char * word = (char*)malloc(sizeof(char) * 5);
    gets(input);//將scanf略過的換行符號讀入
    char ** block_type = (char**)calloc(user, sizeof(char*));
    for(int i = 0; i < user; i++){
        block_type[i] = (char*)calloc(5, sizeof(char));
    }
    int * accept = (int*)calloc(user, sizeof(int));
    int * coordinate = (int*)malloc(sizeof(int) * user);
    for(int i = 0; i < user; i++){
        gets(input);
        // printf("%s\n", input);
        word = strtok(input, " ");
        word = strtok(NULL, " ");
        // printf("%d: %s\n", i, word);
        strcpy(block_type[i], word);
        if(strcmp(word, "1x16") == 0){
            block_len = 1;
            block_wid = 16;
        }else if(strcmp(word, "2x8") == 0){
            block_len = 2;
            block_wid = 8;
        }else if(strcmp(word, "4x4") == 0){
            block_len = 4;
            block_wid = 4;
        }else if(strcmp(word, "8x2") == 0){
            block_len = 8;
            block_wid = 2;
        }else if(strcmp(word, "16x1") == 0){
            block_len = 16;
            block_wid = 1;
        }
        if(block_len <= length && block_wid + current <= width){
            accept[i] = 1;
            coordinate[i] = current;
            current += block_wid;
            cnt++;
        }
    }
    printf("%d\n", cnt);
    for(int i = 0; i < user; i++){
        if(accept[i]){
            printf("%d %s 0 %d\n", i, block_type[i], coordinate[i]);
        }
    }
}