#include <iostream>
#include <chrono>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/protocol/TJSONProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include "Poco/Random.h"

#include "userProfileService.h"
using namespace std;
using Poco::Random;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

void* threadFunc(void *param) {
    std::shared_ptr<TTransport> socket(new TSocket("localhost", 9090));
    //std::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    std::shared_ptr<TTransport> transport(new TFramedTransport(socket));
    std::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    userProfileServiceClient client(protocol);

    try {
        transport->open();
        Random rnd;
        rnd.seed();
        chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        userProfile profile("Client2","Nu",1,1,1992);
        for (int i = 0; i < 10000; i++) {
            userProfileResult ret;
            client.Get(ret,150000 + rnd.next(150));
        }
        chrono::steady_clock::time_point end = chrono::steady_clock::now();
        cout << "Time difference = " << chrono::duration_cast< chrono::microseconds>(end - begin).count() / 1000000.0 << endl;
        transport->close();
    } catch (TException& tx) {
        cout << "ERROR: " << tx.what() << endl;
    }
}

int main(int argc, char** argv) {
    int SO_THREAD = atoi(argv[1]);
    pthread_t threads[SO_THREAD];
    int rc;
    int i;
    for (i = 0; i < SO_THREAD; i++) {

        rc = pthread_create(&threads[i], NULL, threadFunc, NULL);
        if (rc) {
            exit(-1);
        }
    }
    pthread_exit(NULL);
}
