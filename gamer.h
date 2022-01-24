/// <h1>游戏引擎定义部分</h1>
///
/// <p>code by Satar07</p>
#ifndef GAMER_GAMER_H
#define GAMER_GAMER_H

#include "baseheader.h"
#include "timer.h"

#define STATE_FILE "state.dat"
#define SCORE_FILE "score.dat"


using namespace std;

class gamer {

public:
    //标准控制句柄
    static HANDLE hOutput;
    static HANDLE hInput;

    //窗口的宽度的高度
    static short width, height;

    //点击位置
    COORD pos = {0, 0};

    //提示用的窗口
    HWND hwnd = FindWindow("ConsoleWindowClass", nullptr);

    //输入数据记录
    INPUT_RECORD inRec{};

    //已经读取的记录数
    DWORD numRead{};

    //棋盘大小
    int board_width = 9, board_height = 9;

    //雷数
    int mine_num = 10;

    // 9 9 10           25=9*2+7 15=9+6
    // 16 16 40         39   22
    // 30 16 99         67   22
    int mine_seed[3] = {10, 40, 99};

    //棋盘状态的主要的数组  记录地雷的情况
    //x y
    int st[99][99]{};

    //记录格子是否已经开过了
    //x y
    //0 没有翻  -1 记录  1 翻开的
    int used[99][99]{};

    //向8个方向扩展
    // 1  2  3
    // 4  0  5
    // 6  7  8
    int x_step[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

    int y_step[8] = {-1, -1, -1, 0, 0, 1, 1, 1};

    //已经打开了这么多格子了
    int had_open = 0;

    //级别名字
    string se[3] = {"初级", "中级", "高级"};

    //各个级别前三名名字
    string name[9]={};

    //各个级别前三名分数
    //array<double, 9> scr{};
    double scr[9] = {};

    //标记的格子数
    int sign_num = 0;

    //是否正在游戏
    static bool IS_ON_GAME;

    //游戏主体是否正在忙碌中？ 忙的话计时器就不刷新了
    static bool IS_NOW_BUSY;

    //退出程序
    static bool IS_TO_EXIT;

    //保存游戏输赢的状态
    bool IS_WIN = false;
    bool IS_LOSE = false;

    //输出文件是否成功
    bool IS_FILE_OPEN_SUCCESS = false;

    //是否存在旧游戏
    bool IS_OLD_GAME_EXIST = false;

public:

    //初始化游戏引擎
    gamer();

    //初始化cmd窗口
    static void init_console();

    //初始化cmd窗口
    static void init_console(int x, int y);

    //将光标移动到x y处
    static void point(short x, short y);

    //隐藏控制台的光标
    static void hideCursor();

    //显示控制台光标
    static void displayCursor();

    //鼠标点击输入
    int mouseInput();

    //提示信息 (新窗口)
    void message(const CHAR *string1) const;

    //清屏(暴力)
    static void clear();

    //清行(暴力) 并把光标移动到这一行的开头
    static void clearLine(int line);

    //打印菜单在当前光标处
    void printMenu();

    //游戏阶段管理程序
    void gameHolder();

    //初始化地雷
    void init_mine();

    //翻格子
    void open_it(int x, int y);

    //检查当前坐标是否合法 在棋盘上 [0,board_~]
    //x y 坐标
    inline bool is_in_board(int x, int y) const;

    //你输啦
    void you_are_lose() const;

    //你赢了
    void you_are_win();

    //刷新视图
    void update();

    //游玩时中断退出
    void quit_the_game_during_gaming(bool to_exit);

    //退出程序
    static void exit_the_program();

    //初始化游戏状态
    void clear_game_state();

    //调整难度
    void adjust_game_difficulty();

    //存储游戏状态
    bool store_game_static();

    //恢复游戏状态
    bool restore_game_static();

    //检测static文件是否存在
    static bool detect_static_is_exit();

    //检测score文件是否存在
    static bool detect_score_is_exit();

    //最大化排行榜
    void init_to_max_score();

    //显示分数榜
    void show_score_table();

    //恢复排行榜
    void restore_score_table();

    //存储排行榜
    //前条件 已经存储了之前的排行榜了 这是覆盖读写
    void store_score_table();

    //标记格子
    void sign_it(int x, int y);

    //计时器守护程序
    static void timer_holder();

    //最后退出
    static void end_it();

    //左键双击翻开
    void double_flip(int x,int y);
};


#endif //GAMER_GAMER_H
