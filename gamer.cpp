/// <h1>��Ϸ����ʵ�ֲ���</h1>
///
/// <p>code by Satar07</p>
#include "gamer.h"

//��ʼ����̬����
bool gamer::IS_ON_GAME = false;

short gamer::width = 25, gamer::height = 15;

HANDLE gamer::hOutput = GetStdHandle(STD_OUTPUT_HANDLE);//NOLINT

HANDLE gamer::hInput = GetStdHandle(STD_INPUT_HANDLE);//NOLINT

bool gamer::IS_NOW_BUSY = false;

bool gamer::IS_TO_EXIT = false;


gamer::gamer() {
    hideCursor();

    init_console(25, 15);//���ô��ڴ�С

    restore_score_table();//��ʼ�����а��ļ�

}

void gamer::init_console() {
    SetConsoleTitleA("ɨ��");//���ñ���
    //����ָ����������С
    COORD dSiz = {static_cast<SHORT>(width + 1), static_cast<SHORT>(height + 1)};
    SetConsoleScreenBufferSize(hOutput, dSiz);

    //����λ�ýṹ��
    SMALL_RECT rc = {0, 0, width, height};

    //������ʾ��������
    SetConsoleWindowInfo(hOutput, true, &rc);
}

void gamer::init_console(int x, int y) {
    SetConsoleTitleA("ɨ��");//���ñ���

    //����λ�ýṹ��
    SMALL_RECT rc = {0, 0, static_cast<SHORT>(x), static_cast<SHORT>(y)};

    //������ʾ��������
    SetConsoleWindowInfo(hOutput, true, &rc);

    //����ָ����������С
    COORD dSiz = {static_cast<SHORT>(x + 1), static_cast<SHORT>(y + 1)};
    SetConsoleScreenBufferSize(hOutput, dSiz);

}

void gamer::point(short x, short y) {
    //��������λ��
    COORD loc = {x, y};

    //����
    SetConsoleCursorPosition(hOutput, loc);
}

void gamer::hideCursor() {
    CONSOLE_CURSOR_INFO cursorInfo = {1, 0};
    SetConsoleCursorInfo(hOutput, &cursorInfo);
}

void gamer::displayCursor() {
    CONSOLE_CURSOR_INFO cursorInfo = {1, 1};
    SetConsoleCursorInfo(hOutput, &cursorInfo);
}

//return : 1 ���˫��  2 �Ҽ�����  3 �������  4 �Ҽ�˫��
int gamer::mouseInput() {
    while (true) {
        pos = {0, 0};
        ReadConsoleInput(hInput, &inRec, 1, &numRead);
        pos = inRec.Event.MouseEvent.dwMousePosition;

        if (inRec.EventType == MOUSE_EVENT) {//������
            Sleep(50);
            //���
            if (inRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
                if (inRec.Event.MouseEvent.dwEventFlags == DOUBLE_CLICK) {
                    return 1; //���˫��
                } else {
                    return 3; //�������
                }

            }
            if (inRec.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED) {//�Ҽ�
                if (inRec.Event.MouseEvent.dwEventFlags == DOUBLE_CLICK) {
                    return 4; //�Ҽ�˫��
                } else {
                    return 2; //�Ҽ�����
                }
            }
        }
    }
}

void gamer::message(const CHAR *string1) const {
    MessageBox(hwnd, string1, "��ʾ", 0);
}

void gamer::printMenu() {
    init_console(25, 15);
    cout << "\n"
            "        <����Ϸ>\n\n\n"
            "        <���а�>\n\n\n"
            "       <�Ѷ�ѡ��>\n\n\n"
            "         <�˳�>\n\n\n";
    IS_OLD_GAME_EXIST = detect_static_is_exit();
    if (IS_OLD_GAME_EXIST) {
        cout << "        <����Ϸ>";
    }
}

void gamer::clear() {
//ֱ����cls����Ῠ�� û�а취������ȡ�¼���
//������ô�����ķ����ɡ���
    point(0, 0);
    for (int i = 0; i < 5000 + 1; ++i) {
        putchar(' ');
    }
    point(0, 0);
}

