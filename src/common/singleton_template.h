//
// Created by 杨万青 on 2018/7/14.
//

#ifndef NETWORKFILESSENDER_SINGLETON_TEMPLATE_H
#define NETWORKFILESSENDER_SINGLETON_TEMPLATE_H

#include <mutex>
#include <utility>
#include <cstdlib>

#include "nfs_namesapce.h"

NFS_NAMESPACE_BEGIN

template<class Derived>
class Singleton {
 public:
  // Static Methods
  template<typename... Args>
  static inline Derived &getInstance(Args &&...args) {
    return *getInstancePointer(std::forward<Args>(args)...);
  }

  template<typename... Args>
  static inline Derived *getInstancePointer(Args &&...args) {
    static Derived
        *instancePointer = createInstance(std::forward<Args>(args)...);
    return instancePointer;
  }

 protected:
  using Access = Singleton<Derived>;

  // Constructors
  Singleton(void) = default;

  Singleton(Singleton const &) = default;

  Singleton(Singleton &&) = default;

  // Assignment Operators
  Singleton &operator=(Singleton const &) = default;

  Singleton &operator=(Singleton &&) = default;

  // Destructor
  virtual ~Singleton(void) = default;

 private:
  // Static Attributes
  static Derived *instance_pointer;

  static std::mutex lock;

  // Static Methods
  template<typename... Args>
  static inline Derived *createInstance(Args &&...args) {
    if (Singleton::instance_pointer == nullptr) {
      std::lock_guard<decltype(Singleton::lock)> lock(Singleton::lock);
      if (Singleton::instance_pointer == nullptr) {
        void *data = static_cast<void *>(getData());
        new(data) Derived(std::forward<Args>(args)...);
        Singleton::instance_pointer = reinterpret_cast<Derived *>(data);
        std::atexit(&Singleton::destroyInstance);
      }
    }
    return Singleton::instance_pointer;
  }

  static inline void destroyInstance(void) {
    reinterpret_cast<Derived *>(getData())->~Derived();
  }

  static inline unsigned char *getData(void) {
    static unsigned char data[sizeof(Derived)];
    return data;
  }
};

template<class Derived>
Derived *Singleton<Derived>::instance_pointer = nullptr;

template<class Derived>
std::mutex Singleton<Derived>::lock;



NFS_NAMESPACE_END

#endif //NETWORKFILESSENDER_SINGLETON_TEMPLATE_H
