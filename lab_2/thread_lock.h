#ifndef THREAD_LOCK_H_
#define THREAD_LOCK_H_

extern pthread_rwlock_t *rwlocks;

void init_locks(int num_strings);
void destroy_locks(int num_strings);
void read_content(char *dst, int pos, char **theArray);
void write_content(char *src, int pos, char **theArray);

#endif
