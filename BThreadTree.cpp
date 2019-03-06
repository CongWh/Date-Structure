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

typedef char TElemType;
typedef enum{link, thread} PointTag;

typedef struct BThrNode{
	TElemType val;
	PointTag ltag, rtag;
	struct BThrNode *lchild, *rchild;
}BThrNode, *BThrTree;

// ��һ��� 
BThrTree pre;
 

// ǰ��������������ݹ������� 
// ����ǰ������ǴӸ���㿪ʼ������������Ҫ�����������Ժ�
//  
void PreThrTraverse(BThrTree T){
	if (T){
		if (!T->lchild){
			T->ltag = thread;
			T->lchild = pre;
		}
		if (!pre->rchild){
			pre->rtag = thread;
			pre->rchild = T;
		}
		pre = T;
		if (T->ltag == link)	// ��ֹҶ�ӽ���ǰ������������ 
			PreThrTraverse(T->lchild);
		if (T->rtag == link)
			PreThrTraverse(T->rchild);
	}
} 

void PreThreading(BThrTree *t, BThrTree T){
	*t = (BThrTree)malloc(sizeof(BThrNode));		// ����һ��ͷ���
	(*t)->ltag = link;
	(*t)->rtag = thread;
	(*t)->rchild = *t;	// �����ʱָ���Լ� 
	if (T == NULL){
		(*t)->lchild = *t;
	}
	else{
		pre = *t;
		(*t)->lchild = T;
		PreThrTraverse(T);
		pre->rtag = thread;		// ���һ�������Ϊͷ��㣬����ʱ�����ж�����**** 
		pre->rchild = *t;
		(*t)->rchild = pre;		// ͷ���ĺ��Ϊ���һ����㣨����������Ϊ����㣩 
	} 

}

/*
������ǰ�������� 
˼·������ǰ��������ı���˳��Ϊ  ����-->������-->����������ֱ�ӿ�ʼ�����
�������������������Ҳ�����ֱ��������������������̣� 
*/ 
void PreThrOrderTraverse(BThrTree T){
	BThrTree p = T->lchild;	// pָ������
	while (p != T){
		printf ("%c", p->val);
		if (p->ltag == link)
			p = p->lchild;
		else
			p = p->rchild;		
	}	
}

// ����������������ݹ������� 
void InThrTraverse(BThrTree T){		//  
	if (T){
		InThrTraverse(T->lchild);	// ��Ҷ�ӽ�㾡ͷ 
		if (!T->lchild){	// �ж��Ƿ���������������������ǰ�� 
			T->ltag = thread;
			T->lchild = pre;
		}
		if (!pre->rchild){	
			pre->rtag = thread;
			pre->rchild = T;
		}
		pre = T;
		InThrTraverse(T->rchild);
	}
}
/*
�������������
������һ��ͷ��㣨������ָ�����㣬������Ϊ��̣�ָ�������������һ����㣩 
*/
void InThreading(BThrTree *t, BThrTree T){
	*t = (BThrTree)malloc(sizeof(BThrNode));		// ����һ��ͷ���
	(*t)->ltag = link;
	(*t)->rtag = thread;
	(*t)->rchild = *t;	// �����ʱָ���Լ� 
	if (T == NULL){
		(*t)->lchild = *t;
	}
	else{
		pre = *t;
		(*t)->lchild = T;
		InThrTraverse(T);
		pre->rtag = thread;		// ���һ�������Ϊͷ��㣬����ʱ�����ж�����**** 
		pre->rchild = *t;
		(*t)->rchild = pre;		// ͷ���ĺ��Ϊ���һ����㣨����������Ϊ����㣩 
	} 

}

/*
���������������� 
˼·����������������ı���˳��Ϊ  ������-->����-->�������������ҵ���ͷ����������
������� rtag = link����������������������������ʱ�������������㣩���� rtag =
thread�����ڸö������������ˣ���������ָ���̣�ָ����������ɡ� 
*/ 
void InThrOrderTraverse(BThrTree T){
	BThrTree p = T->lchild;	// pָ������
	while (p != T){
		while (p->ltag == link){
			p = p->lchild;
		} 
		printf ("%c", p->val);
		while ((p->rtag == thread) && (p->rchild != T)){	// ��p�к���Һ�̲���ͷ��� 
			 p = p->rchild;
			 printf ("%c", p->val);
		}
		p = p->rchild;		
	}	
}



