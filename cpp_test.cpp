#include <stdio.h>
#include <stdlib.h>

#define HEAD_SZIE (sizeof(char))
#define THREE_NODE_END_SIZE (sizeof(void*)*4)
#define TWO_NODE_END_SIZE (sizeof(void*)*3)
#define GET_HEAD(node) ((char)((char*)node)*)
#define GET_DATA(node) ((void*)((char*)node+HEAD_SZIE))
#define GET_LEFT_CHILD(node) ((void*)((char*)node+HEAD_SZIE+sizeof(void*)))
#define GET_RIGHT_CHILD(node) ((void*)((char*)node+HEAD_SZIE+sizeof(void*)*2))
#define GET_MIDDLE_CHILD(node) ((void*)((char*)node+HEAD_SZIE+sizeof(void*)*3))

class Demo
{
public:
    ~Demo()
    {
        printf("release Demo\n");
    }

    void test()
    {
        Demo *demo = new Demo();
        delete demo;
    }
};
static inline void* empty_list[0];

int main(int argc, char const *argv[])
{
    char *p = malloc(sizeof(char) * 10);

}