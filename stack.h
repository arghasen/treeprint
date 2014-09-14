#include <cstdio>

class Stack {
private:
  struct Node	{
    int info;
    Node *link;
  };
  typedef Node *Nodeptr;
  Nodeptr front;

public:
  Stack();
  void push(int);
  int pop();
  int peep();
  void display();
  void menu();
};

Stack::Stack() {
  front=NULL;
}

int Stack::peep() {
  if(front==NULL) return '\0';
  return front->info;
}

void Stack::push(int data) {
  Nodeptr temp=new Node;
  temp->info=data;
  
  temp->link=front;
  front=temp;
}

int Stack::pop() {
  if(front==NULL) return 0;
  
  Nodeptr temp=front;
  front=front->link;

  int val=temp->info;
  delete temp;
  
  return val;
}

void Stack::display() {
  Nodeptr cursor=front;
  
  while(cursor!=NULL) {
    printf("%d->", cursor->info);
    cursor=cursor->link;
  }
  
  printf("NULL\n");
}
