/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "userProfileHandler.h"
#include "Worker.h"

void Worker::run() {
    AutoPtr<Notification> pNf(_queue.waitDequeueNotification());
    while (pNf) {
        CreatNotification* pCreateNf = dynamic_cast<CreatNotification*> (pNf.get());
        if (pCreateNf) {
            userProfileResult ret;
            H->Create(ret,pCreateNf->data());
        }

        UpdateNotification* pUpdateNf = dynamic_cast<UpdateNotification*> (pNf.get());
        if (pUpdateNf) {
            H->Update(pUpdateNf->getId(),pUpdateNf->data());
        }
        
        DeleteNotification* pDeleteNf = dynamic_cast<DeleteNotification*> (pNf.get());
        if (pDeleteNf) {
            H->Delete(pDeleteNf->getId());
        }
        pNf = _queue.waitDequeueNotification();
    }
    printf("already DONE!\n");
}