#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct booknode{
	char* bookTitle;
	char* bookAuthors;
	int bookYear;
	int bookPages;
	struct booknode* right;
	struct booknode* left;
	};
	
struct booknode* newNode(char* title,char* author,int year,int pages){

	struct booknode* node = (struct booknode*)malloc(sizeof(struct booknode));
	
	node->bookTitle = (char*) malloc(sizeof(char)*256);
	node->bookAuthors = (char*) malloc(sizeof(char)*256);
	
	strcpy(node->bookTitle,title);
	strcpy(node->bookAuthors,author);
	
	node->bookYear = year;
	node->bookPages = pages;

	node->left = NULL;
	node->right = NULL;

	return(node);
}

struct booknode* insertY(struct booknode * root, struct booknode * new) {

	if (root == NULL)
		return new;
	else if (new->bookYear > root->bookYear)
		root->right = insertY(root->right, new);
	else 
		root->left = insertY(root->left, new);
	return(root);
}

struct booknode* insertT(struct booknode * root, struct booknode * new) {

	if (root == NULL)
		return new;
	else if (strcmp(new->bookTitle , root->bookTitle)>0) 
		root->right = insertT(root->right, new);
	else 
		root->left = insertT(root->left, new);
	return(root);
}


void inorder(struct booknode *root) {
if (root != NULL) 
	{
	inorder(root->left); 
	printf(root->bookTitle); 
	printf("\n");
	inorder(root->right); 
	}
}


int main(){
	
	
	
	
	}
