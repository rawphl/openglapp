#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <fstream>

#include "Assets.h"

namespace OpenGLApp {
    std::string Assets::readFile(const std::string path) {
        std::ifstream fd(path);
        auto src = std::string(std::istreambuf_iterator<char>(fd), (std::istreambuf_iterator<char>()));
        return src;
    }

    std::tuple<std::string, std::string> Assets::shaderNameToFilePaths(const std::string name) {
        std::ostringstream vss;
        vss << ASSETS_PATH << "/shaders/" << name << ".vert.glsl";
        std::ostringstream fss;
        fss << ASSETS_PATH << "/shaders/" << name << ".frag.glsl";
        return std::make_tuple(vss.str(), fss.str());
    }
}
