//triedriver.c
#include <stdio.h>
#include <stdlib.h>
#include "trie.h"

int main()
{
	 int i=0, k=0;
	 Trie *root = NULL;
	char arr[k][k],s;
 	FILE *ptrfile;
 	ptrfile=fopen( "mass.txt", "r");
	while ((fscanf(ptrfile, "%c",&s)!=EOF))
		{    if(!ptrfile) break;    //чтобы не делал лишнего
        k+=1;
		}

	rewind(ptrfile);    //перематываем файл для повторного чтения
 	while (!feof(ptrfile)){
        fscanf(ptrfile,"%s",arr[i]);
        if (i=0){
        	root = trieInsert(NULL, arr[i]);
        }
        else{
			root = trieInsert(root, arr[i]);
		}
       i++;
       }
	fclose(ptrfile);
	triePrint(root);
}