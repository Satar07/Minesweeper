/// <h1>主文件</h1>
///
/// <p>code by Satar07</p>
#include "baseheader.h"
#include "gamer.h"

int main() {
    gamer ga;
    ga.printMenu();
    while (!gamer::IS_TO_EXIT) {
        ReadConsoleInput(gamer::hInput, &ga.inRec, 1, &ga.numRead); // 读取1个输入事件
        if (ga.inRec.EventType == MOUSE_EVENT) {
            ga.mouseInput();//等待
            gamer::clear();
            if (ga.pos.Y == 1) {//新游戏
                ga.clear_game_state();
                ga.gameHolder();
            } else if (ga.pos.Y == 4) {//排行榜
                ga.show_score_table();
            } else if (ga.pos.Y == 7) {//调整难度
                ga.adjust_game_difficulty();
            } else if (ga.pos.Y == 10) {//退出程序
                gamer::exit_the_program();
            } else if (ga.IS_OLD_GAME_EXIST and ga.pos.Y == 13) {//旧游戏
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