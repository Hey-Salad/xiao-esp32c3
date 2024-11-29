/**
 * WS2813 LED Ring Controller for Xiao ESP32C3
 * 
 * For HeySalad & Seeedstudio 29/11/24
 * MIT License
 * Use as is - no liability to the Author and Partners
 * 
 * This code controls a Grove RGB LED Ring (20 - WS2813 Mini) connected to 
 * a Xiao ESP32C3 microcontroller. It implements multiple LED patterns
 * with automatic rotation between effects.
 * 
 * Hardware Requirements:
 * - Xiao ESP32C3
 * - Grove RGB LED Ring (20 - WS2813 Mini)
 * - Power supply: 3.3V/5V
 * 
 * Connections:
 * - LED Data Pin -> GPIO 6 (configurable)
 * - VCC -> 3.3V/5V
 * - GND -> GND
 * 
 * Dependencies:
 * - Adafruit_NeoPixel Library
 */

#include <Adafruit_NeoPixel.h>

// Pin and LED configuration
const uint8_t kLedPin = 6;        // Data pin connected to LED ring
const uint8_t kNumLeds = 20;      // Number of LEDs in ring
const uint8_t kBrightness = 50;   // Default brightness (0-255)

// Timing configuration
const uint32_t kPatternDuration = 10000;  // Duration of each pattern (ms)
const uint32_t kUpdateInterval = 50;      // Animation update interval (ms)

// Pattern identifiers
enum PatternType {
  PATTERN_RAINBOW,
  PATTERN_CHASE,
  PATTERN_BREATHE,
  PATTERN_COUNT  // Used to track number of patterns
};

// Global state variables
uint32_t g_last_update = 0;
uint8_t g_current_pattern = PATTERN_RAINBOW;
int16_t g_position = 0;

// Initialize NeoPixel library
Adafruit_NeoPixel g_ring = Adafruit_NeoPixel(
    kNumLeds, 
    kLedPin, 
    NEO_GRB + NEO_KHZ800
);

/**
 * Initializes LED ring hardware and configuration.
 */
void setup() {
  g_ring.begin();
  g_ring.show();  // Initialize all pixels to 'off'
  g_ring.setBrightness(kBrightness);
}

/**
 * Creates a rainbow cycle animation effect.
 * Each LED is set to a different hue that gradually shifts over time.
 */
void DisplayRainbowPattern() {
  for (int i = 0; i < kNumLeds; i++) {
    int hue = (g_position + (i * 65536 / kNumLeds)) % 65536;
    g_ring.setPixelColor(i, g_ring.gamma32(g_ring.ColorHSV(hue)));
  }
  g_ring.show();
  g_position += 256;
}

/**
 * Creates a chase pattern animation.
 * Displays a moving "comet" with a fading tail.
 */
void DisplayChasePattern() {
  g_ring.clear();
  
  // Create trailing effect with 5 pixels
  const uint8_t kTrailLength = 5;
  for (int i = 0; i < kTrailLength; i++) {
    int pos = (g_position - i) % kNumLeds;
    if (pos < 0) pos += kNumLeds;
    
    // Calculate fading red intensity
    uint8_t intensity = 255 - (i * 50);
    uint32_t color = g_ring.Color(intensity, 0, 0);
    g_ring.setPixelColor(pos, color);
  }
  g_ring.show();
  g_position = (g_position + 1) % kNumLeds;
}

/**
 * Creates a breathing effect animation.
 * All LEDs pulse together with smooth brightness transitions.
 */
void DisplayBreathePattern() {
  // Calculate breathing brightness using sine wave
  float brightness = (exp(sin(millis()/2000.0*PI)) - 0.36787944)*108.0;
  g_ring.setBrightness(brightness);
  
  // Set all LEDs to blue
  for (int i = 0; i < kNumLeds; i++) {
    g_ring.setPixelColor(i, g_ring.Color(0, 0, 255));
  }
  g_ring.show();
}

/**
 * Main program loop.
 * Handles pattern switching and timing of animations.
 */
void loop() {
  uint32_t current_time = millis();
  
  // Update pattern if enough time has elapsed
  if (current_time - g_last_update > kUpdateInterval) {
    // Select and display current pattern
    switch(g_current_pattern) {
      case PATTERN_RAINBOW:
        DisplayRainbowPattern();
        break;
      case PATTERN_CHASE:
        DisplayChasePattern();
        break;
      case PATTERN_BREATHE:
        DisplayBreathePattern();
        break;
    }
    
    // Switch patterns periodically
    if (current_time % kPatternDuration == 0) {
      g_current_pattern = (g_current_pattern + 1) % PATTERN_COUNT;
      g_position = 0;  // Reset position for new pattern
    }
    
    g_last_update = current_time;
  }
}