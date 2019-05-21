/**
 * Autogenerated by Thrift Compiler (0.12.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef userProfileService_H
#define userProfileService_H

#include <thrift/TDispatchProcessor.h>
#include <thrift/async/TConcurrentClientSyncInfo.h>
#include "userProfileServices_types.h"



#ifdef _MSC_VER
  #pragma warning( push )
  #pragma warning (disable : 4250 ) //inheriting methods via dominance 
#endif

class userProfileServiceIf {
 public:
  virtual ~userProfileServiceIf() {}
  virtual void Create(userProfileResult& _return, const userProfile& profile) = 0;
  virtual void Get(userProfileResult& _return, const int32_t id) = 0;
  virtual int32_t Update(const int32_t id, const userProfile& newProfile) = 0;
  virtual int32_t Delete(const int32_t id) = 0;
  virtual int32_t ansyCreate(const userProfile& profile) = 0;
  virtual int32_t ansyUpdate(const int32_t id, const userProfile& newProfile) = 0;
  virtual int32_t ansyDelete(const int32_t id) = 0;
};

class userProfileServiceIfFactory {
 public:
  typedef userProfileServiceIf Handler;

  virtual ~userProfileServiceIfFactory() {}

  virtual userProfileServiceIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(userProfileServiceIf* /* handler */) = 0;
};

class userProfileServiceIfSingletonFactory : virtual public userProfileServiceIfFactory {
 public:
  userProfileServiceIfSingletonFactory(const ::apache::thrift::stdcxx::shared_ptr<userProfileServiceIf>& iface) : iface_(iface) {}
  virtual ~userProfileServiceIfSingletonFactory() {}

  virtual userProfileServiceIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(userProfileServiceIf* /* handler */) {}

 protected:
  ::apache::thrift::stdcxx::shared_ptr<userProfileServiceIf> iface_;
};

class userProfileServiceNull : virtual public userProfileServiceIf {
 public:
  virtual ~userProfileServiceNull() {}
  void Create(userProfileResult& /* _return */, const userProfile& /* profile */) {
    return;
  }
  void Get(userProfileResult& /* _return */, const int32_t /* id */) {
    return;
  }
  int32_t Update(const int32_t /* id */, const userProfile& /* newProfile */) {
    int32_t _return = 0;
    return _return;
  }
  int32_t Delete(const int32_t /* id */) {
    int32_t _return = 0;
    return _return;
  }
  int32_t ansyCreate(const userProfile& /* profile */) {
    int32_t _return = 0;
    return _return;
  }
  int32_t ansyUpdate(const int32_t /* id */, const userProfile& /* newProfile */) {
    int32_t _return = 0;
    return _return;
  }
  int32_t ansyDelete(const int32_t /* id */) {
    int32_t _return = 0;
    return _return;
  }
};

typedef struct _userProfileService_Create_args__isset {
  _userProfileService_Create_args__isset() : profile(false) {}
  bool profile :1;
} _userProfileService_Create_args__isset;

class userProfileService_Create_args {
 public:

  userProfileService_Create_args(const userProfileService_Create_args&);
  userProfileService_Create_args& operator=(const userProfileService_Create_args&);
  userProfileService_Create_args() {
  }

  virtual ~userProfileService_Create_args() throw();
  userProfile profile;

  _userProfileService_Create_args__isset __isset;

  void __set_profile(const userProfile& val);

