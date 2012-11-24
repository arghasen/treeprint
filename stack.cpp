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
  if(front==NULL) return NULL;
  
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

void Stack::menu() {
  int data;
  for(;;) {
    printf("Stack [ 1. Push | 2. Pop | 3. Peep | 4. Display ]: ");
    scanf("%d", &data);
    
    switch(data) {
    case 1:
      printf("Enter any no: "); scanf("%d", &data);
      push(data);
      display();
      break;
      
    case 2:
      printf("%d deleted\n", pop());
      display();
      break;
      
    case 3:
      printf("%d peeped\n", peep());
      break;
      
    case 4:
      display();
      break;
				
    default:
      return;
    }
  }
}

int main (int argc, char const* argv[]) {
  Stack s;
  s.menu();
  return 0;
}

