#include <iostream>

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include "userProfileService.h"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

void createTask(userProfileServiceClient client , bool asyn = false){ 
    string name, gender;
    int d,m,y;
    cout << "Enter Your Name: " ;
    cin >> name;
    cout << endl <<"Enter Your Gender: " ;
    cin >> gender;
    cout << endl << "Enter Your BirthDay: " << endl << "Day : " ;
    cin >> d;
    cout  << "Month : " ;
    cin >> m;
    cout  << "Year : " ;
    cin >> y;
    userProfile profile(name, gender, d, m, y);
    if (profile.birth == -1) {
        cout << "you enter a invalid birthday" << endl;
        return;
    }
    if(!asyn){
        userProfileResult ret;
        client.Create(ret, profile);
        if (ret.errorCode == 0) {
            cout << "success create new UserProfile with id :"
                    << ret.profile.id << endl;
        }
    }else{
        client.ansyCreate(profile);
        cout << "success send request" << endl;
    }
}

void updateTask(userProfileServiceClient client , bool asyn = false){
    int id;
    cout << "Enter id: " ;
    cin >> id;
    string name, gender;
    int d,m,y;
    cout << endl << "Enter Your Name: " ;
    cin >> name;
    cout << endl <<"Enter Your Gender: " ;
    cin >> gender;
    cout << endl << "Enter Your BirthDay: " << endl << "Day : " ;
    cin >> d;
    cout  << "Month : " ;
    cin >> m;
    cout  << "Year : " ;
    cin >> y;
    userProfile profile(name,gender,d,m,y);
    if(!asyn){
        int retCode = client.Update(id , profile);
        if(retCode == 0){
            cout << "success update id :" << id << endl;
        }else if(retCode == 1){
            cout << "this user id is not in List" << endl;
        }
    }else{
        client.ansyUpdate(id , profile);
        cout << "success send request" << endl;
    }
};

void getTask(userProfileServiceClient client){
    int id;
    cout << "Enter id: " ;
    cin >> id;
    userProfileResult ret;
    client.Get(ret , id);
    if(ret.errorCode == 0){
        ret.profile.toString();
    }else if(ret.errorCode == 1){
        cout << "this user id is not in List" << endl;
    }
};

void deleteTask(userProfileServiceClient client ,bool asyn = false){
    int id;
    cout << "Enter id: " ;
    cin >> id;
    
    if(!asyn){
        int retCode = client.Delete(id);
        if(retCode == 0){
            cout << "success delete id :" << id << endl;
        }else if(retCode == 1){
            cout << "this user id is not in List" << endl;
        }
    }else{
        client.ansyDelete(id);
        cout << "success send request" << endl;
    }
};



int main() {
  std::shared_ptr<TTransport> socket(new TSocket("localhost", 9090));
  std::shared_ptr<TTransport> transport(new TFramedTransport(socket));
  std::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
  userProfileServiceClient client(protocol);

  try {
      transport->open();
      int QUIT = 0;
      while(QUIT == 0){
          cout << "___________________________" << endl
                  <<"Enter 1 to create:" << endl
                  << "Enter 2 to get:" << endl
                  << "Enter 3 to update:" << endl
                  << "Enter 4 to delete:" << endl
                  << "Enter 5 to asynchronous create" << endl
                  << "Enter 6 to asynchronous update" << endl
                  << "Enter 7 to asynchronous delete" << endl
                  << "Enter other number to quit:" << endl;
          int choose;
          cin >> choose;
          if(choose == 1){createTask(client);}
          else if(choose == 2){ getTask(client); }
          else if(choose == 3) { updateTask(client);}
          else if(choose == 4){deleteTask(client);}
          else if(choose == 5){createTask(client,true);}
          else if(choose == 6){updateTask(client,true);}
          else if(choose == 7){deleteTask(client,true);}
          else {
              QUIT = 1;
          }
      }
      
      

      transport->close();
  } catch (TException& tx) {
    cout << "ERROR: " << tx.what() << endl;
  }
}