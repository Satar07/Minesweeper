/// <h1>计时器实现部分</h1>
///
/// <p>code by Satar07</p>
#include "timer.h"
#include <ctime>

double timer::m_time = 0;

clock_t timer::m_start = 0;

clock_t timer::m_end = 0;

bool timer::is_work = false;

timer::timer() = default;

void timer::start() {
    if (is_work)return;
    m_start = clock();
    is_work = true;
}

void timer::pause() {
    if (!is_work) return;
    m_end = clock();
    update();
    is_work = false;
}

void timer::update() {
    m_time += static_cast<double>(m_end - m_start) / CLOCKS_PER_SEC;
}

double timer::get_time() {
    double res;
    if (is_work) {
        pause();
        res = m_time;
        start();
    } else {
        res = m_time;
    }
    return res;
}

void timer::clearTime() {
    is_work = false;
    m_time = 0;
}

void timer::resetTime(double time) {
    is_work = false;
    m_time = time;
}
