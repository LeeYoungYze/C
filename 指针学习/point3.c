#include <stdio.h>

// 第三章节：函数指针
// 结论：函数名在表达式中会退化成函数的入口地址，和数组名退化成首地址完全一样

int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }

// 定义一个“接收函数指针作为参数”的引擎
void calculate(int a, int b, int (*op)(int, int)) {
    // op 是一个指针，存着函数的入口地址
    // 直接通过指针调用函数，等价于 (*op)(a, b)
    int result = op(a, b);
    printf("结果: %d\n", result);
}

int main() {
    // 1. 声明一个函数指针变量，指向“两个int参数、返回int”的函数
    int (*p)(int, int) = add;   // 函数名 add 退化为地址，直接赋值

    // 2. 通过指针调用（两种写法等价）
    printf("通过 p 调用 add: %d\n", p(10, 5));      // 现代写法
    printf("通过 (*p) 调用 add: %d\n", (*p)(10, 5)); // 老派写法，加*更直观

    // 3. 把函数指针作为参数传递（回调函数）
    // 引擎不参与业务逻辑，只负责调用传进来的螺丝
    calculate(20, 4, add);   // 拧上加法螺丝
    calculate(20, 4, sub);   // 拧上减法螺丝
    calculate(20, 4, mul);   // 拧上乘法螺丝

    // 4. 函数指针数组（拓展：菜单系统）
    // 声明：ops 是一个数组，里面有3个格子，每个格子存一个函数地址
    int (*ops[3])(int, int) = {add, sub, mul};
    int choice = 0; // 假设用户输入0
    printf("菜单选择(0加,1减,2乘): %d\n", ops[choice](100, 20));

    return 0;
}