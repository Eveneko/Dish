# Record

<!-- TOC -->

- [Record](#record)
  - [Problem](#problem)
    - [Server & Environment](#server--environment)
    - [Makefile](#makefile)
    - [Code](#code)
      - [`file-util`](#file-util)
      - [`environment`](#environment)

<!-- /TOC -->

## Problem

### Server & Environment

> 登陆服务器

```
chmod 400 ./auth/guest.pem
ssh ubuntu@bj.tencent.eveneko.com -i ./auth/guest.pem
```

> 权限问题

```
sudo su root
```

> make dish: `error: readline/readline.h: No such file or directory`

```
apt-get install libreadline-dev
```

### Makefile

> Makefile `?=` 是什么意思

`?=` 是如果没有被赋值过就赋予等号后面的值

> 可不可以用g++，不用clang

不行，以下两条是有区别的，具体原因不太了解，反正知道clang可以就行。
```
g++ File.c -o File 
g++ File.c -o File -lreadline
```

### Code

> 顺序

```
-> log
-> string-util(log)
-> arguments(string-util)
-> file-util(log, string-util)
-> environment(string-util, file-util)
-> process_util
-> job-parser(string-util, environment, proc-util)
-> command(envrionment, job-parser, file-util, log, proc-util)
-> pipeline(command, file-util, log)
-> job(environment, job-parser, log, pipeline, command),
```

#### `file-util`

> `#ifdef _GNU_SOURCE`

打开_GNU_SOURCE这个宏可以打开一些功能，比如为了在Linux系统上编译使用带有检测文件type的宏（S_ISxxxx）

> `fcntl`

fcntl()针对(文件)描述符提供控制，通过fcntl可以改变已打开的文件性质。

> `access`

test execution permission

> `stat`

stat函数用来获取指定路径的文件或者文件夹的信息。

> `isalnum`

检查所传的字符是否是字母和数字。

> duplicate symbol

`inline` / `static`
 
#### `environment`

> `extern` xxx

extern是一个关键字，它告诉编译器存在着一个变量或者一个函数，如果在当前编译语句的前面中没有找到相应的变量或者函数，也会在当前文件的后面或者其它文件中定义

> `environ`

in `unistd.h`
```
/*default environment variable defined in system-level*/
char **environ;
```

> map中`count`, `find`的区别

使用count，返回的是被查找元素的个数。如果有，返回1；否则，返回0。注意，map中不存在相同元素，所以返回值只能是1或0。

使用find，返回的是被查找元素的位置，没有则返回map.end()。

> `chdir`

cd

> `getcwd`

getcwd()会将当前工作目录的绝对路径复制到参数buffer所指的内存空间中

> `getpwnam`

getpwnam函数功能是获取用户登录相关信息。

