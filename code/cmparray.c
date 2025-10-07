#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

void *getword(char *word,int sz);

int main()
{
    char arr[SIZE]={"123"},arr1[SIZE]={""},*ptr;
    int cond;
    
    ptr=(char *)getword(arr1,SIZE);
    
    if((cond=strcmp(arr,arr1))<0){
        printf("const is smaller\n");
    }else if(cond>0){
        printf("const is bigger\n");
    }else{
        printf("strings are equal\n");
    }
    
    printf("word %c data %d\n",*ptr,cond);
    
    return 0;
}

void* getword(char *word,int sz){
    
    int c;
    char *w=word;
    while(!isspace(c=getchar()));
    
    if(c!=EOF){
        *w++=c;
    }
    
    if(isalpha(c)){
        *w='\0';
        return (w+0);
    }
    
    while(--sz>0){
        c=getchar();
        if(isdigit(c))
        {
            *w=c;
        }
        w++;
    }
    
    *w='\0';
    
    return (w+0);
    
}