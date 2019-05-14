/**
 * Autogenerated by Thrift Compiler (0.12.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "userProfileServices_types.h"

#include <algorithm>
#include <ostream>

#include <thrift/TToString.h>




userProfile::~userProfile() throw() {
}


void userProfile::__set_id(const int32_t val) {
  this->id = val;
}

void userProfile::__set_name(const std::string& val) {
  this->name = val;
}

void userProfile::__set_birth(const int32_t val) {
  this->birth = val;
}

void userProfile::__set_gender(const bool val) {
  this->gender = val;
}
std::ostream& operator<<(std::ostream& out, const userProfile& obj)
{
  obj.printTo(out);
  return out;
}


uint32_t userProfile::read(::apache::thrift::protocol::TProtocol* iprot) {

  ::apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->id);
          this->__isset.id = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->name);
          this->__isset.name = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->birth);
          this->__isset.birth = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 4:
        if (ftype == ::apache::thrift::protocol::T_BOOL) {
          xfer += iprot->readBool(this->gender);
          this->__isset.gender = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t userProfile::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  ::apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("userProfile");

  xfer += oprot->writeFieldBegin("id", ::apache::thrift::protocol::T_I32, 1);
  xfer += oprot->writeI32(this->id);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("name", ::apache::thrift::protocol::T_STRING, 2);
  xfer += oprot->writeString(this->name);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("birth", ::apache::thrift::protocol::T_I32, 3);
  xfer += oprot->writeI32(this->birth);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("gender", ::apache::thrift::protocol::T_BOOL, 4);
  xfer += oprot->writeBool(this->gender);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(userProfile &a, userProfile &b) {
  using ::std::swap;
  swap(a.id, b.id);
  swap(a.name, b.name);
  swap(a.birth, b.birth);
  swap(a.gender, b.gender);
  swap(a.__isset, b.__isset);
}

userProfile::userProfile(const userProfile& other0) {
  id = other0.id;
  name = other0.name;
  birth = other0.birth;
  gender = other0.gender;
  __isset = other0.__isset;
}
userProfile::userProfile(std::string Name, std::string Gender, int bDay , int bMonth , int bYear){
    name = Name;
    gender = Gender == "Nam";
    birth = getTime(bDay,bMonth,bYear);
    __isset;
};
int userProfile::getTime(int d,int m,int y){
    time_t rawtime;
    struct tm * timeinfo;
    
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    timeinfo->tm_year = y - 1900;
    timeinfo->tm_mon = m - 1;
    timeinfo->tm_mday = d;
    
    return int(mktime(timeinfo));
}
void userProfile::getDMY(int &d,int &m, int &y){
    time_t b = (time_t)this->birth;
    tm *ltm = localtime(&b);
    d= ltm->tm_mday;
    m= ltm->tm_mon + 1;
    y= ltm->tm_year + 1900;
}
void userProfile::toString(){
    int d,m,y;
    std::string gender;
    if (this->gender) gender = "Nam";
    else gender = "Nu";
    getDMY(d,m,y);
    printf("id: %d   name: %s      gender: %s     birth :  %d/%d/%d\n",this->id,this->name.c_str(),gender.c_str(),d,m,y);
}
userProfile& userProfile::operator=(const userProfile& other1) {
  id = other1.id;
  name = other1.name;
  birth = other1.birth;
  gender = other1.gender;
  __isset = other1.__isset;
  return *this;
}
void userProfile::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "userProfile(";
  out << "id=" << to_string(id);
  out << ", " << "name=" << to_string(name);
  out << ", " << "birth=" << to_string(birth);
  out << ", " << "gender=" << to_string(gender);
  out << ")";
}


userProfileResult::~userProfileResult() throw() {
}


void userProfileResult::__set_profile(const userProfile& val) {
  this->profile = val;
}

void userProfileResult::__set_errorCode(const int32_t val) {
  this->errorCode = val;
}
std::ostream& operator<<(std::ostream& out, const userProfileResult& obj)
{
  obj.printTo(out);
  return out;
}


uint32_t userProfileResult::read(::apache::thrift::protocol::TProtocol* iprot) {

  ::apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRUCT) {
          xfer += this->profile.read(iprot);
          this->__isset.profile = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->errorCode);
          this->__isset.errorCode = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t userProfileResult::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  ::apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("userProfileResult");

  xfer += oprot->writeFieldBegin("profile", ::apache::thrift::protocol::T_STRUCT, 1);
  xfer += this->profile.write(oprot);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("errorCode", ::apache::thrift::protocol::T_I32, 2);
  xfer += oprot->writeI32(this->errorCode);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(userProfileResult &a, userProfileResult &b) {
  using ::std::swap;
  swap(a.profile, b.profile);
  swap(a.errorCode, b.errorCode);
  swap(a.__isset, b.__isset);
}

userProfileResult::userProfileResult(const userProfileResult& other2) {
  profile = other2.profile;
  errorCode = other2.errorCode;
  __isset = other2.__isset;
}
userProfileResult& userProfileResult::operator=(const userProfileResult& other3) {
  profile = other3.profile;
  errorCode = other3.errorCode;
  __isset = other3.__isset;
  return *this;
}
void userProfileResult::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "userProfileResult(";
  out << "profile=" << to_string(profile);
  out << ", " << "errorCode=" << to_string(errorCode);
  out << ")";
}

