/**
 * Parser job functions.
 */

#pragma once

#include "string-util.h"
#include "environment.h"
#include "proc-util.h"

using namespace std;

/**
 * Set of structs containing the information necessary to spawn a job
 */

/**
 * Parsed Command describes where a command,
 * and whether it shoudl redirect input or output,
 * potentially including stderr
 */
struct ParsedCommand {
    ParsedCommand() : redirect_stderr(false) {}
    vector<string> words;
    string input_file;
    string output_file;
    bool redirect_stderr;
    void clear() {
        words.clear();
        input_file.clear();
        output_file.clear();
    };
};


class JobParser {
    public:

    private:
};

class IncompleteParseException : public exception {
    public:
        IncompleteParseException() {}
        IncompleteParseException(const string& message, char ch): message(message), problem_char(ch) {}
        IncompleteParseException(const char* message): message(message) {}
        const char* what() const noexcept { return message.c_str(); }
        char unmatched_char() const noexcept { return problem_char; }        
    private:
        string message;
        char problem_char;
};

class FatalParseException : public exception {
    public:
        FatalParseException() {}
        FatalParseException(const string& message): message(message) {}
        FatalParseException(const char* message): message(message) {}
        const char* what() const noexcept { return message.c_str(); }
    private:
        string message;
};

class SyntaxErrorParseException : public FatalParseException {
    public:
        SyntaxErrorParseException(const string& message): message(message) {}
        SyntaxErrorParseException(const char* message): message(message) {}
        SyntaxErrorParseException(const char ch) {
            message = ("syntax error near unexpected token \'" + string(1, ch) + "\'").c_str();
        }
        const char* what() const noexcept { return message.c_str(); }
    private:
        string message;
};