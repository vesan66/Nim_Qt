#pragma once
#include "global_flags.h"
#include "global_func.h"


#if _USEQT == true
    #include <QDebug>
    #include <QString>
#else
    #include <iostream>
#endif


inline void CoutMeMessage(const string& text){
#if _USEQT == true
qDebug() << QString::fromStdString(text);
#else
    std::cout << text << std::endl;
#endif
}


#if _SHOWDESTRUCTORS == true
#define SHOWD cout<< __FUNCTION__ << " $$$" << endl;
#else
#define SHOWD
#endif


#if _SHOWCONSTRUCTORS == true
#define SHOWC cout<< __FUNCTION__ << " ###" << endl;
#else
#define SHOWC
#endif


#if _SHOWOTHERS == true
#define SHOWO cout<< __FUNCTION__ << endl;
#else
#define SHOWO
#endif

#if _SHOWOTHERS == true
#define SHOWOMessage(message) cout<< __FUNCTION__ << ": " << message << endl;
#else
#define SHOWOMessage(message)
#endif

