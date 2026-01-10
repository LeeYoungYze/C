#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

/**
 * @brief 向文件写入计算次数（计数器）
 * @param cnt 当前的计算次数
 */
void files_write_cnt(int cnt) {
	FILE* fp;  // 文件指针，用于操作文件
	// 以"追加模式"打开文件（文件不存在则创建，存在则在末尾追加内容）
	fp = fopen("calculate_data.txt", "a");
	// 判断文件是否打开成功
	if (NULL == fp) {
		perror("fopen");  // 打印文件打开失败的详细错误信息
		return;
	}
	fprintf(fp, "%d ", cnt);  // 将计数器写入文件，末尾加空格分隔后续数据
	fclose(fp);  // 关闭文件，释放文件资源，避免内存泄漏
}

/**
 * @brief 向文件写入运算符号（+、-、*、/）
 * @param operator 输入的有效运算符号
 */
void files_write_ch(char operator) {
	FILE* fp;  // 文件指针
	// 以"追加模式"打开运算记录文件
	fp = fopen("calculate_data.txt", "a");
	if (NULL == fp) {
		perror("fopen");  // 打印文件打开失败信息
		return;
	}
	fprintf(fp, "%c ", operator);  // 将运算符号写入文件，空格分隔后续数据
	fclose(fp);  // 关闭文件，释放资源
}

/**
 * @brief 向文件写入操作数和本次运算后的最终结果
 * @param num 输入的操作数（参与运算的数字）
 * @param sum 本次运算后的累计结果
 */
void files_write_lf(double num, double sum) {
	FILE* fp;  // 文件指针
	// 以"追加模式"打开运算记录文件
	fp = fopen("calculate_data.txt", "a");
	if (NULL == fp) {
		perror("fopen");  // 打印文件打开失败信息
		return;
	}
	// 写入操作数和累计结果，%lf对应双精度浮点数，换行符标记一条记录结束
	fprintf(fp, "%lf %lf\n", num, sum);
	fclose(fp);  // 关闭文件，释放资源
}

/**
 * @brief 从文件中读取并展示所有历史运算记录
 */
void files_read() {
	// 以"只读模式"打开文件，仅用于读取数据，无法修改
	FILE* fp = fopen("calculate_data.txt", "r");
	if (NULL == fp) {
		perror("fopen");  // 打印文件打开失败信息（无记录时会提示文件不存在）
		return;
	}
	int cnt;      // 存储读取到的计算次数
	char ch;      // 存储读取到的运算符号
	double num;   // 存储读取到的操作数
	double sum;   // 存储读取到的累计结果

	// 按"计数器 运算符号 操作数 结果"的格式读取文件，每次读取4个数据
	// 当返回值不等于4时，说明读取到文件末尾或格式错误，终止循环
	while (fscanf(fp, "%d %c %lf %lf", &cnt, &ch, &num, &sum) == 4) {
		// 格式化输出历史记录，%.2lf保留2位小数，提升可读性
		printf("运算次数：%d | 运算：%d %c %.2lf → 结果：%.2lf\n", cnt, cnt, ch, num, sum);
	}
	fclose(fp);  // 关闭文件，释放资源
}

/**
 * @brief 加法运算：将输入的数字累加到总和中
 * @param sum 指向累计结果的指针，用于修改外部的总和变量
 */
void add(double* sum) {
	double num;  // 存储用户输入的操作数
	printf("输入一个数字!\n");
	scanf("%lf", &num);  // 读取用户输入的双精度数字
	while (getchar() != '\n');  // 清空输入缓冲区，避免残留的换行符干扰后续输入

	*sum += num;  // 通过指针修改外部的累计结果，实现加法运算
	files_write_lf(num, *sum);  // 将操作数和最新结果写入文件
	printf("结果等于%.2lf\n", *sum);  // 输出本次运算后的结果
}

/**
 * @brief 减法运算：从总和中减去输入的数字
 * @param sum 指向累计结果的指针，用于修改外部的总和变量
 */
void subtract(double* sum) {
	double num;  // 存储用户输入的操作数
	printf("输入一个数字!\n");
	scanf("%lf", &num);  // 读取用户输入的双精度数字
	while (getchar() != '\n');  // 清空输入缓冲区

	*sum -= num;  // 实现减法运算，修改外部累计结果
	files_write_lf(num, *sum);  // 写入操作数和最新结果到文件
	printf("结果等于%.2lf\n", *sum);  // 输出运算结果
}

/**
 * @brief 乘法运算：将总和与输入的数字相乘
 * @param sum 指向累计结果的指针，用于修改外部的总和变量
 */
void multiply(double* sum) {
	double num;  // 存储用户输入的操作数
	printf("输入一个数字!\n");
	scanf("%lf", &num);  // 读取用户输入的双精度数字
	while (getchar() != '\n');  // 清空输入缓冲区

	*sum *= num;  // 实现乘法运算，修改外部累计结果
	files_write_lf(num, *sum);  // 写入操作数和最新结果到文件
	printf("结果等于%.2lf\n", *sum);  // 输出运算结果
}

/**
 * @brief 除法运算：将总和除以输入的数字（排除除数为0的情况）
 * @param sum 指向累计结果的指针，用于修改外部的总和变量
 */
