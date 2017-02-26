#include <iostream>
#include <Stack.cpp>

int main()
{
    Stack *p;
    {
        Stack s(8);
        s.push(10);
        s.push(9);
        s.push(8);
        s.push(7);
        s.push(6);
        s.pop();
        s.pop();
        s.dump();
        cout << s.top() << endl;
        p = &s;
    }

    (*p).dump();
    Stack s1(15);
    s1.dump();
    cout << s1.empty();
    s1.push(1);
    s1.dump();
    cout << s1.empty() << endl;
    cout << s1.pop() << endl;
    cout << s1.empty() << endl;
    s1.dump();
    return 0;
}
