#include "infra.h"

#include <util/util.h>
#include <boost/filesystem.hpp>

namespace infra {
    std::string getFunctionStubDir() {
        std::string projRoot = util::getEnvVar("FUNC_ROOT", "/usr/local/code/faasm");
        std::string dirStr = projRoot + "/wasm/stubs";

        boost::filesystem::create_directories(dirStr);

        return dirStr;
    }

    std::string getFunctionDir(const message::FunctionCall &call) {
        std::string projRoot = util::getEnvVar("FUNC_ROOT", "/usr/local/code/faasm");
        std::string dirStr = projRoot + "/wasm/" + call.user() + "/" + call.function();

        // Create directory if doesn't exist
        boost::filesystem::create_directories(dirStr);

        return dirStr;
    }

    std::string getFunctionFile(const message::FunctionCall &call) {
        std::string dirPath = getFunctionDir(call);
        std::string filePath = dirPath + "/function.wasm";

        return filePath;
    }

    std::string getFunctionObjectFile(const message::FunctionCall &call) {
        std::string dirPath = getFunctionDir(call);
        std::string filePath = dirPath + "/function.o";

        return filePath;
    }

    std::vector<uint8_t> getFunctionObjectBytes(const message::FunctionCall &call) {
        std::string objectFilePath = getFunctionObjectFile(call);
        std::vector<uint8_t> bytes = util::readFileToBytes(objectFilePath);
        return bytes;
    }

    std::vector<uint8_t> callToBytes(const message::FunctionCall &call) {
        size_t byteSize = call.ByteSizeLong();
        uint8_t buffer[byteSize];
        call.SerializeToArray(buffer, (int) byteSize);

        std::vector<uint8_t> inputData(buffer, buffer + byteSize);

        return inputData;
    }
}
