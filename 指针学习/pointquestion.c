// 原地反转字符串
// 需求：把 "Hello Pointer" 变成 "retnioP olleH"。
// 限制：只能用一级指针 char *，不能新建临时数组（不能 char new[100]），必须在原内存块上操作。
/*
思路（纯地址理解）
用 char *left = str; 指向字符串开头。
用 char *right = str; 先走到字符串末尾的 '\0'，然后退一格指向最后一个有效字符。
只要 left < right（左指针还在右指针左边），就：
交换 *left 和 *right（用临时变量）。
left++（左指针往右走）。
right--（右指针往左走）。

按单词反转（把 "Hello Pointer" 变成 "Pointer Hello"）
这个题目会逼你同时使用 多个指针 和 指针运算，但依然只用一级指针，不用 malloc：

思路：

先整体反转整个字符串 → 得到 "retnioP olleH"。

然后遍历这个字符串，找到每个单词的起点和终点，把每个单词内部再反转一次。

最终结果："Pointer Hello"。

核心循环：用 char *start 标记单词开头，char *end 找空格或 \0，然后调用你写好的 reverse 函数（或者就地反转子串）。
*/
#include<stdio.h>
void swap(char *a,char *b){
    char temp = *a;
    *a = *b;
    *b = temp;
}
void reverse_range(char *start,char *end){
    char *left = start;
    char *right = end-1;
    while(left<right){
        swap(left,right);
        left++;
        right--;
    }
}
void reverse_str(char *str){
    if(*str=='\0'){return;}
    char *end = str;
    while(*end!='\0'){
        end++;
    }
    reverse_range(str,end);
    char *start = str;
    char *clue = str;
    while(*clue!='\0'){
        if(*clue==' '){
            reverse_range(start,clue);
            start = clue+1;
        }
        clue++;
    }
    reverse_range(start,clue);
}
void remove_spaces(char *str){
    if(*str=='\0'){return;}
    char *read = str;
    char *write = str;
    while(*read!='\0'){
        if(*read!=' '){
            *write = *read;
            write++;
        }
        read++;
    }
    *write = '\0';
}
void remove_consecutive_duplicates(char *str){
    if(*str=='\0'){return;}
    char *read = str;
    char *write = str;
    while(*read!='\0'){
        if(*read!=*(read+1)){
            *write = *read;
            write++;
        }
        read++;
    }
    *write = '\0';
}
int main(){
    char str[] = "Hello Pointer";
    printf("%s\n",str);
    reverse_str(str);
    printf("%s\n",str);
    remove_spaces(str);
    printf("%s\n",str);
    char str2[] = "aa";
    remove_consecutive_duplicates(str2);
    printf("%s\n",str2);
    return 0;
}