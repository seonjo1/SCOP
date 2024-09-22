#ifndef GLLOAD_H
# define GLLOAD_H

# include <cstdint>
# include <iostream>
# include <fstream>
# include <sstream>
# include <memory>
# include <optional>
# include <algorithm>
# include <vector>
# include <cmath>

namespace glload {

bool isBmpFile(std::string fileName);
std::unique_ptr<uint8_t[]> loadBmpImg(const char* fileName, int* width, int* height, int* channelCount);
std::optional<std::string> loadShaderFile(const std::string& fileName);


}

#endif