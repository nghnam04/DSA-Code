/*Minh họa các thao tác cơ bản trên cây tổng quát*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include<queue> // cho duyệt theo mức
#include<stack> // cho duyệt theo chiều sâu
#include<set>
using namespace std;

typedef struct TreeNode
{
	char info;
	struct TreeNode* firstChild;
	struct TreeNode* nextSibling;
} TNODE;

/*Hàm tạo ra 1 nút mới*/
TNODE* makeNewNode(char data)
{
	TNODE* p = (TNODE*)malloc(sizeof(TNODE));
	if (NULL != p) {
		p->info = data;
		p->nextSibling = p->firstChild = NULL;
	}	
	return p;
}

/*Hàm thêm nút mới vào làm nút con mới nhất của nút root hiện tại
cây ban đầu phải khác NULL
*/

void addNodeIntoTree(TNODE* root, char data)
{
	TNODE* newNode = makeNewNode(data);

	// TH1. root là nút lá, nút mới sẽ là firstChild
	if (root->firstChild == NULL) {
		root->firstChild = newNode;
	}
	else
	{ // TH2. root đã có firstChile, cần tìm vị trí con nhỏ nhất hiện tại
		TNODE* preNode = root->firstChild;
		while (preNode->nextSibling != NULL) {
			preNode = preNode->nextSibling;
		}
		// gắn nút mới là con nhỏ nhất (sau con nhỏ nhất đã tìm được)
		preNode->nextSibling = newNode;
	}
}

//Hàm tìm kiếm xem 1 khóa có xuất hiện trên cây hay không
// nếu có thì trả về nút chứa khóa
// HÀM có lỗi vì KHÔNG trả về đúng phần tử cần tìm, hãy sửa lỗi
TNODE* findKey(TNODE* root, char key)
{
	if (root == NULL || root->info == key) {
		return root;
	}
	TNODE* currChild = root->firstChild;
	TNODE* resultNode;
	while (currChild != NULL)
	{
		resultNode = findKey(currChild, key);
		if (resultNode != NULL) {
			return resultNode;
		}
		currChild = currChild->nextSibling;
	}
	return NULL;
}

// Hàm đọc cây ban đầu vào từ input
TNODE* loadTreeFromInputData()
{
	TNODE* root = NULL, *pParent;
	char nextLine[255], nextNodeLabel, parentLabel;
	while (1)
	{
		fgets(nextLine, sizeof(nextLine), stdin);
		nextLine[strcspn(nextLine, "\r\n")] = 0;

		if (strcmp(nextLine, "$") == 0) break;

		// get the root name
		if (nextLine[0] == '$') {
			nextNodeLabel = nextLine[2];
			root = makeNewNode(nextNodeLabel);
		}
		else
		{
			parentLabel = nextLine[0];
			pParent = findKey(root, parentLabel);

			if (NULL == pParent) {
				continue;
			}

			unsigned int nextIdx = 2;
			while (nextIdx < strlen(nextLine))
			{
				nextNodeLabel = nextLine[nextIdx];
				addNodeIntoTree(pParent, nextNodeLabel);
				nextIdx = nextIdx + 2;
			}
		}
	}
	
	return root;
}

// Hàm giải phóng cây có gốc là root
// Các nút cần được giải phóng lần lượt
void deleteTree(TNODE** root)
{
	if (*root == NULL) return;

	TNODE* currChild = (*root)->firstChild, * preNode;

	while (currChild != NULL) {
		preNode = currChild;
		currChild = currChild->nextSibling;
		deleteTree(&preNode);
	}

	free(*root);

	*root = NULL;
}


// Hàm duyệt cây theo chiều sâu, duyệt theo thứ tự sau dùng stack ngoài
// NOTE. Hàm đang sai thứ tự, cần đảo ngược lại thứ tự thêm con
void postOrderTraversal(TNODE* root) {
	if (root == NULL) return;
	stack<TNODE*>myStack;
	set<TNODE*> processedNode;
	myStack.push(root);

	TNODE* currNode, * currChild;

	while (!myStack.empty())
	{
		// xem xét nút hiện tại
		currNode = myStack.top();
		// nếu nút hiện tại là nút lá thì xử lý luôn
		if (currNode->firstChild == NULL) {
			myStack.pop();
			printf("%c ", currNode->info);
            if(currNode->nextSibling != NULL){
                myStack.push(currNode->nextSibling);
            }
		}
		else {
			// check xem đã xử lý chưa
			auto it = processedNode.find(currNode);
			// nếu đã có trong set thì xử lý luôn
			if (it != processedNode.end()) {
				myStack.pop();
				printf("%c ", currNode->info);
                if(currNode->nextSibling != NULL){
                myStack.push(currNode->nextSibling);
            }
			}
			else { // chua có trong set thì thêm con vào, và thêm vào set
				processedNode.insert(currNode);
				// nếu có con thì thêm con vào stack trước
				currChild = currNode->firstChild;
				if ( currChild != NULL ) myStack.push(currChild);
				else if (currNode->nextSibling !=NULL ) myStack.push(currNode->nextSibling);
			}

		}

	}
}

// test code
int main()
{
	TNODE* root = NULL;
	char nextCommand[100];
	while (1)
	{
		fgets(nextCommand, sizeof(nextCommand), stdin);
		nextCommand[strcspn(nextCommand, "\r\n")] = 0;
		if (strlen(nextCommand) == 0) continue;
		if (nextCommand[0] != '?') break;
		if (strcmp(&nextCommand[2], "readTree") == 0) {
			root = loadTreeFromInputData();
		}
		else if (strcmp(&nextCommand[2], "postOrderTraversal") == 0) {
			printf("Duyet theo thu tu sau: ");
			postOrderTraversal(root);
			printf("\n");
		}
	}

	deleteTree(&root);
	
	return 0;
}