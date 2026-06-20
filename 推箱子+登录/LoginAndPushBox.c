#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<ctype.h>
#include<string.h>
#define Account 0
#define Password 1
#define Login 2
#define ROW 10
#define COL 10
#define Air 0
#define Wall 1
#define Line 2
#define LevelNum 3
const char admin[] = "admin";
const char adpsw[] = "123456";
char account[16];
char password[16];
int focus = -1;
int acc_size = 0;
int psw_size = 0;

void gotoxy(int y, int x) {
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
// 设置文字颜色
void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
// 恢复默认白色
void resetColor()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void nextFocus() {
    focus = (focus + 1) % 3;
    switch (focus) {
    case Account:
        gotoxy(3, 31 + acc_size);
        break;
    case Password:
        gotoxy(4, 31 + psw_size);
        break;
    case Login:
        gotoxy(5, 28);
        break;
    }
}
void input_account(int key) {
    if (key == '\b' && acc_size > 0) {
        printf("\b \b");
        acc_size--;
        return;
    }
    if (isalnum(key) == 0 || acc_size >= 15) {
        return;
    }
    account[acc_size] = (char)key;
    printf("%c", account[acc_size]);
    acc_size++;
}
void input_password(int key) {
    if (key == '\b' && psw_size > 0) {
        printf("\b \b");
        psw_size--;
        return;
    }
    if (isalnum(key) == 0 || psw_size >= 15) {
        return;
    }
    password[psw_size] = (char)key;
    printf("*");
    psw_size++;
}
int login_tool() {
    account[acc_size] = '\0';
    password[psw_size] = '\0';

    if (acc_size == 0 || psw_size == 0) {
        gotoxy(6, 24);
        setColor(12);
        printf("注意:账号或密码不能为空!");
        resetColor();
        Sleep(1000);
        gotoxy(6, 24);
        printf("                        ");
        return 0;
    }
    if (strcmp(admin, account) != 0 || strcmp(adpsw, password) != 0) {
        for (int i = 0;i < acc_size;i++) {
            gotoxy(3, 31 + i);
            printf(" ");
        }
        for (int i = 0;i < psw_size;i++) {
            gotoxy(4, 31 + i);
            printf(" ");
        }
        acc_size = 0;
        psw_size = 0;
        gotoxy(6, 24);
        setColor(12);
        printf("注意:账号或密码错误!");
        resetColor();
        Sleep(1000);
        gotoxy(6, 24);
        printf("                    ");
        return 0;
    }
    gotoxy(6, 24);
    setColor(14);
    printf("程序启动中……");
    resetColor();
    gotoxy(8, 22);
    printf("[");
    gotoxy(8, 33);
    printf("]");
    for (int i = 0;i < 10;i++) {
        Sleep(200);
        gotoxy(8, 23 + i);
        setColor(10);
        printf("*");
        resetColor();
        gotoxy(7, 26);
        printf("%d%%", 10 * (i + 1));
    }
    gotoxy(9, 24);
    setColor(10);
    printf("登录成功!");
    resetColor();
    Sleep(1000);
    system("cls");
    return 1;
}
typedef struct {
    int row;
    int col;
}position;
typedef struct {
    position player;
    int map[ROW][COL];
    position box[20];
    int boxcount;
}level;
level lvs[LevelNum];
level LoadLevelFromNumber(const int data[ROW][COL]) {
    level lv;
    lv.boxcount = 0;
    for (int i = 0;i < ROW;i++) {
        for (int j = 0;j < COL;j++) {
            lv.map[i][j] = 0;
        }
    }
    for (int i = 0;i < ROW;i++) {
        for (int j = 0;j < COL;j++) {
            int val = data[i][j];
            if (val == 3) {
                lv.box[lv.boxcount].row = i;
                lv.box[lv.boxcount].col = j;
                lv.boxcount++;
            }
            else if (val == 4) {
                lv.player.row = i;
                lv.player.col = j;
            }
            else {
                lv.map[i][j] = val;
            }
        }
    }
    return lv;
}
void InitialLevels() {
    int level1[ROW][COL] = {
        {1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,2,0,0,0,0,1},
        {1,0,0,0,3,0,0,0,0,1},
        {1,0,0,0,4,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1}
    };
    lvs[0] = LoadLevelFromNumber(level1);
    int level2[ROW][COL] = {
        {1,1,1,1,1,1,1,1,1,1},
        {1,1,0,0,1,0,0,1,0,1},
        {1,0,1,1,0,1,0,0,1,1},
        {1,0,0,1,2,0,1,1,0,1},
        {1,1,0,0,0,1,0,1,0,1},
        {1,0,1,0,0,1,1,0,0,1},
        {1,0,0,0,0,3,0,0,1,1},
        {1,1,0,0,0,0,1,0,0,1},
        {1,0,1,4,0,0,0,0,1,1},
        {1,1,1,1,1,1,1,1,1,1}
    };
    lvs[1] = LoadLevelFromNumber(level2);
    int level3[ROW][COL] = {
        {1,1,1,1,1,1,1,1,1,1},
        {1,0,1,1,0,0,1,0,1,1},
        {1,1,2,1,0,1,0,2,0,1},
        {1,0,3,0,1,1,0,0,0,1},
        {1,1,0,1,0,0,1,0,1,1},
        {1,0,0,0,4,0,0,0,0,1},
        {1,0,0,1,0,1,0,0,1,1},
        {1,1,0,0,0,0,3,1,0,1},
        {1,0,1,0,0,0,0,1,1,1},
        {1,1,1,1,1,1,1,1,1,1}
    };
    lvs[2] = LoadLevelFromNumber(level3);
}
void DrawGameMap(const level* lv, int levelNum, int steps) {
    system("cls");
    setColor(14);
    printf("===== 推箱子游戏 =====\n");
    resetColor();
    printf("关卡: %d / %d    步数: %d\n", levelNum, LevelNum, steps);
    setColor(11);
    printf("操作: WASD移动  R重开  Q返回菜单\n\n");
    resetColor();

    char display[ROW][COL];
    for (int i = 0;i < ROW;i++) {
        for (int j = 0;j < COL;j++) {
            switch (lv->map[i][j]) {
            case Wall:display[i][j] = '#';break;
            case Line:display[i][j] = '$';break;
            default:display[i][j] = ' ';break;
            }
        }
    }
    for (int i = 0;i < lv->boxcount;i++) {
        int r = lv->box[i].row;
        int c = lv->box[i].col;
        display[r][c] = (lv->map[r][c] == Line) ? '!' : '*';
    }
    display[lv->player.row][lv->player.col] = '@';
    for (int i = 0;i < ROW;i++) {
        for (int j = 0;j < COL;j++) {
            char ch = display[i][j];
            if (ch == '#') {
                setColor(8); //灰色墙
            }
            else if (ch == '$') {
                setColor(14); //黄色目标点
            }
            else if (ch == '*') {
                setColor(12); //红色箱子
            }
            else if (ch == '!') {
                setColor(10); //绿色箱子（到位）
            }
            else if (ch == '@') {
                setColor(11); //青色玩家
            }
            else {
                resetColor();
            }
            printf("%c", ch);
            resetColor();
        }
        printf("\n");
    }
    setColor(14);
    printf("\n图例: #=墙  $=目标  *=箱子  !=箱子在目标上  @=玩家\n");
    resetColor();
}
int IsWin(const level* lv) {
    for (int i = 0;i < lv->boxcount;i++) {
        int r = lv->box[i].row;
        int c = lv->box[i].col;
        if (lv->map[r][c] != Line)return 0;
    }
    return 1;
}
//dr移动行数,dc移动列数.nr下一个位置的行,nc下一个位置的列
int Move(level* lv, int dr, int dc, int* step) {
    int pr = lv->player.row;
    int pc = lv->player.col;
    int nr = pr + dr;
    int nc = pc + dc;
    if (lv->map[nr][nc] == Wall)return 0;//看看是不是墙
    int BoxIndex = -1;
    for (int i = 0;i < lv->boxcount;i++) {
        if (lv->box[i].row == nr && lv->box[i].col == nc) {//看看箱子在不在下一个位置
            BoxIndex = i;//标记可推动的箱子,获得当前箱子的下标
            break;//一个就好
        }
    }
    if (BoxIndex != -1) {
        int br = nr + dr;
        int bc = nc + dc;
        if (lv->map[br][bc] == Wall)return 0;
        for (int i = 0;i < lv->boxcount;i++) {
            if (lv->box[i].row == br && lv->box[i].col == bc) {
                return 0;
            }
        }
        lv->box[BoxIndex].row = br;
        lv->box[BoxIndex].col = bc;
        lv->player.row = nr;
        lv->player.col = nc;
    }
    else {
        lv->player.row = nr;
        lv->player.col = nc;
    }
    (*step)++;
    return 1;
}
void GameWork() {
    InitialLevels();
    int cur = 0;
    int steps = 0;
    level lv = lvs[cur];
    while (1) {
        DrawGameMap(&lv, cur + 1, steps);
        if (IsWin(&lv)) {
            if (cur >= LevelNum - 1) {
                gotoxy(5 + ROW + 6, 0);
                setColor(10);
                printf("恭喜你通关了!按任意键退出");
                resetColor();
                _getch();
                return;
            }
            else {
                gotoxy(5 + ROW + 4, 0);
                setColor(10);
                printf("恭喜通过了第%d关,即将进入下一关", cur + 1);
                resetColor();
                Sleep(1200);
                cur++;
            }
            lv = lvs[cur];
            steps = 0;
        }
        int key = _getch();
        switch (key) {
        case 'w':case 'W':Move(&lv, -1, 0, &steps);break;
        case 's':case 'S':Move(&lv, 1, 0, &steps);break;
        case 'a':case 'A':Move(&lv, 0, -1, &steps);break;
        case 'd':case 'D':Move(&lv, 0, 1, &steps);break;
        case 'r':case 'R':lv = lvs[cur];steps = 0;break;
        case 'q':case 'Q':return;
        }
    }
}
void menu() {
    int game = 1;
    while (game) {
        system("cls");
        setColor(14);
        printf("===== 游戏菜单 =====\n");
        resetColor();
        printf("1.新的游戏\n");
        printf("2.继续游戏\n");
        printf("3.退出游戏\n");
        setColor(11);
        printf("做出你的选择:");
        resetColor();
        int choice;
        scanf("%d", &choice);
        switch (choice) {
        case 1:
        case 2:GameWork();system("cls");break;
        case 3:game = 0;break;
        default:
            setColor(12);
            printf("输入错误，请按回车重试\n");
            resetColor();
            while (_getch() != '\r');
            break;
        }
    }
}
int main() {
    gotoxy(3, 20);
    setColor(14);
    printf("请输入账号:");
    resetColor();

    gotoxy(4, 20);
    setColor(14);
    printf("请输入密码:");
    resetColor();

    gotoxy(5, 24);
    setColor(10);
    printf("登录");
    resetColor();

    nextFocus();
    int loop = 1;
    while (loop) {
        int key = _getch();
        switch (key) {
        case '\t':
            nextFocus();
            break;
        case '\r':
            if (focus == Login) {
                if (!login_tool()) {
                    nextFocus();
                }
                else {
                    loop = 0;
                }
            }
            else if (focus == Account || focus == Password) {
                nextFocus();
            }
            break;
        default:
            if (focus == Account) {
                input_account(key);
            }
            if (focus == Password) {
                input_password(key);
            }
            break;
        }
    }
    menu();
    return 0;
}