#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
// định nghĩa 1 nút trong danh sách liên kết biểu diễn đa thức bậc n 
struct Node
{
	double heSo;
	int soMu;
	struct Node* next;
};

/*
hàm cấp phát động một nút mới của danh sách và gán giá trị khởi tạo cho nút
*/

struct Node* createNewNode(double heSo, int soMu)
{
	struct Node* p = (struct Node*)malloc(sizeof(struct Node));
	p->heSo = heSo;
	p->soMu = soMu;
	p->next = NULL;

	return p;
}

/*
* Hàm clone phần tử
*/
struct Node* copyNode(struct Node* nSource)
{
	struct Node* p = (struct Node*)malloc(sizeof(struct Node));
	p->heSo = nSource->heSo;
	p->soMu = nSource->soMu;
	p->next = NULL;

	return p;
}

/*
Hàm nhập vào một đa thức bậc n với số mũ giảm dần
*/

struct Node* readData()
{
	struct Node* head = NULL, * p, * last=NULL;
	double heSo;
	int soMu, nElement;

	// doc vao so luong phan tu cua da thuc
	scanf("%d", &nElement);

	// doc vao tung phan tu
	for(int i=0;i< nElement; i++){
		scanf("%lf", &heSo);
		scanf("%d", &soMu);
		if (head == NULL) { // nếu đang rỗng thì thêm vào đầu
			head = createNewNode(heSo, soMu);
			last = head;
		}
		else { // ngược lại thêm vào cuối
			p = createNewNode(heSo, soMu);
			last->next = p;
			last = p;
		}
	}

	return head;
}

/**
In đa thức bậc n hiện có
*/

void printData(struct Node* head)
{
	printf("Content: ");
	int n = 0;
	while (head != NULL) {
		if (n > 0 && head->heSo > 0) {
			printf("+");
		}

		if (head->soMu > 1) {
			if(head->heSo!=1){
				printf("%.2lf x^%d ", head->heSo, head->soMu);
			}
			else{
				printf("x^%d ", head->soMu);
			}
		}
		else if (head->soMu == 1) {
			if (head->heSo != 1){
				printf("%.2lf x ", head->heSo);
			}
			else {
				printf(" x ");
			}
		}
		else {
			printf("%.2lf", head->heSo);
		}

		head = head->next;
		n++;
	}
	printf("\n");
}

/*
* Hàm tính và trả về giá trị của biểu thức ứng với giá trị của x
*/
double calculatePolynomialValue(struct Node* head, double x)
{
	double rel = 0;
	while (head!=NULL){
		rel += head->heSo*pow(x,head->soMu);
        head = head->next;
	}
	return rel;
}

/*
* Thêm phần tử vào cuối danh sách 
* tham số vào gồm con trỏ ở cuối danh sách để đỡ phải duyệt
* và con trỏ newEle trỏ tới phần tử mới được thêm
*/
void addElementLast(struct Node** pHead, struct Node** pLast, struct Node* newEle)
{
	if (*pLast == NULL) { // danh sách đang rỗng
		*pLast = newEle;
		*pHead = newEle;
	}
	else { // danh sách khác rỗng
		(*pLast)->next = newEle;
		(*pLast) = (*pLast)->next;
	}
}
/**
* Hàm cộng đa thức và trả về đa thức tổng qua tên hàm (first + second)
 đa thức đầu vào là first và second KHÔNG được thay đổi
*/
struct Node* addPolynomial(struct Node* first, struct Node* second)
{
	// SINH VIÊN CODE TẠI ĐÂY
    struct Node* p1 = first;
    struct Node* p2 = second;
    //tryAgain:
    if (p1 == NULL ) return p2;
    if (p2 == NULL) return p1;
    /*if ( p1 ->soMu > p2->soMu) {
        struct Node* Rel =createNewNode(p1->heSo,p1->soMu);
        p1 = p1->next;
    }  
    else if (p1->soMu == p2->soMu) {
        if (p1->heSo  + p2->heSo == 0) {
            p1 = p1->next;
            p2 = p2->next;
            // quay lai de tao node dau
            goto tryAgain;
        }
        struct Node* Rel =createNewNode(p1->heSo+p2->heSo,p1->soMu);
        p1 = p1->next;
        p2 = p2->next;
    }
    else {
        struct Node* Rel = createNewNode(p2->heSo,p2->soMu);
        p2 = p2->next;
    }*/
    struct Node* Rel = NULL;
    struct Node* last = Rel;
    while (p1 != NULL && p2 != NULL ){
            
            if ( p1 ->soMu > p2->soMu) {
            struct Node* temp = copyNode(p1);
            addElementLast(&Rel,&last,temp);
            p1 = p1->next;
        }  
        else if (p1->soMu == p2->soMu) {
            if ( p1->heSo + p2->heSo == 0) {
                p1 = p1->next;
                p2 = p2->next;
                continue;
            }
            struct Node* temp = createNewNode(p1->heSo+p2->heSo,p1->soMu);
            addElementLast(&Rel,&last,temp);
            p1 = p1->next;
            p2 = p2->next;
        }
        else {
            struct Node* temp = copyNode(p2);
            addElementLast(&Rel,&last,temp);
            p2 = p2->next;
        }
    }
    while (p1!=NULL) {
        struct Node* temp = copyNode(p1);
        addElementLast(&Rel,&last,temp);
         p1 = p1->next;   
    }
    while (p2!=NULL){
        struct Node* temp = copyNode(p2);
        addElementLast(&Rel,&last,temp);
        p2 = p2->next;
    }
	return Rel;
}

