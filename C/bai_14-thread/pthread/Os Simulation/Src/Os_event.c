#include "Os_event.h"


StatusType WaitEvent(EventMaskType mask)
{
    pthread_mutex_lock(&task->mtx);
    while ((task->event_mask & mask) == 0) {  // Chưa có event mong muốn
        pthread_cond_wait(&task->cv, &task->mtx);
    }
    pthread_mutex_unlock(&task->mtx);
    return E_OK;
}

StatusType SetEvent(TaskType *task, EventMaskType mask)
{
    pthread_mutex_lock(&task->mtx);
    task->event_mask |= mask;           // set bit event
    pthread_cond_signal(&task->cv);     // đánh thức task
    pthread_mutex_unlock(&task->mtx);
    return E_OK;
}
StatusType GetEvent(TaskType *task,EventMaskType *current)
{
    pthread_mutex_lock(&task->mtx);
    *current = task->event_mask;
    pthread_mutex_unlock(&task->mtx);
    return E_OK;
}

StatusType ClearEvent(TaskType *task, EventMaskType mask)
{
    pthread_mutex_lock(&task->mtx);
    task->event_mask &= ~mask;  // clear bit tương ứng
    pthread_mutex_unlock(&task->mtx);
    return E_OK
}
