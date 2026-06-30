#include<stdio.h>
#include<string.h>
//AI改了一下注释，更清晰一些
// 第五章节：字符串和指针
int main(){
    //一个字符串常量的本质是一个字符数组，里面存着每个字符的 ASCII 码，最后还有一个 '\0' 作为结束标志
    //而字符串常量的地址就是这个字符数组的首地址，所以可以用 char* 来接收
    char str[] = "Hello, World!";
    char *p = str;

    printf("%s\n",str);//str是数组名，在表达式中退化为&str[0]，类型为char*，是地址
    //%s接收这个地址后，从该地址开始逐个打印字符直到'\0'
    printf("%s\n",p);//p本身就是char*类型，直接传给%s
    printf("%c\n",*p);//*p对p解引用，取出p指向的字符'H'，类型为char
    //这里的*p不是“退化”，而是纯粹的“解引用”运算
    
    //那如果是指针数组呢？
    char a[] = "Hello";
    char b[] = " ";
    char c[] = "World";
    char *point_str[] = {a,b,c};
    printf("%s\n",point_str);//得到非常奇怪的字符串，也许是地址？
    printf("%p\n",point_str);//确实是地址 
    //解引用看看
    printf("%s\n",*point_str);//获得了Hello,刚好就是a字符串
    //那我们再次对Hello进行解引用，是不是就会获得第一个字符H？
    printf("%c\n",**point_str);
    //确实是H
    //也就是说指针数组是可以被二级指针接收的
    char **list = point_str;//point_str(数组名) 退化为 &point_str[0]，类型 char**，赋值给 list
    printf("%p\n",list);//list存的是 &point_str[0]（第一个盒子的地址）
    printf("%s\n",*list);//*list解引用，取出第一个盒子里的内容（即 "Hello" 的地址）
    printf("%c\n",**list);//**list再解引用，取出 "Hello" 的第一个字符 'H'
    //结果一模一样
    //写上面吧
    return 0;
}