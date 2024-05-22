#include <iostream>
#include <algorithm> // Cho std::min

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

template <typename T>
void ReallocCub(T*** &arr, int oldDepth, int oldRows, int oldCols, int newDepth, int newRows, int newCols) {
    T*** newArr;
    AllocCub(newArr, newDepth, newRows, newCols);

    // Sao chép dữ liệu từ mảng cũ sang mảng mới
    int minDepth = std::min(oldDepth, newDepth);
    int minRows = std::min(oldRows, newRows);
    int minCols = std::min(oldCols, newCols);

    for (int i = 0; i < minDepth; ++i) {
        for (int j = 0; j < minRows; ++j) {
            for (int k = 0; k < minCols; ++k) {
                newArr[i][j][k] = arr[i][j][k];
            }
        }
    }

    // Giải phóng bộ nhớ mảng cũ
    for (int i = 0; i < oldDepth; ++i) {
        for (int j = 0; j < oldRows; ++j) {
            delete[] arr[i][j];
        }
        delete[] arr[i];
    }
    delete[] arr;

    // Cập nhật con trỏ mảng sang mảng mới
    arr = newArr;
}

int main() {
    int ***my3DArray;
    AllocCub(my3DArray, 2, 2, 2); // Cấp phát mảng 3D kích thước 2x2x2

    // Tái cấp phát mảng 3D sang kích thước mới 3x3x3
    ReallocCub(my3DArray, 2, 2, 2, 3, 3, 3);

    // Giải phóng bộ nhớ sau khi sử dụng
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            delete[] my3DArray[i][j];
        }
        delete[] my3DArray[i];
    }
    delete[] my3DArray;

    return 0;
}
