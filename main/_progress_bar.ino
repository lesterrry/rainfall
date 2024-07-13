class ProgressBar {
  public:
    ProgressBar(uint16_t maxValue) {
      _value = maxValue;
      _maxValue = maxValue;
    }

    uint16_t updateMaxValue(uint16_t newMaxValue) {
      _value = newMaxValue;
      return _maxValue = newMaxValue;
    }

    String getString() {
      String result = "";
      uint8_t currentProgress = ceil(_value / (float)_maxValue * LED_WIDTH);
      for(size_t i = 0; i < currentProgress; i++) {
        result += "=";
      }
      return result;
    }

    uint16_t tick() {
      if (_value <= 0) return 0;
      return --_value;
    }

  private:
    uint16_t _value;
    uint16_t _maxValue;
};
