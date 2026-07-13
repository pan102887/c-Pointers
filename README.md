# c-Pointers
C和指针的练习

## 目录结构

- `src/chapter_07` - `src/chapter_16`: 按章节整理的 demo 和练习代码
- `src/common`: 测试入口、打印工具、内存分配等公共代码
- `src/data_structures`: 链表、树、数组列表等跨章节数据结构练习
- `src/algorithms`: KMP 等算法练习
- `src/main.c`: 程序入口

## 构建和运行

```sh
cmake -S . -B build
cmake --build build
./build/c-demo --list
```

也可以使用仓库里的 `Makefile` 包装命令：

```sh
make
make list
```
