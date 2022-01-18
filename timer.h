/// <h1>计时器定义部分</h1>
///
/// <p>code by Satar07</p>

#ifndef GAMER_TIMER_H
#define GAMER_TIMER_H

#include "baseheader.h"

class timer {
private:
    static double m_time;
    static clock_t m_start;
    static clock_t m_end;
    static bool is_work;
public:
    //初始化计时器
    timer();

    //开始计时
    static void start();

    //暂停计时
    static void pause();

    //得到正在进行的时长
    static double get_time();

    //更新计时器总时长
    static void update();

    //清空存储总时间
    static void clearTime();

    //恢复存储总时间
    static void resetTime(double time);

};


#endif //GAMER_TIMER_H
