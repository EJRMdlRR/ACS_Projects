#include "ThreadSafeQueue.h"
#include <iostream>

void thread_safe_queue::push_back(std::tuple<int, int, char *> _aVal)
{
    std::unique_lock<std::mutex> lock(_mutex);
    _data.push_back(_aVal);
}

bool thread_safe_queue::pop_front(std::tuple<int, int, char *> &_aVal)
{
    std::unique_lock<std::mutex> lock(_mutex);
    if (_data.size())
    {
        _aVal = _data.front();
        _data.pop_front();
        return true;
    }
    return false;
}
