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
    }

    int AddRef(void) const
    {
        ++m_RefCount;
        return m_RefCount;
    }

    int Release(void) const
    {
        int RefCount = --m_Count;

        if (!RefCount) {
            delete this;
        }
        return RefCount;
    }
protected:
    mutable std::atomic<size_t> m_RefCount;
};


template <class T>
class CRefObjectFor :
    public T
{
public:
    CRefObjectFor()
        : m_lRefCount(0)
    {
    }

    virtual ~CRefObjectFor()
    {
    }

    virtual int AddRef(void) const
    {
        ++m_RefCount;
        return m_RefCount;
    }

    virtual int Release(void) const
    {
        int RefCount = --m_Count;

        if (!RefCount) {
            delete this;
        }
        return RefCount;
    }
protected:
    mutable std::atomic<size_t> m_RefCount;
};


template <class T>
class CRefObjectForEx :
    public T
{
public:
    CRefObjectForEx()
        : m_lRefCount(0)
    {
    }

    virtual ~CRefObjectForEx()
    {

    }

    virtual bool OnFinalRelease(void) const
    {
        return false;
    }

    int AddRef(void) const
    {
        ++m_RefCount;
        return m_RefCount;
    }

    int Release(void) const
    {
        int RefCount = --m_Count;

        if (!RefCount) {

            if (OnFinalRelease()) {
                return 1;
            }

            delete this;
        }

        return RefCount;
    }
protected:
    mutable std::atomic<size_t> m_RefCount;
};


class CRefVirtualObject :
    public IRefObject
{
public:
    CRefVirtualObject()
        : m_lRefCount(0)
    {
    }

    virtual ~CRefVirtualObject()
    {

    }

    virtual int AddRef(void) const
    {
        ++m_RefCount;
        return m_RefCount;
    }

    virtual int Release(void) const
    {
        int RefCount = --m_Count;

        if (!RefCount) {
            if (!RefCount) {

                if (OnFinalRelease()) {
                    return 1;
                }

                delete this;
            }

            return RefCount;
    }
protected:
    mutable std::atomic<size_t> m_RefCount;
};

}
