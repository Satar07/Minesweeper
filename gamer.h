/// <h1>��Ϸ���涨�岿��</h1>
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
    //��׼���ƾ��
    static HANDLE hOutput;
    static HANDLE hInput;

    //���ڵĿ�ȵĸ߶�
    static short width, height;

    //���λ��
    COORD pos = {0, 0};

    //��ʾ�õĴ���
    HWND hwnd = FindWindow("ConsoleWindowClass", nullptr);

    //�������ݼ�¼
    INPUT_RECORD inRec{};

    //�Ѿ���ȡ�ļ�¼��
    DWORD numRead{};

    //���̴�С
    int board_width = 9, board_height = 9;

    //����
    int mine_num = 10;

    // 9 9 10           25=9*2+7 15=9+6
    // 16 16 40         39   22
    // 30 16 99         67   22
    int mine_seed[3] = {10, 40, 99};

    //����״̬����Ҫ������  ��¼���׵����
    //x y
    int st[99][99]{};

    //��¼�����Ƿ��Ѿ�������
    //x y
    //0 û�з�  -1 ��¼  1 ������
    int used[99][99]{};

    //��8��������չ
    // 1  2  3
    // 4  0  5
    // 6  7  8
    int x_step[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

    int y_step[8] = {-1, -1, -1, 0, 0, 1, 1, 1};

    //�Ѿ�������ô�������
    int had_open = 0;

    //��������
    string se[3] = {"����", "�м�", "�߼�"};

    //��������ǰ��������
    string name[9]={};

    //��������ǰ��������
    //array<double, 9> scr{};
    double scr[9] = {};

    //��ǵĸ�����
    int sign_num = 0;

    //�Ƿ�������Ϸ
    static bool IS_ON_GAME;

    //��Ϸ�����Ƿ�����æµ�У� æ�Ļ���ʱ���Ͳ�ˢ����
    static bool IS_NOW_BUSY;

    //�˳�����
    static bool IS_TO_EXIT;

    //������Ϸ��Ӯ��״̬
    bool IS_WIN = false;
    bool IS_LOSE = false;

    //����ļ��Ƿ�ɹ�
    bool IS_FILE_OPEN_SUCCESS = false;

    //�Ƿ���ھ���Ϸ
    bool IS_OLD_GAME_EXIST = false;

public:

    //��ʼ����Ϸ����
    gamer();

    //��ʼ��cmd����
    static void init_console();

    //��ʼ��cmd����
    static void init_console(int x, int y);

    //������ƶ���x y��
    static void point(short x, short y);

    //���ؿ���̨�Ĺ��
    static void hideCursor();

    //��ʾ����̨���
    static void displayCursor();

    //���������
    int mouseInput();

    //��ʾ��Ϣ (�´���)
    void message(const CHAR *string1) const;

    //����(����)
    static void clear();

    //����(����) ���ѹ���ƶ�����һ�еĿ�ͷ
    static void clearLine(int line);

    //��ӡ�˵��ڵ�ǰ��괦
    void printMenu();

    //��Ϸ�׶ι������
    void gameHolder();

    //��ʼ������
    void init_mine();

    //������
    void open_it(int x, int y);

    //��鵱ǰ�����Ƿ�Ϸ� �������� [0,board_~]
    //x y ����
    inline bool is_in_board(int x, int y) const;

    //������
    void you_are_lose() const;

    //��Ӯ��
    void you_are_win();

    //ˢ����ͼ
    void update();

    //����ʱ�ж��˳�
    void quit_the_game_during_gaming(bool to_exit);

    //�˳�����
    static void exit_the_program();

    //��ʼ����Ϸ״̬
    void clear_game_state();

    //�����Ѷ�
    void adjust_game_difficulty();

    //�洢��Ϸ״̬
    bool store_game_static();

    //�ָ���Ϸ״̬
    bool restore_game_static();

    //���static�ļ��Ƿ����
    static bool detect_static_is_exit();

    //���score�ļ��Ƿ����
    static bool detect_score_is_exit();

    //������а�
    void init_to_max_score();

    //��ʾ������
    void show_score_table();

    //�ָ����а�
    void restore_score_table();

    //�洢���а�
    //ǰ���� �Ѿ��洢��֮ǰ�����а��� ���Ǹ��Ƕ�д
    void store_score_table();

    //��Ǹ���
    void sign_it(int x, int y);

    //��ʱ���ػ�����
    static void timer_holder();

    //����˳�
    static void end_it();

    //���˫������
    void double_flip(int x,int y);
};


#endif //GAMER_GAMER_H
