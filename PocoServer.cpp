#include "Poco/Exception.h"
#include "Poco/ThreadPool.h"
#include "Poco/LRUCache.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/LRUCache.h"
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
    Poco::LRUCache<int, userProfile> users;
    
    kyotocabinet::HashDB db;

    userProfileServiceHandler() :users(300){
        if (!db.open("userProfiles.kch", kyotocabinet::HashDB::OWRITER | kyotocabinet::HashDB::OCREATE)) {
            std::cout << "open database error: " << db.error().name() << std::endl;
        }

        std::string s;

        if (!db.get("0", &s)) {
            newID = 1;
            if(!db.set("0","1")){
                std::cout << db.error().name() << std::endl;
            }
        }else{
            newID = atoi(s.c_str());
        };
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
        std::cout<< "add new to Cache" << std::endl;
        users.add(newProfile.id,newProfile);
        mutexUpdate.unlock();
        
        _return.errorCode = setDB(newProfile.id,newProfile);
        _return.profile = newProfile;
        printf("Create\n");
    }

    void Get(userProfileResult& _return, const int32_t id) {
        mutexUpdate.lock();
        Poco::SharedPtr<userProfile> profile = users.get(id);
        mutexUpdate.unlock();
        if(profile.isNull()){
            _return.errorCode = getDB(id,_return.profile);
            if (_return.errorCode == 0){
                std::cout<< "add new to Cache" << std::endl;
                mutexUpdate.lock();
                users.add(id,_return.profile);
                mutexUpdate.unlock();
            }
        }else{
            std::cout<< "get from Cache" << std::endl;
            _return.errorCode = 0;
            _return.profile = *profile.get();
            _return.profile.id = id;
        }
        printf("Get\n");
    }

    int32_t Update(const int32_t id, const userProfile& newProfile) {
        if (!isContainDB(id)) {
            return 1;
        }
        
        mutexUpdate.lock();
        users.update(id,newProfile);
        mutexUpdate.unlock();
        
        printf("Update\n");
        return setDB(id,newProfile);
    }

    int32_t Delete(const int32_t id) {
        
        mutexUpdate.lock();
        users.remove(id);
        mutexUpdate.unlock();
        
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
        std::string vaule = serializeProfile(profile);
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
        deserilizeProfile(vaule,profile);
        profile.id = id;
        return 0;
    }

    int removeDB(int id) {
        if (id == 0) return 0;
        db.remove(std::to_string(id));
        return 0;
    }
    
    //https://stackoverflow.com/questions/19672155/apache-thrift-serialization-in-c
    std::string serializeProfile(userProfile obj) {
        std::shared_ptr<TMemoryBuffer> transportOut(new TMemoryBuffer());
        std::shared_ptr<TBinaryProtocol> protocolOut(new TBinaryProtocol(transportOut));
        obj.write(protocolOut.get());
        std::string serialized_string = transportOut->getBufferAsString();
        return serialized_string;
    }
    void deserilizeProfile(std::string serializeString , userProfile &profile){
        std::shared_ptr<TMemoryBuffer> transportIn(new TMemoryBuffer());
        std::shared_ptr<TBinaryProtocol> protocolIn(new TBinaryProtocol(transportIn));
        transportIn.get()->write((uint8_t*)serializeString.c_str(),serializeString.length());
        profile.read(protocolIn.get());
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