#ifndef __POKEROBO_LAB_NRF24L01_DEMO_SCREEN_H__
#define __POKEROBO_LAB_NRF24L01_DEMO_SCREEN_H__

#include <Pokerobo_RCB_master.h>
#include <U8g2lib.h>

class CaroMessagePacket {};

class CaroMessageGenerator {
  public:
    void createMessage(char *text);
    virtual CaroMessagePacket* createMessage(CaroMessagePacket *packet);
  private:
    int _count = 0;
};

class CaroMessageSerializer {
  public:
    virtual char* encode(char *payload, CaroMessagePacket *event);
    virtual CaroMessagePacket* decode(CaroMessagePacket *event, char *payload);
};

class CaroDisplayHandler: public DisplayHandler {
  public:
    using DisplayHandler::DisplayHandler;
    CaroDisplayHandler(char *title);
    void renderMessage(char *text);
    void renderMessage(CaroMessagePacket *packet);
  protected:
    virtual void renderMessageInternal(CaroMessagePacket *packet);
  private:
    void renderMessageOrString(CaroMessagePacket *packet, char *text);
    char *_title = NULL;
};

//-------------------------------------------------------------------------------------------------

class CounterMessagePacket: public CaroMessagePacket {
  friend class CounterMessageGenerator;
  friend class CounterMessageSerializer;
  public:
    char* getContent();
    void update(const char* buffer);
  private:
    char _content[20] = {0};
};

class CounterMessageGenerator: public CaroMessageGenerator {
  public:
    CaroMessagePacket* createMessage(CaroMessagePacket *packet);
  private:
    int _count = 0;
};

class CounterMessageSerializer: public CaroMessageSerializer {
  public:
    char* encode(char *payload, CaroMessagePacket *packet);
    CaroMessagePacket* decode(CaroMessagePacket *packet, char *payload);
};

class CounterDisplayHandler: public CaroDisplayHandler {
  public:
    using CaroDisplayHandler::CaroDisplayHandler;
  protected:
    void renderMessageInternal(CaroMessagePacket *packet);
};

#endif//__POKEROBO_LAB_NRF24L01_DEMO_SCREEN_H__
