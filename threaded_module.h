#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include "soxint.h"

enum { IO_BUFSIZE = 4096 };

typedef struct per_thread_state_tag {
    HANDLE ht;
    HANDLE evpro, evcon;
    unsigned tid;
    sox_bool done;
    sox_bool error;

    void *ctx;
    int (*flow)(struct per_thread_state_tag *);
    size_t ilen, olen;
    double ibuf[IO_BUFSIZE], obuf[IO_BUFSIZE];
} per_thread_state_t;

typedef struct lsx_thread_state_tag {
    sox_bool use_threads;
    int count;
    per_thread_state_t *pth;
} lsx_thread_state_t;

int lsx_init_threads(lsx_thread_state_t *state, sox_bool use_threads,
		     int count, void **ctx, int (*flow)(per_thread_state_t *));
int lsx_term_threads(lsx_thread_state_t *state);
int lsx_process_threaded_interleaved(lsx_thread_state_t *state,
				     const float *ibuf, float *obuf,
				     size_t *ilen, size_t *olen);
