#include "model/Context.h"

Context::Context(){
  started = false;
  stopped = false;
  setIDLE();
}

bool Context::isStarted(){
  return started;
}

bool Context::isStopped(){
  return stopped;
}

void Context::setStarted(){
  started = true;
  stopped = false;
}

void Context::setStopped(){
  stopped = true;
  started = false;
}

void Context::reset(){
  started = false;
  stopped = false;
}

void Context::setIDLE() {
  state = IDLE;
} 

void Context::setWORKING() {
  state = WORKING;
}

void Context::setPRE_ALLARM() {
  state = PRE_ALLARM;
}

void Context::setALLARM() {
  state = ALLARM;
}

bool Context::inAllarm() {
  return state == ALLARM;
}

bool Context::inPreAllarm() {
  return state == PRE_ALLARM;
}

bool Context::inIdle() {
  return state == IDLE;
}

