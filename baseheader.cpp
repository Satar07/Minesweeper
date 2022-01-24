/// <h1>通用头文件实现部分</h1>
///
/// <p>code by Satar07</p>
#include "baseheader.h"

string double_to_string(double x) {
    string res;
    res = int_to_string(static_cast<int>(x)) + '.'
          + int_to_string(static_cast<int>((x * 100)) % 100);//保留2位小数
    return res;
}

string int_to_string(int x) {
    string res;
    if (x < 10) {
        res = static_cast<char>(x + '0');
    } else {
        res = int_to_string(x / 10) + static_cast<char>(x % 10 + '0');
    }
    return res;
}

