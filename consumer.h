#ifndef _CONSUMER_H_
#define _CONSUMER_H_

#ifndef Consumer
#define Consumer(type) \
    struct { \
        void (*accept)(type data); \
    }

#endif

#endif