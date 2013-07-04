CygProfiler suite
-----------------

CygProfiler is a set of functions for use with gcc's
-finstrument-functions option. See info page of gcc for
details and description of this option.

To use it, compile your program with -finstrument-functions
and link together with cyg-profile.c. Somewhere at the
beginning of the program call cygprofile_enable() to start
logging all function entries and exits into a logfile. 

By default the name of the logfile is cyglog.$PID, but you
can set a different one using cygprofile_setfilename().
To get current logfile name use cygprofile_getfilename(). 
To see if logging is enabled use cygprofile_isenabled().
You can stop logging by calling cygprofile_disable().

Note that subsequent enabling of logging will overwrite the
previous log with the same name!

After you have created a logfile run cyg-resolve.pl with the
program name that created the logfile as a first argument
and the logfile name as a second argument. On stdout you'll
see a log of all[1] functions invoked while logging was
enabled. 

Example for plain C:
$ gcc -finstrument-functions -o test test.c cyg-profile.c
$ ./test
Logfile: cyglog.1234
$ cyg-progile.pl test cyglog.1234
Loading symbols from test ... OK
Seen 65 symbols, stored 22 function offsets
Level correction set to 0
        +  0 0x80486a9 (from 0x804872f)  function3()
        +  1 0x804866d (from 0x80486c8)   function2()
        +  2 0x8048634 (from 0x804868c)    function1()
done

As you can see - "function3()" called "function2()" which then
called "function1()". Function "main()" isn't in the list,
because the profiling was not yet enabled at the time it was
called.

Example for C++:
$ gcc -c cyg-profile.c
$ g++ -finstrument-functions -c test.cxx
$ g++ -o test test.o cyg-profile.o
$ ./test
Logfile: cyglog.1234
$ ./cyg-resolve.pl test cyglog.1234
Loading symbols from test ... OK
Seen 78 symbols, stored 25 function offsets
Level correction set to 1
        +  1 0x400d1c (from 0x400dcb)   _ZN4test9function3Ec()
        +  2 0x400cd4 (from 0x400d48)    _ZN4test9function2Ei()
        +  3 0x400c98 (from 0x400d01)     _ZN4test9function1El()
        +  0 0x400e3e (from 0x2a95ae2c8b)  __tcf_0()
done

The usage is similar to the plain C case.  Unfortunately you'll
only see the mangled function names, e.g. "_ZN4test9function3Ec"
instead of "int test::function3(char c)".

Michal Ludvig, <michal@logix.cz>
http://www.logix.cz/michal/devel

----
[1] All means all functions, that were compiled with
    -finstrument-functions.
