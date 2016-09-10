#ifndef DEF_SONAR
#define DEF_SONAR


class UltraSound
{
  public:
    void Init(unsigned int trigger, unsigned int echo);
    double GetDistance(unsigned int timeout);

  private:
    void RecordPulseLength();
    int trigger;
    int echo;
    volatile long startTimeUsec;
    volatile long endTimeUsec;
    double distanceCm;
    long DifferenceTimeUsec;
    long now;
};

#endif
