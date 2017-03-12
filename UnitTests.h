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
    TEST(EmptyArrayOperations)
    {
        Array a;
        CHECK_EQUAL(a.size(), 0);
        CHECK_EQUAL(a.empty(), true);
        CHECK_THROW(a.first(), int);
        CHECK_THROW(a.last(), int);
        CHECK_THROW(a.at(10), int);
        CHECK_THROW(a[10], int);
        CHECK_THROW(a.erase(10), int);
        CHECK_THROW(a.insert(10, 66), int);
        CHECK_THROW(a.insert(0, 66), int);
        CHECK_EQUAL(a.resize(10), true);
        CHECK_EQUAL(a.size(), 10);
    }
    TEST(Constructors)
    {
        Array a(10);
        CHECK_EQUAL(a.size(), 10);
        CHECK_EQUAL(a.empty(), false);
        for (size_t i = 0; i < a.size(); i++)
        {
            a[i] = 10 * (i+1);
        }
        Array c = a;
        CHECK_EQUAL(a.size(), c.size());
        for (size_t i = 0; i < c.size(); i++)
        {
            CHECK_EQUAL(a[i], c[i]);
        }
    }
}
