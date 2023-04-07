/* 
   Kyriakopoulos Vasilis
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 183719
#define SIZE2  163632
typedef struct list {
	char * text;
	struct list * next;
}list;
typedef struct item{
	char* str;
	list* chain;
}item;
int DICTIONARYSIZE=0;
int temp ;
unsigned int strtohash(char* str);
void first_question();
void free_arr(char** arr);
void print_arr(char**arr);
void quicksort(char *a, int l, int r);
void second_question();
int check_if_prime(int a);
void print_list(list* a);
void print_arr_with_chains(item* arr);
list* insert_at_end(list* start,char* x);
void free_arr_with_chains(item* arr);
void free_list(list* head);
int main(void){	
	printf("First question !!!!\n");
	first_question();
	printf("\nSecond question !!!!\n");
	second_question();

	return 0;
}

void quicksort(char *a, int l, int r)
{ 
char temp;
 if (l >= r) return;
 int i = l, 
 j = r + 1; 
 int pivot = a[l];
 while (1) { 
 do { 
 i++;
 } while (i<=r && a[i] < pivot);
 
 do { 
 j--;
 } while (a[j] > pivot);
 if (i >= j) {
 	break;
}
 temp=a[i];
 a[i]=a[j];
 a[j]=temp; 
 } 
 a[l] = a[j]; 
 a[j] = pivot;
 quicksort(a, l, j-1); 
 quicksort(a, j+1, r); 
}
list* insert_at_end(list* start,char* x){
  list *t, *temp;

  t = (list*)malloc(sizeof(list));
  t->text=(char*)malloc(sizeof(char)*(strlen(x)+1));
  strcpy(t->text,x);
  if (start == NULL) {
    start = t;
    start->next = NULL;
    return start;
  }
  temp = start;
  while (temp->next != NULL)
    temp = temp->next;

  temp->next = t;
  t->next   = NULL;
  return start;
}
int check_if_prime(int a){
	int y,i,count;
	count =0;
	for(i=1;i<=a;i++){
		y = a%i;
		if(y==0){
			count=count+1;	
		}	
	}
	if (count == 2){
		return 1;
	}
	else
	return 0;
}
void second_question(){
	DICTIONARYSIZE = SIZE2;
	temp=SIZE2;
	while(!check_if_prime(temp)){
		temp++;
	}
	item* arr = (item*)malloc(sizeof(item)*temp);
	if(arr == NULL)
	{
		printf("Failed malloc");
		exit(1);
	}
	int i;
	for(i=0;i<temp;i++){
		arr[i].str=NULL;
		arr[i].chain=NULL;
		
	}
	FILE* fp = fopen("dictionary.txt","r");
	if(fp==NULL){
		printf("Failed to open dictionary.txt\n");
	//	free_arr(arr);
		exit(1);
	}
	char tmp[30]={0};
	char sorted_tmp[30]={0};
	fscanf(fp,"%s",tmp);
	strcpy(sorted_tmp,tmp);
	quicksort(sorted_tmp,0,strlen(sorted_tmp)-1);
	int len;
	int hash;
	while(!feof(fp)){
		len = strlen(tmp)+1;
		hash = strtohash(sorted_tmp);
		if(arr[hash].str==NULL){
		arr[hash].str=(char*)malloc(sizeof(char)*len);
		strcpy(arr[hash].str,sorted_tmp);
		arr[hash].chain=insert_at_end(arr[hash].chain,tmp);
		}
		else if(strcmp(arr[hash].str,sorted_tmp)==0){
			arr[hash].chain=insert_at_end(arr[hash].chain,tmp);
			} 
		else{
		while(1){
		if(hash==temp-1){
			hash=0;
		}
		else
		{
			hash++;
		}
		if(arr[hash].str==NULL){
			arr[hash].str=(char*)malloc(sizeof(char)*len);
			strcpy(arr[hash].str,sorted_tmp);
			arr[hash].chain=insert_at_end(arr[hash].chain,tmp);
			break;	
		}
		else if(strcmp(sorted_tmp,arr[hash].str)==0){
				arr[hash].chain=insert_at_end(arr[hash].chain,tmp);
				break;
			} 
		}
		}
		for(i=0;i<len-1;i++){
			tmp[i]='\0';
			sorted_tmp[i]='\0';
		}
		fscanf(fp,"%s",tmp);
		strcpy(sorted_tmp,tmp);
		quicksort(sorted_tmp,0,strlen(sorted_tmp)-1);
	}
	fclose(fp);
//	print_arr_with_chains(arr);
	printf("Please Give me Word: ");
	scanf("%s",tmp);
	strcpy(sorted_tmp,tmp);
	quicksort(sorted_tmp,0,strlen(sorted_tmp)-1);
	while(getchar()!='\n');
	hash=strtohash(sorted_tmp);
	int hash2 = hash;
	while(1){

		if(arr[hash2].str!=NULL&&strcmp(arr[hash2].str,sorted_tmp)==0){
			printf("Word anagram was found in the dictionary with hash %d code at position %d with the following anagrams: ",hash+1,hash2+1);
			
			print_list(arr[hash2].chain);
			break;	
		}
		if(hash2==temp-1){
			hash2=0;
		}
		else
		{
			hash2++;
		}
		if(hash==hash2){
			printf("Word was not found\n");
			break;
		}
	}
	//print_arr_with_chains(arr);
	free_arr_with_chains(arr);
		
}
void free_arr_with_chains(item* arr){
	int i;
	for(i=0;i<temp;i++){
		if(arr[i].str!=NULL){
			free(arr[i].str);
			free_list(arr[i].chain);
		}
	}
	free(arr);
}
void free_list(list* head)
{
	list* tmp;
	while(head!=NULL)
	{	
		tmp=head;
		head=head->next;
		free(tmp->text);
		free(tmp);
	}
}
void print_arr(char**arr){
	int i,c=1;
	for(i=0;i<temp;i++){
		printf("\n%d) %s",c,arr[i]);
		c++;
	}
}
void print_arr_with_chains(item* arr){
	int i,c=1;
	for(i=0;i<temp;i++){
		if(arr[i].str!=NULL){
		printf("\n%d) %s ",c,arr[i].str);
		print_list(arr[i].chain);
		printf("\n");
	}
		c++;
	}
}
void print_list(list* a){
	if(a == NULL){
		return;
	}
	list* t=a;
	while(t!=NULL){
		printf("%s ",t->text);
		t=t->next;
	}
	
}
void free_arr(char** arr){
	int i ;
	for(i=0;i<temp;i++){
		if(arr[i]!=NULL){
			free(arr[i]);
	}
	}
	free(arr);
}
void first_question(){
	int i;
	do{
	printf("Give me the Dictionary size(0 , 183719): ");
	scanf("%d",&DICTIONARYSIZE);
	while(getchar()!='\n');
	}while(DICTIONARYSIZE<=0||DICTIONARYSIZE>SIZE);
	temp =DICTIONARYSIZE;
	while(!check_if_prime(temp)){
		temp++;
	}
	char ** arr=(char**)malloc(sizeof(char*)*temp);
	if(arr == NULL)
	{
		printf("Failed malloc");
		exit(1);
	}
	for(i=0;i<temp;i++){
		arr[i]=NULL;
	}
	FILE* fp = fopen("dictionary.txt","r");
	if(fp==NULL){
		printf("Failed to open dictionary.txt\n");
		free_arr(arr);
		exit(1);
	}
	char tmp[30]={0};
	fscanf(fp,"%s",tmp);
	int len;
	int hash;
	int num = DICTIONARYSIZE;
	while(num>0){
		len = strlen(tmp)+1;
		hash = strtohash(tmp);
		if(arr[hash]==NULL){
		arr[hash]=(char*)malloc(sizeof(char)*len);
		strcpy(arr[hash],tmp);
		}
		else{
		while(1){
		if(hash==temp-1){
			hash=0;
		}
		else
		{
			hash++;
		}
		if(arr[hash]==NULL){
			arr[hash]=(char*)malloc(sizeof(char)*len);
			strcpy(arr[hash],tmp);
			break;	
		}
		}
		}
		for(i=0;i<len-1;i++){
			tmp[i]='\0';
		}
		fscanf(fp,"%s",tmp);
		num--;
	}
	fclose(fp);
	printf("Please Give me Word: ");
	scanf("%s",tmp);
	while(getchar()!='\n');
	hash=strtohash(tmp);
	int hash2 = hash;
	while(1){

		if(arr[hash2]!=NULL&&strcmp(arr[hash2],tmp)==0){
			printf("Word '%s' was found in the dictionary with hash %d code at position %d",arr[hash2],hash+1,hash2+1);
			break;	
		}
		if(hash2==temp-1){
			hash2=0;
		}
		else
		{
			hash2++;
		}
		if(hash==hash2){
			printf("Word was not found\n");
			break;
		}
	}
	//print_arr(arr);
	free_arr(arr);
}
unsigned int strtohash(char* str){
     unsigned int hash=0;
     while(*str){
      hash=*str+31*hash;
      str++;
     }
     return hash%temp;
}