void gamer::gameHolder() {
    IS_ON_GAME = true;
    timer::start();
    thread timerHolder(timer_holder);
    init_console();
    update();
    clearLine(board_height + 1);
    clearLine(board_height + 2);
    cout << "  <quit>         <menu>   ";
    bool fir = true;
    while (true) {
        ReadConsoleInput(hInput, &inRec, 1, &numRead); // ��ȡ1�������¼�
        if (inRec.EventType == MOUSE_EVENT) {
            int rt = mouseInput();//�ȴ�
            int x = pos.X / 2 - 2, y = pos.Y - 1;  //ת������
            if (rt % 2 == 0) {//�Ҽ����� ��˫�����ڶ����жϿ�Ļ�����˫���ˣ�
                if (is_in_board(x, y)) {
                    sign_it(x, y);
                    update();
                }
                continue;
            }
            if (rt == 1) {
                double_flip(x, y);
            }
            if (rt % 2 == 1) {//������� ��˫��
                //�㵽��Ϸ����
                if (is_in_board(x, y)) {
                    if (IS_OLD_GAME_EXIST) { //���ǵ�һ����
                        fir = false;
                    }
                    if (fir) {//��һ�β��ܷ������� ���������ʱ���ʼ��
                        init_mine();
                        fir = false;
                    }
                    open_it(x, y);
                    update();
                    if (IS_LOSE) {
                        IS_ON_GAME = false;
                        timerHolder.join();
                        timer::pause();
                        you_are_lose();//��ʾ��ը��
                    }
                    if (had_open + mine_num >= board_width * board_height) {
                        IS_ON_GAME = false;
                        timerHolder.join();
                        timer::pause();
                        you_are_win();//��ʾ��Ӯ��
                        IS_WIN = true;
                    }
                    if (IS_WIN or IS_LOSE) {
                        clear_game_state();
                        return;
                    }

                } else if (pos.Y == board_height + 2
                           and ((pos.X >= 3 and pos.X <= 6) or (pos.X >= 17 and pos.X <= 21))) {//��������
                    IS_ON_GAME = false;
                    timerHolder.join();

                    if (pos.X >= 3 and pos.X <= 6) {//exit
                        if (fir) exit_the_program();
                        else quit_the_game_during_gaming(true);
                        return;
                    }

                    if (pos.X >= 17 and pos.X <= 21) {//menu
                        if (!fir) quit_the_game_during_gaming(false);
                        clear_game_state();
                        return;
                    }
                    continue;

                } else continue;
            }
        }
    }
}

void gamer::init_mine() {
    //(1,5)  (1,22)
    //(9,4)  (9,22)
    //��һ�η�����
    int total = board_height * board_width;
    int temp_st[1225];
    memset(temp_st, 0, sizeof(temp_st));
    for (int i = 0; i < mine_num; ++i) {
        temp_st[i] = 1;
    }
    default_random_engine rd(time(nullptr) % 233);
    do {
        shuffle(temp_st, temp_st + total, rd);//һֱϴ�Ƶ�������鲻�ǵ���
    } while (temp_st[board_width * (pos.Y - 1) + pos.X / 2 - 2]);
    int cc = 0;
    for (int i = 0; i < board_height; ++i) {
        for (int j = 0; j < board_width; ++j) {
            st[j][i] = -temp_st[cc++]; //-1 ��ʾ����
        }
    }
    for (int i = 0; i < board_height; ++i) {  //������� x��
        for (int j = 0; j < board_width; ++j) {//y��
            if (st[j][i] == -1)continue;
            int cnt = 0;
            for (int k = 0; k < 8; ++k) {
                int x = j + x_step[k], y = i + y_step[k];
                if (is_in_board(x, y) and st[x][y] == -1) {
                    cnt++;
                }
            }
            st[j][i] = cnt;
        }
    }
}

void gamer::clearLine(int line) {
    point(0, static_cast<short>(line));
    for (int i = 0; i < width + 1; ++i) {
        putchar(' ');
    }
    point(0, static_cast<short>(line));
}

void gamer::open_it(int x, int y) {
    if (used[x][y] == 1)return;
    used[x][y] = 1;
    had_open++;
    int what = st[x][y];
    if (what == -1) {
        IS_LOSE = true;
        return;
    }
    if (what == 0) {
        for (int i = 0; i < 8; ++i) {
            int x_nxt = x + x_step[i], y_nxt = y + y_step[i];
            if (is_in_board(x_nxt, y_nxt)) {
                open_it(x_nxt, y_nxt);
            }
        }
        return;
    }
}

bool gamer::is_in_board(int x, int y) const {
    return (x >= 0 and x < board_width and y >= 0 and y < board_height);
}

void gamer::you_are_lose() const {
    double score = timer::get_time();
    string res = "��ը�� ��ʱ" + double_to_string(score) + "��";
    message(res.c_str());

}

