# Dish

[![](https://img.shields.io/github/last-commit/Eveneko/Dish)](https://github.com/Eveneko/Dish/commits/master)
[![License](https://img.shields.io/github/license/Eveneko/Dish)](https://github.com/Eveneko/Dish/blob/master/LICENSE)

A Simple Bash-Like Shell

```
 ____                   __         
/\  _`\    __          /\ \        
\ \ \/\ \ /\_\     ____\ \ \___    
 \ \ \ \ \\/\ \   /',__\\ \  _ `\  
  \ \ \_\ \\ \ \ /\__, `\\ \ \ \ \ 
   \ \____/ \ \_\\/\____/ \ \_\ \_\
    \/___/   \/_/ \/___/   \/_/\/_/
                                                                                                                
```

## Why Dish?

Life is hard, so is the name.

## Structure

```
.
├── LICENSE
├── Makefile
├── README.md
├── Q&A.md
├── dish
├── his.txt
├── reference
│   ├── CS190\ Project\ 3\ \ Clash.pdf
│   └── CS302-OS-Proj2.pdf
└── src
    ├── Reader.cc
    ├── Reader.h
    ├── SpecialInput
    │   ├── BackSpace.cc
    │   ├── BackSpace.h
    │   ├── Down.cc
    │   ├── Down.h
    │   ├── KeyboardOperation.h
    │   ├── Left.cc
    │   ├── Left.h
    │   ├── Right.cc
    │   ├── Right.h
    │   ├── SpecialInput.h
    │   ├── Up.cc
    │   └── Up.h
    ├── arguments.cc
    ├── arguments.h
    ├── command.cc
    ├── command.h
    ├── dish.cc
    ├── dish.h
    ├── environment.cc
    ├── environment.h
    ├── file-util.cc
    ├── file-util.h
    ├── history.cc
    ├── history.h
    ├── job-parser.cc
    ├── job-parser.h
    ├── job.cc
    ├── job.h
    ├── log.h
    ├── pipeline.cc
    ├── pipeline.h
    ├── proc-util.cc
    ├── proc-util.h
    ├── shell.cc
    ├── shell.h
    ├── string-util.cc
    └── string-util.h
```

## Functions

- Base shell
- Enhanced shell
  - History
  - Code completion
  - Keyboard Operations
  - Display
  - Other Commands
    - cd
    - pwd
    - exit
    - printenv
    - set
    - unset
    - export
    - which

## Environment

- Ubuntu 18.04.1 LTS
- gcc version 7.4.0

## Build

```
git clone https://github.com/Eveneko/Dish.git --depth 1
```

## Reference

- [CS 190: Software Design Studio (Winter 2021)](https://web.stanford.edu/~ouster/cgi-bin/cs190-winter21/clash.php)
- [Tutorial - Write a Shell in C](https://brennan.io/2015/01/16/write-a-shell-in-c/)
- [Clash](https://github.com/feross/clash)
- [键入多个命令、输入和输出重定向](https://github.com/kyuhas/enhanced-linux-shell)
- [历史记录](https://github.com/curusarn/resh)
- [添加github功能](https://github.com/vergissberlin/bashlight)
