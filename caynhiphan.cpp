/*Minh họa các thao tác cơ bản trên cây nhị phân tìm kiếm*/
#include<stdio.h>
#include<stdlib.h>

 

typedef struct TreeNode
{
    int key;
    struct TreeNode *leftChild;
    struct TreeNode *rightChild;
} TNODE;

 

// hàm tạo ra 1 nút mới có khóa là key
TNODE* makeNewNode(int key)
{
    TNODE* newNode = (TNODE*)malloc(sizeof(TNODE));
    newNode->key = key;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    return newNode;
}

 


// Hàm thêm nút mới vào cây tại root
void insert(TNODE** root, int key)
{
    if (*root == NULL) { // nút gốc rỗng
        *root = makeNewNode(key);
    }
    else if (key < (*root)->key) { 
        // thêm vào con trái nếu khóa nhỏ hơn gốc
        insert(&((*root)->leftChild), key);
    } 
    else //if (key > (*root)->key)  
    {
        // thêm vào con phải nếu lớn hơn gốc
        insert(&((*root)->rightChild), key);
    }
}

 

// hàm duyệt cây theo thứ tự giữa
void inorderTraversal(TNODE *root)
{
    if(root==NULL) {
        return;
    }
    inorderTraversal(root->leftChild);
    printf("%d, ", root->key);
    inorderTraversal(root->rightChild);
}

 

// hàm xóa nút tại root 
int remove_node(TNODE **root){
    // nếu cây rỗng thì không làm gì cả
    if((*root) == NULL) {
        return -1; //remove null
    }
    // ghi lại địa chỉ nút để gọi giải phóng bộ nhớ
    TNODE *ptr = *root; 
    
    // nếu nút có 1 con thì cho nút cha trỏ đến con tiếp
    if((*root)->leftChild == NULL){
        (*root)=(*root)->rightChild;
    } 
    else if((*root)->rightChild == NULL) {
        *root=(*root)->leftChild;
    }
    else{ // tìm nút phải nhất trên con trái
        TNODE *preP = *root;
        ptr = (*root)->leftChild;
        while(ptr->rightChild != NULL) {
            preP = ptr;
            ptr = ptr->rightChild;
        }
        // thay thế khóa gốc bằng khóa của nút bị xóa thực sự
        (*root)->key = ptr->key;
        // cập nhật lại con trỏ
        if(preP == *root) (*root)->leftChild = ptr->leftChild;
        else preP->rightChild = ptr->leftChild;
    }
    // gọi lệnh giải phóng bộ nhớ
    free(ptr);
    return 0;
}
// hàm tìm và xóa khóa key trên cây
int removeNode(TNODE** root, int key)
{
    if (*root == NULL || key == (*root)->key)
        return remove_node(root);
    else if (key < (*root)->key)
        return removeNode(&((*root)->leftChild), key);
    else return removeNode(&((*root)->rightChild), key);
}

 

// in ra k nút nhỏ nhất trên cây
int printKSmallest(TNODE* root, int k)
{
    if(root==NULL || k<=0) return 0;
    int k1=0, k2=0;
    // số nút nhỏ nhất trên con trái
    k1 = printKSmallest(root->leftChild,k);
    k=k-k1;
    // nếu vẫn chưa đủ, lấy tiếp gốc
    if(k>0){
        printf("%d, ",root->key);
        k=k-1;
    }
    // nếu vẫn chưa đủ lấy tiếp ở con phải
    if(k>0){
        k2 = printKSmallest(root->rightChild,k);
    }
    // trả về tổng số lượng nút đã in ra
    return k1+k2+1;
}
int main()
{
    // tạo cây mới và test code
    TNODE *root = NULL;
    insert(&root,5);
    insert(&root,3);
    insert(&root,12);
    insert(&root,8);
    insert(&root,6);
    insert(&root,17);
    insert(&root,14);
    
    printf("Duyet cay theo thu tu giua: ");
    inorderTraversal(root);
    printf("\n");
    
    /*
    removeNode(&root,5);
    printf("Duyet cay theo thu tu giua: ");
    inorderTraversal(root);
    printf("\n");
    */
    printf("4 nut nho nhat tren cay: ");
    int k=4;
    printKSmallest(root, k);
    printf("\n");
    
    return 0;
}

