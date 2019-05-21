/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   userProfileHandler.h
 * Author: cpu02331
 *
 * Created on May 21, 2019, 3:26 PM
 */

#ifndef USERPROFILEHANDLER_H
#define USERPROFILEHANDLER_H

#include "Poco/Exception.h"
#include "Poco/ThreadPool.h"
#include "LruCache.h"
#include "Poco/Task.h"
#include "Poco/TaskManager.h"
#include "Poco/Notification.h"
#include "Poco/NotificationQueue.h"
#include "userProfileService.h"
#include "Worker.h"
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

using Poco::Notification;
using Poco::NotificationQueue;
using Poco::ThreadPool;
using Poco::Runnable;
using Poco::AutoPtr;

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

class userProfileServiceHandler : virtual public userProfileServiceIf {
public:
    
    userProfileServiceHandler() ;

    ~userProfileServiceHandler() ;

    void Create(userProfileResult& _return, const userProfile& profile) ;

    void Get(userProfileResult& _return, const int32_t id) ;

    int32_t Update(const int32_t id, const userProfile& newProfile) ;

    int32_t Delete(const int32_t id) ;

    int32_t ansyCreate(const userProfile& profile) ;

    int32_t ansyUpdate(const int32_t id, const userProfile& newProfile) ;

    int32_t ansyDelete(const int32_t id) ;

private:
    int newID;
    std::mutex mutexUpdate;
    
    lruCache<int, userProfile> users;
    
    kyotocabinet::HashDB db;
    
    NotificationQueue queue;
    Worker worker1;
    Worker worker2;
    
    bool isContainDB(int id) ;
    
    int setDB(int id, userProfile profile) ;

    int getDB(int id, userProfile &profile) ;

    int removeDB(int id) ;
    
    std::string serializeProfile(userProfile obj) ;
    void deserilizeProfile(std::string serializeString , userProfile &profile);
};

#endif /* USERPROFILEHANDLER_H */

