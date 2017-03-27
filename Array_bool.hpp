#include <cstdlib>


bool Array<bool> :: operator [] (int n) const
{
    if (n >= size_)
    {
        throw 0;
    }
    else
    {
        int bit = data_[n/8] & 1 << (n % 8);
        return !!bit;
    }
}

void Array<bool>:: print()
{
    for (int i = 0; i < size_; i++)
    {
        std::cout << data_[i]<< std:: endl;
    }
}


/*template<>
Array<bool>& Array<bool>:: operator [] (int n)
{

}
*/
