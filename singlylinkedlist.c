/*
minh họa các thao tác cơ bản trên danh sách liên kết đơn
các thao tác gồm: duyệt, thêm, xóa, tìm kiếm
*/
#include <stdio.h>
#include <stdlib.h>

 

// minh hoa cau truc 1 nut cua danh sach liên kết đơn
struct Node
{
    int data;
    struct Node *next;
};

 

/*
hàm cấp phát động một nút mới của danh sách và gán giá trị khởi tạo cho nút
*/

 

struct Node *createNewNode(int data)
{
    struct Node *p = (struct Node *)malloc(sizeof(struct Node));
    p->data = data;
    p->next = NULL;
    
    return p;
}

 

/*
Minh họa các hàm thêm phân tử mới vào danh sách
*/
// hàm thêm phần tử vào đầu danh sách
// đầu danh sách mới sẽ được trả về thông qua tên hàm
struct Node *insertFront(struct Node *head, struct Node *newNode)
{
    newNode->next = head;
    head = newNode; // có thể bỏ qua nếu return newNode luôn
    return head;
}

 

// hàm thêm phần tử vào đầu danh sách phiên bản 2
// đầu danh sách mới sẽ được trả về thông qua tham số
void insertFront_v2(struct Node **head, struct Node *newNode)
{
    newNode->next = *head;
    *head = newNode; 
}

 


// hàm thêm phần tử vào sau vị trí phần tử cho trước (chèn giữa/cuối)
// phần tử mới thêm sẽ được thêm vào sau phần tử đang được trỏ bởi con trỏ pPrev
// con trỏ pPrev chắc chắn phải khác NULL
void insertAfter(struct Node *pPrev, struct Node *newNode)
{
    newNode->next = pPrev->next;
    pPrev->next = newNode; 
}

 

/*
Hàm tìm kiếm và trả về vị trí phần tử có giá trị bằng khóa key trong danh sách
Nếu không tìm thấy sẽ trả về con trỏ NULL
Nếu có nhiều khóa trùng thì chỉ trả về phần tử đầu tiên chứa khóa
*/
struct Node * searchList(struct Node *head, int key)
{
    while(head!=NULL){
        if(head->data==key) break;//return head;
        head=head->next;
    }
    return head;
}

 


/**
Hàm tìm và trả về phần tử ở cuối danh sách
*/
struct Node * getLast(struct Node *head)
{
    while(head->next!=NULL){
        head=head->next;
    }
    return head;
}

 

/*
Hàm in ra danh sách các phần tử hiện có
*/
void printList(struct Node *head)
{
    printf("Content: ");
    while(head!=NULL){
        printf("%d ",head->data);
        head=head->next;
    }
    printf("\n");
}

 

/*
Hàm giải phóng toàn bộ các phần tử trong danh sách liên kết đơn
sau khi gọi hàm này cần gán head thành NULL
*/
struct Node *deleteList(struct Node *head)
{
    // dùng con trỏ phụ p để lưu lại địa chỉ phần tử trước khi gọi lệnh giải phóng
    struct Node *p;
    while(head!=NULL){
        p = head;
        head=head->next;
        free(p);
    }
    return NULL;
}

 

/*
Hàm xóa phần tử trong danh sách đang trỏ bởi con trỏ p
yêu cầu p là phần tử giữa/cuối danh sách, KHÔNG phải đầu danh sách
*/
void removeAt(struct Node* head, struct Node *p)
{
    // tìm vị tri phần tử trước phần tử cần xóa
    struct Node *pPre = head;
    while(pPre->next != p){
        pPre=pPre->next;
    }
    
    pPre->next = p->next;
    free(p);
}

 

/*
Hàm xóa phần tử ở đầu danh sách, danh sách phải khác rỗng
*/
struct Node *removeFront(struct Node *head)
{
    struct Node *p = head;
    head = head->next;
    free(p);
    return head;
}

 

int main()
{
    // minh họa sử dụng 1 số hàm cơ bản trong danh sách liên kết đơn
    struct Node *head, *p;
    
    //khởi tạo danh sách 10->5->3->2;
    head = createNewNode(2);
    
    p =createNewNode(3);
    insertFront_v2(&head, p);
    
    p =createNewNode(5);
    insertFront_v2(&head, p);
    
    p =createNewNode(10);
    insertFront_v2(&head, p);
    
    //in ra danh sách 10->5->3->2;
    printList(head);
    
    // chen khoa 12 vào sau 5
    struct Node *pPre = searchList(head, 5);
    p =createNewNode(12);
    insertAfter(pPre, p);
    
    //in ra danh sách 10->5-->12->3->2;
    printList(head);
    
    
    // thêm khóa 25 vào cuối danh sách
    pPre = getLast(head);
    p =createNewNode(25);
    insertAfter(pPre, p);
    
    //in ra danh sách 10->5-->12->3->2-->25;
    printList(head);
    
    // xóa phần tử ở đầu danh sách
    head = removeFront(head);
    
    //in ra danh sách 5-->12->3->2-->25;
    printList(head);
    
    // tìm và xóa 3 trong danh sách
    p = searchList(head, 3);
    removeAt(head, p);
    
    //in ra danh sách 5-->12->2-->25;
    printList(head);
    
    // giải phóng toàn bộ danh sách
    head = deleteList(head);
    return 0;
}