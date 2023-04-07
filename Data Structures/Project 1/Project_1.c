/* 
   Kyriakopoulos Vasilis
*/
#include <stdio.h>
#include <stdlib.h>
#define Max_Num 1000
typedef struct list {
	int data;
	struct list * next;
}list;
typedef struct Item {
	list * ptr_list;  
} Item;
Item *Stack;
int N;
int STACKempty();
void STACKinit(int maxN);
void STACKpush(list *item);
Item STACKpop();
void printList(list * head);
int is_list_empty(list *head);
void deleteLast(list *head);
list * insertlast(list * head,int item);
list * createlist(int item);
void createsum(list* head);
void free_list(list* head);
list *copy(list *start1);
int main(void){
	int choose_number=0;
	printf("Give an integer positive number between 1 and %d:",Max_Num-1);
	do{
	scanf("%d",&choose_number);
	if(choose_number<=0){
		printf("Please give me an integer\n");
	}
	if(choose_number>=Max_Num){
		printf("Please give a smaller integer\n");
	}
	while(getchar()!='\n');
    }while(choose_number<=0||choose_number>=Max_Num);
    Item head;
    STACKinit(choose_number);
    STACKpush(createlist(choose_number));
    int c=1;
   while(!STACKempty())
   {
   		head = STACKpop();
   		printf("%d",c);
   		printList(head.ptr_list);
   		createsum(head.ptr_list);
		c++;
		free_list(head.ptr_list);
   }
   free(Stack);
   return 0;
}
void createsum(list* head)
 {
 	int i,k=head->data;
 	list *arr;
 	for(i=0;i<k-1;i++)
 	{
 		arr =createlist(k-1-i);
 		arr =insertlast(arr,i+1);
 		list * temp = arr;
 		while(temp->next!=NULL)
 		temp=temp->next;
 		temp->next=copy(head->next);
 		STACKpush(arr);
	 }
 }
int STACKempty(){ return N == 0;}
void STACKinit(int maxN){ Stack  = (Item *)malloc(maxN*sizeof(Item)); N = 0;}
void STACKpush(list *item){ Stack[N++].ptr_list = item; }
Item STACKpop(){ return Stack[--N];}
int is_list_empty(list *head){
	if(head == NULL)
	return 0;
	return 1;
}
void printList(list *head) {
   list *ptr = head;
   printf("[ ");	
   while(ptr != NULL) {
      printf("(%d)",ptr->data);
      ptr = ptr->next;
   }
   printf(" ]\n");
}
list * insertlast(list * head,int item){
	list * curr = head;
	while (curr->next!=NULL)
    {
        curr = curr->next;
    }
    curr->next = (list*)malloc(sizeof(list));
    curr->next->data = item;
	curr->next->next = NULL; 
    return head;
}
list * createlist(int item)
{
		list *head = (list*)malloc(sizeof(list));
		head->data=item;
		head->next = NULL;
		return head;	
}
void free_list(list* head)
{
	list* tmp;
	while(head!=NULL)
	{	
		tmp=head;
		head=head->next;
		free(tmp);
	}
}
list *copy(list *start1)
{
list *start2=NULL,*previous=NULL;
while(start1!=NULL)
{
    list * temp = (list *) malloc (sizeof(list));
    temp->data=start1->data;
    temp->next=NULL;
    if(start2==NULL) {start2=temp;previous=temp; }
    else{previous->next=temp;previous=temp;}
    start1=start1->next;
}
return start2;
}
