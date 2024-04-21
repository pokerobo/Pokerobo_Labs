#ifndef __EXTENDED_PLAY_SPACE_H__
#define __EXTENDED_PLAY_SPACE_H__

#include "Pokerobo_Lab_Air_Balloon.h"

class ExtendedPlaySpace: public PlaySpace {
  public:
    using PlaySpace::PlaySpace;
    bool hasLost();
    void reset();
  protected:
    void onBalloonExploded(Balloon* balloon);
    void onBalloonEscaped(Balloon* balloon);
    void drawExplodingBalloon(Balloon* b);
    void drawFlyingBalloon(Balloon* b);
    void drawGameInfoBar();
  private:
    int16_t _rewardPointAmount = 0;
    uint16_t _rewardPointTotal = 0;
};

#endif
