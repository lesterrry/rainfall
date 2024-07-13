class Display {
public:
  Display(int address, int width, int height) 
  : _display(address, width, height) {}

  void begin() {
    _display.init();
    _display.backlight();
  }

  void print(String text, int8_t x = -1, int8_t y = -1) {
    if (x != -1 || y != -1) _display.setCursor(x, y);
    _display.print(text);
  }

  void clear() {
    _display.clear();
  }
private:
  LiquidCrystal_I2C _display;
};