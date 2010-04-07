/* ---------------------------------------------------------------------------
 *
 * (c) The GHC Team, 2006
 *
 * Thread-related functionality
 *
 * --------------------------------------------------------------------------*/

#ifndef THREADS_H
#define THREADS_H

BEGIN_RTS_PRIVATE

#define END_BLOCKED_EXCEPTIONS_QUEUE ((MessageThrowTo*)END_TSO_QUEUE)

StgTSO * unblockOne (Capability *cap, StgTSO *tso);
StgTSO * unblockOne_ (Capability *cap, StgTSO *tso, rtsBool allow_migrate);

void checkBlockingQueues (Capability *cap, StgTSO *tso);
void wakeBlockingQueue   (Capability *cap, StgBlockingQueue *bq);
void tryWakeupThread     (Capability *cap, StgTSO *tso);
void migrateThread       (Capability *from, StgTSO *tso, Capability *to);

// like tryWakeupThread(), but assumes the TSO is not ThreadRelocated
void tryWakeupThread_    (Capability *cap, StgTSO *tso);

// Wakes up a thread on a Capability (probably a different Capability
// from the one held by the current Task).
//
#ifdef THREADED_RTS
void wakeupThreadOnCapability (Capability *cap,
                               Capability *other_cap, 
                               StgTSO *tso);
#endif

void updateThunk         (Capability *cap, StgTSO *tso,
                          StgClosure *thunk, StgClosure *val);

rtsBool removeThreadFromQueue     (Capability *cap, StgTSO **queue, StgTSO *tso);
rtsBool removeThreadFromDeQueue   (Capability *cap, StgTSO **head, StgTSO **tail, StgTSO *tso);

StgBool isThreadBound (StgTSO* tso);

#ifdef DEBUG
void printThreadBlockage (StgTSO *tso);
void printThreadStatus (StgTSO *t);
void printAllThreads (void);
void printThreadQueue (StgTSO *t);
#endif

END_RTS_PRIVATE

#endif /* THREADS_H */
