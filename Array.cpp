#include <assert.h>
#include "smartArray.h"
#include <cmath>

CSmartArray::CSmartArray(const unsigned int _nSize) : nSize(_nSize), nReserve(nSize + 10)
{
    pData = new int[nReserve];
}

CSmartArray::CSmartArray(const CSmartArray &_copy): nSize(_copy.getSize()), nReserve(nSize + 10)
{
     pData = new int[nReserve];

    for (unsigned int i = 0; i < nSize; i++ )
    {
        pData[i] = _copy.pData[i];
    }
}

int& CSmartArray::operator[](const unsigned int _n)
{
    if (_n >= nSize)
    {
        assert(0);
    }

    return pData[_n];
}

void CSmartArray::clr()
{
    delete [] pData;
    nSize = 0;
}

//destructor
CSmartArray::~CSmartArray()
{
    clr();
};

void CSmartArray::resize(const unsigned int _n)
{
    int numRes = 10;

    if (_n < nSize)
    {
        numRes = 10 - (nSize/_n);
        nSize = _n;
    }
    else if (_n <= nReserve)
    {
        nSize = _n;
    }

    int *pNewData = new int [_n + numRes];

    for (unsigned int i = 0; i < nSize; i++)
    {
        pNewData[i] = pData[i];
    }

    clr();

    nSize = _n;
    nReserve = nSize + numRes;

    pData = pNewData;


}

 unsigned int CSmartArray :: add(const unsigned int _idx, const int _n)
{
    if (nSize == nReserve)
    {
        this ->resize(nSize);
    }

    if (_idx >= nSize)
    {
        assert(0);
    }

    int *pNewData = new int [nSize - _idx - 1];

    for (unsigned int i = _idx + 1 ; i < nSize; i++)
    {
        pNewData[i - _idx - 1] = pData[i];
    }

    pData[_idx + 1] = _n;

    for (unsigned int i = _idx + 2; i < nSize + 1; i++)
    {
          pData[i] = pNewData[i - _idx - 2];
    }

    nSize = nSize + 1;
    nReserve = nReserve - 1;

    return nSize;

}

unsigned int CSmartArray :: remove(const unsigned int _idx)
{
    if (_idx >= nSize)
    {
        assert(0);
    }

    int *pNewData = new int [nSize - _idx - 1];

    for (unsigned int i = _idx + 1 ; i < nSize; i++)
    {
        pNewData[i - _idx - 1] = pData[i];
    }

    for (unsigned int i = 0; i < nSize - _idx ; i++)
    {
        pData[i+ _idx] = pNewData[i];
    }

    this -> resize(nSize - 1);

    return nSize;
}



CSmartArray& CSmartArray::operator=(const CSmartArray &_copy)
{

    this->resize(_copy.getSize());

    for (unsigned int i = 0; i < nSize; i++ )
    {
        pData[i] = _copy.pData[i];
    }

    return *this;
}
