/*新题目：给定一个字符串数组，找出其中最长的字符串并打印它
例如：

输入：{"Alice", "Bob", "Charlie", "David"}
输出："Charlie"（长度 7）

输入：{"C", "Python", "Java", "Rust"}
输出："Python"（长度 6，如果有并列长度，取第一个就行）

要求：

遍历时只用指针（不许用 arr[i] 下标）。

比较长度用标准库 strlen（这不算犯规，因为标准库做的事就是帮你数数）。

返回指向最长字符串的指针（char*），这样调用者可以直接拿到结果。*/
#include<stdio.h>
#include<string.h>
char *get_longest_str(char **str,int n){
    char **p = str;
    char **end = str+n;
    char *longest = *str;
    while(p<end){
        if(strlen(longest)<strlen(*p)){
            longest = *p;
        }
        p++;
    }
    return longest;
}
int main(){
    char *str[]= {"Alice", "Bob", "Charlie", "David"};
    char **list = str;
    char str1[] = "abcde";
    int len = strlen(*(str+1));
    printf("length=%d\n",len);
    int n = sizeof(str)/sizeof(str[0]);
    char *max_str = get_longest_str(list,n);
    printf("%s",max_str);
    return 0;
}