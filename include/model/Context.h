#ifndef __CONTEXT__
#define __CONTEXT__

class Context {
  public:
    Context();

    void setStarted();
    void setStopped();

    bool isStarted();  
    bool isStopped();
    void setIDLE();
    void setWORKING();
    void setPRE_ALLARM();
    void setALLARM();
    bool inAllarm();
    bool inIdle();
    bool inPreAllarm();
    void reset();

  private:
    enum {IDLE, WORKING, PRE_ALLARM, ALLARM} ;
    bool started; 
    bool stopped;
    int state;
};

#endif