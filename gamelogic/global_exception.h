#ifndef GLOBAL_EXCEPTION_H
#define GLOBAL_EXCEPTION_H

#include "global_flags.h"



/*
    Example:
    try {
        throw ExceptionCustom("Hallo");
    }  catch (ExceptionCustom &e) {
        qDebug() << e.what();
    }

    Example2:
    try {
        throw EXCEPTSWICTH("Hallo");
    }  catch (EXCEPTSWICTH &e) {
        qDebug() << e.what();
    }
*/



#if _USEQT == true
    #include <iostream>
    #include <exception>
    using namespace std;

    class ExceptionCustom: public std::exception
    {
    public:
        inline explicit ExceptionCustom(char const* const _Message) noexcept : std::exception(), _What{} { this->_What = _Message; }
        inline const char * what () const throw () { return _What; }
    private:
        char const* _What;
    };

    #define EXCEPTSWICTH ExceptionCustom

#else
    #define EXCEPTSWICTH exception
#endif

#endif // GLOBAL_EXCEPTION_H
