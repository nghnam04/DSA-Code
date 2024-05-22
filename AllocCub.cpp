#include <iostream>

template <typename T>
void AllocCub(T*** &arr, int depth, int rows, int cols) {
    arr = new T**[depth];
    for (int i = 0; i < depth; ++i) {
        arr[i] = new T*[rows];
        for (int j = 0; j < rows; ++j) {
            arr[i][j] = new T[cols];
        }
    }
}

int main() {
    // Ví dụ sử dụng
    int ***my3DArray;
    AllocCub(my3DArray, 3, 4, 5); // Cấp phát bộ nhớ cho mảng 3D có kích thước 3x4x5

    // Luôn nhớ giải phóng bộ nhớ sau khi sử dụng
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            delete[] my3DArray[i][j];
        }
        delete[] my3DArray[i];
    }
    delete[] my3DArray;

    return 0;
}
                        