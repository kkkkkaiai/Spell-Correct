 ///
 /// @file    Nocopyable.cc
 /// @author  WarrenC(Chenkai0130@outlook.com)
 /// @date    2019-02-20 03:27:33
 ///
 
#ifndef __SC_NOCOPYABLE_H__
#define __SC_NOCOPYABLE_H__

namespace sc
{

class Nocopyable
{
public:
	Nocopyable(){};
	~Nocopyable(){};

private:
	Nocopyable(const Nocopyable&) = delete;
	Nocopyable & operator=(const Nocopyable&) = delete;
};

}


#endif

