#include <iostream>
#include <Stack.cpp>

#define TEST(what,cond)\
    if (cond())                 \
        cout << "Test passed!" << endl; \
    else                        \
        cout << "Test not passed!" << endl; \

#define ASSERT_EQ(cond1,cond2)  \
    if (cond1!=cond2)           \
        assert(0);              \

#define EXCEPT_EQ(cond1,cond2)  \
    if (cond1!=cond2)           \
        return false;           \

bool PushSingleNumber()
{
    Stack s;
    s.push(3802);
    EXCEPT_EQ(s.top(), 0xEDA);
    s.pop();
    EXCEPT_EQ(s.size(), 0);
    return true;
}

bool DestroyedStack()
{
    Stack *p;
    {
        Stack s;
        for (int i = 0; i < s.capacity(); i++)
            s.push(100 + i);
        p = &s;
    }
    EXCEPT_EQ(p->ok(), false);
    return true;
}

bool CannotPushMore()
{
    Stack s;
    for (int i = 0; i < s.capacity(); i++)
        s.push(100 + i);
    EXCEPT_EQ(s.push(0xF00D), false);
    return true;
}


int main()
{
    Stack s;
    TEST(Stack, PushSingleNumber);
    TEST(Stack, CannotPushMore);
    TEST(Stack, DestroyedStack);

    /*Stack *p;
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
    s1.dump();*/
    return 0;
}
