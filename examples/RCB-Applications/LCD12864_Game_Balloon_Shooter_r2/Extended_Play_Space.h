#ifndef __EXTENDED_PLAY_SPACE_H__
#define __EXTENDED_PLAY_SPACE_H__

#include "Pokerobo_Lab_Game_BalloonShooter_PlaySpace.h"

class ExtendedPlaySpace: public PlaySpace {
  public:
    using PlaySpace::PlaySpace;
  protected:
    void drawExplodingBalloon(Balloon* b);
};

#endif
