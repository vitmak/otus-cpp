#include "async.h"

#include "AsyncBulkApp.h"


namespace async {

handle_t connect(std::size_t bulk) {
    return new AsyncBulkApp{bulk};
}

void receive(handle_t handle, const char *data, std::size_t size) {
    auto hanlePtr = static_cast<AsyncBulkApp*>(handle);
    if (hanlePtr != nullptr) {
        hanlePtr->ReadBuffer(data, size);
    }
}

void disconnect(handle_t handle) {
    delete handle;
}

}
