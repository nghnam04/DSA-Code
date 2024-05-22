#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Khai báo cấu trúc dữ liệu cho mỗi xe
typedef struct Car {
    char ID[12];
    char licensePlate[11];
    char pdate[20];
    int type;
    struct Car* next;
} Car;

// Hàm để thêm một xe mới vào danh sách liên kết đơn
void addCar(Car** head, char ID[], char licensePlate[], char date[], int type) {
    Car* newCar = (Car*)malloc(sizeof(Car));
    strcpy(newCar->ID, ID);
    strcpy(newCar->licensePlate, licensePlate);
    strcpy(newCar->pdate, date);
    newCar->type = type;
    newCar->next = NULL;

    if (*head == NULL) {
        *head = newCar;
    }
    else {
        Car* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newCar;
    }
}

// Hàm để đọc thông tin các xe trong bãi từ input
void readCarList(Car** head) {
    char ID[12];
    char licensePlate[11];
    char pdate[20], nextLine[100];
    int type;
    int count = 0;
    while (1) {
        fgets(nextLine, sizeof(nextLine), stdin);
        nextLine[strcspn(nextLine, "\r\n")] = 0;
        sscanf(nextLine, "%s", ID);
        if (strlen(ID) == 0) continue;
        if (strcmp(ID, "-1") == 0) {
            break;
        }
        fgets(nextLine, sizeof(nextLine), stdin);
        nextLine[strcspn(nextLine, "\r\n")] = 0;
        strcpy(licensePlate, nextLine);

        fgets(nextLine, sizeof(nextLine), stdin);
        nextLine[strcspn(nextLine, "\r\n")] = 0;
        strcpy(pdate, nextLine);
        
        fgets(nextLine, sizeof(nextLine), stdin);
        nextLine[strcspn(nextLine, "\r\n")] = 0;
        sscanf(nextLine, "%d", &type);
        count++;
        addCar(head, ID, licensePlate, pdate, type);
    }
    printf("Total: %d\n", count);
}

/*
===============================================================
Phần code của sinh viên tại đây!
===============================================================
*/
// Hàm để đếm số lượng xe đang có trong bãi
int countCars(Car* head) {
// VIẾT CODE TẠI ĐÂY
Car* p=head;
int count=0;
while(p!=NULL){
    count++;
    p=p->next;
}
return count;
}

// Hàm để tìm kiếm xe theo biển số
// Trả về NULL nếu không tìm thấy xe
// ngược lại trả về địa chỉ của phần tử chứa biển số
Car* findaCarByLicensePlate(Car* head, char licensePlate[]) {
	// VIẾT CODE TẠI ĐÂY
	Car* p=head;
    while(p!=NULL){
        if(strcmp(p->licensePlate, licensePlate)==0) return p;
        p=p->next;
    }
    return NULL;
}

// Hàm để trả xe dựa trên ID thẻ và xóa khỏi danh sách
// Giải phóng bộ nhớ của xe bị xóa
// hàm trả về 1 nếu xóa thành công và 0 nếu không thành công
int returnCarByID(Car** head, char ID[]) {
	// VIẾT CODE TẠI ĐÂY
	Car*p=*head;
    if(p==NULL) return 0;
    if(strcmp(p->ID, ID)==0){
        *head=p->next;
        free(p);
        return 1;
    }
    while(p->next!=NULL){
        if(strcmp(p->next->ID, ID)==0){
        Car*temp=p->next;
        p->next=temp->next;
        free(temp);
        return 1;
        }
        p=p->next;
}
return 0;
}


/*
==================================
	Hết phần viết code của sinh viên
==================================
*/

void findCarByLicensePlates(Car* head)
{
    char licensePlate[11];
    Car* aCar = NULL;
    while (1) {
        fgets(licensePlate, sizeof(licensePlate), stdin);
        licensePlate[strcspn(licensePlate, "\r\n")] = 0;
        if (strcmp(licensePlate, "-1") == 0) {
            break;
        }
        aCar = findaCarByLicensePlate(head, licensePlate);
        if (aCar == NULL) printf("Plate NOT FOUND\n");
        else printf("Found a car parked at %s\n", aCar->pdate);
    }
}

void returnCarByIDs(Car** head)
{
    char ID[12], nextLine[100];
    while (1) {
        fgets(nextLine, sizeof(nextLine), stdin);
        nextLine[strcspn(nextLine, "\r\n")] = 0;
        sscanf(nextLine, "%s", ID);
        if (strcmp(ID, "-1") == 0) {
            break;
        }
        if (returnCarByID(head, ID))
            printf("DONE Remove\n");
        else
            printf("ID NOT FOUND\n");
    }
}


int main() {
    Car* carList = NULL;
    char nextCommand[100];
    while (1)
    {
        fgets(nextCommand, sizeof(nextCommand), stdin);
        nextCommand[strcspn(nextCommand, "\r\n")] = 0;
        if (nextCommand[0] != '?') break;
        if (strcmp(&nextCommand[2], "readCarList") == 0)
            readCarList(&carList);
        else if (strcmp(&nextCommand[2], "findCarByLicensePlates") == 0)
            findCarByLicensePlates(carList);
        else if (strcmp(&nextCommand[2], "returnCarByIDs") == 0)
            returnCarByIDs(&carList);
        else if (strcmp(&nextCommand[2], "countCars") == 0)
            printf("Total cars: %d\n", countCars(carList));
    }

    return 0;
}