// ����������������ݹ������� 
void PostThrTraverse(BThrTree T){		//  
	if (T){
		InThrTraverse(T->lchild);	// ��Ҷ�ӽ�㾡ͷ
		InThrTraverse(T->rchild);
		if (!T->lchild){	// �ж��Ƿ���������������������ǰ�� 
			T->ltag = thread;
			T->lchild = pre;
		}
		if (!pre->rchild){	
			pre->rtag = thread;
			pre->rchild = T;
		}
		pre = T;
	}
}
/*
�������������
������һ��ͷ��㣨������ָ�����㣬������Ϊ��̣�ָ�������������һ����㣩 

*/
void PostThreading(BThrTree *t, BThrTree T){
	*t = (BThrTree)malloc(sizeof(BThrNode));		// ����һ��ͷ���
	(*t)->ltag = link;
	(*t)->rtag = thread;
	(*t)->rchild = *t;	// �����ʱָ���Լ� 
	if (T == NULL){
		(*t)->lchild = *t;
	}
	else{
		pre = *t;
		(*t)->lchild = T;
		PostThrTraverse(T);
		pre->rtag = thread;		// ���һ�������Ϊͷ��㣬����ʱ�����ж�����**** 
		pre->rchild = *t;
		(*t)->rchild = pre;		// ͷ���ĺ��Ϊ���һ����㣨����������Ϊ����㣩 
	} 

}

/*
���������������� 
˼·����������������ı���˳��Ϊ  ������-->������-->���㣬�����ҵ���ͷ����������
������� rtag = link����������������������������ʱ�������������㣩���� rtag =
thread�����ڸö������������ˣ���������ָ���̣�ָ����������ɡ� 
*/ 
void PostThrOrderTraverse(BThrTree T){
	BThrTree p = T->lchild;	// pָ������
	while (p != T){
		while (p->ltag == link && p->lchild != pre) {
			p = p->lchild;
		} 
		while (p->rtag == link && p->rchild != pre){
			p = p->rchild;
		} 
		if ((p->rtag == thread) && (p->rchild != T)){	// ��p�к���Һ�̲���ͷ��� 
			 printf ("%c", p->val);
			 pre = p;
			 p = p->rchild;
			 
		}

//		p = p->rchild;
//		printf ("%c", p->val);
				
	}	
}






// ǰ��������������� 
void CreateBiTree(BThrTree *T){

	char c;
	scanf("%c", &c);
	if (c == '#'){
		*T = NULL;
		return;
	}	
	else{
		*T = (BThrTree)malloc(sizeof(BThrNode));
		(*T)->val = c;
		(*T)->ltag = link;
		(*T)->rtag = link;
	} 
	CreateBiTree(&(*T)->lchild);
	CreateBiTree(&(*T)->rchild);
}

void delBiTree(BThrTree *T){
	if (*T){
		delBiTree(&(*T)->lchild);
		delBiTree(&(*T)->rchild);
		free(*T);
		*T = nullptr;		
	}
}


int main(int argc, char *argv[])
{
	BThrTree T = NULL,t = NULL;
	printf("��ǰ����������㣺");
	CreateBiTree(&T);
	printf("��������������������㣺");
	InThreading(&t,T);
	InThrOrderTraverse(t);
	delBiTree(&T);
	delBiTree(&t);
/*
	printf("ǰ������������������㣺");
	PreThreading(&t,T);
	PreThrOrderTraverse(t);
	delBiTree(&T);
	delBiTree(&t); */
/*	
	printf("��������������������㣺");
	PostThreading(&t,T);
	PostThrOrderTraverse(t);
	delBiTree(&T);
	delBiTree(&t); */
	return 0;
}

