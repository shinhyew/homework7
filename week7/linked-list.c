/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node //노드가 실제 키값을 가지고 있는 구조체
{
	int key; //int형 변수 key선언
	struct Node* link; //노드 구조체의 포인터 link 선언
} listNode;

typedef struct Head //likedlist를 가리키는 첫번째 head 구조체 선언
{
	struct Node* first; //head 구조체의 포인터 first 선언
} headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h); /*headnode 포인터를 매개인자로 받아 연결리스트의 헤드 노드를 초기화하고, 초기화된 헤드 노드를 가리키는 포인터를 반환하는 initialize 함수*/
int freeList(headNode* h);  //headnode 포인터를 매개인자로 받는 int형 함수 freelist

int insertFirst(headNode* h, int key); //headnode 포인터와 int형 변수 key를 매개인자로 받는 int형 함수 insertfirst
int insertNode(headNode* h, int key); //headnode 포인터와 int형 변수 key를 매개인자로 받는 int형 함수 insertnode
int insertLast(headNode* h, int key); //headnode 포인터와 int형 변수 key를 매개인자로 받는 int형 함수 insertlast

int deleteFirst(headNode* h); //headnode 포인터를 매개인자로 받는 int형 함수 deletefirst
int deleteNode(headNode* h, int key); //headnode 포인터와 int형 변수 ket를 매개인자로 받는 int형 함수 deletenode
int deleteLast(headNode* h); //headnode 포인터를 매개인자로 받는 int형 함수 deletelast
int invertList(headNode* h); //headnode 포인터를 매개인자로 받는 int형 함수 invertlist

void printList(headNode* h); //headnode 포인터를 매개인자로 받는 함수 printlist

int main()
{
	char command; //char형 변수 command 선언
	int key; //int형 변수 key 선언
	headNode* headnode=NULL; //headnode 포인터 headnode 선언 후 null로 초기화 

    printf("-----[신혜원] [2023041057]-----");

	do //menu 출력
    {
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = "); //command 입력을 받기 위한 출력
		scanf(" %c", &command); //입력받은 키 command에 저장

		switch(command) { //command에 따른 switch 조건문
         case 'z': case 'Z': //z대소문자 입력 받으면
            headnode = initialize(headnode); //headenode에 초기화한 headnode값 할당
			break;
		case 'p': case 'P': //대소문자 p입력 받으면
			printList(headnode); //headnode를 매개인자로 받는 printlist함수 출력
			break;
		case 'i': case 'I': //대소문자 i입력 받으면
			printf("Your Key = "); //key입력하라고 출력
			scanf("%d", &key); //key 입력 받기
			insertNode(headnode, key); //headnode와 입력받은 key값을 매개인수로 insertnode 함수 실행
			break;
		case 'd': case 'D': //대소문자 d입력 받으면
			printf("Your Key = "); //key입력하라고 출력
			scanf("%d", &key); //key 입력 받기
			deleteNode(headnode, key); //headnode와 입력받은 key값을 매개인수로 deletenode함수 실행
			break;
		case 'n': case 'N': //대소문자 n입력 받으면
			printf("Your Key = "); //key입력하라고 출력
			scanf("%d", &key); //key 입력 받기
			insertLast(headnode, key); //headnode와 입력받은 key값을 매개인수로 insertnode함수 실행
			break;
		case 'e': case 'E': //대소문자 e입력 받으면
			deleteLast(headnode); //headnode를 매개인자로 deletelast 함수 실행
			break;
		case 'f': case 'F': //대소문자 f입력 받으면
			printf("Your Key = "); //key입력하라고 출력
			scanf("%d", &key); //key 입력 받기
			insertFirst(headnode, key); //headnode와 key를 매개인수로 insertfirst함수 실행
			break;
		case 't': case 'T': //대소문자 t입력 받으면
			deleteFirst(headnode); //headnode를 매개인자로 deletefirst 함수 실행
			break;
		case 'r': case 'R': //대소문자 r입력 받으면
			invertList(headnode); //headnode를 매개인자로 invertlist 함수 실행
			break; 
		case 'q': case 'Q': //대소문자 q입력 받으면
			freeList(headnode); //headnode를 매개인자로 freelist 함수 실행
			break;
		default: //그 외 입력시
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //q가 입력되지 않은 동안 반복

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL) //headnode h가 null이 아니면
		freeList(h); //할당된 메모리 해제

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode)); //headnode의 크기만큼 temp에 저장
	temp->first = NULL; //temp의 first에 null 저장
	return temp; //temp 리턴
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first; //listnode의 포인터 p선언 후 h를 통해 first 노드를 p에 할당

	listNode* prev = NULL; //listnode의 포인터 prev 선언 후 null값 할당
	while(p != NULL) { //p가 null이 아닐동안
		prev = p; //prev에 p값 할당
		p = p->link; //p의 link를 p에 할당
		free(prev); //prev 메모리 해제
	}
	free(h); //h 메모리 헤제
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) 
{

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listnode 구조체 크기만큼 동적으로 메모리 할당하여 node에 할당
	node->key = key; //node의 key에 key값 할당

	node->link = h->first; //node의 key값에 h의 key값 할당
	h->first = node; //h의 first에 node 값 대입

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) 
{
    listNode* newNode = (listNode*)malloc(sizeof(listNode));
    node->key = key;
    node -> link=NULL;
    
    if(h->first==NULL) 
    {
        h->first =newNode;
        return 0;
    }
	
    listNode* n= h-> first;
    listNode* trail = h->first;

    while(n!=NULL)
    {
        if(n->key >=key)
        {
            if(n== h-> first)
            {
                h->first=node;
                node->link=n;
            }
            else{
                node->link=n;
                trail->link=node;
            }
            return 0;
        }
        trail=n;
        n= n->link;
    }
    trail->link=node;
    return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key)
{

    listNode* node = (listNode*)malloc(sizeof(listNode));
    node -> key=key;
    node -> link =NULL;

    if(h->first == NULL)
    {
        h -> first = node;
        return 0;
    }

    listNode* n=h->first;
    while(n->link!=NULL)
    {
        n=n->link;
    }
    n->link=node;
    return 0;

}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h)
 {
    if(h->first == NULL)
    {
        printf("nothing to delete. \n");
        return 0;
    }
    listNode* n = h->first;

    h->first = n->link;
    free(n);

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key)
{
    if(h->first==NULL)
    {
        printf("nothing to delete. \n");
        return 0;
    }
    listNode* n=h->first;
    listNode* trail=NULL;

    while(n!=NULL)
    {
        if(n->key == key)
        {
            if(n==h-> first)
            {
                h->first = n->link;
            }
            else
            {
                trail->link = n->link;
            }
            free(n);
            return 0;
        }
        trail=n;
        n=n->link;
    }

    printf("cannot find the node for key = %d\n", key);
	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) 
{
    if(h->first==NULL)
    {
        printf("nothing to delete.\n");
        return 0;
    }

    listNode* n = h->first;
    listNode* trail = NULL;

    if(n->link == NULL)
    {
        h->first=NULL;
        free(n);
        return 0;
    }

    while(n->link!=NULL)
    {
        trail=n;
        n=n->link;
    }

    trail->link=NULL;
    free(n);

    return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) 
{
    if(h->first==NULL)
    {
        printf("nothing to invert...\n");
        return 0;
    }
    listNode *n=h->first;
    listNode *trail=NULL;
    listNode *middle=NULL;

    while(n!=NULL)
    {
        trail=middle;
        middle=n;
        n=n->link;
        middle->link = trail;
    }
    h-> first = middle;

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
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

