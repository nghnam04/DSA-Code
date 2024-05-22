/**
Minh hoa các thao tác cơ bản của danh sách liên kết đôi
Thao tác cơ bản gồm thêm, xóa, tìm kiếm, giải phóng bộ nhớ
*/

 

#include <stdio.h>
#include <stdlib.h>

 

// cấu trúc minh họa 1 nút với phần tử kiểu int
struct DNode 
{
    int data;
    struct DNode *next, *prev;
};

 

/**
Hàm cấp phát đống 1 nút mới với dữ liệu ban dầu là data
*/
struct DNode* createNewNode(int data)
{
    struct DNode *nNode = (struct DNode *)malloc(sizeof(struct DNode ));
    nNode->data = data;
    nNode->next = nNode->prev = NULL;
    
    return nNode;
}

 

/**
Hàm thêm phần tử vào đầu danh sách liên kết đôi
Danh sách ban đầu trỏ bởi head và phải khác rỗng
Phần tử mới thêm sẽ có giá trị  là data
*/

 

struct DNode* insertFront(struct DNode* head, int data)
{
    struct DNode* nNode = createNewNode(data);
    
    // gắn nút mới vào đầu danh sách
    nNode->next = head;
    head->prev = nNode;
    
    return nNode;    
}

 

/**
Hàm thêm phần tử mới vào sau 1 nút đang trỏ bởi con trỏ p trong danh sách
Phần tử mới có dữ liệu là data
*/
void insertAfter(struct DNode* p, int data)
{
    struct DNode* nNode = createNewNode(data);
    
    // gắn vao sau vị trí nút đang trỏ bởi p
    nNode->next = p->next;
    
    // kiểm tra xem p có phải cuối danh sách
    if(p->next!=NULL){
        p->next->prev = nNode;
    }
    
    p->next = nNode;
    nNode->prev = p;
}

 

/*
Hàm tìm kiếm xem 1 giá trị key có xuất hiện trong danh sách hay không,
Nếu xuất hiện thì trả về địa chỉ phần tử đầu tiên chứa giá trị bằng key
*/
struct DNode* findKey(struct DNode* head, int key)
{
    while(head!=NULL){
        if(head->data==key) {
            return head;
        }
        head = head->next;
    }
    return NULL;
}

 

/*
Hàm giải phóng toàn bộ các phần tử cấp phát động của danh sách
Chú ý: sau khi gọi hàm cần gán head = NULL
*/

 

struct DNode* freeList(struct DNode* head)
{
    struct DNode* p;
    while(head!=NULL){
        p = head;
        head = head->next;
        free(p);
    }
    return NULL;
}

 

/**
Hàm xóa phần tử ở đầu danh sách
*/
struct DNode* removeFront(struct DNode* head)
{
    struct DNode* p;
    if(head!=NULL){
        p = head;
        head = head->next;
        free(p);
        
        // cần phải cập nhật lại prev của đầu mới
        head->prev = NULL;
    }
    return head;
}

 

/*
Hàm xóa phần tử có giá trị bằng key trong danh sách (nếu có)
Có 2 TH có thể xảy ra:
TH1. Phần tử cần xóa là đầu danh sách --> gọi lại hàm removeFront
TH2. Phần tử cần xóa ở giữa/cuối --> tìm con trỏ tới trước vị trí cần xóa
*/
struct DNode* removeKey(struct DNode* head, int key)
{
    if(head==NULL) { // nếu danh sách ban đầu đã rỗng --> không làm gì
        return NULL;
    }
    // check TH1. khóa là đầu danh sách
    if(head->data == key) {
        return removeFront(head);
    }
    
    // ngược lại, tìm con trỏ tới trước vị trí khóa cần xóa
    struct DNode* p= head;
    while(p->next!=NULL && p->next->data!=key){
        p=p->next;
    }
    // check xem khóa cần xóa có tồn tại
    if(p->next==NULL){
        return head;
    }
    
    // xóa phần tử ngay sau p
    struct DNode* delNode = p->next; 
    p->next = delNode->next;
    
    // nếu nút cần xóa đã không phải là cuối danh sách --> con trỏ ngược
    if(delNode->next!=NULL){
        delNode->next->prev = p;
    }
    
    // giải phóng bộ nhớ phần tử cần xóa
    free(delNode);
    
    return head;
}

 

/*
Hàm in nội dung danh sách hiện tại
*/
void printList(struct DNode* head)
{
    printf("Danh sach hien tai: ");
    while(head!=NULL){
        printf("%d, ", head->data);
        head = head->next;
    }
    printf("\n");
}

 


// Test thử code
int main()
{
    struct DNode* head = NULL;
    // tạo danh sách 7->3->4->2
    head = createNewNode(2);
    head = insertFront(head, 4);
    head = insertFront(head, 3);
    head = insertFront(head, 7);
    
    printList(head);
    
    // them 6 vào sau khóa 7
    struct DNode* p = findKey(head, 7);
    insertAfter(p,6);
    
    // them 6 vào cuối danh sách
    p = findKey(head, 2);
    insertAfter(p,6);
    
    printList(head);
    
    // xóa phần tử ở đầu danh sách
    head = removeFront(head);
    printList(head);
    
    // xóa khóa 2
    head = removeKey(head, 2);
    printList(head);
    
    // xóa khóa 6
    head = removeKey(head, 6);
    printList(head);
    // giải phóng bộ nhớ của danh sách
    head = freeList(head);
    return 0;
}