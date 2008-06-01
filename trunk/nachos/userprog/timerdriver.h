#ifndef TIMERDRIVER_H_
#define TIMERDRIVER_H_

#include "thread.h"
#include "scheduler.h"

#define MaxTimerCount	10

struct ntimer_t_ {
	Thread *t;
	int ticksRemaining;
};

typedef struct ntimer_t_ ntimer_t;

extern Scheduler *scheduler;

class TimerDriver
{
public:
	TimerDriver();
	virtual ~TimerDriver();
	
	int addTimer(Thread *thread, int ticks);
	void checkTimer(void);
private:
	static ntimer_t timers[MaxTimerCount];
	void initTimer(int i);
};

#endif /*TIMERDRIVER_H_*/
