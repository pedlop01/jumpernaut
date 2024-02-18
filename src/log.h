#ifndef JUMP_LOG_H
#define JUMP_LOG_H

#define LOG_INIT (1 << 0)

extern int jump_loglevel;

void jump_log(const char *fmt, ...);

static inline bool jump_loglevel_mask(int mask)
{
    return (jump_loglevel & mask) != 0;
}

#define jump_log_mask(MASK, FMR, ...)                    \
    do {                                                 \
        if (unlikely(jump_loglevel_mask(MASK)))          \
            jump_log(FMR, ## __VA_ARGS__);               \
        }                                                \
    } while(0)

#endif
