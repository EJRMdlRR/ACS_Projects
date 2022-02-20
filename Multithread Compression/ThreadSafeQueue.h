#include <list>
#include <condition_variable>
#include <mutex>
#include <atomic>
#include <cassert>

class thread_safe_queue
{
private:
    std::list<std::tuple<int, int, char *>> _data;
    std::mutex _mutex;

public:
    void push_back(std::tuple<int, int, char *> _aVal);
    bool pop_front(std::tuple<int, int, char *> &_aVal);
    int size() {return _data.size();}
};