/**
 * The entry point into the Dish program.
 */

#pragma once

#include <string>
#include <vector>

#include "arguments.h"
#include "log.h"
#include "shell.h"

using namespace std;

LogType LOG_LEVEL = INFO;

static const string INTRO_TEXT =
R"(Dish - A Simple Bash-Like Shell

 ____                   __         
/\  _`\    __          /\ \        
\ \ \/\ \ /\_\     ____\ \ \___    
 \ \ \ \ \\/\ \   /',__\\ \  _ `\  
  \ \ \_\ \\ \ \ /\__, `\\ \ \ \ \ 
   \ \____/ \ \_\\/\____/ \ \_\ \_\
    \/___/   \/_/ \/___/   \/_/\/_/

SUSTech CS302 Operating System Project.
)";