/*
  treeprint - Tree Printer
  Sun Nov 11 17:26:34 NPT 2008
*/

#include "./stack/istack.h"

int level=-1;
int xtab;//tab backup
int tabs=0;
int child=0;
int xchild;
Stack path;

//Stack ltabs[2];

void BSTree::printree(Nodeptr root){
  if(root==NULL) return;
  
  level++;
  path.push(root->info);
  
  xchild=child;
  child=0;
  if(root->left!=NULL) child++;
  if(root->right!=NULL) child++;

  xtab=tabs;
  if(child==2) tabs++;
  
  //extra info
  printf("%d %d %d %d", level, child, xtab, tabs);
  int i;
  for(i=level; i<7; i++) cout<<"   ";
  path.display();
  printf(" %c ",221);
  
  int j=0;
  if(level>0) {
    for(i=0; i<level-1; i++) {
      if(j++<tabs) printf("%d%c",j,179);
      else printf("%d$",j);
      
      printf("   ");
    }
    
    if(j<tabs) {
      if(xchild==2)  printf("%d%c%c%c%c",++j,195,196,'*',196); //j++ not need coz last level
      else  printf("%d%c%c%c%c",++j,192,196,'/',196);
    }
    else {
      if(xchild!=2) printf("%d%c%c%c%c",++j,192,196,'`',196);
      else
	if(child==0) printf("%d%c%c%c%c",++j,195,196,'~',196);
    }

  }
  
  if(child!=0) cout<<"[+]";
  else printf("[%c]", 250);
  
  cout<<root->info<<endl;
  
  printree(root->left);
  printree(root->right);
  
  if(xtab==tabs) tabs--;
  path.pop();
  level--;
}
