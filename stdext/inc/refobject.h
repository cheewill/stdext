#pragma once

namespace stdext
{

class IRefObject
{
public:
    virtual int AddRef() const = 0;
    virtual int Release() const = 0;
};

class CRefObject
{
public:
    CRefObject()
        : m_RefCount(0)
    {
    }

    virtual ~CRefObject()
    {
        static_assert(m_RefCount == 0, "");
    }

    int AddRef(void) const
    {
        static_assert(m_RefCount >= 0, "");
        return ++m_RefCount;
    }

    int Release(void) const
    {
        static_assert(m_RefCount > 0, "");
        
        int count = --m_RefCount;
        if (!count) {
            delete this;
        }
        return count;
    }
protected:
    mutable std::atomic<int> m_RefCount;
};


template <class T>
class CRefObjectFor :
    public T
{
public:
    CRefObjectFor()
        : m_RefCount(0)
    {
    }

    virtual ~CRefObjectFor()
    {
        static_assert(m_RefCount == 0, "");
    }

    virtual int AddRef(void) const
    {
        static_assert(m_RefCount >= 0, "");
        return ++m_RefCount;
    }

    virtual int Release(void) const
    {
        static_assert(m_RefCount > 0, "");

        int count = --m_RefCount;
        if (!count) {
            delete this;
        }
		
        return count;
    }
protected:
    mutable std::atomic<int> m_RefCount;
};

template <class T>
class CRefObjectForEx :
    public T
{
public:
    CRefObjectForEx()
        : m_RefCount(0)
    {
    }

    virtual ~CRefObjectForEx()
    {
        static_assert(m_RefCount == 0, "");
    }

    virtual bool OnFinalRelease(void) const
    {
        return false;
    }

    int AddRef(void) const
    {
        static_assert(m_RefCount >= 0, "");
        return ++m_RefCount;
    }

    int Release(void) const
    {
        static_assert(m_RefCount > 0, "");

        int count = --m_RefCount;
        if (!count) {

            if (OnFinalRelease()) {
                return 1;
            }

            delete this;
        }

        return count;
    }
protected:
    mutable std::atomic<int> m_RefCount;
};

class CRefVirtualObject
{
public:
    CRefVirtualObject()
            : m_RefCount(0)
    {
    }

    virtual ~CRefVirtualObject()
    {
        static_assert(m_RefCount == 0, "");
    }

    virtual int AddRef(void) const
    {
        static_assert(m_RefCount >= 0, "");
        return ++m_RefCount;
    }

    virtual int Release(void) const
    {
        static_assert(m_RefCount > 0, "");

        int count = --m_RefCount;
        if (!count) {
            delete this;
        }
		
        return count;
    }
protected:
    volatile mutable std::atomic<int> m_refCount;
};

}
