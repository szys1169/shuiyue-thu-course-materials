#include "sort.h"
#include <cstdio>

// 辅助函数：调整数组中的三个元素顺序
inline void sortThree(int &a, int &b, int &c, int &minVal, int &maxVal) {
    int tmpMin, tmpMax;
    compare(a, b, c, &tmpMax, &tmpMin);
    
    // 找到最小值和最大值的位置
    if (tmpMin == a) {
        if (tmpMax == b) {
            // a最小, b最大, c中间
            // 已经是正确顺序: a, c, b
            int temp = c;
            c = b;
            b = temp;
        } else if (tmpMax == c) {
            // a最小, c最大, b中间
            // 已经是正确顺序: a, b, c
        }
    } else if (tmpMin == b) {
        if (tmpMax == a) {
            // b最小, a最大, c中间
            int temp = a;
            a = b;
            b = c;
            c = temp;
        } else if (tmpMax == c) {
            // b最小, c最大, a中间
            int temp = a;
            a = b;
            b = temp;
        }
    } else if (tmpMin == c) {
        if (tmpMax == a) {
            // c最小, a最大, b中间
            int temp = a;
            a = c;
            c = b;
            b = temp;
        } else if (tmpMax == b) {
            // c最小, b最大, a中间
            int temp = a;
            a = c;
            c = temp;
        }
    }
}

// 插入排序，使用三值比较器
void insertionSortWithThreeComparator(int *a, int n) {
    for (int i = 1; i < n; i++) {
        // 使用二分查找找到插入位置
        int left = 0, right = i;
        while (left < right) {
            int mid = (left + right) / 2;
            int minVal, maxVal;
            
            // 比较a[mid], a[i]和a[(mid+right)/2]
            int mid2 = (mid + right) / 2;
            if (mid2 == mid) mid2++;
            if (mid2 >= right) mid2 = right - 1;
            
            compare(a[mid], a[i], a[mid2], &maxVal, &minVal);
            
            if (minVal == a[i]) {
                // a[i]最小，应该插入到当前位置之前
                right = mid;
            } else if (maxVal == a[i]) {
                // a[i]最大，应该插入到当前位置之后
                left = mid + 1;
            } else {
                // a[i]在中间
                if (a[mid] == minVal || a[mid2] == minVal) {
                    left = mid + 1;
                } else {
                    right = mid;
                }
            }
        }
        
        // 插入a[i]到正确位置
        int temp = a[i];
        for (int j = i; j > left; j--) {
            a[j] = a[j - 1];
        }
        a[left] = temp;
    }
}

// 快速排序分区函数，使用三值比较器
int partition(int *a, int low, int high) {
    // 选择三个元素作为pivot候选
    int mid = (low + high) / 2;
    int minVal, maxVal;
    
    compare(a[low], a[mid], a[high], &maxVal, &minVal);
    
    // 选择中间值作为pivot
    int pivot;
    if (a[low] != minVal && a[low] != maxVal) {
        pivot = a[low];
    } else if (a[mid] != minVal && a[mid] != maxVal) {
        pivot = a[mid];
        // 交换到low位置
        int temp = a[low];
        a[low] = a[mid];
        a[mid] = temp;
    } else {
        pivot = a[high];
        // 交换到low位置
        int temp = a[low];
        a[low] = a[high];
        a[high] = temp;
    }
    
    int i = low;
    for (int j = low + 1; j <= high; j++) {
        // 比较a[j], pivot和a[i+1]来决定是否需要交换
        if (j == i + 1) {
            int minVal2, maxVal2;
            compare(a[j], pivot, a[j], &maxVal2, &minVal2);
            if (minVal2 == a[j]) {
                // a[j]小于pivot
                i++;
                int temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        } else {
            int minVal2, maxVal2;
            compare(a[j], pivot, a[i + 1], &maxVal2, &minVal2);
            
            if (minVal2 == a[j]) {
                // a[j]最小，小于pivot
                i++;
                int temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            } else if (maxVal2 == pivot) {
                // pivot最大，a[j]和a[i+1]都小于pivot
                i++;
                int temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
    
    // 将pivot放到正确位置
    int temp = a[low];
    a[low] = a[i];
    a[i] = temp;
    
    return i;
}

// 快速排序主函数
void quickSort(int *a, int low, int high) {
    if (low < high) {
        // 对于小数组使用插入排序
        if (high - low + 1 <= 16) {
            insertionSortWithThreeComparator(a + low, high - low + 1);
            return;
        }
        
        int pi = partition(a, low, high);
        quickSort(a, low, pi - 1);
        quickSort(a, pi + 1, high);
    }
}

// 归并排序的合并函数
void merge(int *a, int left, int mid, int right, int *temp) {
    int i = left, j = mid + 1, k = 0;
    
    while (i <= mid && j <= right) {
        // 使用三值比较器比较a[i], a[j]和a[mid]
        int minVal, maxVal;
        int compareMid = (i + mid) / 2;
        
        compare(a[i], a[j], a[compareMid], &maxVal, &minVal);
        
        if (minVal == a[i]) {
            temp[k++] = a[i++];
        } else if (maxVal == a[i]) {
            temp[k++] = a[j++];
        } else {
            // a[i]在中间
            if (a[j] == minVal) {
                temp[k++] = a[j++];
            } else {
                temp[k++] = a[i++];
            }
        }
    }
    
    while (i <= mid) {
        temp[k++] = a[i++];
    }
    
    while (j <= right) {
        temp[k++] = a[j++];
    }
    
    for (i = 0; i < k; i++) {
        a[left + i] = temp[i];
    }
}

// 归并排序
void mergeSort(int *a, int left, int right, int *temp) {
    if (left < right) {
        // 对于小数组使用插入排序
        if (right - left + 1 <= 16) {
            insertionSortWithThreeComparator(a + left, right - left + 1);
            return;
        }
        
        int mid = (left + right) / 2;
        mergeSort(a, left, mid, temp);
        mergeSort(a, mid + 1, right, temp);
        merge(a, left, mid, right, temp);
    }
}

// 堆排序，使用三值比较器
void heapify(int *a, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n) {
        int minVal, maxVal;
        compare(a[largest], a[left], (right < n) ? a[right] : a[left], &maxVal, &minVal);
        
        if (maxVal == a[left]) {
            largest = left;
        }
    }
    
    if (right < n) {
        int minVal, maxVal;
        compare(a[largest], a[right], a[(largest + right) / 2], &maxVal, &minVal);
        
        if (maxVal == a[right]) {
            largest = right;
        }
    }
    
    if (largest != i) {
        int temp = a[i];
        a[i] = a[largest];
        a[largest] = temp;
        heapify(a, n, largest);
    }
}

void heapSort(int *a, int n) {
    // 构建堆
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(a, n, i);
    }
    
    // 一个一个提取元素
    for (int i = n - 1; i > 0; i--) {
        int temp = a[0];
        a[0] = a[i];
        a[i] = temp;
        heapify(a, i, 0);
    }
}

// 主排序函数
void sort(int n, int limit, int *a) {
    // 根据n的大小选择不同的排序算法
    if (n <= 100) {
        // 小数组使用插入排序
        insertionSortWithThreeComparator(a, n);
    } else if (n <= 10000) {
        // 中等数组使用快速排序
        quickSort(a, 0, n - 1);
    } else if (n <= 100000) {
        // 较大数组使用归并排序
        int *temp = new int[n];
        mergeSort(a, 0, n - 1, temp);
        delete[] temp;
    } else {
        // 大数组使用堆排序
        heapSort(a, n);
    }
}