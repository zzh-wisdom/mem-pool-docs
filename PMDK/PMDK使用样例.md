# PMDK 使用样例

安装好 PMDK 后可以按照下面的步骤运行样例程序。

首先安装后，需要重启，或者运行 ldconfig 命令

> `ldconfig` 命令的用途是在默认搜寻目录(/lib和/usr/lib)以及动态库配置文件/etc/ld.so.conf内所列的目录下,搜索出可共的动态 链接库(格式如lib*.so*),进而创建出动态装入程序(ld.so)所需的连接和缓存文件.缓存文件默认为 /etc/ld.so.cache,此文件保存已排好序的动态链接库名字列表. 通常在系统启动时会执行命令ldconfig。**当用户安装了一个新的动态链接库时,就需要手动运行lfconfig命令**.

## 样例程序

**wirte_obj:**

```c
#include <stdio.h>
#include <string.h>
#include <libpmemobj.h>
 
#define LAYOUT_NAME "intro_1"
#define MAX_BUF_LEN 10
 
struct my_root {
	size_t len;
	char buf[MAX_BUF_LEN];
};
 
int
main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("usage: %s file-name\n", argv[0]);
		return 1;
	}
    // 创建内存池
	PMEMobjpool *pop = pmemobj_create(argv[1], LAYOUT_NAME,
				PMEMOBJ_MIN_POOL, 0666);
 
	if (pop == NULL) {
		perror("pmemobj_create");
		return 1;
	}
    // 创建根对象
	PMEMoid root = pmemobj_root(pop, sizeof(struct my_root));
    // 获取根对象的直接指针
	struct my_root *rootp = pmemobj_direct(root);
 
	char buf[MAX_BUF_LEN] = {0};
	if (scanf("%9s", buf) == EOF) {
		fprintf(stderr, "EOF\n");
		return 1;
	}
 
	rootp->len = strlen(buf);
    // 持久化长度
	pmemobj_persist(pop, &rootp->len, sizeof(rootp->len));
    // 持久化内容
	pmemobj_memcpy_persist(pop, rootp->buf, buf, rootp->len);
    // 关闭pool
	pmemobj_close(pop);
	return 0;
}
```

**read-obj:**

```c
#include <stdio.h>
#include <string.h>
#include <libpmemobj.h>
 
#define LAYOUT_NAME "intro_1"
#define MAX_BUF_LEN 10
 
struct my_root {
	size_t len;
	char buf[MAX_BUF_LEN];
};
 
int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("usage: %s file-name\n", argv[0]);
		return 1;
	}
 
	PMEMobjpool *pop = pmemobj_open(argv[1], LAYOUT_NAME);
	if (pop == NULL) {
		perror("pmemobj_open");
		return 1;
	}
 
	PMEMoid root = pmemobj_root(pop, sizeof(struct my_root));
	struct my_root *rootp = pmemobj_direct(root);
 
	if (rootp->len == strlen(rootp->buf))
		printf("%s\n", rootp->buf);
 
	pmemobj_close(pop);
 
	return 0;
}
```

## 编译运行

**Makefile:**

```makefile
CC = gcc
CFLAGS = #-std=c++11 #-ggdb -Wall -Werror
LDFLAGS = -lpmemobj -lpmem

RM = rm -f

obj_write_test = bin/obj_write_test
obj_read_test = bin/obj_read_test
TARGETS = $(obj_write_test) $(obj_read_test)

.PHONY: all clean test clean-data-files

all: $(TARGETS)

$(obj_write_test):
	$(CC) $(CFLAGS) -o $@ obj_write_test.c $(LDFLAGS)

$(obj_read_test):
	$(CC) $(CFLAGS) -o $@ obj_read_test.c $(LDFLAGS)

test: clean-data-files
	@echo "请输入您的对象(< 10 bytes):"
	@./bin/obj_write_test ./pmem-fs/obj-fs
	@echo "读取对象的结果为:"
	@./bin/obj_read_test ./pmem-fs/obj-fs

clean-data-files:
	$(RM) ./pmem-fs/*

clean:
	$(RM) ./bin/* ./pmem-fs/*
```

## 结果

```shell
zzh@DESKTOP-9OSBLA6:~/Code/github/pmdk/mytest/pmemobj$ make
gcc  -o bin/obj_write_test obj_write_test.c -lpmemobj -lpmem
gcc  -o bin/obj_read_test obj_read_test.c -lpmemobj -lpmem
zzh@DESKTOP-9OSBLA6:~/Code/github/pmdk/mytest/pmemobj$ make test
rm -f ./pmem-fs/*
请输入您的对象(< 10 bytes):
1234567890
读取对象的结果为:
123456789
zzh@DESKTOP-9OSBLA6:~/Code/github/pmdk/mytest/pmemobj$
```
