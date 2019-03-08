#include <iostream>

using namespace std;
typedef int TElemType; 

typedef struct BiTNode{
	TElemType data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree; 


/*
����������ԭ�� һ������������һ����ʱ��������Ϊ�� root���ٴβ�����ֵ key ����������бȽϣ�
�� key > root ����������������Ƚϣ���֮������������Ƚϡ�������·�ϵĸ������Ƚϡ����յ�������
��˳��Ϊ��������������� 
*/


// ���� 
int BST(BiTree T, BiTree parent, int key, BiTree *p){
	if (!T){
		*p = parent;  // ��Ҫ����������������ʹ��������*p ֻ��һ����㣬��һ�����ṹ 
		return 0;
	}
	else if (key < T->data){
		BST(T->lchild,T,key,&(*p));
	}
	else if (key > T->data){
		BST(T->rchild,T,key,&(*p));
	}
	else if (key == T->data){
		*p = T;
		return 1;
	}
}

// ���ң��ǵݹ� 
int BST2(BiTree T, BiTree f, int key, BiTree *p){

	BiTree s;	// ָ����һ��� 
	if(!T){	
		*p = f;		
		return 0;	
	}
	while(T){
		if(key == T->data){	
			*p = T;		
			return 1;	
		}
		if(key > T->data){	
			s = T;	
			T = T->rchild;		
		}
		else{	
			s = T;	
			T = T->lchild;		
		}
	}
	*p = s;
	return 0;

}

int InsertBST(BiTree *T,int key){
	BiTree p = NULL, s = NULL;

	if (!BST(*T,NULL,key,&p)){		// ��û�У���ʱ p ָ��������һ����� 

		s = (BiTree)malloc(sizeof(BiTNode));
		s->data = key;	// ������� key
		s->lchild = s->rchild = nullptr;	// ���ǵݹ飬��Ҫ�ֶ���ʼ���������� 
		if (!p){	// ���ж��Ƿ�Ϊ�� 
			*T = s;
		} 		
		else if (key > p->data){
			p->rchild = s;
		} 
		else{
			p->lchild = s;
		}

		return 1;
	}
	return 0;	
}

int Delete(BiTree *p){	// ɾ��ĳ��� ����Ҫ�޽������������� 
	if (!(*p))
		return 0;
	BiTree s = *p;
	if (!(*p)->lchild){		// ɾ�����������ֻ���������������� 
		(*p) = (*p)->rchild;
		free(s);
	}
	else if (!(*p)->rchild){
		(*p) = (*p)->lchild;
		free(s);
	}	
	else{		// �������������ڣ�����ǰ�����õ������������������Ȳ������ӣ� 
		s = (*p)->lchild;	// ����������ص� ǰ��Ϊ�ý�㣬����������������
		BiTree tmp = *p;
		if (!s->rchild){	// �ж�б��:����б��lchildΪǰ�� 
			*p = s;
			free(tmp);
			return 1;
		}
		while (s->rchild){	// �����������Ҷ˵Ľ�㣬�õ�Ϊǰ�� 
			tmp = s;
			s = s->rchild;
		} 
		(*p)->data = s->data;
		if (s->lchild){
			tmp->lchild = s->lchild;
			free(s);
		}
	} 
	return 1;
}

int DeleteBST(BiTree *T, int key)
{
	if(!(*T))
		return 0;	// �����ڹؼ��ֵ���key������Ԫ�� 
	else{
		if( key == (*T)->data )
			Delete(T);
		else if( key < (*T)->data)
			DeleteBST(&(*T)->lchild, key);
		else
			DeleteBST(&(*T)->rchild, key);
	}
}

// ��������� ��Ϊ�����Σ�����˳�� ������-->����-->������
void InOrderTraverse(BiTree T){
	if (T == NULL)
		return ;
	InOrderTraverse(T->lchild);
	printf("%d ", T->data);
	InOrderTraverse(T->rchild);
} 

int main(){
	BiTree p = NULL,T = NULL;
	int key = 51, n = 10;
	int i;
	int a[10] = {62,88,58,47,35,73,51,99,37,93};
	for( i = 0; i < n; i++ )
		InsertBST(&T, a[i]);

	printf("�������������������\n");
	InOrderTraverse(T);
	printf("\n");
	printf("ɾ��51���������������������\n");
	DeleteBST(&T,key);
	InOrderTraverse(T);
	return 0;
}

