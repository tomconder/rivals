#pragma once

#include <string>

class LinuxFile {
   public:
    static std::string getLogDir(const std::string& app);
};
