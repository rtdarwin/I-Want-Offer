#include <exception>
#include <iostream>
#include <stack>

using namespace std;

template <typename T>
class Queue
{
public:
    Queue() = default;

    void appendTail(const T& e);
    T head();
    void deleteHead();

private:
    stack<T> _stack1;
    stack<T> _stack2;
};

template <typename T>
void
Queue<T>::appendTail(const T& e)
{
    _stack1.push(e);
}

template <typename T>
T
Queue<T>::head()
{
    if (!_stack2.empty()) {
        return _stack2.top();
    } else {
        while (_stack1.size() > 0) {
            _stack2.push(_stack1.top());
            _stack1.pop();
        }

        return _stack2.top();
    }
}

template <typename T>
void
Queue<T>::deleteHead()
{
    if (!_stack2.empty()) {
        _stack2.pop();
    } else {
        while (_stack1.size() > 0) {
            _stack2.push(_stack1.top());
            _stack1.pop();
        }

        if (_stack2.empty()) {
            throw logic_error("queue is empty");
        } else {
            _stack2.pop();
        }
    }
}

int
main()
{
    Queue<int> q;
    q.appendTail(1), printf("enqueue 1\n");
    q.appendTail(2), printf("enqueue 2\n");
    q.appendTail(3), printf("enqueue 3\n");
    printf("queue head is %d\n", q.head());
    q.deleteHead(), printf("dequeue\n");
    q.deleteHead(), printf("dequeue\n");
    q.appendTail(4), printf("enqueue 4\n");
    printf("queue head is %d\n", q.head());
    q.deleteHead(), printf("dequeue\n");
    q.deleteHead(), printf("dequeue\n");

    // a `logic_error' is expected
    q.deleteHead();

    return 0;
}
