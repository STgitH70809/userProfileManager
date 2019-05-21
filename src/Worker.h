/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Worker.h
 * Author: cpu02331
 *
 * Created on May 21, 2019, 3:45 PM
 */

#ifndef WORKER_H
#define WORKER_H

#include "Poco/Notification.h"
#include "Poco/NotificationQueue.h"
#include "Poco/ThreadPool.h"
#include "Poco/Runnable.h"
#include "Poco/AutoPtr.h"
#include "userProfileHandler.h"
#include "userProfileService.h"

using Poco::Notification;
using Poco::NotificationQueue;
using Poco::ThreadPool;
using Poco::AutoPtr;

class userProfileServiceHandler;

class CreatNotification : public Notification {
public:
CreatNotification(userProfile data) : _data(data) {
    }

    userProfile data() const {
        return _data;
    }
private:
    userProfile _data;
};

class UpdateNotification : public Notification {
public:
UpdateNotification(int id,userProfile data) : _id(id),_data(data) {
    }
    int getId() const {
        return _id;
    }
    userProfile data() const {
        return _data;
    }
private:
    int _id;
    userProfile _data;
};

class DeleteNotification : public Notification {
public:
DeleteNotification(int id) : _id(id) {
    }
    int getId() const {
        return _id;
    }
private:
    int _id;
};

class Worker : public Poco::Runnable {
public:
    NotificationQueue& _queue;
    userProfileServiceHandler* H;
    Worker(NotificationQueue& queue ) : _queue(queue) {
    }

    void run() ;
};

#endif /* WORKER_H */

