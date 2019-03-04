# Spell-Correct

## Ⅰ.Purpose

*The usage of the project is to practice the knowledge in the following list:*    

> 1) socket net programming
> 2) reactor server frame
> 3) cache system (memory cache and disk cache)
> 4) using threadpool
> 5) log system (log4cpp)
> 6) Generate original dictionary and index file from corpus
> 7) the open source library cppjieba

## Ⅱ.Pre-usage

<u>**The project need some opensource library:**</u>

#### *1.log4cpp*

download in the page: http://log4cpp.sourceforge.net/

```
tar xzvf log4cpp-1.1.3.tar.gz
./configure
make
make check
make install
```

### *2.json*

It's a little complex. But  there are many way to install json-c. 

You can read the tutor in this page: https://blog.csdn.net/qq_40273354/article/details/78349648

or check the github of json-c in the page: https://github.com/json-c/json-c

### *3.cppjieba*

Good news,  the file has been included in the directory.  So you don't need to care about it.

### *4.POSIX*

It's meaning that you'd better run it on Linux or Unix.  In fact, it's only can be run on Linux or Unix.

On macos,  it didn't word because it didn't have *epoll library*.  On Window,  sorry for my no test.

## Ⅲ.Usage

*Finally, we arrive at  the excited part.* Although it's a tiny project, for us it's a good start-step, didn't it?

The project has two part, *the dictionary part* and *the server part*.

##### Dictionay Part

<u>If you want to build your own dictionary, you could put your corpus in ./Spell-Correct/GenDict/lib .</u>

The Chinese corpus should be in the /cn, and the English in the /en.

Then generate the library, you could do the follow:

```
cd ./Spell-Correct/GenDict
make
./Pre
```

After finished, the dictionary have been in /Spell-Correct/data.

##### Server Part

```
cd ./Spell-Correct
make
cd ./bin
./server.exe
```

Then the server will be run on your machine.

## Ⅳ.Test

In ./Spell-Correct/client, there has a client for test. You could use it to test the status of the server.

**THANKS.**

