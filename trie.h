//trie.h
typedef struct Trie 
{ 
	char ch;
	int  count;
	struct trie *subtrie; /* subtrie node */
	struct trie *child; /* First child node */
} Trie; 


Trie *trieInsert(Trie *root, char *key); // функция вставки узла
Trie *trieDelete(Trie *root, char *key); // удаление по ключу
void triePrint(Trie *root); // печать дерева
