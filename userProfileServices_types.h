/**
 * Autogenerated by Thrift Compiler (0.12.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef userProfileServices_TYPES_H
#define userProfileServices_TYPES_H

#include <iosfwd>

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/TBase.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>

#include <thrift/stdcxx.h>




class userProfile;

class userProfileResult;

typedef struct _userProfile__isset {
  _userProfile__isset() : id(false), name(false), birth(false), gender(false) {}
  bool id :1;
  bool name :1;
  bool birth :1;
  bool gender :1;
} _userProfile__isset;

class userProfile : public virtual ::apache::thrift::TBase {
 public:

  userProfile(const userProfile&);
  userProfile& operator=(const userProfile&);
  userProfile() : id(0), name(), birth(0), gender(0) {
  }
  userProfile(std::string Name, std::string Gender, int bDay , int bMonth , int bYear);

  virtual ~userProfile() throw();
  int32_t id;
  std::string name;
  int32_t birth;
  bool gender;

  _userProfile__isset __isset;

  void __set_id(const int32_t val);

  void __set_name(const std::string& val);

  void __set_birth(const int32_t val);

  void __set_gender(const bool val);

  bool operator == (const userProfile & rhs) const
  {
    if (!(id == rhs.id))
      return false;
    if (!(name == rhs.name))
      return false;
    if (!(birth == rhs.birth))
      return false;
    if (!(gender == rhs.gender))
      return false;
    return true;
  }
  bool operator != (const userProfile &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const userProfile & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
  int getTime(int d, int m ,int y);
  void getDMY(int &d , int &m , int &y);
  void toString();
};

void swap(userProfile &a, userProfile &b);

std::ostream& operator<<(std::ostream& out, const userProfile& obj);

typedef struct _userProfileResult__isset {
  _userProfileResult__isset() : profile(false), errorCode(false) {}
  bool profile :1;
  bool errorCode :1;
} _userProfileResult__isset;

class userProfileResult : public virtual ::apache::thrift::TBase {
 public:

  userProfileResult(const userProfileResult&);
  userProfileResult& operator=(const userProfileResult&);
  userProfileResult() : errorCode(0) {
  }

  virtual ~userProfileResult() throw();
  userProfile profile;
  int32_t errorCode;

  _userProfileResult__isset __isset;

  void __set_profile(const userProfile& val);

  void __set_errorCode(const int32_t val);

  bool operator == (const userProfileResult & rhs) const
  {
    if (!(profile == rhs.profile))
      return false;
    if (!(errorCode == rhs.errorCode))
      return false;
    return true;
  }
  bool operator != (const userProfileResult &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const userProfileResult & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(userProfileResult &a, userProfileResult &b);

std::ostream& operator<<(std::ostream& out, const userProfileResult& obj);



#endif