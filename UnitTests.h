#include "UnitTest++.h"

SUITE(Stack)
{

    TEST(PushSingleNumber)
    {
        Stack s;
        s.push(3802);
        CHECK_EQUAL(s.top(), 0xEDA);
        s.pop();
        CHECK_EQUAL(s.empty(), true);
    }

    TEST(CheckDestroyedStack)
    {
        Stack *p;
        {
            Stack s;
            for (size_t i = 0; i < s.capacity(); i++)
                s.push(100 + i);
            p = &s;
        }
        CHECK_EQUAL(p->ok(), false);
    }

    TEST(CannotPushMore)
    {
        Stack s;
        for (size_t i = 0; i < s.capacity(); i++)
            s.push(100 + i);
        CHECK_EQUAL(s.push(0xF00D), false);
    }

}

SUITE(Array)
{

}
