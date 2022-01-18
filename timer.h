/// <h1>��ʱ�����岿��</h1>
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
    //��ʼ����ʱ��
    timer();

    //��ʼ��ʱ
    static void start();

    //��ͣ��ʱ
    static void pause();

    //�õ����ڽ��е�ʱ��
    static double get_time();

    //���¼�ʱ����ʱ��
    static void update();

    //��մ洢��ʱ��
    static void clearTime();

    //�ָ��洢��ʱ��
    static void resetTime(double time);

};


#endif //GAMER_TIMER_H