void gamer::you_are_win() {
    double score = timer::get_time();
    string res = "��Ӯ�� ��ʱ" + double_to_string(score) + "��";
    message(res.c_str());

    string who = "��������";
    int index = 114514;
    //����Ƿ��Ƶ������ļ�¼
    restore_score_table();
    for (int i = 0; i < 3; ++i) {
        if (mine_seed[i] == mine_num) {
            for (int j = i * 3; j < i * 3 + 3; j++) {
                if (score < scr[j]) {
                    swap(score, scr[j]);
                    swap(who, name[j]);
                    index = min(j, index);
                }
            }
        }
    }
    clear();
    if (index != 114514) {
        cout << "�������� �����а���\n�������������" << endl;
        displayCursor();
        cin >> name[index];
        hideCursor();
    }
    store_score_table();
}

void gamer::update() {
    while (IS_NOW_BUSY);
    IS_NOW_BUSY = true;
    for (int i = 0; i < board_height; ++i) {
        point(0, static_cast<short>(i + 1));
        printf("    ");
        for (int j = 0; j < board_width; ++j) {
            if (used[j][i] == 1) {
                if (st[j][i] == 0) {
                    putchar(' '), putchar(' ');
                } else if (st[j][i] == -1) {
                    putchar('!'), putchar('!');
                } else {
                    printf("%d ", st[j][i]);
                }
            } else if (used[j][i] == 0) {
                printf("��");
            } else {
                printf("��");
            }
        }
        for (int j = 4 + board_width * 2; j <= width; ++j) {
            putchar(' ');
        }
    }
    IS_NOW_BUSY = false;
}

void gamer::quit_the_game_during_gaming(bool to_exit) {
    clearLine(board_height + 2);
    cout << "�Ƿ񱣴��¼? yes  no   ";
    while (true) {
        ReadConsoleInput(hInput, &inRec, 1, &numRead); /* ��ȡ1�������¼� */
        if (inRec.EventType == MOUSE_EVENT) {
            mouseInput();//�ȴ�
            if (pos.Y == board_height + 2) {
                if (pos.X <= 16 and pos.X >= 13) {
                    //�洢��Ϸ״̬
                    IS_FILE_OPEN_SUCCESS = store_game_static();
                    if (!IS_FILE_OPEN_SUCCESS)message("�ļ���ʧ��");
                }
                if ((pos.X <= 16 and pos.X >= 13) or (pos.X >= 19 and pos.X <= 20)) {
                    if (to_exit)exit_the_program();
                    break;
                }
            }
        }
    }
}

void gamer::exit_the_program() {
    clear();
    IS_TO_EXIT = true;
    //exit(0);
}

void gamer::clear_game_state() {
    timer::clearTime();//��ռ�ʱ��
    memset(st, 0, sizeof(st));
    memset(used, 0, sizeof(used));
    IS_WIN = IS_LOSE = false;
    IS_OLD_GAME_EXIST = false;
    had_open = 0;
}

void gamer::adjust_game_difficulty() {
    cout << endl
         << "     ����   9*9   10\n\n"
         << "     �м�  16*16  40\n\n"
         << "     �߼�  30*16  99\n\n";
    while (true) {
        ReadConsoleInput(hInput, &inRec, 1, &numRead); /* ��ȡ1�������¼� */
        if (inRec.EventType == MOUSE_EVENT) {
            mouseInput();//�ȴ�
            if (pos.Y == 1) {
                width = 25;
                height = 15;
                board_width = 9;
                board_height = 9;
                mine_num = 10;
                return;
            }
            if (pos.Y == 3) {
                width = 39;
                height = 22;
                board_width = 16;
                board_height = 16;
                mine_num = 40;
                return;
            }
            if (pos.Y == 5) {
                width = 67;
                height = 22;
                board_width = 30;
                board_height = 16;
                mine_num = 99;
                return;
            }
        }
    }
}


bool gamer::store_game_static() {
    ofstream fout(STATE_FILE);
    if (!fout.is_open())return false;
    fout << board_width << ' ' << board_height << ' ' << timer::get_time() << endl;
    for (int i = 0; i < board_height; ++i) {
        for (int j = 0; j < board_width; ++j) {
            fout << st[j][i] << ' ';
        }
        fout << endl;
    }

    for (int i = 0; i < board_height; ++i) {
        for (int j = 0; j < board_width; ++j) {
            fout << used[j][i] << ' ';
        }
        fout << endl;
    }
    return true;
}

