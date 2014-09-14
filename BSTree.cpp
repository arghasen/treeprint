/*
  Binary Search Tree
  11 Nov 2008
  Last Update: 8 Dec 2008
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

class BSTree {
private:
  typedef struct Node {
    int info;
    Node *left;
    Node *right;
    Node();
  }*Nodeptr;

  Nodeptr root;

public:
  BSTree();
  BSTree(int [], int);

  ~BSTree();

  void destory(Nodeptr &);
  void insert(int , Nodeptr &);
  void remove(int, Nodeptr &);

  void traverse(Nodeptr);
  void inorder(Nodeptr);
  void preorder(Nodeptr);
  void postorder(Nodeptr);

  void printree(Nodeptr, char);

  Nodeptr search(Nodeptr &, int);

  Nodeptr findmin(Nodeptr);
  Nodeptr findmax(Nodeptr);

  void menu(char ch='0');
};

int main() {
  int a[]= {29, 25, 14, 16, 9, 11, 7, 10, 12, 15, 27, 8};
  BSTree BST(a, 12);

  BST.menu('6');
  return 0;
}

BSTree::Node::Node() {
  left=NULL;
  right=NULL;
}

BSTree::BSTree(): root(NULL) {}

BSTree::BSTree(int A[], int size) {
  root=NULL;
  for(int i=0; i<size; i++) insert(A[i], root);
}

BSTree::~BSTree() {
  destory(root);
}

void BSTree::destory(Nodeptr &root) {
  if(root->left!=NULL) destory(root->left);
  if(root->right!=NULL) destory(root->right);

  delete root;
  root=NULL;
}

void BSTree::insert(int data, Nodeptr &root) {
  if(root==NULL) {
    Nodeptr temp=new Node;
    temp->info=data;
    root=temp;
    return;
  }
  //if(root->info==data)
  if(root->info>data) insert(data, root->left);
  else insert(data, root->right);
}

void BSTree::remove(int info, Nodeptr &root) {
  if(root==NULL) {//empty pointer| tree
    cout<<"No not found !!";
    getchar();
    fflush(stdout);
    return;
  }

  Nodeptr temp;
  if(info<root->info) remove(info, root->left);
  else if(info>root->info) remove(info, root->right);
  else if(root->left!=NULL && root->right!=NULL) {//two children
    temp=findmin(root->right);
    root->info=temp->info;
    remove(root->info, root->right);
  }
  else {
    temp=root;
    if(root->left==NULL) root=root->right;
    else if(root->right==NULL) root=root->left;
    delete temp;
  }
}

BSTree::Nodeptr BSTree::search(Nodeptr &root, int info) {
  if(root==NULL) return NULL; //empty pointer| tree

  if(root->info==info) return root;
  else if(root->info>info) return search(root->left, info);
  else return search(root->right, info);
}

BSTree::Nodeptr BSTree::findmin(Nodeptr root) {
  if(root==NULL) return NULL; //empty pointer| tree
  if(root->left!=NULL) return findmin(root->left);
  else return root;
}

BSTree::Nodeptr BSTree::findmax(Nodeptr root) {
  if(root==NULL) return NULL; //empty pointer| tree
  if(root->right!=NULL) return findmax(root->right);
  else return root;
}

void BSTree::traverse(Nodeptr root) {
  if(root==NULL) {
    cout<<"Tree is empty";
    return;
  }

  cout<<"In-order [L|ROOT|R]:\n"; inorder(root);
  cout<<"\nPost-order [L|R|ROOT]:\n";	postorder(root);
  cout<<"\nPre-order [ROOT|L|R]:\n"; preorder(root);
  cout<<"\nPrint Tree [PRE-ORDER]:\n"; printree(root, 'C');
}

void BSTree::preorder(Nodeptr root) {
  if(root==NULL) return;

  cout<<root->info<<", ";
  preorder(root->left);
  preorder(root->right);
}

void BSTree::inorder(Nodeptr root) {
  if(root==NULL) return;

  inorder(root->left);
  cout<<root->info<<", ";
  inorder(root->right);
}

void BSTree::postorder(Nodeptr root)
{
  if(root==NULL) return;

  postorder(root->left);
  postorder(root->right);
  cout<<root->info<<", ";
}

int level=-1;
int tabs=0;
int xtab; //tab backup
int child=0;
int xchild; //double mistake so no need to use
int i;
int flag=0;
int bab[10]={0,0,0,0,0, 0,0,0,0,0};

#include "stack.h"
Stack path;

void BSTree::printree(Nodeptr root, char pos='S') {
  if(root==NULL) return;
  if(flag==1) {
    bab[level]=0;
    flag=0;
  }

  level++;
  path.push(root->info);

  xchild=child;
  child=0;
  if(root->left!=NULL) child++;
  if(root->right!=NULL) child++;

  xtab=tabs;
  if(child==2) {
    tabs++;
    bab[level]=1;
  }

  //extra info
  printf("%d ", level);
  for(i=0; i<5; i++) cout<<bab[i];
  printf(" %d %d ", child, tabs);
  for(i=level; i<7; i++) cout<<"   ";
  path.display();
  cout<<char(221);

  //Level Tabs
  for(i=0; i<level-1; i++) {
    if(bab[i]==1) printf(" %c   ", 179);
    else printf("     ");
  }

  if(level!=0) {
    cout<<level;

    if(xchild == 2) cout<<(char)195;
    else cout<<char(192);

    printf("%c%c%c",pos,196,196);
  }

  if(child!=0) cout<<"[+]";
  else printf("[%c]", 250);

  printf("%d\n",root->info);

  printree(root->left, 'L');
  printree(root->right, 'R');

  if(xtab==tabs) {
    tabs--;
    flag=1;
  }

  path.pop();
  level--;
}

void BSTree::menu(char ch) {
  int data;
  for(;;ch=0) {
    system("clear");
    cout<<"Binary Search Tree\n"
	<<"\n1. Push"
	<<"\n2. Search"
	<<"\n3. Findn"
	<<"\n4. Find Max"
	<<"\n5. Pop"
	<<"\n6. Traversal"
	<<"\n\nEnter your choice: ";

    if(ch==0) ch=getchar();fflush(stdout);
    switch(ch) {
    case 13:
    case '1':
      system("clear");
      cout<<"Enter any no: "; cin>>data;
      insert(data, root);
      break;

    case '2':
      system("clear");
      cout<<"No to be searched: "; cin>>data;
      Nodeptr temp;
      temp=search(root, data);
      if(temp!=NULL) cout<<temp->info<<" is found !!";
      else cout<<data<<" is not found !!";
      getchar();fflush(stdout);
      break;

    case '3':
      system("clear");
      temp=findmin(root);
      if(temp!=NULL) cout<<temp->info<<" is min value !!";
      else cout<<"Tree is empty !!";
      getchar();fflush(stdout);
      break;

    case '4':
      system("clear");
      temp=findmax(root);
      if(temp!=NULL) cout<<temp->info<<" is max value !!";
      else cout<<"Tree is empty !!";
      getchar();fflush(stdout);
      break;

    case '5':
      system("clear");
      cout<<"No to be deleted: "; cin>>data;
      remove(data, root);
      break;

    case '6':
      system("clear");
      traverse(root);
      getchar();fflush(stdout);
      break;

    case 27:
      return;
    };
  }
}
