/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "userProfileHandler.h"
#include "Worker.h"

userProfileServiceHandler::userProfileServiceHandler() : users(300), worker1(queue), worker2(queue) {
    worker1.H = this;
    worker2.H = this;
    ThreadPool::defaultPool().start(worker1);
    ThreadPool::defaultPool().start(worker2);

    if (!db.open("userProfiles.kch", kyotocabinet::HashDB::OWRITER | kyotocabinet::HashDB::OCREATE)) {
        std::cout << "open database error: " << db.error().name() << std::endl;
    }

    std::string s;

    if (!db.get("0", &s)) {
        newID = 1;
        if (!db.set("0", "1")) {
            std::cout << db.error().name() << std::endl;
        }
    } else {
        newID = atoi(s.c_str());
    };
    std::cout << "nextID will be: " << newID << std::endl;
}

userProfileServiceHandler::~userProfileServiceHandler() {
    if (!db.close()) {
        std::cout << "close database error: " << db.error().name() << std::endl;
    }
    while (!queue.empty()) {
        Poco::Thread::sleep(100);
    }
    Poco::Thread::sleep(1000);
    queue.wakeUpAll();
    ThreadPool::defaultPool().joinAll();
}

void userProfileServiceHandler::Create(userProfileResult& _return, const userProfile& profile) {

    userProfile newProfile(profile);
    mutexUpdate.lock();
    newProfile.id = newID++;
    if (!db.set("0", std::to_string(newID))) {
        std::cout << "error update key : " << db.error().name() << std::endl;
    }
    std::cout << "add new to Cache" << std::endl;
    users.add(newProfile.id, newProfile);
    mutexUpdate.unlock();

    _return.errorCode = setDB(newProfile.id, newProfile);
    _return.profile = newProfile;
    printf("Create\n");
}

void userProfileServiceHandler::Get(userProfileResult& _return, const int32_t id) {
    try {
        mutexUpdate.lock();
        _return.profile = users.get(id);
        mutexUpdate.unlock();
        std::cout << "get from Cache" << std::endl;
        _return.errorCode = 0;
        _return.profile.id = id;
    } catch (std::out_of_range e) {
        mutexUpdate.unlock();
        _return.errorCode = getDB(id, _return.profile);
        if (_return.errorCode == 0) {
            std::cout << "add new to Cache" << std::endl;
            mutexUpdate.lock();
            users.add(id, _return.profile);
            mutexUpdate.unlock();
        }
    }
    printf("Get\n");
}

int32_t userProfileServiceHandler::Update(const int32_t id, const userProfile& newProfile) {
    if (!isContainDB(id)) {
        return 1;
    }

    mutexUpdate.lock();
    users.update(id, newProfile);
    mutexUpdate.unlock();

    printf("Update\n");
    return setDB(id, newProfile);
}

int32_t userProfileServiceHandler::Delete(const int32_t id) {

    mutexUpdate.lock();
    users.remove(id);
    mutexUpdate.unlock();

    printf("Delete\n");
    return removeDB(id);
}

int32_t userProfileServiceHandler::ansyCreate(const userProfile& profile) {
    queue.enqueueNotification(new CreatNotification(profile));
    printf("ansyCreate\n");
    return 0;
}

int32_t userProfileServiceHandler::ansyUpdate(const int32_t id, const userProfile& newProfile) {
    queue.enqueueNotification(new UpdateNotification(id,newProfile));
    printf("ansyUpdate\n");
    return 0;
}


int32_t userProfileServiceHandler::ansyDelete(const int32_t id) {
    queue.enqueueNotification(new DeleteNotification(id));
    printf("ansyDelete\n");
    return 0;
}

bool userProfileServiceHandler::isContainDB(int id) {
    if (id == 0) return false;
    std::string s;
    if (!db.get(std::to_string(id), &s)) {
        return false;
    };
    return true;
}

int userProfileServiceHandler::setDB(int id, userProfile profile) {
    if (id == 0) return 1;
    std::string vaule = serializeProfile(profile);
    if (!db.set(std::to_string(id), vaule)) {
        return 2;
    }
    return 0;
}

int userProfileServiceHandler::getDB(int id, userProfile &profile) {
    if (id == 0) return 1;
    std::string vaule;
    if (!db.get(std::to_string(id), &vaule)) {
        return 1;
    };
    deserilizeProfile(vaule, profile);
    profile.id = id;
    return 0;
}

int userProfileServiceHandler::removeDB(int id) {
    if (id == 0) return 0;
    db.remove(std::to_string(id));
    return 0;
}

//https://stackoverflow.com/questions/19672155/apache-thrift-serialization-in-c

std::string userProfileServiceHandler::serializeProfile(userProfile obj) {
    std::shared_ptr<TMemoryBuffer> transportOut(new TMemoryBuffer());
    std::shared_ptr<TBinaryProtocol> protocolOut(new TBinaryProtocol(transportOut));
    obj.write(protocolOut.get());
    std::string serialized_string = transportOut->getBufferAsString();
    return serialized_string;
}

void userProfileServiceHandler::deserilizeProfile(std::string serializeString, userProfile &profile) {
    std::shared_ptr<TMemoryBuffer> transportIn(new TMemoryBuffer());
    std::shared_ptr<TBinaryProtocol> protocolIn(new TBinaryProtocol(transportIn));
    transportIn.get()->write((uint8_t*) serializeString.c_str(), serializeString.length());
    profile.read(protocolIn.get());
}