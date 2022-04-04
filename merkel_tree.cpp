#include<bits/stdc++.h>
using namespace std;
 
/* determines the maximimum capacity of Hash Tree */
int maxim = 20;        
/* determines the number of elements present in Hash Tree */
int size = 0;

struct node
{
  int key;
  int value;
  struct node *left;
  struct node *right;
};

struct binary_tree
{
  /* head pointing to the root of Binary Tree */
  struct node *head;
};

struct binary_tree *arr;

//hash function that takes a key as its parameter.
int hashvalue(int key)
{
  return (key % maxim);
}

/* this function inserts the newly created node
   in the existing Binary Tree */
void insert_element(struct node *tree,struct node *item)
{
  if (item->key < tree->key)
  {
    if (tree->left == NULL)
    {
      tree->left = item;
      return;
    }
    else
    {
      insert_element(tree->left, item);
      return;
    }
  }
  else if (item->key > tree->key)
  {
    if (tree->right == NULL)
    {
      tree->right = item;
      return;
    }
    else
    {
      insert_element(tree->right, item);
      return;
    }
  }
}

/* this function finds the given key in the Binary Tree*/
struct node* find(struct node *tree, int key)
{
  if (tree == NULL)
  {
    return NULL;
  }
  if (tree->key == key)
  {
    return tree;
  }
  else if (key < tree->key)
  {
    return find(tree->left, key);
  }
  else
  {
    return find(tree->right, key);
  }
}

//function that adds a node in merkle tree. 
void add(int key, int value)
{
  int index = hashvalue(key);
  struct node *tree = (struct node*) arr[index].head;
   
  /* creating an item to insert in the hashTree */
  struct node *item = (struct node*)malloc(sizeof(struct node));
 
  item->key = key;
  item->value = value;
  item->left = NULL;
  item->right = NULL;
 
  if (tree == NULL)
  {
    /* absence of Binary Tree at a given
       index of Hash Tree */
    arr[index].head = item;
    size++;//incrementing size
  }
  else
  {
    /* a Binary Tree is present at given index
       of Hash Tree */
    struct node *temp = find(tree, key);
    if (temp == NULL)
    {
      /* Key not found in existing Binary Tree.*/
      insert_element(tree, item);
      size++;
    }
    else
    {
      
      /* Key already present in existing Binary Tree 
      Updating the value of already existing key
       */
      temp->value = value;
    }
  }
}

/* displays content of binary tree of
particular index */
void display_tree(struct node *tree)
{ 
  if (tree == NULL)
  {
    return;
  }
  cout << tree->key << " and " <<
                          tree->value << "   ";
  if (tree->left != NULL)
  {
    display_tree(tree->left);
  }
  if (tree->right != NULL)
  {
    display_tree(tree->right);
  }
}

/* displays the content of hash Tree */
void display()
{
  int i = 0;
  for(i = 0; i < maxim; i++)
  {
    struct node *tree = arr[i].head;
    if (tree == NULL)
    {
      cout << "arr[" << i << "] has no elements" << endl;
    }
    else
    {
      display_tree(tree);
    }
  }
}

void init()
{
  int i = 0;
  for(i = 0; i < maxim; i++)
  {
    arr[i].head = NULL;
  }
}

/* returns the size of hash Tree */
int size_of_hashTree()
{
  return size;
}

struct node* remove(struct node *tree, int key)
{
  if (tree == NULL)
  {
    return NULL;
  }
  if (key < tree->key)
  {
    tree->left = remove(tree->left, key);
    return tree;
  }
  else if (key > tree->key)
  {
    tree->right = remove(tree->right, key);
    return tree;
  }
  else
  {
      /* reached the node */
    if (tree->left == NULL  &&  tree->right == NULL)
    {
      size--;
      return tree->left;
    }
    else if (tree->left != NULL  &&  tree->right == NULL)
    {
      size--;
      return tree->left;
    }
    else if (tree->left == NULL  &&  tree->right != NULL)
    {
      size--;
      return tree->right;
    }
    else
    {
      struct node *left= tree->left;
      while (left->right != NULL)
      {
        left= left->right;
      }
      tree->key = left->key;
      tree->value = left->value;
      tree->left = remove(tree->left, tree->key);
      return tree;
    }
  }
}

void delete_element(int key)
{
  int index = hashvalue(key);
  struct node *tree = (struct node*)arr[index].head;
  if (tree == NULL)
  {
    cout << key << " Key is not present" << endl;
  }
  else
  {
    struct node *temp = find(tree, key);
    if (temp == NULL)
    {
      cout << key << " is not present";
    }
    else
    {
      tree = remove(tree, key);
    }
  }
}

int main()
{
  int choice, key, value, n, c;
  arr = (struct binary_tree *)malloc(maxim *sizeof(struct binary_tree*));
  init();
  do
  {
    cout <<"1.Insert an item in the Hash Tree"
      "\n2.Remove an item from the Hash Tree"
      "\n3.Check the size of Hash Tree"
      "\n4.Display Hash Tree"
      "\n\n Please enter your choice-:";
    cin >> choice;
    switch(choice)
    {
      case 1:
        cout << "Enter key and value-:    ";
        cin >> key >> value;
        add(key, value);
        break;
      case 2:
        cout << "\n Enter the key to delete-:";
        cin >> key;
        delete_element(key);
        break;
      case 3:
        n = size_of_hashTree();
        cout << "Size of Hash Tree is-:" << n << endl;
        break;
      case 4:
        display();
        break;
      default:
        cout << "Wrong Input" << endl;
    }
    cout << "\n Do you want to continue-: (press 1 for yes)     ";
    cin >> c;
  }while(c == 1);
  return 0;
}
