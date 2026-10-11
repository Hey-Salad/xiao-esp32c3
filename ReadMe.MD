# LED Ring Control for Xiao ESP32C3 🌈

## Powered by Seeedstudio's Grove RGB LED Ring

The Grove RGB LED Ring (20 - WS2813 Mini) is a versatile LED display solution that combines powerful WS2813 addressable LEDs with Grove's plug-and-play simplicity. Perfect for creating stunning visual effects and indicators.

### ⚡ Key Features of Grove RGB LED Ring

- 🎨 20 Individually Addressable RGB LEDs
- 💡 WS2813 Chipset with Built-in Controllers
- 🛡️ Intelligent Reverse-connection Protection
- 🔄 Signal Break-point Continuous Transmission
- 📊 256 Gray Levels
- 🎨 16,777,216 Colors

## 🔍 Hardware Specifications

- Operating Voltage: 3.3V/5V
- Quiescent Current: 0.7mA/LED
- RGB Channel Current: 16mA/LED
- Refresh Rate: 2KHz
- Operating Temperature: -25℃ to 85℃

## 🚀 About The Code

This project implements three stunning LED patterns with smooth transitions:

### 1. Rainbow Cycle Pattern
```cpp
void DisplayRainbowPattern() {
  for (int i = 0; i < kNumLeds; i++) {
    int hue = (g_position + (i * 65536 / kNumLeds)) % 65536;
    g_ring.setPixelColor(i, g_ring.gamma32(g_ring.ColorHSV(hue)));
  }
}
```
Creates a smooth rainbow effect by:
- Calculating unique hue values for each LED
- Using HSV color space for smooth transitions
- Applying gamma correction for natural-looking colors

### 2. Chase Pattern
```cpp
void DisplayChasePattern() {
  const uint8_t kTrailLength = 5;
  for (int i = 0; i < kTrailLength; i++) {
    int pos = (g_position - i) % kNumLeds;
    uint8_t intensity = 255 - (i * 50);
    g_ring.setPixelColor(pos, color);
  }
}
```
Implements a "comet" effect with:
- Leading bright pixel
- Fading tail of 5 pixels
- Smooth circular movement

### 3. Breathe Pattern
```cpp
void DisplayBreathePattern() {
  float brightness = (exp(sin(millis()/2000.0*PI)) - 0.36787944)*108.0;
  g_ring.setBrightness(brightness);
}
```
Creates a pulsing effect using:
- Sinusoidal brightness calculation
- Exponential scaling for natural-looking fade
- Synchronized LED brightness control

## 🛠️ Setup Instructions

1. **Hardware Connection**
   - Connect LED Ring data pin to GPIO 6
   - Connect VCC to 3.3V/5V
   - Connect GND to ground

2. **Software Setup**
   ```bash
   # Create project directory
   mkdir LED_Ring_Control
   cd LED_Ring_Control
   
   # Create main sketch file
   touch LED_Ring_Control.ino
   ```

3. **Library Installation**
   - Open Arduino IDE
   - Go to Tools > Manage Libraries
   - Search for "Adafruit NeoPixel"
   - Click Install

## ⚙️ Configuration Options

Key parameters you can modify:
```cpp
const uint8_t kLedPin = 6;        // Change pin number
const uint8_t kBrightness = 50;   // Adjust brightness (0-255)
const uint32_t kPatternDuration = 10000;  // Pattern duration in ms
```

## 📝 License

Copyright (C) 2024-2026 HeySalad Inc.

Licensed under the GNU Affero General Public License v3.0 only (AGPL-3.0-only). See [LICENSE](LICENSE) and [NOTICE](NOTICE). If you run a modified version of this software to provide a network service, the AGPL requires you to offer its users the corresponding source code. Versions published before this change remain under their previous licence.

## ☕ Support

If you find this code useful, please consider supporting us!

<img src="https://github.com/Hey-Salad/.github/blob/a4cbf4a12cca3477fdbfe55520b3fdfe0e0f35a4/buy-me-a-coffee.png" alt="Buy Me A Coffee QR Code" width="200"/>

<a href="https://www.buymeacoffee.com/heysalad"><img src="https://github.com/Hey-Salad/.github/blob/a4cbf4a12cca3477fdbfe55520b3fdfe0e0f35a4/bmc-button.png" alt="Buy Me A Coffee" width="200"/></a>

## 🤝 Contributing

We welcome contributions! Areas for improvement:
- New pattern designs
- Performance optimizations
- Additional configuration options
- Documentation improvements

## 🔧 Troubleshooting

Common issues and solutions:
1. **LEDs not lighting up**
   - Check power supply voltage
   - Verify data pin connection
   - Ensure correct PIN number in code

2. **Colors not displaying correctly**
   - Check power supply current capacity
   - Verify LED ring model compatibility
   - Check for correct color order (RGB vs GRB)

---
Made with ❤️ by HeySalad