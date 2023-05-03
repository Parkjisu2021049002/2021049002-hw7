#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 if necessary */


typedef struct Node {
	int key;
	struct Node* llink;//왼쪽으로 가는 link
	struct Node* rlink;//오른쪽으로 가는 link
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;//실제노드의 첫번쨰 노드를 가리킴

/* 함수리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음 */
int initialize(headNode** h);//이중포인터를 매개변수로 받아 호출하는 h의 값이 바뀜

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해할 것
         - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);//값을 그냥 복사하기 때문에 호출되는 값이 바뀌지 않음

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{printf("%d \n", 2021049002);
 printf("박지수");
	char command;
	int key;
	headNode* headnode=NULL;//headnode를 가리키는 포인터 현재 null

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {


	if(*h != NULL)
		freeList(*h);


	*h = (headNode*)malloc(sizeof(headNode));
	(*h)->first = NULL;
	return 1;
}

int freeList(headNode* h){

	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->rlink;
		free(prev);
	}
	free(h);
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}




/**
 * list에 key에 대한 노드 하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;

	if (h->first == NULL)
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;
	while(n->rlink != NULL) {
		n = n->rlink;
	}
	n->rlink = node;
	node->llink = n;
	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;


	if(n->rlink == NULL) {
		h->first = NULL;
		free(n);
		return 0;
	}


	while(n->rlink != NULL) {
		trail = n;
		n = n->rlink;
	}

	
	trail->rlink = NULL;
	free(n);

	return 0;
}



int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = node->llink = NULL;

	if(h->first == NULL)
	{
		h->first = node;
		return 1;
	}

	node->rlink = h->first;
	node->llink = NULL;

	listNode *p = h->first;
	p->llink = node;
	h->first = node;

	return 0;
}


int deleteFirst(headNode* h) {

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first;
	h->first = n->rlink;

	free(n);

	return 0;
}



int invertList(headNode* h) {


	if(h->first == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first;
	listNode *trail = NULL;
	listNode *middle = NULL;

	while(n != NULL){
		trail = middle;
		middle = n;
		n = n->rlink;
		middle->rlink = trail;
		middle->llink = n;
	}

	h->first = middle;

	return 0;
}


int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = node->rlink = NULL;

	if (h->first == NULL)
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;


	while(n != NULL) {
		if(n->key >= key) {
			
			if(n == h->first) {
				insertFirst(h, key);
			} else { 
				node->rlink = n;
				node->llink = n->llink;
				n->llink->rlink = node;
			}
			return 0;
		}

		n = n->rlink;
	}


	insertLast(h, key);
	return 0;
}

int deleteNode(headNode* h, int key) {

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* n = h->first;

	while(n != NULL) {
		if(n->key == key) {
			if(n == h->first) {
				deleteFirst(h);
			} else if (n->rlink == NULL){ 
				deleteLast(h);
			} else { 
				n->llink->rlink = n->rlink;
				n->rlink->llink = n->llink;
				free(n);
			}
			return 1;
		}

		n = n->rlink;
	}

	
	printf("cannot find the node for key = %d\n", key);
	return 1;
}

