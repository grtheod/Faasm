#include <catch/catch.hpp>
#include <worker/worker.h>
#include <proto/faasm.pb.h>

namespace tests {

    TEST_CASE("Test executing simple WASM module", "[worker]") {
        // Note, we require this function to be present
        message::FunctionCall call;
        call.set_user("simon");
        call.set_function("dummy");

        worker::WasmModule module;
        int returnValue = module.execute(call);

        REQUIRE(0 == returnValue);
    }
}
