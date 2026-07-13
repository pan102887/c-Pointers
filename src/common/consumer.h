#ifndef CP_COMMON_CONSUMER_H
#define CP_COMMON_CONSUMER_H

#ifndef CP_CONSUMER
#define CP_CONSUMER(type) \
    struct { \
        void (*accept)(type data); \
    }

#endif

#endif