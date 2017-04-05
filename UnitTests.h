#include "UnitTest++.h"
#include <iostream>
#include <stdexcept>

#define MESSAGE(msg) \
    std::cout << std::endl << "Testing " << msg << "..." << std::endl; \

using namespace thirtythree;

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

    TEST(FilledStack)
    {
        MESSAGE("Stack_FilledStack");
        Stack <float> s(10);
        for (size_t i = 0; i < s.capacity(); i++)
            s.push(100 + i);
        CHECK_EQUAL(10, s.size());
        s.push(23);
        CHECK_EQUAL(11, s.size());
        CHECK_EQUAL(11, s.capacity());
    }

}

SUITE(Vector)
{

    TEST(ConstructorsCheck)
    {
        MESSAGE("Vector_ConstructorsCheck");
        Vector <float> a(10);
        CHECK_EQUAL(a.size(), 10);
        CHECK_EQUAL(a.empty(), false);
        for (size_t i = 0; i < a.size(); i++)
        {
            CHECK_EQUAL(0, a[i]);
            a[i] = 10 * (i+1);
        }
        Vector <float> c = a;
        CHECK_EQUAL(a.size(), c.size());
        for (size_t i = 0; i < c.size(); i++)
        {
            CHECK_EQUAL(a[i], c[i]);
        }
        Vector <float> b;
        CHECK_EQUAL(b.size(), 0);
        CHECK_EQUAL(b.empty(), true);
    }
    TEST(EraseCheck)
    {
        MESSAGE("Vector_EraseCheck");
        Vector <float> a(10);
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
        MESSAGE("Vector_InsertCheck");
        Vector <float> a(10);
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
        CHECK_EQUAL(a.insert(12, 33), 13);
        CHECK_EQUAL(a[12], 33);
    }

    TEST(ResizeCheck)
    {
        MESSAGE("Vector_ResizeCheck");
        Vector <float> a(10);
        for (size_t i = 0; i < a.size(); i++)
        {
            a[i] = 10 * (i+1);
        }
        CHECK_THROW(a.resize(9), int);
        CHECK_EQUAL(a.resize(15), 15);
        for (size_t i = 0; i < a.size(); i++)
        {
            if (i < 10)
                CHECK_EQUAL(10 * (i+1), a[i]);
            else
                CHECK_EQUAL(0, a[i]);
        }
    }

    TEST(EmptyVectorOperations)
    {
        MESSAGE("Vector_EmptyVectorOperations");
        Vector <float> a;

        CHECK_EQUAL(a.size(), 0);
        CHECK_EQUAL(a.empty(), true);
        CHECK_THROW(a.first(), int);
        CHECK_THROW(a.last(), int);
        CHECK_THROW(a.at(10), int);
        CHECK_THROW(a[10], int);
        CHECK_THROW(a.erase(10), int);
        CHECK_THROW(a.insert(10, 66), int);
        CHECK_THROW(a.insert(1, 66), int);
        CHECK_EQUAL(a.resize(10), 10);
        CHECK_EQUAL(a.size(), 10);
    }

    TEST(FirstLastAtCheck)
    {
        MESSAGE("Vector_FirstLastAtCheck");
        Vector <float> a(10);
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

    TEST(OperatorEqualCheck)
    {
        MESSAGE("Vector_OperatorEqualCheck");
        Vector <float> a(10);
        for (size_t i = 0; i < a.size(); i++)
        {
            a[i] = 10 * (i+1);
        }
        Vector <float> b = a;
        CHECK_EQUAL(a == b, true);
        b[1] = 99;
        CHECK_EQUAL(a == b, false);
        Vector <float> c(a);
        c.erase(3);
        CHECK_EQUAL(a == c, false);
    }
    TEST(OperatorPlusCheck)
    {
        MESSAGE("Vector_OperatorPlusCheck");
        Vector <float> a(10), b(10);
        for (size_t i = 0; i < a.size(); i++)
        {
            a[i] = 10 * (i+1);
            b[i] = 11 * (i+1);
        }

        CHECK_EQUAL((a + b).size(), a.size() + b.size());
        Vector <float> c = a + b;
        for (size_t i = 0; i < c.size(); i++)
        {
            if (i < a.size())
            {
                CHECK_EQUAL(a[i], c[i]);
            }
            else
            {
                CHECK_EQUAL(b[i - a.size()], c[i]);
            }
        }

    }
    TEST(IteratorCheck)
    {
        MESSAGE("Vector_IteratorCheck");
        Vector <int> a(10);
        for (size_t i = 0; i < a.size(); i++)
        {
            a[i] = i;
        }
        Vector<int>::Vector_iterator it;
        int j = 0;
        for (it = a.begin(); it != a.end(); it++)
        {
            CHECK_EQUAL(j++, *it);
        }
        CHECK_EQUAL(j, *it);

        Vector<int>::Vector_iterator it2;
        j = 9;
        for (it2 = a.end(); it2 != a.begin(); it2--)
        {
            CHECK_EQUAL(j--, *it2);
        }
        CHECK_EQUAL(j, *it2);
    }
    TEST(InitializerListConstructor)
    {
        MESSAGE("Vector_InitializerListConstructor");
        Vector <int> a = {1, 2, 3, 4, 5, 6};
        CHECK_EQUAL(6, a.size());
        for (size_t i = 0; i < a.size(); i++)
        {
            CHECK_EQUAL(a[i], i + 1);
        }
    }
}

TEST(PrintFunction)
{
    MESSAGE("PrintFunction");
    print("This is a % functi%n test % % %", "print()", 'O', 42, 4.2, "\n");
}

SUITE(SmartPtr)
{
    TEST(my_auto_ptr)
    {
        MESSAGE("SmartPtr_my_auto_ptr");
        my_auto_ptr <int> p1(new int);
        *p1 = 10;
        CHECK_EQUAL(10, *p1);
        my_auto_ptr <int> p2;
        p2 = p1;
        CHECK_EQUAL(10, *p2);
        CHECK_THROW(*p1, std::exception);
        int *p3 = p2.release();
        CHECK_EQUAL(10, *p3);
        CHECK_THROW(*p2, std::exception);
    }
}

SUITE(Vector_bool)
{
    TEST(Bitset)
    {
        MESSAGE("Bitset");
        Bitset bits(10);

        bits[9] = 1;
        CHECK_EQUAL(true, bits[9]);
        CHECK_THROW(bits[10], std::exception);

        CHECK_EQUAL(bits[8], --bits[9]);
        bool b1 = --bits[9];
        CHECK_EQUAL(b1, bits[8]);
        bool b2 = bits[9];
        CHECK_EQUAL(b2, bits[9]);
        bits[8] = bits[9];
        CHECK_EQUAL(bits[9], bits[8]);

        CHECK_EQUAL(true, bits[9] == bits[8]);
        CHECK_EQUAL(false, bits[9] == bits[0]);
        CHECK_EQUAL(true, bits[9] != bits[0]);
        CHECK_EQUAL(false, !bits[9]);

        CHECK_EQUAL(16, bits.resize(16));
        CHECK_EQUAL(16, bits.size());
        for (int i = 10; i < bits.size(); i++)
        {
            CHECK_EQUAL(false, bits[i]);
        }
        bits[15] = 1;
        CHECK_EQUAL(true, bits[15]);
        CHECK_THROW(bits[16], std::exception);

    }
    TEST(ConstructorsCheck)
    {
        MESSAGE("Vector_Bool_ConstructorsCheck");
        Vector <bool> a(10);
        CHECK_EQUAL(10, a.size());
        CHECK_EQUAL(false, a.empty());
        for (size_t i = 0; i < a.size(); i++)
        {
            CHECK_EQUAL(0, a[i]);
            a[i] = i % 2;
        }
        Vector <bool> c = a;
        CHECK_EQUAL(a.size(), c.size());
        for (size_t i = 0; i < c.size(); i++)
        {
            CHECK_EQUAL(c[i], a[i]);
        }
        Vector <bool> b;
        CHECK_EQUAL(0, b.size());
        CHECK_EQUAL(true, b.empty());
    }
    TEST(EraseCheck)
    {
        MESSAGE("Vector_Bool_EraseCheck");
        Vector <bool> a(10);
        for (size_t i = 0; i < a.size(); i++)
        {
            a[i] = i % 2;
        }
        CHECK_EQUAL(9, a.erase(0));
        CHECK_EQUAL(9, a.size());
        for (size_t i = 0; i < a.size(); i++)
        {
            CHECK_EQUAL((i + 1) % 2, a[i]);
        }
        CHECK_THROW(a.erase(-1), int);
        CHECK_THROW(a.erase(a.size() + 100), int);
    }

    TEST(InsertCheck)
    {
        MESSAGE("Vector_Bool_InsertCheck");
        Vector <bool> a(10);
        for (size_t i = 0; i < a.size(); i++)
        {
            a[i] = i % 2;
        }
        CHECK_EQUAL(11, a.insert(0, 0));
        CHECK_EQUAL(11, a.size());
        for (size_t i = 0; i < a.size(); i++)
        {
            if (i == 0)
                CHECK_EQUAL(0, a[i]);
            else
                CHECK_EQUAL((i - 1) % 2, a[i]);
        }
        CHECK_THROW(a.insert(-1, 0), int);
        CHECK_THROW(a.insert(a.size() + 100, 0), int);
        CHECK_EQUAL(a.insert(5, false), 12);
        CHECK_EQUAL(false, a[5]);
        CHECK_EQUAL(13, a.insert(12, true));
        CHECK_EQUAL(true, a[12]);
    }

    TEST(ResizeCheck)
    {
        MESSAGE("Vector_Bool_ResizeCheck");
        Vector <bool> a(10);
        for (size_t i = 0; i < a.size(); i++)
        {
            a[i] = i % 2;
        }
        CHECK_THROW(a.resize(9), int);
        CHECK_EQUAL(15, a.resize(15));
        for (size_t i = 0; i < a.size(); i++)
        {
            if (i < 10)
                CHECK_EQUAL(i % 2, a[i]);
            else
                CHECK_EQUAL(false, a[i]);
        }
    }

    TEST(EmptyVectorOperations)
    {
        MESSAGE("Vector_Bool_EmptyVectorOperations");
        Vector <bool> a;

        CHECK_EQUAL(0, a.size());
        CHECK_EQUAL(true, a.empty());
        CHECK_THROW(a.first(), int);
        CHECK_THROW(a.last(), int);
        CHECK_THROW(a.at(10), int);
        CHECK_THROW(a[10], int);
        CHECK_THROW(a.erase(10), int);
        CHECK_THROW(a.insert(10, 66), int);
        CHECK_THROW(a.insert(1, 66), int);
        CHECK_EQUAL(10, a.resize(10));
        CHECK_EQUAL(10, a.size());
    }

    TEST(FirstLastAtCheck)
    {
        MESSAGE("Vector_Bool_FirstLastAtCheck");
        Vector <bool> a(10);
        for (size_t i = 0; i < a.size(); i++)
        {
            a[i] = i % 2;
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

    TEST(OperatorEqualCheck)
    {
        MESSAGE("Vector_Bool_OperatorEqualCheck");
        Vector <bool> a(10);
        for (size_t i = 0; i < a.size(); i++)
        {
            a[i] = i % 2;
        }
        Vector <bool> b = a;
        CHECK_EQUAL(true, a == b);
        b[1] = false;
        CHECK_EQUAL(false, a == b);
        Vector <bool> c(a);
        c.erase(3);
        CHECK_EQUAL(false, a == c);
    }

    TEST(OperatorPlusCheck)
    {
        MESSAGE("Vector_Bool_OperatorPlusCheck");
        Vector <bool> a(10), b(10);
        for (size_t i = 0; i < a.size(); i++)
        {
            a[i] = i % 2;
            b[i] = (i + 1 ) % 2;
        }

        CHECK_EQUAL((a + b).size(), a.size() + b.size());
        Vector <bool> c = a + b;
        for (size_t i = 0; i < c.size(); i++)
        {
            if (i < a.size())
            {
                CHECK_EQUAL(a[i], c[i]);
            }
            else
            {
                CHECK_EQUAL(b[i - a.size()], c[i]);
            }
        }

    }
//    TEST(IteratorCheck)
//    {
//        MESSAGE("Vector_Bool_IteratorCheck");
//        Vector <bool> a(10);
//        for (size_t i = 0; i < a.size(); i++)
//        {
//            a[i] = i % 2;
//        }
//        cout << "check1" << endl;
//        Vector<bool>::Vector_iterator it;
//        int j = 0;
//        cout << "check2" << endl;
//        cout << *it << endl;
//        it = a.begin();
//        cout << "check3" << endl;
//        for (it = a.begin(); it != a.end(); it++)
//        {
//
//            CHECK_EQUAL((j % 2), *it);
//            j++;
//        }
//        CHECK_EQUAL(j, *it);
//
//        Vector<bool>::Vector_iterator it2;
//        j = 9;
//        for (it2 = a.end(); it2 != a.begin(); it2--)
//        {
//            CHECK_EQUAL((j % 2), *it2);
//            j--;
//        }
//        CHECK_EQUAL(j, *it2);
//    }
    TEST(InitializerListConstructor)
    {
        MESSAGE("Vector_Bool_InitializerListConstructor");
        Vector <bool> a = {true, false, true, false, true, false};
        CHECK_EQUAL(6, a.size());
        for (size_t i = 0; i < a.size(); i++)
        {
            CHECK_EQUAL(a[i], (i + 1) % 2);
        }
    }
}
