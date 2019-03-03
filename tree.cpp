#include <iostream>

using namespace std;


#define MAX_TREE_SIZE 100
typedef int TElemType;

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
}BiTNode, *BiTNode; 


//	���ṹ 
typedef struct{
	PTNode nodes[MAX_TREE_SIZE];
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


// ��������� ��Ϊ�����Σ�����˳�� ������-->����-->������
void InOrderTraverse(BiTree T){
	if (T == NULL)
		return ;
	InOrderTraverse(T->lchild);
	printf("%c", T->data);
	InOrderTraverse(T->rchild);
} 


int main(){
	
	return 0;
}
