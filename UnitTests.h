#include "UnitTest++.h"
#define MESSAGE(msg) \
    std::cout << std::endl << "Testing " << msg << "..." << std::endl; \

SUITE(Stack)
{

    TEST(PushSingleNumber)
    {
        MESSAGE("Stack_PushSingleNumber");
        Stack s;
        s.push(3802);
        CHECK_EQUAL(s.top(), 0xEDA);
        s.pop();
        CHECK_EQUAL(s.empty(), true);
    }

    TEST(CheckDestroyedStack)
    {
        MESSAGE("Stack_CheckDestroyedStack");
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
        MESSAGE("Stack_CannotPushMore");
        Stack s;
        for (size_t i = 0; i < s.capacity(); i++)
            s.push(100 + i);
        CHECK_EQUAL(s.push(0xF00D), false);
    }

}

SUITE(Array)
{

    TEST(ConstructorsCheck)
    {
        MESSAGE("Array_ConstructorsCheck");
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
        Array b;
        CHECK_EQUAL(b.size(), 0);
        CHECK_EQUAL(b.empty(), true);
    }

    TEST(EmptyArrayOperations)
    {
        MESSAGE("Array_EmptyArrayOperations");
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

    TEST(FirstLastAtCheck)
    {
        MESSAGE("Array_FirstLastAtCheck");
        Array a(10);
        for (size_t i = 0; i < a.size(); i++)
        {
            a[i] = 10 * (i+1);
        }
        CHECK_EQUAL(a[0], a.first());
        CHECK_EQUAL(a[a.size() - 1], a.last());
        for (size_t i = 0; i < a.size(); i++)
        {
            CHECK_EQUAL(a[i], a.at(i));
        }
        CHECK_THROW(a.at(a.size() + 1), int);
        CHECK_THROW(a.at(-1), int);
    }

    TEST(EraseCheck)
    {
        MESSAGE("Array_EraseCheck");
        Array a(10);
        for (size_t i = 0; i < a.size(); i++)
        {
            a[i] = 10 * (i+1);
        }
        CHECK_EQUAL(a.erase(0), 9);
        CHECK_EQUAL(a.size(), 9);
        for (size_t i = 0; i < a.size(); i++)
        {
            CHECK_EQUAL(a[i], 10 * (i+2));
        }
        CHECK_THROW(a.erase(-1), int);
        CHECK_THROW(a.erase(a.size() + 100), int);
    }

    TEST(InsertCheck)
    {
        MESSAGE("Array_InsertCheck");
        Array a(10);
        for (size_t i = 0; i < a.size(); i++)
        {
            a[i] = 10 * (i+1);
        }
        CHECK_EQUAL(a.insert(0, 0), 11);
        CHECK_EQUAL(a.size(), 11);
        for (size_t i = 0; i < a.size(); i++)
        {
            CHECK_EQUAL(a[i], 10 * i);
        }
        CHECK_THROW(a.insert(-1, 0), int);
        CHECK_THROW(a.insert(a.size() + 100, 0), int);

        CHECK_EQUAL(a.insert(5, 111), 12);
        CHECK_EQUAL(a[5], 111);
    }

    TEST(ResizeCheck)
    {
        MESSAGE("Array_ResizeCheck");
        Array a(10);
        for (size_t i = 0; i < a.size(); i++)
        {
            a[i] = 10 * (i+1);
        }
        CHECK_EQUAL(a.resize(9), false);
        CHECK_EQUAL(a.resize(15), true);
        for (size_t i = 0; i < a.size(); i++)
        {
            if (i < 10)
                CHECK_EQUAL(a[i], 10 * (i+1));
            else
                CHECK_EQUAL(a[i], 0);
        }
    }

    TEST(OperatorEqualCheck)
    {
        MESSAGE("Array_OperatorEqualCheck");
        Array a(10);
        for (size_t i = 0; i < a.size(); i++)
        {
            a[i] = 10 * (i+1);
        }
        Array b = a;
        CHECK_EQUAL(a == b, true);
        b[1] = 99;
        CHECK_EQUAL(a == b, false);
        Array c(a);
        c.erase(3);
        CHECK_EQUAL(a == c, false);
    }

    TEST(OperatorPlusCheck)
    {
        MESSAGE("Array_OperatorPlusCheck");
        Array a(10), b(10);
        for (size_t i = 0; i < a.size(); i++)
        {
            a[i] = 10 * (i+1);
            b[i] = 11 * (i+1);
        }
        Array c = a + b;
        for (size_t i = 0; i < c.size(); i++)
        {
            CHECK_EQUAL(a[i] + b[i], c[i]);
            CHECK_EQUAL(a[i] + b[i], (a+b)[i]);
        }
        b.insert(1, 99);
        CHECK_THROW(a + b, int);
    }

    TEST(OperatorMinusCheck)
    {
        MESSAGE("Array_OperatorMinusCheck");
        Array a(10), b(10);
        for (size_t i = 0; i < a.size(); i++)
        {
            a[i] = 10 * (i+1);
            b[i] = 11 * (i+1);
        }
        Array c = a + b;
        for (size_t i = 0; i < c.size(); i++)
        {
            CHECK_EQUAL(a[i] - b[i], c[i]);
            CHECK_EQUAL(a[i] - b[i], (a+b)[i]);
        }
        b.insert(1, 99);
        CHECK_THROW(a - b, int);
    }
}
