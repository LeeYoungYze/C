#include <stdio.h>
#include <string.h>   // 用于 memcpy

// 第四章节：void* 泛型指针
// 结论：void* 能接收任意类型的地址，但无法直接解引用，也无法直接做算术运算
// 必须强转成 char* 结合 size（字节数）手动跳地址

typedef struct {
    char name[12];
    float score;
} Student;

// 比较器：按分数升序（返回 1 表示需要交换）
int score_asc(void *a, void *b) {
    Student *pa = (Student *)a;
    Student *pb = (Student *)b;
    return pa->score > pb->score;
}

// 泛型冒泡排序（一套代码，能排 int、float、结构体）
void bubble_sort(void *base, size_t nmemb, size_t size,
                 int (*compare)(void *, void *)) {
    // 关键步骤：void* 不能做运算，先强转为 char*（char* 加 1 跳 1 字节）
    char *p = (char *)base;
    char *temp = (char *)malloc(size);  // 临时仓库，大小等于单个元素
    if (!temp) return;

    for (size_t i = 0; i < nmemb - 1; i++) {
        for (size_t j = 0; j < nmemb - 1 - i; j++) {
            // 手算地址：首地址 + (下标 * 单个元素字节数)
            char *elem1 = p + j * size;
            char *elem2 = p + (j + 1) * size;

            if (compare(elem1, elem2)) {
                // 按字节拷贝交换，完全不知道外面是 int 还是 Student
                memcpy(temp, elem1, size);
                memcpy(elem1, elem2, size);
                memcpy(elem2, temp, size);
            }
        }
    }
    free(temp);
}

void print_students(Student *arr, size_t n) {
    for (size_t i = 0; i < n; i++) {
        printf("%s: %.1f\n", (arr + i)->name, (arr + i)->score);
    }
    printf("\n");
}

int main() {
    // 测试结构体数组
    Student s_arr[] = {
        {"Alice", 85.5},
        {"Bob", 92.0},
        {"Charlie", 78.3}
    };
    size_t n = sizeof(s_arr) / sizeof(s_arr[0]);
    size_t size = sizeof(Student);

    printf("原始数据:\n");
    print_students(s_arr, n);

    // 调用泛型排序：传入首地址、个数、单个字节数、比较器
    bubble_sort(s_arr, n, size, score_asc);

    printf("按分数升序:\n");
    print_students(s_arr, n);

    return 0;
}