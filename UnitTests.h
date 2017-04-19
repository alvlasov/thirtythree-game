#include "UnitTest++.h"
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <cstdio>

#include "Smart_ptr.h"
#include "Stack.h"
#include "Vector.h"
#include "Utility.h"
#include "CPU.h"

#define MESSAGE(msg) \
    std::cout << std::endl << "Testing " << msg << "..." << std::endl;

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
        CHECK_THROW(a.erase(-1), std::exception);
        CHECK_THROW(a.erase(a.size() + 100), std::exception);
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
        CHECK_THROW(a.insert(-1, 0), std::exception);
        CHECK_THROW(a.insert(a.size() + 100, 0), std::exception);
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
        CHECK_THROW(a.resize(9), std::exception);
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
        CHECK_THROW(a.first(), std::exception);
        CHECK_THROW(a.last(), std::exception);
        CHECK_THROW(a.at(10), std::exception);
        CHECK_THROW(a[10], std::exception);
        CHECK_THROW(a.erase(10), std::exception);
        CHECK_THROW(a.insert(10, 66), std::exception);
        CHECK_THROW(a.insert(1, 66), std::exception);
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
        CHECK_THROW(a.at(a.size() + 1), std::exception);
        CHECK_THROW(a.at(-1), std::exception);
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
        Vector<int>::iterator it;
        int j = 0;
        for (it = a.begin(); it != a.end(); it++)
        {
            CHECK_EQUAL(j++, *it);
        }

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

    TEST(my_unique_ptr)
    {
        MESSAGE("SmartPtr_my_unique_ptr");
        my_unique_ptr <int> p1(new int);
        *p1 = 10;
        CHECK_EQUAL(10, *p1);
        my_unique_ptr <int> p2;
        p2 = my_unique_ptr <int>(new int (42));
        CHECK_EQUAL(42, *p2);
    }

    TEST(my_shared_ptr)
    {
         MESSAGE("SmartPtr_my_shared_ptr");
         my_shared_ptr <int> p1(new int(10));
         *p1 = 20;
         CHECK_EQUAL(20, *p1);
         my_shared_ptr <int> p2;
         p2 = p1;
         CHECK_EQUAL(20, *p1);
         CHECK_EQUAL(false, p1.unique());
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
        CHECK_THROW(a.erase(-1), std::exception);
        CHECK_THROW(a.erase(a.size() + 100), std::exception);
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
        CHECK_THROW(a.insert(-1, 0), std::exception);
        CHECK_THROW(a.insert(a.size() + 100, 0), std::exception);
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
        CHECK_THROW(a.resize(9), std::exception);
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
        CHECK_THROW(a.first(), std::exception);
        CHECK_THROW(a.last(), std::exception);
        CHECK_THROW(a.at(10), std::exception);
        CHECK_THROW(a[10], std::exception);
        CHECK_THROW(a.erase(10), std::exception);
        CHECK_THROW(a.insert(10, 66), std::exception);
        CHECK_THROW(a.insert(1, 66), std::exception);
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
        CHECK_THROW(a.at(a.size() + 1), std::exception);
        CHECK_THROW(a.at(-1), std::exception);
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
    TEST(IteratorCheck)
    {
        MESSAGE("Vector_Bool_IteratorCheck");
        Vector <bool> a(10);
        for (size_t i = 0; i < a.size(); i++)
        {
            a[i] = i % 2;
        }
        Vector<bool>::iterator it;
        int j = 0;
        for (it = a.begin(); it != a.end(); it++)
        {
            CHECK_EQUAL((j % 2), *it);
            *it = true;
            j++;
        }
        for (it = a.begin(); it != a.end(); it++)
        {
            CHECK_EQUAL(true, *it);
        }

    }
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

SUITE(CPU)
{
    TEST(RegistersIndexing)
    {
        MESSAGE("CPU_RegistersIndexing");
        CPU cpu;
        CHECK_EQUAL(8, cpu.registersCount());
        CHECK_EQUAL(0, cpu[1]);
        cpu[1] = 101;
        CHECK_EQUAL(101, cpu[1]);
        CHECK_EQUAL(101, cpu.readRegister(1));
        cpu.setRegister(25, 7);
        CHECK_EQUAL(25, cpu[7]);
        cpu.setAllRegisters({1, 2, 3, 4});
        CHECK_EQUAL(4, cpu.registersCount());
        std::vector<double> regs = cpu.readAllRegisters();
        for (int i = 1; i <= 4; i++)
        {
            CHECK_EQUAL(i, regs[i - 1]);
        }

        CHECK_THROW(cpu[5], std::exception);
    }
    TEST(Push_Pop_Add_Div)
    {
        MESSAGE("CPU_Push_Pop_Add_Mult_Div");

        std::ofstream fout("test.script");
        fout << "push x1 \n push 324 \n add \n pop x0 \n push x0 \n push x2 \n div \n pop x2 \n push x2 \n push 3 \n mult \n pop x1 end";
        fout.close();

        CPU cpu("test.script", {0, 33, 714});
        cpu.execute();
        CHECK_EQUAL(357, cpu.readRegister(0));
        CHECK_EQUAL(1.5, cpu.readRegister(1));
        CHECK_EQUAL(0.5, cpu.readRegister(2));

        remove("test.script");
    }
    TEST(Call_Ret)
    {
        MESSAGE("CPU_Call_Ret");

        std::ofstream fout("test.script");
        fout << "push 1 \n push 2 \n div \n call 3 \n pop x0 \n end \n mark 3 \n pop x1 \n push x1 \n push x1 \n mult \n ret ";
        fout.close();

        CPU cpu("test.script");
        cpu.execute();
        CHECK_EQUAL(0.25, cpu.readRegister(0));

        remove("test.script");
    }
    TEST(Jump)
    {
        MESSAGE("CPU_Jump");

        std::ofstream fout("test.script");
        fout << " push x0 \n push x0 \n add \n pop x1 \n push x0 \n push x1 \n add \n pop x2 \n mark 10 \n push x0 \n push x1 \n add \n pop x1 \n push x1 \n push x2 \n add \n pop x2 \n push x1 \n push 4 \n jge 20 \n jmp 10 \n mark 20 \n end";
        fout.close();

        CPU cpu("test.script", {1, 0, 0, 0});
        cpu.execute();
        int f = 0;
        for (int i = 1; i <= 4; i++)
        {
            f += i;
        }
        CHECK_EQUAL(f, cpu.readRegister(2));

        remove("test.script");
    }

}