void divide(double* sum) {
	double num;  // 存储用户输入的操作数
	printf("输入一个数字!\n");
	scanf("%lf", &num);  // 读取用户输入的双精度数字
	while (getchar() != '\n');  // 清空输入缓冲区

	// 除数不能为0，进行合法性判断
	if (num == 0) {
		printf("错误：除数不能为0！\n");
		return;  // 直接返回，不执行后续运算和写入操作
	}

	*sum /= num;  // 实现除法运算，修改外部累计结果
	files_write_lf(num, *sum);  // 写入操作数和最新结果到文件
	printf("结果等于%.2lf\n", *sum);  // 输出运算结果
}

/**
 * @brief 运算调度函数：根据运算符号调用对应的运算函数，同时写入计数器和运算符号
 * @param operator 输入的有效运算符号
 * @param sum 指向累计结果的指针，传递给具体运算函数
 * @param cnt 当前的计算次数，用于写入文件
 */
void rule(char operator, double* sum, int cnt) {
	files_write_cnt(cnt);   // 第一步：写入计算次数（计数器），补齐记录的第一个数据
	files_write_ch(operator);  // 第二步：写入运算符号，补齐记录的第二个数据

	// 根据运算符号分支，调用对应的具体运算函数
	switch (operator) {
	case'+':add(sum); break;    // 加法运算
	case'-':subtract(sum); break;  // 减法运算
	case'*':multiply(sum); break;  // 乘法运算
	case'/':divide(sum); break;    // 除法运算
	}
}

/**
 * @brief 混合运算主逻辑：接收用户输入的运算符号，调度运算，统计计算次数
 */
void mix() {
	int n = 1;          // 运算阶段标记：1表示首次运算（仅支持+、-），>1表示后续运算（支持+、-、*、/）
	int cnt = 0;        // 计算次数计数器，初始化为0，有效运算后自增
	double sum = 0;     // 运算累计结果，初始化为0
	char operator;      // 存储用户输入的运算符号

	while (1) {  // 无限循环，直到用户输入q/Q退出
		printf("请输入运算符号(输入q退出)!\n");
		if (n == 1) {  // 首次运算逻辑
			printf("选择+或-\n");
			scanf(" %c", &operator);  // 前面加空格，跳过输入缓冲区中的空白字符
			while (getchar() != '\n');  // 清空输入缓冲区

			// 退出条件：用户输入q或Q
			if (operator=='q' || operator=='Q') {
				printf("最终结果：sum=%.2lf\n", sum);
				break;
			}

			// 合法性判断：仅允许+、-
			if (operator!='+' && operator!='-') {
				printf("请重新输入!\n");
				continue;  // 跳过后续逻辑，重新进入循环
			}

			// 有效运算：计数器自增，调度具体运算
			cnt++;
			rule(operator, &sum, cnt);
			n++;  // 阶段标记自增，后续运算支持*、/
		}
		else {  // 非首次运算逻辑（支持+、-、*、/）
			printf("选择+或-或*或/\n");
			scanf(" %c", &operator);  // 前面加空格，跳过输入缓冲区中的空白字符
			while (getchar() != '\n');  // 清空输入缓冲区，避免残留字符干扰

			// 退出条件：用户输入q或Q
			if (operator=='q' || operator=='Q') {
				printf("最终结果：sum=%.2lf\n", sum);
				break;
			}

			// 合法性判断：仅允许+、-、*、/
			if (operator!='+' && operator!='-' && operator!='*' && operator!='/') {
				printf("请重新输入!\n");
				continue;  // 跳过后续逻辑，重新进入循环
			}

			// 有效运算：计数器自增，调度具体运算
			cnt++;
			rule(operator, &sum, cnt);
			n++;  // 阶段标记自增（仅用于标记非首次，无其他实际意义）
		}
	}
}

/**
 * @brief 清空历史运算记录文件
 */
void delete() {
	// 以"写入模式"打开文件：文件不存在则创建，存在则清空原有内容
	FILE* fp = fopen("calculate_data.txt", "w");
	if (NULL == fp) {
		perror("清空文件失败");  // 打印清空失败的错误信息
		return;
	}
	fclose(fp);  // 打开后直接关闭，完成文件清空操作
	printf("历史记录已清空！\n");
}

/**
 * @brief 程序主函数：提供菜单选择，调度各个功能模块
 * @return int 程序退出状态码，0表示正常退出
 */
int main()
{
	while (1) {  // 无限循环，展示菜单直到用户选择退出
		// 菜单界面格式化输出
		printf("======================================================\n");
		printf("请选择项目：\n");
		printf("0:退出   1:混合计算   2:查看历史记录   3:删除记录\n");
		printf("======================================================\n");

		int choice = 0;  // 存储用户的菜单选择
		scanf("%d", &choice);  // 读取用户输入的菜单选项
		while (getchar() != '\n');  // 清空输入缓冲区，避免干扰后续字符输入

		// 根据用户选择调度对应功能
		switch (choice) {
		case 0:  // 退出程序
			printf("程序退出中...\n");
			return 0;
		case 1:  // 执行混合计算
			mix();
			break;
		case 2:  // 查看历史运算记录
			printf("---------------------- 历史运算记录 ----------------------\n");
			files_read();
			system("pause");  // 暂停程序，方便用户查看记录
			system("cls");    // 清屏，优化界面展示
			break;
		case 3:  // 清空历史运算记录
			delete();
			system("pause");  // 暂停程序，提示用户操作结果
			system("cls");    // 清屏，优化界面展示
			break;
		default:  // 无效输入处理
			printf("\n输入无效，请重新选择！\n");
			system("pause");
			system("cls");
			break;
		}
	}
}