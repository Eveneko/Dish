#include "proc-util.h"

pid_t ProcUtil::CreateProcess() {
    pid_t pid = fork();
    if (pid == -1) {
        throw ProcException("Unable to create new process");
    }
    return pid;
}

void ProcUtil::SetCurrentWorkingDirectory(const string& new_cwd) {
    if (chdir(new_cwd.c_str()) == -1) {
        throw ProcException(new_cwd + ": No such file or directory");
    }
}

string ProcUtil::GetCurrentWorkingDirectory() {
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        throw ProcException(cwd + string(": No such file or directory"));
    }
    return string(cwd);
}

string ProcUtil::GetUserHomeDirectory(const string& user) {
    passwd * pw = getpwnam(user.c_str());

    if (pw == NULL) {
        return "";
    }

    char * home_dir = pw->pw_dir;
    return string(home_dir);
}

string ProcUtil::GetUserName(){
    uid_t userid;  
    struct passwd * pwd;  
    userid = getuid();  
    pwd = getpwuid(userid);  
    return pwd->pw_name; 
}

string ProcUtil::GetHostName(){
    char name[256] = {0};
    gethostname(name, 256);
    log(DEBUG, "%d", StringUtil::Split(name, ".")[0].length());
    return StringUtil::Split(name, ".")[0];
}