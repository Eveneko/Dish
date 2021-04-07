/**
 * Friendly interface for parsing a command line argument string
 * into a useful struture.
 */

#pragma once

#include <algorithm>
#include <exception>
#include <map>
#include <string>
#include <vector>

#include "string-util.h"

using namespace std;

class Arguments {
    public:
        /**
         * Construct a command line argument parser
         * 
         * @param intro Help text to describe the function of the program
         */
        Arguments(string intro) : intro(intro) {};

        /**
         * Register a boolean command line argument with the given name and description.
         * Defaultss to false.
         * 
         * @param name The full name.
         * @param description Friendly description of the argument's function.
         */
        void RegisterBool(const string name, const string description);

        /**
         * Register a int command line argument with the given name and description.
         * Defaultss to -1.
         * 
         * @param name The full name.
         * @param description Friendly description of the argument's function.
         */
        void RegisterInt(const string name, const string description);

        /**
         * Register a string command line argument with the given name and description.
         * Defaultss to "".
         * 
         * @param name The full name.
         * @param description Friendly description of the argument's function.
         */
        void RegisterString(const string name, const string description);

        /**
         * Register a one character command alias with the given name.
         * 
         * @param alias One charactor.
         * @param name The full name. 
         */
        void RegisterAlias(const char alias, const string name);
        
        /**
         * Parse the user-provided command line argument string.
         * 
         * @param argc Number of command line arguments
         * @param argv Array of command line argument strings
         */
        void Parse(int argc, char* argv[]);

        /**
         * Return the value of the boolean arguments with the given name.
         * 
         * @throw ArgumentsException
         * 
         * @param name Argument name
         * @return Argument value
         */
        bool GetBool(const string name);

        /**
         * Return the value of the int arguments with the given name.
         * 
         * @throw ArgumentsException
         * 
         * @param name Argument name
         * @return Argument value
         */
        int GetInt(const string name);

        /**
         * Return the value of the string arguments with the given name.
         * 
         * @throw ArgumentsException
         * 
         * @param name Argument name
         * @return Argument value
         */
        const string& GetString(const string name);

        /**
         * Return a vector of the unnamed arguments
         * included in the command line argument string.
         * 
         * Example:
         *  "./program --pool --int 42 unnamed1 unnamed2"
         * 
         * @return Vector of unnamed argument strings
         */
        const vector<string>& GetUnnamed();

        /**
         * Returns the program's help text.
         * argument names, descriptions, and types.
         *
         * @return string of command line help text
         */
        string GetHelpText();

    private:
        /**
         * Text to describe the purpose of the program.
         * Used to generate the --help text.
         */
        string intro;
        
        /**
         * Argument descriptions.
         */
        map<string, string> descriptions;

        /**
         * Argument value map.
         * bool, int, string
         */
        map<string, bool> bool_args;
        map<string, int> int_args;
        map<string, string> string_args;

        /**
         * Map alias and name.
         * -h, --help
         */
        map<string, string> alias2name;
        map<string, string> name2alias;

        /**
         * Vector of the unnamed arguments
         * included in the command line argument string.
         */
        vector<string> unnamed_args;
};

class ArgumentsException : public exception {
    public:
        ArgumentsException(const string& message): message(message) {}
        ArgumentsException(const char* message): message(message) {}
        const char* what() const noexcept {
            return message.c_str();
        }

    private:
        string message;
};