/**
* Hàm cộng giá trị đa thức second vào đa thức target
*/
void addPolynomialToCurrentPlynomial(struct Node** target, struct Node* second)
{
	struct Node* first = *target, * preFirst = NULL;;   
	struct Node* pNew = NULL;

	while (first != NULL && second != NULL)
	{
		// Nếu số mũ của đa thức 1 lớn hơn
		if (first->soMu > second->soMu) {
			preFirst = first;
			first = first->next;
		}
		else if (first->soMu == second->soMu) { // nếu số mũ bằng nhau
			if (first->heSo + second->heSo != 0)
			{
				first->heSo = first->heSo + second->heSo;
			}
			preFirst = first;
			first = first->next;
			second = second->next;
		}
		else { // ngược lại, số mũ đa thức 1 hiện tại nhỏ hơn
			pNew = copyNode(second);
			second = second->next;
			if (preFirst != NULL) { // thêm vào sau preFirst
				pNew->next = first;
				preFirst->next = pNew;
				preFirst = pNew;
			}
			else { // thêm vào trước phần tử đầu đa thức 1 nếu nó đang nhỏ hơn
				pNew->next = *target;
				*target = pNew;
				preFirst = pNew;
			}
		}
	}

	// thêm nốt các phần tử còn lại của đa thức 2 vào
	if (first == NULL) {
		first = preFirst;
	}
	while (second != NULL) {
		pNew = copyNode(second);
		second = second->next;

		// nếu danh sách ban đầu rỗng
		if (*target == NULL) {
			*target = pNew;
			first = pNew;
		}
		else {
			first->next = pNew;
			first = first->next;
		}		
	}
}

/*
* Hàm trừ 2 đa thức và trả về đa thức hiệu qua tên hàm (first - second)
 đa thức đầu vào là first và second KHÔNG được thay đổi
*/
struct Node* subtractPolynomial(struct Node* first, struct Node* second)
{
	// SINH VIÊN CODE TẠI ĐÂY

    struct Node* p1 = first;
    struct Node* p2 = second;
	// 1 trong 2 da thuc rong
    if (p1 == NULL ) {
        struct Node* Rel = NULL;
        struct Node* last = Rel;
        while (p2!=NULL){
            struct Node* temp = createNewNode(-(p2->heSo ), p2->soMu );
            addElementLast(&Rel,&last,temp);
            p2 = p2->next;
        }
        return Rel;
    }
    if (p2 == NULL) return p1;
    
    struct Node* Rel = NULL;
    struct Node* last = Rel;
    while (p1 != NULL && p2 != NULL ){
            
        if ( p1 ->soMu > p2->soMu) {
            struct Node* temp = copyNode(p1);
            addElementLast(&Rel,&last,temp);
            p1 = p1->next;
        }  
        else if (p1->soMu == p2->soMu) {
            if ( p1->heSo == p2->heSo ) {
                p1 = p1->next;
                p2 = p2->next;
                continue;
            }
            struct Node* temp = createNewNode(p1->heSo - p2->heSo,p1->soMu);
            addElementLast(&Rel,&last,temp);
            p1 = p1->next;
            p2 = p2->next;
        }
        else {
            struct Node* temp = createNewNode(-(p2->heSo),p2->soMu);
            addElementLast(&Rel,&last,temp);
            p2 = p2->next;
        }
    }
    while (p1!=NULL) {
        struct Node* temp = copyNode(p1);
        addElementLast(&Rel,&last,temp);
        p1 = p1->next;   
    }
    while (p2!=NULL){
        struct Node* temp = createNewNode(-(p2->heSo),p2->soMu);
        addElementLast(&Rel,&last,temp);
        p2 = p2->next;
    }
	return Rel;
}