bool gamer::restore_game_static() {
    ifstream fin(STATE_FILE);
    double preTime;
    if (!fin.is_open())return false;
    fin >> board_width >> board_height >> preTime;
    timer::resetTime(preTime);
    mine_num = 0;
    had_open = 0;
    for (int i = 0; i < board_height; ++i) {
        for (int j = 0; j < board_width; ++j) {
            fin >> st[j][i];
            if (st[j][i] == -1)
                mine_num++;
        }
    }
    for (int i = 0; i < board_height; ++i) {
        for (int j = 0; j < board_width; ++j) {
            fin >> used[j][i];
            if (used[j][i] == 1)
                had_open++;
        }
    }
    width = static_cast<short>(board_width * 2 + 7);
    height = static_cast<short>(board_height + 6);
    return true;
}


bool gamer::detect_static_is_exit() {
    // ע�⣡������
    // ��Ϊ�ǰ��µ�һ��ʱ�ų�ʼ�� ����ʲô�������ʹ洢��Ϸ״̬���������ǿ���Ϸ
    // �� ���Բ������û�ʲô������ʹ��� ��ʱ�򷵻ز˵�������
    ifstream fin(STATE_FILE);
    if (!fin.is_open())return false;
    else return true;
}

void gamer::show_score_table() {
    restore_score_table();
    int cnt = 0;
    for (auto &i: se) {
        cout << endl << i << endl;
        for (int j = 0; j < 3; ++j) {
            cout << j + 1 << '\t' << name[cnt] << '\t' << scr[cnt] << endl;
            cnt++;
        }
    }
    mouseInput();
}

void gamer::create_file() {
    ofstream fout(SCORE_FILE);
}

void gamer::restore_score_table() {
    ifstream fin(SCORE_FILE);
    if (!detect_score_is_exit()) {
        init_to_max_score();
    }
    for (int i = 0; i < 9; ++i) {
        fin >> name[i] >> scr[i];
    }
}

void gamer::store_score_table() {
    ofstream fout(SCORE_FILE);
    if (!fout.is_open()) {
        message("���а��ļ��򿪴��� �����Ƿ������������");
        return;
    }
    for (int i = 0; i < 9; ++i) {
        fout << name[i] << ' ' << scr[i] << endl;
    }
}

void gamer::sign_it(int x, int y) {
    if (used[x][y] == 0) {//û�з��ĸ���
        used[x][y] = -1;
        sign_num++;
    } else if (used[x][y] == -1) {
        used[x][y] = 0;
        sign_num--;
    }
}

void gamer::timer_holder() {
    while (IS_ON_GAME) {
        std::chrono::milliseconds dura(100);
        std::this_thread::sleep_for(dura);
        if (IS_NOW_BUSY)continue;//����æ�Ҿ�ͣ
        IS_NOW_BUSY = true;
        //��������λ��
        COORD loc = {0, static_cast<SHORT>(height - 1)};
        //����
        SetConsoleCursorPosition(hOutput, loc);
        for (int i = 0; i < width + 2; ++i) {
            putchar(' ');
        }
        //����
        SetConsoleCursorPosition(hOutput, loc);
        cout << timer::get_time();
        IS_NOW_BUSY = false;
    }
}

void gamer::end_it() {
    gamer::clear();
    cout <<
         "                   \n"
         "                   \n"
         " ����������    ����������\n"
         "    ����         ����  \n"
         "    ����         ����  \n"
         "                   \n"
         "                   \n"
         "       ��    ��     \n"
         "        ������      \n"
         "\n"
         "\n"
         "\n"
         "\n"
         "\n"
         "     code by Satar07";//��Ȩ��ʶ��ǿ
    Sleep(500);
    exit(0);
}

void gamer::double_flip(int x, int y) {
    if (used[x][y] == 0)return;
    int mine_around = 0, now_x, now_y;
    for (int i = 0; i < 8; ++i) {
        now_x = x + x_step[i];
        now_y = y + y_step[i];
        if (is_in_board(now_x, now_y) and used[now_x][now_y] == -1) {
            mine_around++;
        }
    }
    if (mine_around != st[x][y])return;
    for (int i = 0; i < 8; ++i) {
        now_x = x + x_step[i];
        now_y = y + y_step[i];
        if (is_in_board(now_x, now_y) and used[now_x][now_y] == 0) {
            open_it(now_x, now_y);
        }
    }
}

void gamer::init_to_max_score() {
    for (auto &i: name) {
        i = "noname";
    }
    for (double &i: scr) {
        i = 999.9;
    }
}

bool gamer::detect_score_is_exit() {
    ifstream fin(SCORE_FILE);
    return fin.is_open();
}
