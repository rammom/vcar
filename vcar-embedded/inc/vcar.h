#ifndef VCAR_H
#define VCAR_H

#include <pthread.h>
#include <cstdlib>
#include <ctime>
#include <future>
#include <list>
#include <mutex>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

extern "C" {
    #include <linux/can.h>
    #include <linux/can/raw.h>

    #include <lib.h>
}

#define VCAR_NAME "vcar"

class vcar {
    bool running = true;

    int sock;
    struct ifreq ifr {};
    struct sockaddr_can addr {};
    struct canfd_frame frame {};
    int enable_canfd = 1;
    int required_mtu;

    std::mutex incoming_connections_mutex;
    std::list<std::future<int> > incoming_connections;

    std::future<void> vcar_future;

    void start();

public:
    vcar();

    // Disable copying
    vcar(vcar const&) = delete;
    vcar& operator=(vcar const&) = delete;

    // Default move
    vcar(vcar &&) = default;
    vcar& operator=(vcar &&) = default;

    int sendCanFrame(char* sFrame);
    int recvCanFrame();
};

#endif
