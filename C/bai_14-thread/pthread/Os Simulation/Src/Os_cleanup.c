/* Cleanup đảm bảo PostTaskHook + running=0 luôn được gọi kể cả khi pthread_exit() */
void OS_TaskCleanup(void *arg)
{
    OsTaskCtl *const tc = (OsTaskCtl *)arg;
    PostTaskHook(); /* gọi hook hậu-task */
    pthread_cond_destroy(&tc->cv);
    pthread_mutex_destroy(&tc->mtx);
    atomic_store(&tc->running, 0); /* đánh dấu task đã kết thúc (cho phép kích lại) */
    tc->thread = (pthread_t)NULL;  /* reset địa chỉ của task Os cần chạy lại */
}