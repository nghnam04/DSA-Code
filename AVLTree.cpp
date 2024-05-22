/*Minh họa các thao tác cơ bản trên cây nhị phân tìm kiếm*/
#include<stdio.h>
#include<stdlib.h>

 

// hằng số để phân biệt cây AVL hay không cho hàm kiểm tra cây AVL phiên bản 2
#define LARGEST_HEIGHT  999999
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
// gốc là root, khó mới thêm là key 
// chỉ thêm nút tại nút lá rỗng
// vì cây ban đầu có thể rỗng nên root có thể bị thay đổi địa chỉ (cấp phát động)
// nên cần truyền là **root
void insert(TNODE** root, int key)
{
    if (*root == NULL) { // nút gốc rỗng --> thêm nút mới vào
        *root = makeNewNode(key);
    }
    // ngược lại tìm vị trí thêm trong con trái hoặc phải
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

 


// Hàm thêm nút mới vào cây tại root
// trả về nút gốc cây mới thêm qua tên hàm
// vậy không cần truyền **root như hàm trên 
TNODE* insert_v2(TNODE* root, int key)
{
    if (root == NULL) { // nút gốc rỗng, trả về địa chỉ nút mới sẽ là gốc mới
        return makeNewNode(key);
    }
    // nếu cây khác rỗng, tìm vị trí thêm tại con trái/phải
    else if (key < root->key) { 
        // thêm vào con trái nếu khóa nhỏ hơn gốc
        root->leftChild = insert_v2(root->leftChild, key);   
        return root;     
    } 
    else //if (key > root->key)  
    {
        // thêm vào con phải nếu lớn hơn gốc
        root->rightChild = insert_v2(root->rightChild, key);
        return root;
    }
}

 

// hàm duyệt cây theo thứ tự giữa
// như trong sách/slide
void inorderTraversal(TNODE *root)
{
    if(root==NULL) {
        return;
    }
    inorderTraversal(root->leftChild);
    printf("%d, ", root->key);
    inorderTraversal(root->rightChild);
}

 

 
// hàm xóa nút tại root (nút bị xóa đang trỏ bởi root)
// sau khi xóa cần cập nhật root thành NULL (nếu là lá)--> cần dùng **root
// nếu nút root có 1 con, thay root bằng con trái/phải
// nếu có đủ 2 con, thay bằng trái nhất trên con phải
// luôn phải gọi hàm free để giải phóng bộ nhớ cấp phát động
int remove_node(TNODE **root){
    // nếu cây rỗng thì không làm gì cả
    if((*root) == NULL) {
        return -1; //remove null
    }
    // ghi lại địa chỉ nút để gọi giải phóng bộ nhớ
    TNODE *ptr = *root; 
    
    // nếu nút có 1 con thì cho nút cha trỏ đến con tiếp
    // 1 con là con phải?
    if((*root)->leftChild == NULL){
        (*root)=(*root)->rightChild;
    } // 1 con là con trái
    else if((*root)->rightChild == NULL) {
        *root=(*root)->leftChild;
    }
    else{ // có 2 con, tìm nút thay thế là nút phải nhất trên con trái
        // cần lưu lại địa chỉ nút cha của nút bị thay thế
        TNODE *preP = *root; // ban đầu sẽ là root
        // tìm nút phải nhất trên con trái
        ptr = (*root)->leftChild;
        while(ptr->rightChild != NULL) {
            preP = ptr;
            ptr = ptr->rightChild;
        }
        // thay thế khóa tại root bằng khóa của nút bị xóa thực sự
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
// sử dụng hàm remove_node để xóa nút khi tìm được
int removeNode(TNODE** root, int key)
{
    if (*root == NULL || key == (*root)->key)
        return remove_node(root);
    else if (key < (*root)->key)
        return removeNode(&((*root)->leftChild), key);
    else return removeNode(&((*root)->rightChild), key);
}

 

// hàm xóa nút dùng đệ quy
// kết hợp 2 hàm tìm và xóa trong 1 hàm
void remove_node_recc(TNODE **root, int key)
{
    if(*root==NULL) return;
    if((*root)->key == key) // xóa tại gốc 
    {
        // nếu nút bị xóa là lá, giải phóng root và gán NULL
        if((*root)->leftChild == NULL && (*root)->rightChild==NULL){
            free(*root);
            *root = NULL;
        }
        // nếu nút bị xóa là nút có 1 con
        // xử lý TH1. chỉ có con phải
        else if((*root)->leftChild ==NULL && (*root)->rightChild!=NULL)
        {
            TNODE *p=*root; // lưu lại địa chỉ gốc cũ để gọi giải phóng
            *root = (*root)->leftChild;
            free(p);
        }
        // xử lý TH2. chỉ có con trái
        else if((*root)->leftChild !=NULL && (*root)->rightChild==NULL)
        {
            TNODE *p=*root; // lưu lại địa chỉ gốc cũ để gọi giải phóng
            *root = (*root)->rightChild;
            free(p);
        }
        else // có đủ 2 con, thay thế bằng nút trái nhất trên con phải
        {
            // thay thế giá trị tại gốc bằng giá trị trái nhất trên con phải
            TNODE *preP = *root; // con trỏ tới nút trước nút bị xóa thực sự
            TNODE *p = (*root)->rightChild;
            while(p->leftChild!=NULL){
                preP = p;
                p=p->leftChild;
            }
            // thay thế giá trị gốc bằng giá trị tại nút bị xóa thực sự
            (*root)->key = p->key;
            free(p);
            preP->leftChild = NULL;
        }
    }
    // trường hợp ngược lại, gọi đệ quy để tìm nút cần xóa
    else if((*root)->key<key){
        remove_node_recc(&((*root)->rightChild),key);
    }
    else{
        remove_node_recc(&((*root)->leftChild),key);
    }
}

 

// in ra k nút nhỏ nhất trên cây
int printKSmallest(TNODE* root, int k)
{
    if(root==NULL || k<=0) return 0;
    int k1=0, k2=0;
    // số nút nhỏ nhất trên con trái
    // trả về k1 là số lượng nút lấy được
    k1 = printKSmallest(root->leftChild,k);
    k=k-k1;
    // nếu vẫn chưa đủ,k còn >0, lấy tiếp gốc
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

 

//Ví dụ 15. Kiểm tra xem các nút trong của cây nhị phân chỉ có chính xác 1 con
// hàm trả về 0 nếu không đúng,
// trả về 1 nếu đúng
int checkAllNodesHaveOnlyOneChild(TNODE* root)
{
    // nếu nút gốc rỗng hoặc là nút lá thì trả về 0
    if(root == NULL || (root->leftChild ==NULL && root->rightChild==NULL) ||
        (root->leftChild !=NULL && root->rightChild!=NULL))
    {
        return 0;
    }
    // nếu nút có 1 con
    if(root->leftChild==NULL && root->rightChild!=NULL){
        // nếu cháu của nó là nút lá, trả về 1
        if(root->rightChild->leftChild==NULL && root->rightChild->rightChild==NULL){
            return 1;
        }
        else // kiểm tra tiếp nút con
        {
            return checkAllNodesHaveOnlyOneChild(root->rightChild);
        }
    }
    else // root->leftChild!=NULL && root->rightChild==NULL
    {
        if(root->leftChild->leftChild==NULL && root->leftChild->rightChild==NULL){
            return 1;
        }
        else
        {
            return checkAllNodesHaveOnlyOneChild(root->leftChild);
        }
    }
}
int MAX(int a, int b)
{
    return a>b?a:b;
}
// hàm tính chiều cao 1 nút
// thời gian tính là O(n)
int getHeight(TNODE* root)
{
    if(root==NULL) return -1;
    int leftHeight = getHeight(root->leftChild);
    int rightHeight = getHeight(root->rightChild);
    return 1 + MAX(leftHeight,rightHeight);
}

 

/*Kiểm tra cây nhị phân tìm kiếm có phải cây AVL
Hàm trả về 1 nếu là cây AVL và 0 nếu ngược lại
Thời gian là O(n^2)*/
int isAVLTree(TNODE* root)
{
    if(root==NULL ||(root->leftChild ==NULL && root->rightChild==NULL)){
        return 1;
    }
    int leftHeight = getHeight(root->leftChild);
    int rightHeight = getHeight(root->rightChild);
    if(abs(leftHeight-rightHeight)>1) return 0;
    return isAVLTree(root->leftChild) && isAVLTree(root->rightChild);
}

 

/*Kiểm tra cây nhị phân tìm kiếm có phải cây AVL
Hàm trả về 1 nếu là cây AVL và 0 nếu ngược lại
Thời gian chỉ còn O(n)
Nếu giá trị trả về >=LARGEST_HEIGHT thi KHÔNG phai AVL */
int isAVLTree_v2(TNODE* root)
{
    if(root==NULL){
        return -1;
    }
    int leftHeight = getHeight(root->leftChild);
    int rightHeight = getHeight(root->rightChild);
    
    if(abs(leftHeight-rightHeight)>1) return LARGEST_HEIGHT;
    return 1 + MAX(leftHeight,rightHeight);;
}
int main()
{
    // tạo cây mới và test code
    TNODE *root = NULL;
    root = insert_v2(root, 5);
    root = insert_v2(root, 3);
    root = insert_v2(root, 17);
    root = insert_v2(root, 15);
    root = insert_v2(root, 19);
    root = insert_v2(root, 11);

 

    /*
    insert(&root,5);
    insert(&root,3);
    insert(&root,12);
    insert(&root,8);
    insert(&root,6);
    insert(&root,17);
    insert(&root,14);
    */
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
    
    /*
    // test hàm xóa nút phiên bản 2
    remove_node_recc(&root,1);
    remove_node_recc(&root,2);
    remove_node_recc(&root,3);    
    /*
    remove_node_recc(&root,4);
    remove_node_recc(&root,6);
    */
    remove_node_recc(&root,11);
    printf("Duyet cay theo thu tu giua: ");
    inorderTraversal(root);
    printf("\n");
    /*
    if(checkAllNodesHaveOnlyOneChild(root)==1)
    {
        printf("Cay chi co nut 1 con!");
    }
    else
    {
        printf("Cay co ca nut 1 con, 2 con, va nut la!");
    }
    */
    printf("Chieu cao goc: %d\n",getHeight(root));
    if(isAVLTree_v2(root)<LARGEST_HEIGHT){
        printf("Day la cay AVL!\n");
    }
    else{
        printf("KHONG phai cay AVL!\n");
    }
    return 0;
}