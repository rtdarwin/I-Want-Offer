#include <exception>
#include <queue>
#include <stdexcept>

using namespace std;

template <typename T>
class Stack
{
public:
    Stack() = default;

    void push(const T& e);
    T top();
    void pop();

private:
    int _tailQueue = 1;
    queue<T> _q1;
    queue<T> _q2;
};

template <typename T>
void
Stack<T>::push(const T& e)
{
    if (_tailQueue == 1) {
        _q1.push(e);
    } else {
        _q2.push(e);
    }
}

template <typename T>
T
Stack<T>::top()
{
    // if (!_q1.empty()) {
    //     while (_q1.size() > 1) {
    //         _q2.push(_q1.front());
    //         _q1.pop();
    //     }
    //     return _q1.front();
    // } else {
    //     if (_q2.empty()) {
    //         throw logic_error("stack is empty");
    //     } else {
    //     }
    // }

    queue<T>& tailQ = (_tailQueue == 1) ? _q1 : _q2;
    queue<T>& theOtherQ = (_tailQueue == 1) ? _q2 : _q1;

    if (tailQ.size() == 0) {
        throw logic_error("stack is empty");
    }

    while (tailQ.size() > 1) {
        theOtherQ.push(tailQ.front());
        tailQ.pop();
    }
    return tailQ.front();
}

template <typename T>
void
Stack<T>::pop()
{
    queue<T>& tailQ = (_tailQueue == 1) ? _q1 : _q2;
    queue<T>& theOtherQ = (_tailQueue == 1) ? _q2 : _q1;

    if (tailQ.size() == 0) {
        throw logic_error("stack is empty");
    }

    while (tailQ.size() > 1) {
        theOtherQ.push(tailQ.front());
        tailQ.pop();
    }
    tailQ.pop();
    _tailQueue = (_tailQueue == 1) ? 2 : 1;
}

int
main()
{
    Stack<int> q;

    q.push(1), printf("push 1\n");
    q.push(2), printf("push 2\n");
    q.push(3), printf("push 3\n");
    printf("stack top is %d\n", q.top());
    printf("stack top is %d\n", q.top());
    q.pop(), printf("pop\n");
    q.pop(), printf("pop\n");
    printf("stack top is %d\n", q.top());
    printf("stack top is %d\n", q.top());
    q.pop(), printf("pop\n");
    q.pop(), printf("pop\n");
}
