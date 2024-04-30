
#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node //노드가 실제 키값을 가지고 있는 구조체 선언
{
	int key; //int형 변수 key선언
	struct Node* link; //노드 구조체의 포인터 link 선언
} listNode; //listNode 구조체 정의

typedef struct Head //likedlist를 가리키는 첫번째 head 구조체 선언
{
	struct Node* first; //head 구조체의 포인터 first 선언
} headNode; 


/* 함수 리스트 */
headNode* initialize(headNode* h); //headnode 포인터를 매개인자로 받아 연결리스트의 헤드 노드를 초기화하고, 초기화된 헤드 노드를 가리키는 포인터를 반환하는 initialize 함수
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

    printf("-----[신혜원] [2023041057]-----\n");

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
			scanf("%d", &key); //key값 입력 받기
			insertNode(headnode, key); //headnode와 입력받은 key값을 매개인수로 insertnode 함수 실행
			break;
		case 'd': case 'D': //대소문자 d입력 받으면
			printf("Your Key = "); //key입력하라고 출력
			scanf("%d", &key); //key값 입력 받기
			deleteNode(headnode, key); //headnode와 입력받은 key값을 매개인수로 deletenode함수 실행
			break;
		case 'n': case 'N': //대소문자 n입력 받으면
			printf("Your Key = "); //key입력하라고 출력
			scanf("%d", &key); //key값 입력 받기
			insertLast(headnode, key); //headnode와 입력받은 key값을 매개인수로 insertnode함수 실행
			break;
		case 'e': case 'E': //대소문자 e입력 받으면
			deleteLast(headnode); //headnode를 매개인자로 deletelast 함수 실행
			break;
		case 'f': case 'F': //대소문자 f입력 받으면
			printf("Your Key = "); //key입력하라고 출력
			scanf("%d", &key); //key값 입력 받기
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

	}while(command != 'q' && command != 'Q'); //대소문자 q가 입력되지 않을 동안 반복

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
		p = p->link; //p에 p의 link 할당
		free(prev); //prev 메모리 해제
	}
	free(h); //h에 할당된 메모리 헤제
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) 
{

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listnode의 크기만큼 동적으로 메모리 할당하여 node에 할당
	node->key = key; //node의 key에 key값 할당

	node->link = h->first; //node의 key값에 h의 key값 할당
	h->first = node; //h의 first에 node 값 대입

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) 
{
    listNode* node = (listNode*)malloc(sizeof(listNode)); //listnode 구조체 크기만큼 listnode의 포인터 node에 메모리 할당
    node->key = key; //node의 key에 입력받은 key 할당
    node -> link=NULL; //node의 link에 NULL 값 할당
    
    if(h->first==NULL)  //h의 first가 NULL이면
    {
        h->first =node; //h의 first에 node 할당
        return 0;
    }
	
    listNode* n= h-> first; //listnode의 포인터 n에 h의 first 값 할당
    listNode* trail = h->first; //listnode의 포인터 trail에 h의 first 값 할당

    while(n!=NULL) //n이 NULL이 아닐동안
    {
        if(n->key >=key) //n의 key가 key보다 크거나 같다면
        {
            if(n== h-> first) //n이 h의 first와 같다면
            {
                h->first=node; //h의 first에 node 값 할당
                node->link=n; //node의 link에 n 값 할당
            }
            else{ //n이 h의 first와 같이 않다면
                node->link=n; //node의 link에 n값 할당
                trail->link=node; //trail의 link에 node 값 할당
            }
            return 0;
        }
        trail=n;  //trail에 n 값 할당
        n= n->link; //n에 n의 link 값 할당
    }
    trail->link=node; //trail의 link에 node 삽입
    return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key)
{

    listNode* node = (listNode*)malloc(sizeof(listNode)); //listnode의 크기만큼 listnode의 포인터 node에 메모리 할당
    node -> key=key; //node의 key에 key값 할당
    node -> link =NULL; //node의 link에 NULL값 할당

    if(h->first == NULL) //h의 first가 NULL이라면
    {
        h -> first = node; //h의 first에 node 값 할당
        return 0;
    }

    listNode* n=h->first; //listnode의 포인터 n에 h의 first 값 할당
    while(n->link!=NULL) //n의 link가 NULL이 아닐 동안
    {
        n=n->link; //n에 n의 link값 할당
    }
    n->link=node; //n의 link에 node의 값 할당
    return 0;

}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h)
 {
    if(h->first == NULL) //h의 first가 NULL이라면
    {
        printf("nothing to delete. \n"); //삭제할 것이 없다고 출력
        return 0;
    }
    listNode* n = h->first; //listnode의 포인터 n에 h의 first값 할당

    h->first = n->link; //h의 first에 n의 link값 할당
    free(n); //n에 할당된 메모리 해제

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key)
{
    if(h->first==NULL) //h의 first가 NULL이라면
    {
        printf("nothing to delete. \n"); //삭제할것이 없다고 출력
        return 0;
    }
    listNode* n=h->first; //listnode의 포인터 n에 first 값 할당
    listNode* trail=NULL; //listnode의 포인터 trail에 NULL 값 할당

    while(n!=NULL) //n이 NULL이 아닐동안
    {
        if(n->key == key) //n의 key가 key값과 같다면
        {
            if(n==h-> first) //n이 h의 first와 같다면
            {
                h->first = n->link; //h의 first에 n의 link값 할당
            }
            else
            {
                trail->link = n->link; //trail의 link에 n의 link 값 할당
            }
            free(n); //n에 할당된 메모리 해제
            return 0;
        }
        trail=n; //trail에 n값 할당
        n=n->link; //n에 n의 link 값 할당
    }

    printf("cannot find the node for key = %d\n", key); //key의 node를 찾을 수 없다고 출력
	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) 
{
    if(h->first==NULL) //h의 first가 NULL이라면
    {
        printf("nothing to delete.\n"); //삭제할 것이 없다고 출력
        return 0;
    }

    listNode* n = h->first; //listnode의 포인터 n에 h의 first 값 할당
    listNode* trail = NULL; //listnode의 포인터 trail에 NULL값 할당

    if(n->link == NULL) //n의 link가 비어있다면
    {
        h->first=NULL; //h의 first에 NULL 값 할당
        free(n); //n에 할당된 메모리 해제
        return 0;
    }

    while(n->link!=NULL) //n의 link가 NULL이 아닐동안
    {
        trail=n; //trail에 n 값 할당
        n=n->link; //n에 n의 link값 할당
    }

    trail->link=NULL; //trail의 link에 NULL값 할당
    free(n); //n에 할당된 메모리 해제

    return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) 
{
    if(h->first==NULL) //h의 first가 NULL이라면
    {
        printf("nothing to invert\n"); //전환할것이 없다고 출력
        return 0;
    }
    listNode *n=h->first; //listnode의 포인터 n에 h의 first값 할당
    listNode *trail=NULL; //listnode의 포인터 trail에 NULL값 할당
    listNode *middle=NULL; //listnode의 포인터 middle에 NULL값 할당

    while(n!=NULL) //n이 NULL이 아닐동안
    {
        trail=middle; //trail에 middle값 할당
        middle=n; //middle에 n값 할당
        n=n->link; //n에 n의 link값 할당
        middle->link = trail; //middle의 link에 trail 값 할당
    }
    h-> first = middle; //h의 first에 middle값 할당

	return 0;
}


void printList(headNode* h) 
{
	int i = 0; //int형 변수 i를 0으로 초기화
	listNode* p; 

	printf("\n---PRINT\n");

	if(h == NULL) //h의 값이 NULL이라면 
    {
		printf("Nothing to print\n"); //print할 것이 없다고 출력
	}

	p = h->first; //p에 h의 first값 할당 

	while(p != NULL) //p가 NULL이 아닐동안 
    {
		printf("[ [%d]=%d ] ", i, p->key); //i값과 p의 key값 출력
		p = p->link; //p에 p의 link값 할당
		i++; 
	}

	printf("  items = %d\n", i);
}

