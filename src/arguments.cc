#include "arguments.h"

string named_prefix = "--";
string alias_prefix = "-";


void Arguments::RegisterBool(const string name, const string descrition) {
    bool_args[name] = false;
    descriptions[name] = descrition;
}

void Arguments::RegisterInt(const string name, const string descrition) {
    int_args[name] = -1;
    descriptions[name] = descrition;
}

void Arguments::RegisterString(const string name, const string descrition) {
    string_args[name] = "";
    descriptions[name] = descrition;
}

void Arguments::RegisterAlias(const char alias, const string name) {
    alias2name[string(1, alias)] = name;
    name2alias[name] = alias;
}

void Arguments::Parse(int argc, char* argv[]) {
    vector<string> arguments(argv + 1, argv + argc);
    for (int i = 0; i < arguments.size(); i++) {
        string arg = arguments[i];
        string name;

        if (arg.substr(0, named_prefix.size()) == named_prefix) {
            name = arg.substr(named_prefix.size());
        }else if (arg.substr(0, alias_prefix.size()) == alias_prefix) {
            string alias = arg.substr(alias_prefix.size());
            if (alias2name.count(alias)) {
                name = alias2name[alias];
            } else {
                throw ArgumentsException(arg + " option was unexpected");
            }
        }

        if (!name.empty()) {
            if (bool_args.count(name)) {
                bool_args[name] = true;
            } else if (int_args.count(name) || string_args.count(name)) {
                // determine the argument value
                i += 1;
                if (i >= arguments.size()) {
                    throw ArgumentsException(arg + " option requires an argument");
                }
                string value = arguments[i];
                if (int_args.count(name)) {
                    int_args[name] = stoi(value);
                } else if (string_args.count(name)) {
                    string_args[name] = value;
                }
            } else {
                throw ArgumentsException(arg + " option was unexpected");
            }
        }  else {
            unnamed_args.push_back(arg);
        }
    }
}

bool Arguments::GetBool(const string name) {
    if (!bool_args.count(name)) {
        throw ArgumentsException("Missing argument " + name);
    }
    return bool_args[name];
}

int Arguments::GetInt(const string name) {
    if (!int_args.count(name)) {
        throw ArgumentsException("Missing argument " + name);
    }
    return int_args[name];
}

const string& Arguments::GetString(const string name) {
    if (!string_args.count(name)) {
        throw ArgumentsException("Missing argument " + name);
    }
    return string_args[name];
}

const vector<string>& Arguments::GetUnnamed() {
    return unnamed_args;
}

string Arguments::GetHelpText() {
    string result;

    if (intro.size()) {
        result = intro + "\n";
    }

    result += "Usage:";

    unsigned long max_name_len = 0;
    unsigned long max_description_len = 0;
    for (auto const& kv : descriptions) {
        auto const& name = kv.first;
        auto const& description = kv.second;
        max_name_len = max(max_name_len, name.size());
        max_description_len = max(max_description_len, description.size());
    }

    for (auto const& kv : descriptions) {
        auto const& name = kv.first;
        auto const& description = kv.second;
        string type;
        if (bool_args.count(name)) {
            type = "bool";
        }else if (int_args.count(name)) {
            type = "int";
        }else if (string_args.count(name)) {
            type = "string";
        }else {
            type = "undefine";
        }

        string alias;
        if (name2alias.count(name)) {
            alias = alias_prefix + name2alias[name];
        }

        result += "\n\t";
        result += StringUtil::PadRight(alias, alias.size() + 1);
        result += named_prefix + StringUtil::PadRight(name, max_name_len) + "  ";
        result += StringUtil::PadRight(description, max_description_len);
        result += " [" + type + "]";
    }
    return result;
}