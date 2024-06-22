#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

char * SaisirChaine()
{
    unsigned int c, nbc = 0 ;
    char * ch = NULL ;
    while((c = getchar()) != '\n')
    {
        ch = realloc(ch, (nbc+1)*sizeof(char));
        ch[nbc++] = c ;
    }
    ch = realloc(ch, (nbc+1)*sizeof(char));
    ch[nbc] = '\0' ;
    return ch ;
}
