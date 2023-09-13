#include <stdio.h>

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
    Demo demo;
    demo.test();
    return 0;
}