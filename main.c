#include <stdio.h>
#include <stdlib.h>
struct tree{
	int data;
	struct tree *left;
	struct tree *right;
};

struct tree *insert(struct tree *root,int data){
	struct tree* newnode = (struct tree*)malloc(sizeof(struct tree));
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->data = data;
	if(root == NULL) return newnode;
	else{
		struct tree* cpy = (struct tree*)malloc(sizeof(struct tree));
		cpy = root;
		while(1){
			if(cpy->left == NULL && data < cpy->data){ cpy->left = newnode; return root;}
			else if(cpy->right == NULL && data >= cpy->data){ cpy->right = newnode; return root;}
			else if(data < cpy->data) cpy = cpy->left;
			else cpy = cpy->right;
		}
	}
}

struct tree *findpredecessor(struct tree *root){
	struct tree* cpy = (struct tree*)malloc(sizeof(struct tree));
	struct tree* pcpy = (struct tree*)malloc(sizeof(struct tree));
	cpy = root;
	pcpy = root;
	while(cpy->right != NULL){pcpy = cpy; cpy = cpy->right;}
	return pcpy;
}

struct tree *findsuccessor(struct tree *root){
	struct tree* cpy = (struct tree*)malloc(sizeof(struct tree));
	struct tree* pcpy = (struct tree*)malloc(sizeof(struct tree));
	cpy = root;
	pcpy = root;
	while(cpy->left != NULL){pcpy = cpy; cpy = cpy->left;}
	return pcpy;
}

int height(struct tree *root){
	if(root == NULL) return 0;
	else{
		int l = height(root->left);
		int r = height(root->right);
		if(l>r) return l+1;
		else return r+1;
	}
}

int numnode(struct tree *root){
	if(root == NULL) return 0;
	else return numnode(root->right) + numnode(root->left) +1;
}

int internal(struct tree *root){
	if(root == NULL) return 0;
	if(root->left == NULL && root->right == NULL) return 0;
	else return internal(root->left) + internal(root->right) +1;
}

int external(struct tree *root){
	if(root == NULL) return 0;
	if(root->left == NULL && root->right == NULL){printf("->%d\n",root->data); return 1;}
	else return external(root->left) + external(root->right);
}
void delete(struct tree *root,struct tree *pre,int d,int data){
	struct tree* tmp = root;
	if(root == NULL) return;
	if(root->data == data){
		if(root->left == NULL && root->right == NULL){
			if(d) pre->right = NULL;
			else pre->left = NULL;
		}
		else if(root->left != NULL && root->right == NULL){
			root->data = root->left->data;
			root->left = NULL;
		}
		else if(root->left == NULL && root->right != NULL){
			root->data = root->right->data;
			root->right = NULL;
		}
		else if(root->left != NULL && root->right != NULL){
			struct tree* cpy = (struct tree*)malloc(sizeof(struct tree));
			cpy = findpredecessor(root->left);
			if(cpy->right !=NULL){
				root->data= cpy->right->data;
				 cpy->right->data = -1;
				delete(tmp,tmp,0,cpy->right->data);
			}
			else{
			 root->data= cpy->data;
			cpy->data = -1;
			delete(tmp,tmp,0,cpy->data);
			}
		}
		return;
	}
	delete(root->left,root,0,data);
	delete(root->right,root,1,data);

}

struct tree *search(struct tree *root,int data){
	if(root == NULL || root->data == data) return root;
	search(root->left,data);
	search(root->right,data);
}

// print functions
void inorder(struct tree *root){
	if(root == NULL) return;
	inorder(root->left);
	printf("%d\n",root->data);
	inorder(root->right);
}
void preorder(struct tree *root){
	if(root == NULL) return;
	printf("%d\n",root->data);
	preorder(root->left);
	preorder(root->right);
}
void postorder(struct tree *root){
	if(root == NULL) return;
	postorder(root->left);
	postorder(root->right);
	printf("%d\n",root->data);
}


int main()
{
	struct tree *root = (struct tree *)malloc(sizeof(struct tree));
	root = NULL;
	root = insert(root,34);
	root = insert(root,4);
	root = insert(root,44);
	root = insert(root,42);
	root = insert(root,41);
	root = insert(root,39);
	root = insert(root,40);
	root = insert(root,43);
	root = insert(root,
6);
	root = insert(root,312);
	root = insert(root,3);
	delete(root,root,0,312);
	int y =internal(root);
	int x =external(root);
	printf("internal: %d, external: %d\n",y,x);
	/*inorder(root);
	printf("------\n");
	preorder(root);*/
    return 0;
}

