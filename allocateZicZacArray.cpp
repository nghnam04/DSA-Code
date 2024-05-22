#include <iostream>
using namespace std;

// Hàm cấp phát bộ nhớ cho mảng 2D zic zac
int** allocateZigZagArray(int numRows, int* columnWidths) {
    // Cấp phát bộ nhớ cho mảng chứa con trỏ đến từng hàng
    int** array = new int*[numRows];

    // Cấp phát bộ nhớ cho từng hàng dựa vào độ rộng cột được cung cấp
    for (int i = 0; i < numRows; ++i) {
        array[i] = new int[columnWidths[i]]; // Cấp phát bộ nhớ cho từng hàng
        // Khởi tạo giá trị mặc định cho mảng (tùy chọn)
        for (int j = 0; j < columnWidths[i]; ++j) {
            array[i][j] = 0; // Hoặc giá trị khởi tạo khác tùy ý
        }
    }

    return array; // Trả về con trỏ đến mảng 2D
}

// Hàm đọc dữ liệu cho mảng 2D zic zac
void readZigZagArrayData(int** array, int numRows, int* columnWidths) {
    cout << "Nhập dữ liệu cho mảng 2D zic zac:" << endl;
    for (int i = 0; i < numRows; ++i) {
        cout << "Hàng " << i+1 << " (nhập " << columnWidths[i] << " giá trị):" << endl;
        for (int j = 0; j < columnWidths[i]; ++j) {
            cout << "array[" << i << "][" << j << "] = ";
            cin >> array[i][j];
        }
    }
}

// Hàm hiển thị dữ liệu mảng
void displayZigZagArray(int** array, int numRows, int* columnWidths) {
    cout << "Dữ liệu mảng 2D zic zac:" << endl;
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < columnWidths[i]; ++j) {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }
}