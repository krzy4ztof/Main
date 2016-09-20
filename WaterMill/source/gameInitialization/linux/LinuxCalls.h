/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   LinuxCalls.h
 * Author: Krzysztof
 *
 * Created on 2 maja 2016, 19:22
 */


#ifndef LINUXCALLS_H
#define LINUXCALLS_H

#ifdef __LINUX__
//#ifdef __WIN32__

namespace watermill {

    class LinuxCalls {
    public:
        LinuxCalls();
        LinuxCalls(const LinuxCalls& orig);
        virtual ~LinuxCalls();
        bool IsOnlyInstance(char*);
        //bool IsOnlyInstance(LPCTSTR);
    private:
    };
}
#endif /* __LINUX__ */

#endif /* LINUXCALLS_H */

