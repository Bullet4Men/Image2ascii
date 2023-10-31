#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

class ArgumentParser {
public:
    ArgumentParser(const ArgumentParser&) = delete;
    ArgumentParser& operator=(const ArgumentParser&) = delete;

    static ArgumentParser& getInstance() {
        static ArgumentParser instance;
        return instance;
    }

    void parseArguments(int argc, char** argv);
    bool hasArgument(const std::string& key);
    bool hasArgumentValue(const std::string& key);
    std::string getValue(const std::string& key);

    bool hasAnyArgument(const std::string& shortArg, const std::string& longArg);
    std::string returnValue(const std::string& shortArg, const std::string& longArg);

private:
    ArgumentParser() {}
    std::unordered_map<std::string, std::string> arguments;
};
