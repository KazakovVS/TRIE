/*trie.h*/
#include <stdio.h>
#include <stdlib.h>

 
typedef struct trieNode {
    char key;
    int count;
    struct trieNode *next;
    struct trieNode *prev;
    struct trieNode *children;
    struct trieNode *parent;
} Trie;
 
void TrieCreate(Trie **root);
Trie* TrieSearch(Trie *root, const char *key);
void TrieAdd(Trie **root, char *key, int data);
void TrieDestroy( Trie* root );

/*trie.c*/
 
Trie *TrieCreateNode(char key, int data);
 
void TrieCreate(Trie **root)
{
    *root = TrieCreateNode('\0', 0xffffffff);
}
 
Trie *TrieCreateNode(char key, int data)
{
    Trie *node = NULL;
    node = (Trie *)malloc(sizeof(Trie));
 
 if(NULL == node)
 { 
    printf("Malloc failed\n");
    return node;
 }
    node->key = key;
    node->next = NULL;
    node->children = NULL;
    node->count = data;
    node->parent= NULL;
    node->prev= NULL;
    return node;
}
 
void TrieAdd(Trie **root, char *key, int data)
{
 Trie *node = NULL;
 
 if(NULL == *root)
 {
  return;
 }
 node = (*root)->children;
 if(node == NULL)
 {
  /*First Node*/
  for(node = *root; *key; node = node->children)
  {
   node->children = TrieCreateNode(*key, 0xffffffff);
   node->children->parent = node;

   key++;
  }
  node->children = TrieCreateNode('\0', data);
  node->children->parent = node;

  return;
 }
 
 if(TrieSearch(node, key))
 {
  return;
 }
 
 while(*key != '\0')
 {
  if(*key == node->key)
  {
   key++;
   node = node->children;
  }
  else
   break;
 }
 
 while(node->next)
 {
  if(*key == node->next->key)
  {
   key++;
   TrieAdd(&(node->next), key, data);
   return;
  }
  node = node->next;
 }
 
 if(*key)
 {
  node->next = TrieCreateNode(*key, 0xffffffff);
 }
 else
 {
  node->next = TrieCreateNode(*key, data);
 }
 
 node->next->parent = node->parent;
 node->next->prev = node;
 
 if(!(*key))
  return;
 
 key++;
 
 for(node = node->next; *key; node = node->children)
 {
  node->children = TrieCreateNode(*key, 0xffffffff);
  node->children->parent = node;
  key++;
 }
 
 node->children = TrieCreateNode('\0', data);
 node->children->parent = node;
 return;
}
 
Trie* TrieSearch(Trie *root, const char *key)
{
 Trie *level = root;
 Trie *pPtr = NULL;
 
 int lvl=0;
 while(1)
 {
  Trie *found = NULL;
  Trie *curr;
 
  for (curr = level; curr != NULL; curr = curr->next)
  {
   if (curr->key == *key)
   {
    found = curr;
    lvl++;
    break;
   }
  }
 
  if (found == NULL)
   return NULL;
 
  if (*key == '\0')
  {
   pPtr = curr;
   return pPtr;
  }
 
  level = found->children;
  key++;
 }
}

void TrieDestroy( Trie* root )
{
 Trie *node = root;
 Trie *tmp = NULL;
 
  while(node)
 {
    while(node->children)
    {
        node = node->children;
    } 
    if( node->prev && node->next)
    {
        tmp = node;
        node->next->prev = node->prev;
        node->prev->next = node->next;
        free(tmp);
    }
    else if(node->prev && !(node->next))
    {
        tmp = node;
        node->prev->next = NULL;
        free(tmp);
    }
    else if(!(node->prev) && node->next)
    {
        tmp = node;
        node->parent->children = node->next;
        node->next->prev = NULL;
        node = node->next;
        free(tmp);
    }
    else
    {
        tmp = node;
        if(node->parent == NULL)
        {
            /*Root*/
            free(tmp);
            return;
         }
        node = node->parent;
        node->children = NULL;
        free(tmp);
    }
 }
 
}

/*triedriver.c*/
 
int main()
{
    Trie *root;
    printf("Trie Example\n");
     
    /*Create a trie*/
    TrieCreate(&root);
     
    TrieAdd(&root, "andrew", 1);
    TrieAdd(&root, "tina", 2);
    TrieAdd(&root, "argo", 3);
    TrieAdd(&root, "timor", 5);
    TrieAdd(&root, "tim", 6);
    TrieAdd(&root, "ti", 6);
    TrieAdd(&root, "amy", 7);
    TrieAdd(&root, "aramis", 8);
 
    /*Destroy the trie*/
    TrieDestroy(root);
}