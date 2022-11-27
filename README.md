# Embedded Mono runtime - example
Demo is destined for Windows. You need to have Mono installed.
## for ubuntu (20.04) users
1. install mono runtime
2. change compilation flags in makefile. Remove CPPFLAGS, LDFLAGS, LDLIBS and add the following:
```
CFLAGS=`pkg-config --cflags mono-2`
LDFLAGS=`pkg-config --libs mono-2`
```
3. run
```
make
./test-mono.exe
``` 
