/* 
   Kyriakopoulos Vasilis
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
typedef struct TreeNode{
	char *data;
	struct TreeNode* l;
	struct TreeNode* r;
}link;
int b = 8;
int c =1;
void codeString(link* root ,char* str);
void DecodeString(link* root);
void printTree(link * root,int height);
unsigned char* chartoBinary(unsigned char n);
link* CreateTree(int height);
void putAscii(link* root,int height);
void putgrey(link* root,int height);
void DestroyTree(link* root);
link* CreateAnyGrey(link* root1,link* root2,int height);
link *SimpleGrayTree(link * root1,int height);
void copycode(link* root1,link* root2,int height);
int count(link* h);
int main(void){
	int height = 8;
	link * root = CreateTree(height);
//	int a = count(root);
//	printf("%d\n",a);
	putAscii(root,height);
	
//	printTree(root,height);
//	printTree(root2,height);
	unsigned char str[10000]={0};
	printf("\nGive a message : ");
	fgets(str,sizeof(str),stdin);
	int i =0;
	while(str[i]!='\0'){
		if(str[i]=='\n'){
			str[i]='\0';
		}
		i++;
	}
	codeString(root,str);
	DestroyTree(root);
//	printf("\n");
//	scanf("%d");
	link * root2 = CreateTree(height);
	putgrey(root2,height);
	DecodeString(root2);
	DestroyTree(root2);
	root = SimpleGrayTree(CreateTree(1),1);
	printf("\nTell me the size of the gray tree you want to create: ");
	int choice;
	scanf("%d",&choice);
	root = SimpleGrayTree(CreateTree(1),1);
	i = 1;
	while(i < choice){
	link *root3 = CreateTree(i);
	copycode(root,root3,i);
	link* x = (link*)malloc(sizeof(link));
	x->l = root;
	x->r = root3;
	x->data = NULL;
	root = x;
	i++;
	}
	c=1;
	printTree(root,i);
	DestroyTree(root);
	return 0;
}
void DecodeString(link* root){
	FILE* fp;
	int j;
	unsigned char* ptr;
	unsigned char decode;
	link* tree =NULL;
	if((fp = fopen("Codedtext.txt","r"))==NULL){
		printf("File could not open \n");
		DestroyTree(root);
		exit(1);
	}
	unsigned char ch = getc(fp);
	printf("\nThe Decoded message is:");
	while(!feof(fp)){
		ptr= chartoBinary(ch);
		tree = root;
		j=0;
		while(ptr[j]!='\0'){
			if(ptr[j]=='0'){
				tree=tree->l;
			}
			else if(ptr[j]=='1'){
				tree=tree->r;
			}
			j++;
		}
		decode = 0;
		for(j=strlen(ptr)-1;j>=0;j--){
			if(tree->data[strlen(ptr)-1-j]=='1')
			{
				decode+=pow(2,j);
			}	
		}
		free(ptr);
		printf("%c",decode);
		ch = getc(fp);			
	}
}
link *SimpleGrayTree(link * root1,int height){
	root1->l->data = (unsigned char *)malloc(sizeof(unsigned char)*(height+1));
	root1->r->data = (unsigned char *)malloc(sizeof(unsigned char)*(height+1));
	root1->l->data[0]='0';
	root1->r->data[0]='1';
	root1->l->data[1]='\0';
	root1->r->data[1]='\0';
	return root1;
}
void copycode(link* root1,link* root2,int height){
	
	if(root1->l==NULL||root1->r==NULL){
		int i =0;
		char* tmp = (unsigned char *)malloc(sizeof(unsigned char)*(height+1));
		for(i = 0 ;i<height+1;i++){
			tmp[i]=root1->data[i];
		}
		root1->data = (unsigned char *)malloc(sizeof(unsigned char)*(height+2));
		root2->data = (unsigned char *)malloc(sizeof(unsigned char)*(height+2));
		root1->data[0]='0';
		root2->data[0]='1';
		
		for(i=1;i<height+2;i++)
		{
			root1->data[i]=root2->data[i]=tmp[i-1];			
		}
		root1->data[height+1]=root2->data[height+1]='\0';
		free(tmp);
	}
	else{
	copycode(root1->l,root2->r,height);
	copycode(root1->r,root2->l,height);
	}	
}
void codeString(link* root ,char* str){
	int i,j;
	unsigned char *ptr ;
	
	unsigned char code;
	link * tree=NULL;
	FILE* fp;
	if((fp = fopen("Codedtext.txt","w"))==NULL){
		printf("File could not open \n");
		DestroyTree(root);
		exit(1);
	}
	printf("The Coded message is:");
	
	for(i=0;i<strlen(str);i++)
	{
		ptr =chartoBinary(str[i]);
		tree = root;
		j=0;
		while(ptr[j]!='\0'){
			if(ptr[j]=='0'){
				tree=tree->l;
			}
			else if(ptr[j]=='1'){
				tree=tree->r;
			}
			j++;
		}
		code = 0;
		for(j=strlen(ptr)-1;j>=0;j--){
			if(tree->data[strlen(ptr)-1-j]=='1')
			{
				code+=pow(2,j);
			}	
		}
		free(ptr);
		if(i == 0){
			fprintf(fp,"g",code);
			printf("%c",code);
		}
		else{
		fprintf(fp,"%c",code);
		printf("%c",code);	
		}
	}
	fclose(fp);
}
link* CreateTree(int height){
 		if (height == -1){return NULL;}
	link* x = (link*)malloc(sizeof(link));
	x->l = CreateTree(height-1);
	x->r = CreateTree(height-1); 
	x->data = NULL;
	if(height == 0)
		x->l = x->r=NULL;
	return x;
}
void putgrey(link* root,int height){
	FILE* fp;
	link* tree=root;
	if((fp = fopen("BinarytoGray.txt","r"))==NULL){
		printf("\nFailed to open file\n");
		DestroyTree(root);
		exit(1);
	}
	unsigned char ascii[height+1],gray[height+1];
	ascii[height]='\0';
	gray[height]='\0';
	int count = 0,i;
	while(count<256){
		fgets(ascii,sizeof(ascii),fp);
		fscanf(fp,":");
		fgets(gray,sizeof(gray),fp);
		fscanf(fp,"\n");
		int h = 0;
		tree = root;
		while(h<height){
			if(gray[h]=='0'){
				tree = tree->l;
			}
			else if(gray[h]=='1'){
				
				tree = tree->r;
			}
			h++;
			}
			tree->data =(unsigned char*)malloc(sizeof(unsigned char)*(height+1));
			for(i=0;i<=height;i++){
				tree->data[i] =ascii[i]; 	
			}
			count++;
		}	
	fclose(fp);
}
void putAscii(link* root,int height){
	FILE* fp;
	link* tree=root;
	if((fp = fopen("BinarytoGray.txt","r"))==NULL){
		printf("\nFailed to open file\n");
		DestroyTree(root);
		exit(1);
	}
	unsigned char ascii[height+1],gray[height+1];
	ascii[height]='\0';
	gray[height]='\0';
	int count = 0,i;
	while(count<256){
		fgets(ascii,sizeof(ascii),fp);
		fscanf(fp,":");
		fgets(gray,sizeof(gray),fp);
		fscanf(fp,"\n");
		int h = 0;
		tree = root;
		while(h<height){
			if(ascii[h]=='0'){
				tree = tree->l;
			}
			else if(ascii[h]=='1'){
				
				tree = tree->r;
			}
			h++;
			}
			tree->data =(unsigned char*)malloc(sizeof(unsigned char )*(height+1));
			for(i=0;i<=height;i++){
				tree->data[i] =gray[i]; 	
			}
			count++;
		}	
	fclose(fp);
}
unsigned char* chartoBinary(unsigned char n){
int i;
int size = 8 * sizeof(unsigned char);
unsigned char *ps = (unsigned char *)malloc(size+1);
for (i = size - 1; i >= 0; i--, n >>= 1){
 		ps[i] = (n & 1) + '0';
}
ps[size] = '\0';
return ps;
} 
void printTree(link * root,int height){
	if(root==NULL){
		return;
	}
	if(height == 0){
	printf("%d) %s\n",c,root->data);
	c++;
	}
	printTree(root->l,height-1);
	printTree(root->r,height-1);	
}
void DestroyTree(link* root){
	if(root == NULL){
		return;
	}
	if(root->data!=NULL){
	free(root->data);
	}
	DestroyTree(root->l);
	DestroyTree(root->r);
	
	free(root);	
}
int count(link* h){    if (h == NULL) return 0;return count(h->l) + count(h->r) + 1;}
