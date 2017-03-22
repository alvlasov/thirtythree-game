#include "UnitTest++.h"
#define MESSAGE(msg) \
    std::cout << std::endl << "Testing " << msg << "..." << std::endl; \

SUITE(Stack)
{

    TEST(PushSingleNumber)
    {
        MESSAGE("Stack_PushSingleNumber");
        Stack <float> s;
        s.push(3802);
        CHECK_EQUAL(s.top(), 0xEDA);
        s.pop();
        CHECK_EQUAL(s.empty(), true);
    }

    TEST(CheckDestroyedStack)
    {
        MESSAGE("Stack_CheckDestroyedStack");
        Stack <float> *p;
        {
            Stack <float> s;
            for (size_t i = 0; i < s.capacity(); i++)
                s.push(100 + i);
            p = &s;
        }
        CHECK_EQUAL(p->ok(), false);
    }

    TEST(CannotPushMore)
    {
        MESSAGE("Stack_CannotPushMore");
        Stack <float> s;
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
        Array <float> a(10);
        CHECK_EQUAL(a.size(), 10);
        CHECK_EQUAL(a.empty(), false);
        for (size_t i = 0; i < a.size(); i++)
        {
            a[i] = 10 * (i+1);
        }
        Array <float> c = a;
        CHECK_EQUAL(a.size(), c.size());
        for (size_t i = 0; i < c.size(); i++)
        {
            CHECK_EQUAL(a[i], c[i]);
        }
        Array <float> b;
        CHECK_EQUAL(b.size(), 0);
        CHECK_EQUAL(b.empty(), true);
    }

    TEST(EmptyArrayOperations)
    {
        MESSAGE("Array_EmptyArrayOperations");
        Array <float> a;
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
        Array <float> a(10);
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
        Array <float> a(10);
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
        Array <float> a(10);
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
        Array <float> a(10);
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
        Array <float> a(10);
        for (size_t i = 0; i < a.size(); i++)
        {
            a[i] = 10 * (i+1);
        }
        Array <float> b = a;
        CHECK_EQUAL(a == b, true);
        b[1] = 99;
        CHECK_EQUAL(a == b, false);
        Array <float> c(a);
        c.erase(3);
        CHECK_EQUAL(a == c, false);
    }
    TEST(OperatorPlusCheck)
    {
        MESSAGE("Array_OperatorPlusCheck");
        Array <float> a(10), b(10);
        for (size_t i = 0; i < a.size(); i++)
        {
            a[i] = 10 * (i+1);
            b[i] = 11 * (i+1);
        }

        CHECK_EQUAL((a + b).size(), a.size());
        Array <float> c = a + b;
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
        Array <float> a(10), b(10);
        for (size_t i = 0; i < a.size(); i++)
        {
            a[i] = 10 * (i+1);
            b[i] = 11 * (i+1);
        }
        Array <float> c = a - b;
        for (size_t i = 0; i < c.size(); i++)
        {
            CHECK_EQUAL(a[i] - b[i], c[i]);
            CHECK_EQUAL(a[i] - b[i], (a-b)[i]);
        }
        b.insert(1, 99);
        CHECK_THROW(a - b, int);
    }
    TEST(OperatorNewCheck)
    {
        MESSAGE("Array_OperatorNewCheck");
        Array <int> *a = new Array <int>(10);
        for (size_t i = 0; i < a->size(); i++)
        {
            (*a)[i] = 10 * (i+1);
        }
        for (size_t i = 0; i < a->size(); i++)
        {
            CHECK_EQUAL(10 * (i+1), (*a)[i]);
        }

        Array <int> *b = new Array <int>(*a);
        for (size_t i = 0; i < b->size(); i++)
        {
            CHECK_EQUAL(10 * (i+1), (*b)[i]);
        }
    }
    TEST(IteratorCheck)
    {
        MESSAGE("Array_IteratorCheck");
        Array <int> a(10);
        for (size_t i = 0; i < a.size(); i++)
        {
            a[i] = i;
        }
        Array<int>::Array_iterator it;
        int j = 0;
        for (it = a.begin(); it != a.end(); it++)
        {
            CHECK_EQUAL(j++, *it);
        }
        CHECK_EQUAL(j, *it);

        Array<int>::Array_iterator it2;
        j = 9;
        for (it2 = a.end(); it2 != a.begin(); it2--)
        {
            CHECK_EQUAL(j--, *it2);
        }
        CHECK_EQUAL(j, *it2);
    }
    TEST(InitializerListConstructor)
    {
        MESSAGE("Array_InitializerListConstructor");
        Array <int> a = {1, 2, 3, 4, 5, 6};
        CHECK_EQUAL(6, a.size());
        for (size_t i = 0; i < a.size(); i++)
        {
            CHECK_EQUAL(a[i], i + 1);
        }
    }
}

TEST(PrintFunction)
{
    print("This is a % functi%n test % % %", "print()", 'O', 42, 4.2, "\n");
}
