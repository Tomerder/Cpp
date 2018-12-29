#ifndef __RUNNABLE_H__
#define __RUNNABLE_H__

namespace m10
{

class Runnable
{
public:
    Runnable() {}
    virtual void operator()() = 0;
};



template <class T, void (T::*MF)()>
class MemberFuncWrapper : public Runnable
{
    T& m_that;

public:

    MemberFuncWrapper(T& _that):m_that(_that){};

    void operator()()
    {
        (m_that.*MF)();
    }

private:
    MemberFuncWrapper(const MemberFuncWrapper&);
    MemberFuncWrapper& operator=(const MemberFuncWrapper&);

};


}
#endif // __RUNNABLE_H__