/*
* Hàm nhân đa thức với 1 giá trị dạng a x ^b
* Hàm trả về tích qua tên hàm
*/
struct Node* multiplyPolynomialWithNode(struct Node* head, struct Node* multiplier)
{
	// SINH VIÊN CODE TẠI ĐÂY
	struct Node* p = head;
	struct Node* Rel = NULL;
	struct Node* last = Rel;
	while (p!=NULL){
		struct Node* temp = createNewNode(p->heSo * multiplier->heSo, p->soMu + multiplier->soMu);
		addElementLast(&Rel,&last,temp);
		p = p->next;
	}
	return Rel;
}

/*
* Hàm giải phóng bộ nhớ của đa thức
*/
void freePolynomial(struct Node** head)
{
	struct Node* curNode = NULL;
	while (*head != NULL)
	{
		curNode = *head;
		*head = (*head)->next;
		free(curNode);
	}
}

/**
* Hàm nhân 2 đa thức bằng cách nhân từng số hạng rồi cộng dồn
* Đa thức kết quả là đa thức mới trả về qua tên hàm
*/
struct Node* multiplyTwoPolynomial(struct Node* first, struct Node* second)
{
	// SINH VIÊN CODE TẠI ĐÂY
	struct Node* Rel = NULL;
	while (second != NULL) {
		struct Node* multiElement = multiplyPolynomialWithNode( first, second);
		addPolynomialToCurrentPlynomial(&Rel, multiElement);
		freePolynomial(&multiElement);
		second = second->next;
	}
	return Rel;
}


/*
Test code
*/
int main()
{
	char nextCommand[100];
	int polyIndex;
	struct Node *hPoly1=NULL, *hPoly2=NULL, *hPoly3, *aNode;
	double x, heSo;
	int soMu;
	hPoly2 = readData();
	while (1)
	{
		fgets(nextCommand, sizeof(nextCommand), stdin);
		nextCommand[strcspn(nextCommand, "\r\n")] = 0;
		if (strlen(nextCommand) == 0) continue;
		if (nextCommand[0] != '?') break;
		if (strcmp(&nextCommand[2], "readPolynomialExpression") == 0) {			
			scanf("%d", &polyIndex);
			if (polyIndex == 1) {
				hPoly1 = readData();
			}
			else{
				hPoly2 = readData();
			}
		}
		else if (strcmp(&nextCommand[2], "printPolynomial") == 0) {
			scanf("%d", &polyIndex);
			if (polyIndex == 1) {
				printData(hPoly1);
			}
			else {
				printData(hPoly2);
			}
		}
		else if (strcmp(&nextCommand[2], "calculatePolynomialValue") == 0) {
			scanf("%d", &polyIndex);
			scanf("%lf", &x);
			if (polyIndex == 1) {
				printf("Value of Polynomial at x= %.2lf is %.2lf\n",x, calculatePolynomialValue(hPoly1, x));
			}
			else {
				printf("Value of Polynomial at x= %.2lf is %.2lf\n", x, calculatePolynomialValue(hPoly2, x));
			}
		}
		else if (strcmp(&nextCommand[2], "addTwoPolynomial") == 0) {
			hPoly3 = addPolynomial(hPoly1, hPoly2);
			printData(hPoly3);
			freePolynomial(&hPoly3);
		}
		else if (strcmp(&nextCommand[2], "subtractTwoPolynomial") == 0) {
			hPoly3 = subtractPolynomial(hPoly1, hPoly2);
			printData(hPoly3);
			freePolynomial(&hPoly3);
		}
		else if (strcmp(&nextCommand[2], "multiplyTwoPolynomial") == 0) {
			hPoly3 = multiplyTwoPolynomial(hPoly1, hPoly2);
			printData(hPoly3);
			freePolynomial(&hPoly3);
		}
		else if (strcmp(&nextCommand[2], "multiplyPolynomialWithOperand") == 0) {
			scanf("%lf%d", &heSo, &soMu);
			aNode = createNewNode(heSo,soMu);
			hPoly3 = multiplyPolynomialWithNode(hPoly1, aNode);
			printData(hPoly3);
			freePolynomial(&hPoly3);
			freePolynomial(&aNode);
		}
	}

	freePolynomial(&hPoly1);
	freePolynomial(&hPoly2);
	return 0;
}