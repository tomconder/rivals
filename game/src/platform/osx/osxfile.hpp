#pragma once

#include <string>

class OSXFile {
   public:
    static std::string getLogDir(const std::string& app);
    static std::string getResourceDir();

   private:
    static std::string expandTilde(const char* str);
};
