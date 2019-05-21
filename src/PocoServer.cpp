#include "Poco/Exception.h"
#include "Poco/ThreadPool.h"
#include "Poco/LRUCache.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "LruCache.h"
#include "Poco/Task.h"
#include "Poco/TaskManager.h"
#include "userProfileService.h"
#include "userProfileHandler.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/protocol/TJSONProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/server/TThreadPoolServer.h>
#include <thrift/server/TNonblockingServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TNonblockingServerSocket.h>
#include <thrift/concurrency/PosixThreadFactory.h>
#include <thrift/transport/TBufferTransports.h>
#include <iostream>
#include <mutex>
#include <vector>
#include <kchashdb.h>
#include <unistd.h>

using Poco::Util::ServerApplication;
using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::OptionCallback;
using Poco::Util::HelpFormatter;

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;



class userProfileTask : public Poco::Task {
public:
    int _serverRequested;

    userProfileTask(int sr) : Task("userProfileTask"), _serverRequested(sr) {
    }

    void runTask() {
        int port = 9090;
        ::apache::thrift::stdcxx::shared_ptr<userProfileServiceHandler> handler(new userProfileServiceHandler());
        ::apache::thrift::stdcxx::shared_ptr<TProcessor> processor(new userProfileServiceProcessor(handler));
        ::apache::thrift::stdcxx::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
        ::apache::thrift::stdcxx::shared_ptr<TTransportFactory> transportFactory(new TFramedTransportFactory());
        ::apache::thrift::stdcxx::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

        int choose = _serverRequested;

        if (choose == 0) {
            printf("start SimpleServer\n");
            TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
            server.serve();
        } else if (choose == 1) {
            printf("start ThreadedServer\n");
            ::apache::thrift::stdcxx::shared_ptr<::apache::thrift::concurrency::PosixThreadFactory> threadFactory =
                    ::apache::thrift::stdcxx::shared_ptr<::apache::thrift::concurrency::PosixThreadFactory>(new ::apache::thrift::concurrency::PosixThreadFactory());
            TThreadedServer server(processor, serverTransport, transportFactory, protocolFactory, threadFactory);
            server.serve();
        } else if (choose == 2) {
            printf("start ThreadPoolServer\n");
            ::apache::thrift::stdcxx::shared_ptr<ThreadManager> threadManager = ThreadManager::newSimpleThreadManager(8);
            ::apache::thrift::stdcxx::shared_ptr<::apache::thrift::concurrency::PosixThreadFactory> threadFactory =
                    ::apache::thrift::stdcxx::shared_ptr<::apache::thrift::concurrency::PosixThreadFactory>(new ::apache::thrift::concurrency::PosixThreadFactory());
            threadManager->threadFactory(threadFactory);
            threadManager->start();
            TThreadPoolServer server(processor, serverTransport, transportFactory, protocolFactory, threadManager);
            server.serve();
        } else if (choose == 3) {
            printf("start NonBlockingServer\n");
            ::apache::thrift::stdcxx::shared_ptr<TNonblockingServerTransport> nonblockserverTransport(new TNonblockingServerSocket(port));
            ::apache::thrift::stdcxx::shared_ptr<ThreadManager> threadManager = ThreadManager::newSimpleThreadManager(2);
            ::apache::thrift::stdcxx::shared_ptr<::apache::thrift::concurrency::PosixThreadFactory> threadFactory =
                    ::apache::thrift::stdcxx::shared_ptr<::apache::thrift::concurrency::PosixThreadFactory>(new ::apache::thrift::concurrency::PosixThreadFactory());
            threadManager->threadFactory(threadFactory);
            threadManager->start();
            TNonblockingServer server(processor, protocolFactory, nonblockserverTransport, threadManager);
            server.setNumIOThreads(2);
            server.serve();
        }
    }
};

class userProfileServer : public Poco::Util::ServerApplication {
public:

    userProfileServer() : _helpRequested(false), _serverRequested(0) {
    }

    ~userProfileServer() {
    }

protected:

    void initialize(Application& self) {
        loadConfiguration();
        ServerApplication::initialize(self);
    }

    void uninitialize() {
        ServerApplication::uninitialize();
    }

    void defineOptions(OptionSet& options) {
        ServerApplication::defineOptions(options);

        options.addOption(
                Option("help", "h", "display argument help information")
                .required(false)
                .repeatable(false)
                .callback(OptionCallback<userProfileServer>(
                this, &userProfileServer::handleHelp)));
        options.addOption(
                Option("start", "s", "choose type of server you want to start\nvaule=0: SimpleServer(default),\nvaule=1: ThreadedServer,\nvaule=2: ThreadPoolServer,\nvaule=3: NonBlockingServer")
                .required(false)
                .repeatable(false)
                .argument("vaule")
                .callback(OptionCallback<userProfileServer>(
                this, &userProfileServer::handleServer)));
    }

    void handleHelp(const std::string& name,
            const std::string& value) {
        HelpFormatter helpFormatter(options());
        helpFormatter.setCommand(commandName());
        helpFormatter.setUsage("OPTIONS");
        helpFormatter.setHeader(
                "UserProfile Manager Server");

        helpFormatter.format(std::cout);
        stopOptionsProcessing();
        _helpRequested = true;
    }

    void handleServer(const std::string& name,
            const std::string& value) {
        _serverRequested = atoi(value.c_str());
        if (_serverRequested < 0 or _serverRequested > 3){
            _serverRequested = 0;
        }
    }

    int main(const std::vector<std::string>& args) {
        if (!_helpRequested) {
            Poco::TaskManager tm;
            tm.start(new userProfileTask(_serverRequested));
            waitForTerminationRequest();
            tm.cancelAll();
            tm.joinAll();
        }
        return Application::EXIT_OK;
    }

private:
    bool _helpRequested;
    int _serverRequested;
};

POCO_SERVER_MAIN(userProfileServer)