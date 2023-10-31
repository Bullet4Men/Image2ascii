#include "argument-parser.h"

void ArgumentParser::parseArguments(int argc, char **argv) {
    for (size_t i = 1; i < argc; ++i) {
        if (argv[i][0] == '-') {
            arguments[argv[i]] = "";
        } else if (i == 1 && argv[i][0] != '-') {
            throw std::invalid_argument("Value must have argument");
        } else {
            arguments[argv[i - 1]] = argv[i];
        }
    }
}

bool ArgumentParser::hasArgument(const std::string& key) {
    return arguments.count(key) > 0;
}

bool ArgumentParser::hasArgumentValue(const std::string &key) {
    return !arguments[key].empty();
}

std::string ArgumentParser::getValue(const std::string &key) {
    return arguments[key];
}

bool ArgumentParser::hasAnyArgument(const std::string &shortArg, const std::string &longArg) {
    return hasArgument(shortArg) || hasArgument(longArg);
}

std::string
ArgumentParser::returnValue(const std::string &shortArg, const std::string &longArg) {
    if ((hasArgument(shortArg) && !hasArgumentValue(shortArg))
         || (hasArgument(longArg) && !hasArgumentValue(longArg))) {
        std::string error_message = "Missing value for argument " + shortArg + " or " + longArg;
        throw std::invalid_argument(error_message);
    }

    if (hasArgument(shortArg) || hasArgumentValue(shortArg)) {
        return getValue(shortArg);
    }
    else if (hasArgument(longArg) || hasArgumentValue(longArg)) {
        return getValue(longArg);
    }

    return "";
}