  bool operator == (const userProfileService_Create_args & rhs) const
  {
    if (!(profile == rhs.profile))
      return false;
    return true;
  }
  bool operator != (const userProfileService_Create_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const userProfileService_Create_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class userProfileService_Create_pargs {
 public:


  virtual ~userProfileService_Create_pargs() throw();
  const userProfile* profile;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _userProfileService_Create_result__isset {
  _userProfileService_Create_result__isset() : success(false) {}
  bool success :1;
} _userProfileService_Create_result__isset;

class userProfileService_Create_result {
 public:

  userProfileService_Create_result(const userProfileService_Create_result&);
  userProfileService_Create_result& operator=(const userProfileService_Create_result&);
  userProfileService_Create_result() {
  }

  virtual ~userProfileService_Create_result() throw();
  userProfileResult success;

  _userProfileService_Create_result__isset __isset;

  void __set_success(const userProfileResult& val);

  bool operator == (const userProfileService_Create_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const userProfileService_Create_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const userProfileService_Create_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _userProfileService_Create_presult__isset {
  _userProfileService_Create_presult__isset() : success(false) {}
  bool success :1;
} _userProfileService_Create_presult__isset;

class userProfileService_Create_presult {
 public:


  virtual ~userProfileService_Create_presult() throw();
  userProfileResult* success;

  _userProfileService_Create_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _userProfileService_Get_args__isset {
  _userProfileService_Get_args__isset() : id(false) {}
  bool id :1;
} _userProfileService_Get_args__isset;

class userProfileService_Get_args {
 public:

  userProfileService_Get_args(const userProfileService_Get_args&);
  userProfileService_Get_args& operator=(const userProfileService_Get_args&);
  userProfileService_Get_args() : id(0) {
  }

  virtual ~userProfileService_Get_args() throw();
  int32_t id;

  _userProfileService_Get_args__isset __isset;

  void __set_id(const int32_t val);

  bool operator == (const userProfileService_Get_args & rhs) const
  {
    if (!(id == rhs.id))
      return false;
    return true;
  }
  bool operator != (const userProfileService_Get_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const userProfileService_Get_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class userProfileService_Get_pargs {
 public:


  virtual ~userProfileService_Get_pargs() throw();
  const int32_t* id;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _userProfileService_Get_result__isset {
  _userProfileService_Get_result__isset() : success(false) {}
  bool success :1;
} _userProfileService_Get_result__isset;

class userProfileService_Get_result {
 public:

  userProfileService_Get_result(const userProfileService_Get_result&);
  userProfileService_Get_result& operator=(const userProfileService_Get_result&);
  userProfileService_Get_result() {
  }

  virtual ~userProfileService_Get_result() throw();
  userProfileResult success;

  _userProfileService_Get_result__isset __isset;

  void __set_success(const userProfileResult& val);

  bool operator == (const userProfileService_Get_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const userProfileService_Get_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const userProfileService_Get_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _userProfileService_Get_presult__isset {
  _userProfileService_Get_presult__isset() : success(false) {}
  bool success :1;
} _userProfileService_Get_presult__isset;

class userProfileService_Get_presult {
 public:


  virtual ~userProfileService_Get_presult() throw();
  userProfileResult* success;

  _userProfileService_Get_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _userProfileService_Update_args__isset {
  _userProfileService_Update_args__isset() : id(false), newProfile(false) {}
  bool id :1;
  bool newProfile :1;
} _userProfileService_Update_args__isset;

class userProfileService_Update_args {
 public:

  userProfileService_Update_args(const userProfileService_Update_args&);
  userProfileService_Update_args& operator=(const userProfileService_Update_args&);
  userProfileService_Update_args() : id(0) {
  }

  virtual ~userProfileService_Update_args() throw();
  int32_t id;
  userProfile newProfile;

  _userProfileService_Update_args__isset __isset;

  void __set_id(const int32_t val);

  void __set_newProfile(const userProfile& val);

  bool operator == (const userProfileService_Update_args & rhs) const
  {
    if (!(id == rhs.id))
      return false;
    if (!(newProfile == rhs.newProfile))
      return false;
    return true;
  }
  bool operator != (const userProfileService_Update_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const userProfileService_Update_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class userProfileService_Update_pargs {
 public:


  virtual ~userProfileService_Update_pargs() throw();
  const int32_t* id;
  const userProfile* newProfile;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _userProfileService_Update_result__isset {
  _userProfileService_Update_result__isset() : success(false) {}
  bool success :1;
} _userProfileService_Update_result__isset;

class userProfileService_Update_result {
 public:

  userProfileService_Update_result(const userProfileService_Update_result&);
  userProfileService_Update_result& operator=(const userProfileService_Update_result&);
  userProfileService_Update_result() : success(0) {
  }

  virtual ~userProfileService_Update_result() throw();
  int32_t success;

  _userProfileService_Update_result__isset __isset;

  void __set_success(const int32_t val);

  bool operator == (const userProfileService_Update_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const userProfileService_Update_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const userProfileService_Update_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _userProfileService_Update_presult__isset {
  _userProfileService_Update_presult__isset() : success(false) {}
  bool success :1;
} _userProfileService_Update_presult__isset;

class userProfileService_Update_presult {
 public:


  virtual ~userProfileService_Update_presult() throw();
  int32_t* success;

  _userProfileService_Update_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _userProfileService_Delete_args__isset {
  _userProfileService_Delete_args__isset() : id(false) {}
  bool id :1;
} _userProfileService_Delete_args__isset;

class userProfileService_Delete_args {
 public:

  userProfileService_Delete_args(const userProfileService_Delete_args&);
  userProfileService_Delete_args& operator=(const userProfileService_Delete_args&);
  userProfileService_Delete_args() : id(0) {
  }

  virtual ~userProfileService_Delete_args() throw();
  int32_t id;

  _userProfileService_Delete_args__isset __isset;

  void __set_id(const int32_t val);

  bool operator == (const userProfileService_Delete_args & rhs) const
  {
    if (!(id == rhs.id))
      return false;
    return true;
  }
  bool operator != (const userProfileService_Delete_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const userProfileService_Delete_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class userProfileService_Delete_pargs {
 public:


  virtual ~userProfileService_Delete_pargs() throw();
  const int32_t* id;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _userProfileService_Delete_result__isset {
  _userProfileService_Delete_result__isset() : success(false) {}
  bool success :1;
} _userProfileService_Delete_result__isset;

class userProfileService_Delete_result {
 public:

  userProfileService_Delete_result(const userProfileService_Delete_result&);
  userProfileService_Delete_result& operator=(const userProfileService_Delete_result&);
  userProfileService_Delete_result() : success(0) {
  }

  virtual ~userProfileService_Delete_result() throw();
  int32_t success;

  _userProfileService_Delete_result__isset __isset;

  void __set_success(const int32_t val);

  bool operator == (const userProfileService_Delete_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const userProfileService_Delete_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const userProfileService_Delete_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _userProfileService_Delete_presult__isset {
  _userProfileService_Delete_presult__isset() : success(false) {}
  bool success :1;
} _userProfileService_Delete_presult__isset;

class userProfileService_Delete_presult {
 public:


  virtual ~userProfileService_Delete_presult() throw();
  int32_t* success;

  _userProfileService_Delete_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _userProfileService_ansyCreate_args__isset {
  _userProfileService_ansyCreate_args__isset() : profile(false) {}
  bool profile :1;
} _userProfileService_ansyCreate_args__isset;

class userProfileService_ansyCreate_args {
 public:

  userProfileService_ansyCreate_args(const userProfileService_ansyCreate_args&);
  userProfileService_ansyCreate_args& operator=(const userProfileService_ansyCreate_args&);
  userProfileService_ansyCreate_args() {
  }

  virtual ~userProfileService_ansyCreate_args() throw();
  userProfile profile;

  _userProfileService_ansyCreate_args__isset __isset;

  void __set_profile(const userProfile& val);

  bool operator == (const userProfileService_ansyCreate_args & rhs) const
  {
    if (!(profile == rhs.profile))
      return false;
    return true;
  }
  bool operator != (const userProfileService_ansyCreate_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const userProfileService_ansyCreate_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class userProfileService_ansyCreate_pargs {
 public:


  virtual ~userProfileService_ansyCreate_pargs() throw();
  const userProfile* profile;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _userProfileService_ansyCreate_result__isset {
  _userProfileService_ansyCreate_result__isset() : success(false) {}
  bool success :1;
} _userProfileService_ansyCreate_result__isset;

class userProfileService_ansyCreate_result {
 public:

  userProfileService_ansyCreate_result(const userProfileService_ansyCreate_result&);
  userProfileService_ansyCreate_result& operator=(const userProfileService_ansyCreate_result&);
  userProfileService_ansyCreate_result() : success(0) {
  }

  virtual ~userProfileService_ansyCreate_result() throw();
  int32_t success;

  _userProfileService_ansyCreate_result__isset __isset;

  void __set_success(const int32_t val);

  bool operator == (const userProfileService_ansyCreate_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const userProfileService_ansyCreate_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const userProfileService_ansyCreate_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _userProfileService_ansyCreate_presult__isset {
  _userProfileService_ansyCreate_presult__isset() : success(false) {}
  bool success :1;
} _userProfileService_ansyCreate_presult__isset;

class userProfileService_ansyCreate_presult {
 public:


  virtual ~userProfileService_ansyCreate_presult() throw();
  int32_t* success;

  _userProfileService_ansyCreate_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _userProfileService_ansyUpdate_args__isset {
  _userProfileService_ansyUpdate_args__isset() : id(false), newProfile(false) {}
  bool id :1;
  bool newProfile :1;
} _userProfileService_ansyUpdate_args__isset;

class userProfileService_ansyUpdate_args {
 public:

  userProfileService_ansyUpdate_args(const userProfileService_ansyUpdate_args&);
  userProfileService_ansyUpdate_args& operator=(const userProfileService_ansyUpdate_args&);
  userProfileService_ansyUpdate_args() : id(0) {
  }

  virtual ~userProfileService_ansyUpdate_args() throw();
  int32_t id;
  userProfile newProfile;

  _userProfileService_ansyUpdate_args__isset __isset;

  void __set_id(const int32_t val);

  void __set_newProfile(const userProfile& val);

  bool operator == (const userProfileService_ansyUpdate_args & rhs) const
  {
    if (!(id == rhs.id))
      return false;
    if (!(newProfile == rhs.newProfile))
      return false;
    return true;
  }
  bool operator != (const userProfileService_ansyUpdate_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const userProfileService_ansyUpdate_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class userProfileService_ansyUpdate_pargs {
 public:


  virtual ~userProfileService_ansyUpdate_pargs() throw();
  const int32_t* id;
  const userProfile* newProfile;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _userProfileService_ansyUpdate_result__isset {
  _userProfileService_ansyUpdate_result__isset() : success(false) {}
  bool success :1;
} _userProfileService_ansyUpdate_result__isset;

class userProfileService_ansyUpdate_result {
 public:

  userProfileService_ansyUpdate_result(const userProfileService_ansyUpdate_result&);
  userProfileService_ansyUpdate_result& operator=(const userProfileService_ansyUpdate_result&);
  userProfileService_ansyUpdate_result() : success(0) {
  }

  virtual ~userProfileService_ansyUpdate_result() throw();
  int32_t success;

  _userProfileService_ansyUpdate_result__isset __isset;

  void __set_success(const int32_t val);

  bool operator == (const userProfileService_ansyUpdate_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const userProfileService_ansyUpdate_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const userProfileService_ansyUpdate_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _userProfileService_ansyUpdate_presult__isset {
  _userProfileService_ansyUpdate_presult__isset() : success(false) {}
  bool success :1;
} _userProfileService_ansyUpdate_presult__isset;

class userProfileService_ansyUpdate_presult {
 public:


  virtual ~userProfileService_ansyUpdate_presult() throw();
  int32_t* success;

  _userProfileService_ansyUpdate_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _userProfileService_ansyDelete_args__isset {
  _userProfileService_ansyDelete_args__isset() : id(false) {}
  bool id :1;
} _userProfileService_ansyDelete_args__isset;

class userProfileService_ansyDelete_args {
 public:

  userProfileService_ansyDelete_args(const userProfileService_ansyDelete_args&);
  userProfileService_ansyDelete_args& operator=(const userProfileService_ansyDelete_args&);
  userProfileService_ansyDelete_args() : id(0) {
  }

  virtual ~userProfileService_ansyDelete_args() throw();
  int32_t id;

  _userProfileService_ansyDelete_args__isset __isset;

  void __set_id(const int32_t val);

  bool operator == (const userProfileService_ansyDelete_args & rhs) const
  {
    if (!(id == rhs.id))
      return false;
    return true;
  }
  bool operator != (const userProfileService_ansyDelete_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const userProfileService_ansyDelete_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class userProfileService_ansyDelete_pargs {
 public:


  virtual ~userProfileService_ansyDelete_pargs() throw();
  const int32_t* id;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _userProfileService_ansyDelete_result__isset {
  _userProfileService_ansyDelete_result__isset() : success(false) {}
  bool success :1;
} _userProfileService_ansyDelete_result__isset;

class userProfileService_ansyDelete_result {
 public:

  userProfileService_ansyDelete_result(const userProfileService_ansyDelete_result&);
  userProfileService_ansyDelete_result& operator=(const userProfileService_ansyDelete_result&);
  userProfileService_ansyDelete_result() : success(0) {
  }

  virtual ~userProfileService_ansyDelete_result() throw();
  int32_t success;

  _userProfileService_ansyDelete_result__isset __isset;

  void __set_success(const int32_t val);

  bool operator == (const userProfileService_ansyDelete_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const userProfileService_ansyDelete_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const userProfileService_ansyDelete_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _userProfileService_ansyDelete_presult__isset {
  _userProfileService_ansyDelete_presult__isset() : success(false) {}
  bool success :1;
} _userProfileService_ansyDelete_presult__isset;

class userProfileService_ansyDelete_presult {
 public:


  virtual ~userProfileService_ansyDelete_presult() throw();
  int32_t* success;

  _userProfileService_ansyDelete_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class userProfileServiceClient : virtual public userProfileServiceIf {
 public:
  userProfileServiceClient(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  userProfileServiceClient(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void Create(userProfileResult& _return, const userProfile& profile);
  void send_Create(const userProfile& profile);
  void recv_Create(userProfileResult& _return);
  void Get(userProfileResult& _return, const int32_t id);
  void send_Get(const int32_t id);
  void recv_Get(userProfileResult& _return);
  int32_t Update(const int32_t id, const userProfile& newProfile);
  void send_Update(const int32_t id, const userProfile& newProfile);
  int32_t recv_Update();
  int32_t Delete(const int32_t id);
  void send_Delete(const int32_t id);
  int32_t recv_Delete();
  int32_t ansyCreate(const userProfile& profile);
  void send_ansyCreate(const userProfile& profile);
  int32_t recv_ansyCreate();
  int32_t ansyUpdate(const int32_t id, const userProfile& newProfile);
  void send_ansyUpdate(const int32_t id, const userProfile& newProfile);
  int32_t recv_ansyUpdate();
  int32_t ansyDelete(const int32_t id);
  void send_ansyDelete(const int32_t id);
  int32_t recv_ansyDelete();
 protected:
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class userProfileServiceProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  ::apache::thrift::stdcxx::shared_ptr<userProfileServiceIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (userProfileServiceProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_Create(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_Get(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_Update(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_Delete(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_ansyCreate(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_ansyUpdate(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_ansyDelete(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  userProfileServiceProcessor(::apache::thrift::stdcxx::shared_ptr<userProfileServiceIf> iface) :
    iface_(iface) {
    processMap_["Create"] = &userProfileServiceProcessor::process_Create;
    processMap_["Get"] = &userProfileServiceProcessor::process_Get;
    processMap_["Update"] = &userProfileServiceProcessor::process_Update;
    processMap_["Delete"] = &userProfileServiceProcessor::process_Delete;
    processMap_["ansyCreate"] = &userProfileServiceProcessor::process_ansyCreate;
    processMap_["ansyUpdate"] = &userProfileServiceProcessor::process_ansyUpdate;
    processMap_["ansyDelete"] = &userProfileServiceProcessor::process_ansyDelete;
  }

  virtual ~userProfileServiceProcessor() {}
};

class userProfileServiceProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  userProfileServiceProcessorFactory(const ::apache::thrift::stdcxx::shared_ptr< userProfileServiceIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::apache::thrift::stdcxx::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::apache::thrift::stdcxx::shared_ptr< userProfileServiceIfFactory > handlerFactory_;
};

class userProfileServiceMultiface : virtual public userProfileServiceIf {
 public:
  userProfileServiceMultiface(std::vector<apache::thrift::stdcxx::shared_ptr<userProfileServiceIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~userProfileServiceMultiface() {}
 protected:
  std::vector<apache::thrift::stdcxx::shared_ptr<userProfileServiceIf> > ifaces_;
  userProfileServiceMultiface() {}
  void add(::apache::thrift::stdcxx::shared_ptr<userProfileServiceIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  void Create(userProfileResult& _return, const userProfile& profile) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->Create(_return, profile);
    }
    ifaces_[i]->Create(_return, profile);
    return;
  }

  void Get(userProfileResult& _return, const int32_t id) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->Get(_return, id);
    }
    ifaces_[i]->Get(_return, id);
    return;
  }

  int32_t Update(const int32_t id, const userProfile& newProfile) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->Update(id, newProfile);
    }
    return ifaces_[i]->Update(id, newProfile);
  }

  int32_t Delete(const int32_t id) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->Delete(id);
    }
    return ifaces_[i]->Delete(id);
  }

  int32_t ansyCreate(const userProfile& profile) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->ansyCreate(profile);
    }
    return ifaces_[i]->ansyCreate(profile);
  }

  int32_t ansyUpdate(const int32_t id, const userProfile& newProfile) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->ansyUpdate(id, newProfile);
    }
    return ifaces_[i]->ansyUpdate(id, newProfile);
  }

  int32_t ansyDelete(const int32_t id) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->ansyDelete(id);
    }
    return ifaces_[i]->ansyDelete(id);
  }

};

// The 'concurrent' client is a thread safe client that correctly handles
// out of order responses.  It is slower than the regular client, so should
// only be used when you need to share a connection among multiple threads
class userProfileServiceConcurrentClient : virtual public userProfileServiceIf {
 public:
  userProfileServiceConcurrentClient(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  userProfileServiceConcurrentClient(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void Create(userProfileResult& _return, const userProfile& profile);
  int32_t send_Create(const userProfile& profile);
  void recv_Create(userProfileResult& _return, const int32_t seqid);
  void Get(userProfileResult& _return, const int32_t id);
  int32_t send_Get(const int32_t id);
  void recv_Get(userProfileResult& _return, const int32_t seqid);
  int32_t Update(const int32_t id, const userProfile& newProfile);
  int32_t send_Update(const int32_t id, const userProfile& newProfile);
  int32_t recv_Update(const int32_t seqid);
  int32_t Delete(const int32_t id);
  int32_t send_Delete(const int32_t id);
  int32_t recv_Delete(const int32_t seqid);
  int32_t ansyCreate(const userProfile& profile);
  int32_t send_ansyCreate(const userProfile& profile);
  int32_t recv_ansyCreate(const int32_t seqid);
  int32_t ansyUpdate(const int32_t id, const userProfile& newProfile);
  int32_t send_ansyUpdate(const int32_t id, const userProfile& newProfile);
  int32_t recv_ansyUpdate(const int32_t seqid);
  int32_t ansyDelete(const int32_t id);
  int32_t send_ansyDelete(const int32_t id);
  int32_t recv_ansyDelete(const int32_t seqid);
 protected:
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
  ::apache::thrift::async::TConcurrentClientSyncInfo sync_;
};

#ifdef _MSC_VER
  #pragma warning( pop )
#endif



#endif