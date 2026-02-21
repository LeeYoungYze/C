#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 跨平台清屏
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// 统一写一条完整记录
void writeRecord(int cnt, char op, double num, double sum) {
    FILE* fp = fopen("calculate_data.txt", "a");
    if (fp == NULL) {
        perror("fopen failed");
        return;
    }
    fprintf(fp, "%d %c %.2lf %.2lf\n", cnt, op, num, sum);
    fclose(fp);
}

// 读取历史记录
void showHistory() {
    FILE* fp = fopen("calculate_data.txt", "r");
    if (fp == NULL) {
        printf("暂无历史记录\n");
        return;
    }

    int cnt;
    char op;
    double num, res;
    printf("---------------- 历史记录 ----------------\n");
    while (fscanf(fp, "%d %c %lf %lf", &cnt, &op, &num, &res) == 4) {
        printf("第%d次 | 运算：%c %.2lf | 结果：%.2lf\n",
            cnt, op, num, res);
    }
    fclose(fp);
}

// 清空记录
void clearHistory() {
    FILE* fp = fopen("calculate_data.txt", "w");
    if (fp != NULL) {
        fclose(fp);
    }
    printf("历史记录已清空\n");
}

// 运算函数
void add(double* sum) {
    double num;
    printf("输入数字：");
    scanf("%lf", &num);
    *sum += num;
}

void subtract(double* sum) {
    double num;
    printf("输入数字：");
    scanf("%lf", &num);
    *sum -= num;
}

void multiply(double* sum) {
    double num;
    printf("输入数字：");
    scanf("%lf", &num);
    *sum *= num;
}

void divide(double* sum) {
    double num;
    printf("输入数字：");
    scanf("%lf", &num);
    if (num == 0) {
        printf("错误：除数不能为0\n");
        return;
    }
    *sum /= num;
}

// 累计计算模式
void calcLoop() {
    double sum = 0.0;
    int cnt = 0;
    char op;

    while (1) {
        printf("\n当前结果：%.2lf\n", sum);
        printf("输入运算符 (+ - * /)，q 退出：");
        scanf(" %c", &op);

        if (op == 'q' || op == 'Q') {
            printf("\n最终结果：%.2lf\n", sum);
            break;
        }

        // 判断合法运算符
        if (op != '+' && op != '-' && op != '*' && op != '/') {
            printf("输入无效\n");
            continue;
        }

        cnt++;
        double old = sum;

        // 执行运算
        switch (op) {
        case '+': add(&sum); break;
        case '-': subtract(&sum); break;
        case '*': multiply(&sum); break;
        case '/': divide(&sum); break;
        }

        // 写入记录
        writeRecord(cnt, op, sum - old, sum);
        printf("运算后：%.2lf\n", sum);
    }
}

// 单次计算模式（新增！）
void singleCalc() {
    while (getchar() != '\n');
    double a, b, res;
    char op;
    printf("输入表达式（如 5+6）：");
    if (scanf("%lf%c%lf", &a, &op, &b) != 3) {
        printf("输入格式错误\n");
        return;
    }

    switch (op) {
    case '+': res = a + b; break;
    case '-': res = a - b; break;
    case '*': res = a * b; break;
    case '/':
        if (b == 0) {
            printf("除数不能为0\n");
            return;
        }
        res = a / b;
        break;
    default:
        printf("不支持的运算符\n");
        return;
    }

    printf("结果：%.2lf\n", res);
    FILE* fp = fopen("calculate_data.txt", "r");
    int cnt = 0;
    if (fp != NULL) {
        int temp1; char temp2; double temp3, temp4;
        while (fscanf(fp, "%d %c %lf %lf", &temp1, &temp2, &temp3, &temp4) == 4) {
            cnt++;
        }
        fclose(fp);
    }
    cnt++; // 新记录的序号
    writeRecord(cnt, op, b, res); // 写入单次计算记录
}

// 主菜单
int main() {
    int choice;
    while (1) {
        clearScreen();
        printf("============= 计算器 =============\n");
        printf("1：累计计算\n");
        printf("2：单次计算（新增）\n");
        printf("3：查看历史\n");
        printf("4：清空历史\n");
        printf("0：退出\n");
        printf("=======================================\n");
        printf("请选择：");

        if (scanf("%d", &choice) != 1) {
            // 清空输入错误
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
        case 1: calcLoop(); break;
        case 2: singleCalc(); break;
        case 3: showHistory(); break;
        case 4: clearHistory(); break;
        case 0: return 0;
        default: printf("输入错误\n");
        }

        printf("\n按回车继续...");
        getchar(); getchar();
    }
    return 0;
}