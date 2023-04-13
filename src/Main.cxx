#include <cstdlib>
#include <mutex>
#include <thread>
#include <vector>

static std::vector< std::jthread > threads;
static std::mutex                  mtx;

void emit ( const char* command )
{
    threads.emplace_back (
        [ command ]
        {
            // Fix:
            std::scoped_lock lock { mtx };

            std::system ( command );
        }
    );
}

int main ()
{
    emit ( "echo a" );
    emit ( "echo b" );
    emit ( "echo c" );

    return 0;
}

// 1. cmake -S . -B build
// 2. cd build && cmake --build .
// 3. echo "exit" | lldb -o "settings set target.process.stop-on-exec false" -o "pro hand -p false -s false -n true
// SIGCHLD" -o run -o bt -o "exit 1" ./test

// Typical Response:
/*
a
c
b
Process 86200 stopped and restarted: thread 1 received signal: SIGCHLD
Process 86200 stopped and restarted: thread 1 received signal: SIGCHLD
Process 86200 stopped and restarted: thread 1 received signal: SIGCHLD
Process 86200 exited with status = 0 (0x00000000)
*/

// Failed Response, Without Mutex:
/*
a
Process 86473 exited with status = -1 (0xffffffff) lost connection
Process 86473 launched: '/home/eshnek/work/lldb-with-std-system/build/test' (x86_64)
*/
