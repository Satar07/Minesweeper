/// <h1>���ļ�</h1>
///
/// <p>code by Satar07</p>
#include "baseheader.h"
#include "gamer.h"

int main() {
    gamer ga;
    ga.printMenu();
    while (!gamer::IS_TO_EXIT) {
        ReadConsoleInput(gamer::hInput, &ga.inRec, 1, &ga.numRead); // ��ȡ1�������¼�
        if (ga.inRec.EventType == MOUSE_EVENT) {
            ga.mouseInput();//�ȴ�
            gamer::clear();
            if (ga.pos.Y == 1) {//����Ϸ
                ga.clear_game_state();
                ga.gameHolder();
            } else if (ga.pos.Y == 4) {//���а�
                ga.show_score_table();
            } else if (ga.pos.Y == 7) {//�����Ѷ�
                ga.adjust_game_difficulty();
            } else if (ga.pos.Y == 10) {//�˳�����
                gamer::exit_the_program();
            } else if (ga.IS_OLD_GAME_EXIST and ga.pos.Y == 13) {//����Ϸ
                ga.restore_game_static();
                ga.gameHolder();
            }
            gamer::clear();
            gamer::init_console(25,15);
            ga.printMenu();
        }
    }
    gamer::init_console(25,15);
    gamer::end_it();
    return 0;
}