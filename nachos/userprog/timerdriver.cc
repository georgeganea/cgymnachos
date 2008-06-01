#include "timerdriver.h"

ntimer_t TimerDriver::timers[MaxTimerCount];

TimerDriver::TimerDriver()
{
	int i;
	for (i = 0; i < MaxTimerCount; i++)
		initTimer(i);
}

TimerDriver::~TimerDriver()
{
}

/* Adds a new timer for a thread. The timer will activate
 * after the number of ticks given.
 */
int TimerDriver::addTimer(Thread *thread, int ticks)
{
	int rc = -1, i;
	
	for (i = 0; i < MaxTimerCount; i++)
		if (timers[i].t == NULL) break;
	
	if (i == MaxTimerCount) {
		// nu mai este loc
		DEBUG('u', "No more timers available.");
	} else {
		timers[i].t = thread;
		timers[i].ticksRemaining = ticks;
		
		rc = 0;
	}
	
	return rc;
}

/* Called by the kernel, will decrement the number 
 * of remaining ticks on all timers and wake up any
 * threads whose remainingTicks value has reached 0.
 */
void TimerDriver::checkTimer(void)
{
	int i;
	
	for (i = 0; i < MaxTimerCount; i++) {
		if (timers[i].t != NULL) {
			if (--timers[i].ticksRemaining == 0) {
				scheduler->ReadyToRun(timers[i].t);
				initTimer(i);
				
				DEBUG('u', "waking up thread\n");
			}
		}
	}
}

/* Initialize the timer data structure to a void timer */
void TimerDriver::initTimer(int i)
{
	timers[i].t = NULL;
	timers[i].ticksRemaining = -1;
}
