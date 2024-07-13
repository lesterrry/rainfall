class Timer {
  public:
    Timer(uint16_t initialSecondsLeft, uint16_t maxSecondsLeft) {
      _secondsLeft = initialSecondsLeft;
      _maxSecondsLeft = maxSecondsLeft;
    }

    String timeLeft() {
      String result = "";

      uint8_t hours = _secondsLeft / 3600;
      uint8_t minutes = (_secondsLeft % 3600) / 60;
      uint8_t seconds = _secondsLeft % 60;
      
      if (hours < 10) result += "0";
      result += String(hours) + ":";
      
      if (minutes < 10) result += "0";
      result += String(minutes) + ":";
      
      if (seconds < 10) result += "0";
      result += String(seconds);

      return result;
    }

    bool isFinished() {
      return _secondsLeft <= 0;
    }

    uint16_t adjust(int32_t seconds) {
      int32_t adjusted = _secondsLeft + seconds;
      if (adjusted <= 0) return _secondsLeft = 1;
      if (adjusted > _maxSecondsLeft) return _secondsLeft = _maxSecondsLeft;
      
      return _secondsLeft = adjusted;
    }

    uint16_t tick() {
      if (_secondsLeft <= 0) return 0;
      return --_secondsLeft;
    }

  private:
    uint16_t _secondsLeft;
    uint16_t _maxSecondsLeft;
};
