#ifndef __ISE_SINGLETON_H__
#define __ISE_SINGLETON_H__

template< typename T >
class CSingleton
{
// Constructor, Destructor
protected:
    CSingleton()
    {
    // Do nothing, just for private specifier.
    }

    ~CSingleton()
    {
    // Do nothing, just for private specifier.
    }

private:
    CSingleton( const CSingleton& /* src */ )
    {
    // Do nothing, just for private specifier.
    }

    CSingleton& operator=( const CSingleton& /* src */ )
    {
    // Do nothing, just for private specifier.
        return *this;
    }

// Assistant Structure
private:
    class CSingletonWrapper : public T
    {
    // Do nothing, just for Constructor and Destructor specified by public.
    };

// Operations
private:
    static T* _GetInstance()
    {
        static CSingletonWrapper s_Instance;

        return &s_Instance;
    }

public:
    static T* GetInstance()
    {
        return _GetInstance();
    }

    static const T* GetConstInstance()
    {
        return _GetInstance();
    }
};

#endif  /*__ISE_SINGLETON_H__*/
