#include <catch/catch.hpp>
#include <worker/worker.h>

namespace tests {

    TEST_CASE("Test executing simple WASM module", "[worker]") {
        // Note, we require this function to be present
        message::FunctionCall call;
        call.set_user("simon");
        call.set_function("dummy");

        worker::WasmModule module;
        int returnValue = module.execute(call);

        std::cout << "Ret val: " << returnValue << "\n";

        module.printMemory(returnValue);

        const char *ptr = (char *) &returnValue;

        std::cout << "PTR: " << ptr << "\n";

        std::string strVal(ptr);

        REQUIRE("foobar" == strVal);

        module.clean();
    }
}