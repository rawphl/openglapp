#pragma once

#include <string>
#include <tuple>

namespace OpenGLApp  {
    class Assets {
    public:
        static std::string readFile(const std::string path);
        static std::tuple<std::string, std::string> shaderNameToFilePaths(const std::string name);
    };
}
