#include "Mutex.h"
#include "timespec.h"
#include <stdexcept>

Mutex::Mutex() {
  pthread_mutexattr_t mutexAttribute;
  pthread_mutexattr_init(&mutexAttribute);
  pthread_mutexattr_settype(&mutexAttribute, PTHREAD_MUTEX_DEFAULT);
  pthread_mutex_init(&posixId, &mutexAttribute);
  pthread_cond_init(&posixCondId, nullptr);
  pthread_mutexattr_destroy(&mutexAttribute);
}

Mutex::~Mutex() {
  pthread_mutex_destroy(&posixId);
  pthread_cond_destroy(&posixCondId);
}

void Mutex::lock() {
  pthread_mutex_lock(&posixId);
}

bool Mutex::lock(double timeout_ms) {
  return ! (bool)pthread_mutex_timedlock(&posixId, &timespec_from_ms(timeout_ms));
}

bool Mutex::trylock() {
  return ! (bool)pthread_mutex_trylock(&posixId);
}

void Mutex::unlock() {
  pthread_mutex_unlock(&posixId);
}

Mutex::Lock::Lock(Mutex &m) : mtx(m) {
  mtx.lock();
}

Mutex::Lock::Lock(Mutex &m, double timeout_ms) : mtx(m) {
  int retval = mtx.lock(timeout_ms);
  if (retval != 0){
    // TODO create Timeout Exception
  }
}

Mutex::Lock::~Lock(){
  mtx.unlock();
}

void Mutex::Lock::wait() {
  pthread_cond_wait(&mtx.posixCondId, &mtx.posixId);
}

bool Mutex::Lock::wait(double timeout_ms) {
  return ! (bool)pthread_cond_timedwait(&mtx.posixCondId, &mtx.posixId, &timespec_from_ms(timeout_ms));
}

void Mutex::Lock::notify() {
  pthread_cond_signal(&mtx.posixCondId);
}

void Mutex::Lock::notifyAll() {
  pthread_cond_broadcast(&mtx.posixCondId);
}