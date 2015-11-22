#include <stdio.h>
#include <stdlib.h>

typedef struct Trie 
{ 
	//char *value;
	char ch;
	int  count;
	struct trie *sibling; /* Sibling node */
	struct trie *child; /* First child node */
} Trie; 


//Создает пустой узел Trie
Trie* trie_create()
{
	Trie* node;
	if ( (node = malloc(sizeof(*node))) == NULL)
		return NULL;
	node->ch = '\0';
	//node->value = NULL;
	node->count = 0;
	node->sibling = NULL;
	node->child = NULL;
	return node;
}

//Поиск узла в Trie по ключу
/*
char *trie_lookup(Trie *root, char *key)
{
	Trie *node, *list;
	for (list = root; *key != '\0'; key++) {
		for (node = list; node != NULL; node = node->sibling)
		{
			if (node->ch == *key)
			break;
		}
	if (node != NULL)
		list = node->child;
	else
		return NULL;
	}
		/* Check: Node must be a leaf node! */
/*	return node->value;
}*/

//Вставка узла в Trie
Trie *trie_insert(Trie *root, char *key)
{
	Trie *node, *parent, *list;
	parent = NULL;
	list = root;
	for (; *key != '\0'; key++) {
	/* Lookup sibling node */
		for (node = list; node != NULL; node = node->sibling)
		{	
			if (node->ch == *key)
				break;
		}
		if (node == NULL) {
	/* Node not found. Add new node */
			node = trie_create();
			node->ch = *key;
			node->count = 1;
			node->sibling = list;
			if (parent != NULL)
				parent->child = node;
			else
				root = node;
				list = NULL;
		} else {
	/* Node found. Move to next level */
			node->count++;
			list = node->child;
		}
		parent = node;
	}
		return root;
} 

Trie *trie_delete_dfs(Trie *root, Trie *parent, char *key, int *found)
{
	Trie*node, *prev = NULL;
	*found = (*key == '\0' && root == NULL) ? 1 : 0;
	if (root == NULL || *key == '\0')
		return root;
	for (node = root; node != NULL;node = node->sibling)
	{
		if (node->ch == *key)
			break;
		prev = node;
	}
	if (node == NULL)
		return root;
	trie_delete_dfs(node->child, node, key + 1, found);
	if (*found > 0 && node->child == NULL) {
	/* Delete node */
		if (prev != NULL)
			prev->sibling = node->sibling;
		else {
			if (parent != NULL)
				parent->child = node->sibling;
			else
				root = node->sibling;
		}
		free(node);
	}
	return root;
}

Trie *trie_delete(Trie *root, char *key)
{
	int found;
	return trie_delete_dfs(root, NULL, key, &found);
}

void trie_print(Trie *root, int level)
{
	Trie *node;
	int i;
	for (node = root; node != NULL; node = node->sibling)
	{
		for (i = 0; i < level; i++)
			printf(" ");
			printf("%c %d \n", node->ch, node->count);
		if (node->child != NULL)
			trie_print(node->child, level + 1);
	}
}

int calcArr(){
	FILE *ptrfile;
	int i=0;
	char s;
	ptrfile=fopen( "mass.txt", "r");
	while ((fscanf(ptrfile, "%c",&s)!=EOF))
		{    
		if(!ptrfile) 
			break;    //чтобы не делал лишнего
       		i++;
		}
	fclose(ptrfile);
	return i;
}

int main()
{
	 int i=0, k=0;
	 Trie *root = NULL;
	char base[k][k],s;
 	FILE *ptrfile;
 	ptrfile=fopen( "mass.txt", "r");
	while ((fscanf(ptrfile, "%c",&s)!=EOF))
		{    if(!ptrfile) break;    //чтобы не делал лишнего
        k+=1;
		}

	rewind(ptrfile);    //перематываем файл для повторного чтения
 	while (!feof(ptrfile)){
        fscanf(ptrfile,"%s",base[i]);
        if (i=0){
        	root = trie_insert(NULL, base[i]);
        }
        else{
			root = trie_insert(root, base[i]);
		}
       i++;
       }
fclose(ptrfile);
trie_print(root, 0 );
}