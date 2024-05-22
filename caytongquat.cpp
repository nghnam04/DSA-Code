/*Minh họa các thao tác cơ bản trên cây tổng quát*/

 

#include <stdio.h>
#include <stdlib.h>

 

#include<queue> // cho duyệt theo mức
#include<stack> // cho duyệt theo chiều sâu
#include<set>
using namespace std;

 

typedef struct TreeNode
{
    char info;
    struct TreeNode *firstChild;
    struct TreeNode *nextSibling;
} TNODE;

 

/*Hàm tạo ra 1 nút mới*/
TNODE *makeNewNode(char data)
{
    TNODE *p = (TNODE*)malloc(sizeof(TNODE));
    p->info = data;
    p->nextSibling=p->firstChild=NULL;
    return p;
}

 

/*Hàm thêm nút mới vào làm nút con mới nhất của nút root hiện tại
cây ban đầu phải khác NULL
*/

 

void addNodeIntoTree(TNODE * root, char data)
{
    TNODE *newNode = makeNewNode(data);
    
    // TH1. root là nút lá, nút mới sẽ là firstChild
    if(root->firstChild==NULL){
        root->firstChild = newNode;
    } else
    { // TH2. root đã có firstChile, cần tìm vị trí con nhỏ nhất hiện tại
        TNODE *preNode = root->firstChild;
        while(preNode->nextSibling!=NULL){
            preNode=preNode->nextSibling;
        }
        // gắn nút mới là con nhỏ nhất (sau con nhỏ nhất đã tìm được)
        preNode->nextSibling = newNode;
    }
}

 

// hàm tạo cây mặc định ban đầu
TNODE *createAGeneralTree()
{
    // gốc là A
    TNODE *root = makeNewNode('A');
    // thêm B và C là con của A theo đúng thứ tự
    addNodeIntoTree(root,'B');
    addNodeIntoTree(root,'C');
    // thêm K là con của B
    addNodeIntoTree(root->firstChild,'K');
    // thêm D,E,F là con của C
    TNODE *subRoot = root->firstChild->nextSibling;  
    addNodeIntoTree(subRoot,'D');
    addNodeIntoTree(subRoot,'E');
    addNodeIntoTree(subRoot,'F');
    // thêm G,H là con của E
    subRoot = root->firstChild->nextSibling->firstChild->nextSibling;
    addNodeIntoTree(subRoot,'G');
    addNodeIntoTree(subRoot,'H');
    
    return root;
}
// Hàm duyệt cây theo mức == duyệt theo chiều rộng
void levelTraversal(TNODE *root)
{
    if(NULL==root) {
        return;
    }
    queue<TNODE*> myQueue;
    myQueue.push(root);
    
    TNODE* currNode, *currChild;
    // lặp khi mà queue còn khác rỗng
    while(!myQueue.empty())
    {
        currNode = myQueue.front();
        myQueue.pop();
        printf("%c ", currNode->info);
        
        // thêm các con của nút hiện tại vào tiếp queue
        currChild = currNode->firstChild;
        while(currChild!=NULL){
            myQueue.push(currChild);
            currChild=currChild->nextSibling;
        }
    }
}
// Hàm duyệt cây theo chiều sâu, duyệt theo thứ tự trước cài đặt đệ quy
void preOrderTraversal(TNODE* root){
   if(root == NULL) return;   
   printf("%c ", root->info);
   // gọi đệ quy đến các cây con
   TNODE* currChild = root->firstChild;
   
   while(currChild!=NULL){
        preOrderTraversal(currChild);
        currChild = currChild->nextSibling;
   }
}

 

// Hàm duyệt cây theo chiều sâu, duyệt theo thứ tự sau dùng stack ngoài
// NOTE. Hàm đang sai thứ tự, cần đảo ngược lại thứ tự thêm con
void postOrderTraversal(TNODE* root){
   if(root == NULL) return;   
   stack<TNODE*>myStack;
   set<TNODE*> processedNode;
   myStack.push(root);
   
   TNODE* currNode, *currChild;
   
   while(!myStack.empty())
   {
           // xem xét nút hiện tại
           currNode = myStack.top();
           // nếu nút hiện tại là nút lá thì xử lý luôn
        if(currNode->firstChild==NULL){
               myStack.pop();
               printf("%c ", currNode->info);
        }
        else { 
            // check xem đã xử lý chưa
            auto it = processedNode.find(currNode);
            // nếu đã có trong set thì xử lý luôn
            if(it!= processedNode.end()) {
                myStack.pop();
                printf("%c ", currNode->info);
            }
            else{ // chua có trong set thì thêm con vào, và thêm vào set
                processedNode.insert(currNode);
                // nếu có con thì thêm con vào stack trước
                currChild = currNode->firstChild;   
                while(currChild!=NULL){
                    myStack.push(currChild);
                    currChild = currChild->nextSibling;
                }
            }
            
        }
        
   }
}

 

// hàm tính và trả về độ cao của root
// độ cao của lá là 0
int findHeight(TNODE* root)
{
    if(root == NULL) { // nút rỗng
        return -1;
    }
    if(root->firstChild == NULL){ // nút lá
        return 0;
    }
    int maxChildHeight = -10, currChildHeight;
    TNODE* currChild = root->firstChild;
    while(currChild!=NULL)
    {
        currChildHeight = findHeight(currChild);
        if(currChildHeight>maxChildHeight){
            maxChildHeight = currChildHeight;
        }
        currChild=currChild->nextSibling;
    }
    return 1 + maxChildHeight;
}

 

//Hàm tìm kiếm xem 1 khóa có xuất hiện trên cây hay không
// nếu có thì trả về nút chứa khóa
// HÀM có lỗi vì KHÔNG trả về đúng phần tử cần tìm, hãy sửa lỗi
TNODE* findKey(TNODE* root, char key)
{
    if(root==NULL || root->info == key){
        return root;
    }
    TNODE* currChild = root->firstChild;
    while(currChild!=NULL)
    {
        if(findKey(currChild,key)!=NULL) return currChild;
        currChild=currChild->nextSibling;
    }
} 
// test code
int main()
{
    TNODE* root = createAGeneralTree();
    printf("Duyet theo muc: ");
    levelTraversal(root);
    printf("\n");
    
    printf("Duyet theo thu tu truoc: ");
    preOrderTraversal(root);
    printf("\n");
    
    printf("Duyet theo thu tu sau: ");
    postOrderTraversal(root);
    printf("\n");
    
    printf("Chieu cao cua cay: %d\n",findHeight(root));
    
    TNODE *p =  findKey(root, 'H');
    if(p!=NULL) {
        printf("H co xuat hien tren cay!\n");    
        printf("%c \n",p->info);    
    }
    
    // thêm I là con của H
    addNodeIntoTree(p,'I');
    
    printf("Duyet theo muc: ");
    levelTraversal(root);
    printf("\n");
    
    return 0;
}