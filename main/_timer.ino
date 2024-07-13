class Timer {
  public:
    Timer(uint16_t lastSetSecondsLeft, uint16_t maxSecondsLeft) {
      _lastSetSecondsLeft = lastSetSecondsLeft;
      _secondsLeft = lastSetSecondsLeft;
      _maxSecondsLeft = maxSecondsLeft;
    }

    String timeLeft() {
      return formatSeconds(_secondsLeft);
    }

    String lastSet() {
      return formatSeconds(_lastSetSecondsLeft);
    }

    bool isFinished() {
      return _secondsLeft <= 0;
    }

    uint16_t adjust(int32_t seconds) {
      int32_t adjusted = _secondsLeft + seconds;
      if (adjusted <= 0) return _secondsLeft = 1;
      if (adjusted > _maxSecondsLeft) return _lastSetSecondsLeft = _secondsLeft = _maxSecondsLeft;

      return _lastSetSecondsLeft = _secondsLeft = adjusted;
    }

    void setSecondsLeft(uint16_t seconds) {
      _lastSetSecondsLeft = _secondsLeft = seconds;
    }

    uint16_t getSecondsLeft() {
      return _secondsLeft;
    }

    uint16_t getLastSet() {
      return _lastSetSecondsLeft;
    }

    uint16_t tick() {
      if (_secondsLeft <= 0) return 0;
      return --_secondsLeft;
    }

    static String formatSeconds(uint16_t secondsValue) {
      String result = "";

      uint8_t hours = secondsValue / 3600;
      uint8_t minutes = (secondsValue % 3600) / 60;
      uint8_t seconds = secondsValue % 60;
      
      if (hours < 10) result += "0";
      result += String(hours) + ":";
      
      if (minutes < 10) result += "0";
      result += String(minutes) + ":";
      
      if (seconds < 10) result += "0";
      result += String(seconds);

      return result;
    }

  private:
    uint16_t _lastSetSecondsLeft;
    uint16_t _secondsLeft;
    uint16_t _maxSecondsLeft;
};
