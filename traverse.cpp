/*
Tree: 	
						A
				B				C
			D				E		F		
		 G	  H			  I	


ǰ�������ABDGHCEIF
ǰ�����룺ABDG##H###CEI###F## 

*/
#include <iostream>
#include <queue>
#include <stack>

using namespace std;


#define MAX_TREE_SIZE 100
typedef char TElemType;

// ˫�ױ�ʾ�� 
struct PTNode{
	TElemType data;
	int parent;		// root's parent: -1
}PTNode;

// ˫�ױ�ʾ����չ�����ӳ�����
typedef struct PTNode1{
	TElemType data;
	int parent;		
	int lchild;   // Not exist: -1 
}PTNode1; 

// ���ӱ�ʾ��
typedef struct CLinkedList{
	TElemType data;
	TElemType *next;
}CLinkedList;

typedef struct CTNode{
	TElemType data;
	CLinkedList *firstChild;
}CTNode; 

// �ֵܱ�ʾ���� �����ӵ�������˶�����
typedef struct BTNode{
	TElemType data;
	struct BTNode *firstChild, *rightBro;
}BTNode; 


// �������Ķ�������
typedef struct BiTNode{
	TElemType data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree; 


//	���ṹ 
typedef struct Tree{
	struct PTNode nodes[MAX_TREE_SIZE];
	int r, n;
};


// ��������� ��Ϊ�����Σ�����˳�� ����-->������-->������
void PreOrderTraverse(BiTree T){
	if (T == NULL)
		return ;
	printf("%c",T->data);
	PreOrderTraverse(T->lchild);
	PreOrderTraverse(T->rchild);
} 
// ��������� �ǵݹ顣����ջ���������ж����������Ĵ��ڡ� 
void PreOrderTraverseLoop(BiTree T){
	stack<BiTree> s;
	BiTree t = T, tmp;
	
	while (t != NULL || !s.empty()){	// ��ջΪ�����������Ϊ��ʱ���� 
		
		while (t != NULL){		// �������ڣ�����������, ֱ�����һ�������������������ڣ� 
			printf ("%c", t->data);
			s.push(t);
			t = t->lchild;
		}
		tmp = s.top();		// ��ջ���ص��ϸ���㣬���������� 
		t = tmp->rchild;
		s.pop();
	}
} 


// ��������� ��Ϊ�����Σ�����˳�� ������-->����-->������
void InOrderTraverse(BiTree T){
	if (T == NULL)
		return ;
	InOrderTraverse(T->lchild);
	printf("%c", T->data);
	InOrderTraverse(T->rchild);
} 
// ��������� �ǵݹ顣����ջ���������ж����������Ĵ��ڡ� 
void InOrderTraverseLoop(BiTree T){
	stack<BiTree> s;
	BiTree t = T;
	
	while (t != NULL || !s.empty()){	// ��ջΪ�����������Ϊ��ʱ���� 
		
		while (t != NULL){		// �������ڣ�����������, ֱ�����һ�������������������ڣ� 
			s.push(t);
			t = t->lchild;
		}
		t = s.top();		// ��ջ���ص��ϸ����ڵĽ�㣬��� 
		s.pop();
		printf ("%c", t->data);
		t = t->rchild;
	}
} 



// ��������� ��Ϊ�����Σ�����˳�� ������-->������-->����
void PostOrderTraverse(BiTree T){
	if (T == NULL)
		return ;
	PostOrderTraverse(T->lchild);
	PostOrderTraverse(T->rchild);
	printf("%c", T->data);
} 
// ��������� �ǵݹ顣����ջ���������ж����������Ĵ��ڡ� 
void PostOrderTraverseLoop(BiTree T){
	stack<BiTree> s;
	BiTree t = T,top,last = nullptr;
	
	while (t != NULL || !s.empty()){	// ��ջΪ�����������Ϊ��ʱ���� 
		
		while (t != NULL){		// �������ڣ�����������, ֱ�����һ�������������������ڣ� 
			s.push(t);
			t = t->lchild;
		}
		top = s.top();	// ��ջ���ص��ϸ����ڵĽ�㣬��� 
		if (top->rchild == NULL || top->rchild == last){
			printf ("%c", top->data);
			s.pop();
			last = top;
		}
		else
			t = top->rchild;
	}
} 



// ��������� ���������������ϵ��¡����������α����� 
// ˼·������һ�����У�ĳһ��� A ����ӣ�A����ʱ�����ĺ�����ӣ��������С� 
void LevelOrderTraverse(BiTree T){
	if (T == NULL)
		return;
	queue<BiTree> q;
	BiTree front; 
	q.push(T); 
	while (!q.empty()){
		front = q.front();
		q.pop();
		if (front->lchild)
			q.push(front->lchild);
		if (front->rchild)
			q.push(front->rchild);
		printf("%c", front->data);
	}
	
} 

// ǰ����������� 
void CreateBiTree_Pre(BiTree *T){
	char c;
	scanf("%c",&c);
	
	if (c == '#'){
		*T = NULL;
		return;
	}
	
	*T = (BiTree)malloc(sizeof(BiTNode));
	(*T)->data = c;
	
	CreateBiTree_Pre(&(*T)->lchild);
	CreateBiTree_Pre(&(*T)->rchild);
	return;	
}

// �ͷŶ�������ռ���ڴ� 
void delNode(BiTree *T) 
{
  if (*T == NULL) 
  	return;
  delNode(&(*T)->lchild);
  delNode(&(*T)->rchild);
  free(*T);
  *T = NULL; 
  return;
}

int main(int argc, char *argv[])
{
	BiTree T = NULL;
	printf("��ǰ����������㣺");
	CreateBiTree_Pre(&T);
	printf("ǰ�������");
	PreOrderTraverse(T);
	printf("\nǰ��ǵݹ������");
	PreOrderTraverseLoop(T);
	printf("\n���������");
	InOrderTraverse(T);
	printf("\n����ǵݹ������");
	InOrderTraverseLoop(T);
	printf("\n���������");
	PostOrderTraverse(T);
	printf("\n����ǵݹ������");
	PostOrderTraverseLoop(T);
	printf("\n���������");
	LevelOrderTraverse(T);
	delNode(&T);
	
	
	return 0;
}

