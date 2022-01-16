#include <iostream>

#include "async.h"

#include <thread>
#include <chrono>

namespace async {

using handle_t = void *;

handle_t connect(std::size_t bulk);
void receive(handle_t handle, const char *data, std::size_t size);
void disconnect(handle_t handle);

}


int main(int, char *[]) {
    std::size_t bulk = 5;
    auto h = async::connect(bulk);
    auto h2 = async::connect(bulk);
        
    async::receive(h, "1", 1);

    async::receive(h2, "cmd1\n", 5);
    async::receive(h2, "cmd2\n", 5);
    
    async::receive(h, "\n2\n3\n4\n5\n6\n{\na\n", 15);
    async::receive(h, "b\nc\nd\n}\n89\n", 11);

    async::receive(h2, "cmd3\n", 5);
    async::receive(h2, "cmd4\n", 5);
    async::receive(h2, "cmd5\n", 5);

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(3000ms);
    async::disconnect(h);
    async::disconnect(h2);

    return 0;
}
