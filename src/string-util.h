/**
 * String utility functions
 */

#pragma once

#include <algorithm>

#include <stdio.h>
#include <cstring>
#include <iostream>
#include <vector>
#include <string>
#include "log.h"

using namespace std;

class StringUtil {
    public:
        /**
         * Split the given string with the given single-character delimiter delim.
         * 
         * @param str The string to split
         * @param delim The delimiter to search
         * @return Vector of the split strings
         */ 
        static vector<string> Split(const string &str, const string &delim);
        static vector<string> Split(const char * str, const string &delim);

        /**
         * Return a new string with space to right of the the given string.
         * 
         * @param str The string to pad
         * @param size The size to ensure the new string
         * @return The result string
         */
        static string PadRight(string const& str, size_t size);

        /**
         * Return a new string with space to letf of the the given string.
         * 
         * @param str The string to pad
         * @param size The size to ensure the new string
         * @return The result string
         */
        static string PadLeft(string const& str, size_t size);

        /**
         * Return a new string with whitespace trimmed from the given string.
         *
         * @param str String to trim
         * @return The result string
         */
        static string Trim(std::string &str);

        /**
         * Return a new string with whitespace trimmed from the given string only left.
         *
         * @param str String to trim only left
         * @return The result string
         */
        static string TrimLeft(string &str);

        /**
         * Return a new string with whitespace trimmed from the given string only right.
         *
         * @param str String to trim only right
         * @return The result string
         */
        static string TrimRight(string &str);
};