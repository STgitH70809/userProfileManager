#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Timestamp.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/Exception.h"
#include "Poco/ThreadPool.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "userProfileService.h"
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

class userProfileServiceHandler : virtual public userProfileServiceIf {
public:
    int newID;
    std::mutex mutexUpdate;
    //std::map<int, userProfile> users;
    kyotocabinet::HashDB db;

    userProfileServiceHandler() {
        if (!db.open("userProfiles.kch", kyotocabinet::HashDB::OWRITER | kyotocabinet::HashDB::OCREATE)) {
            std::cout << "open database error: " << db.error().name() << std::endl;
        }

        std::string s;

        if (!db.get("0", &s)) {
            std::cout << db.error().name() << std::endl;
        };

        newID = atoi(s.c_str());
        std::cout << "nextID will be: " << newID << std::endl;
    }

    ~userProfileServiceHandler() {
        if (!db.close()) {
            std::cout << "close database error: " << db.error().name() << std::endl;
        }
    }

    void Create(userProfileResult& _return, const userProfile& profile) {

        userProfile newProfile(profile);
        mutexUpdate.lock();
        newProfile.id = newID++;
        if(!db.set("0",std::to_string(newID))){
            std::cout<< "error update key : " << db.error().name() << std::endl;
        }
        
        mutexUpdate.unlock();
        
        _return.profile = newProfile;
        _return.errorCode = setDB(newProfile.id,newProfile);
        printf("Create\n");
    }

    void Get(userProfileResult& _return, const int32_t id) {
        
        _return.errorCode = getDB(id,_return.profile);
        printf("Get\n");
    }

    int32_t Update(const int32_t id, const userProfile& newProfile) {
        if (!isContainDB(id)) {
            return 1;
        }
        
        
        printf("Update\n");
        return setDB(id,newProfile);
    }

    int32_t Delete(const int32_t id) {
        
        printf("Delete\n");
        return removeDB(id);
    }

    bool isContainDB(int id) {
        if (id == 0) return false;
        std::string s;
        if (!db.get(std::to_string(id), &s)) {
            return false;
        };
        return true;
    }

    int setDB(int id, userProfile profile) {
        if (id == 0) return 1;
        std::string vaule = profile.name + "\t" + (profile.gender?"1":"0") + "\t" + std::to_string(profile.birth);
        if(!db.set(std::to_string(id),vaule)){
            return 2;
        }
        return 0;
    }

    int getDB(int id, userProfile &profile) {
        if(id == 0) return 1;
        std::string vaule;
        if (!db.get(std::to_string(id), &vaule)) {
            return 1;
        };
        int date , gen;
        char name[50];
        sscanf(vaule.c_str(),"%s\t%d\t%d",name,&gen,&date);
        profile.id = id;
        profile.birth = date;
        profile.name = name;
        profile.gender = ((gen == 1) ? true : false);
        return 0;
    }

    int removeDB(int id) {
        if (id == 0) return 0;
        db.remove(std::to_string(id));
        return 0;
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
    }

    int main(const std::vector<std::string>& args) {
        if (!_helpRequested) {
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
        return Application::EXIT_OK;
    }

private:
    bool _helpRequested;
    int _serverRequested;
};

int main(int argc, char** argv) {
    userProfileServer app;
    return app.run(argc, argv);
}