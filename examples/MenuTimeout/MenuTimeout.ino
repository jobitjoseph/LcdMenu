/*
 Menu Timeout

 https://lcdmenu.forntoh.dev/examples/timeout

*/

#include <LcdMenu.h>
#include <interface/LiquidCrystalI2CAdapter.h>
#include <utils/commandProccesors.h>

#define LCD_ROWS 2
#define LCD_COLS 16

// Configure keyboard keys (ASCII)

#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'
#define ENTER ' '
#define BACK 'b'
#define BACKSPACE 'v'
#define CLEAR 'c'

MAIN_MENU(
    ITEM_BASIC("Start service"),
    ITEM_BASIC("Connect to WiFi"),
    ITEM_BASIC("Settings"),
    ITEM_BASIC("Blink SOS"),
    ITEM_BASIC("Blink random")
);

LiquidCrystalI2CAdapter lcdAdapter(0x27, LCD_COLS, LCD_ROWS);
LcdMenu menu(lcdAdapter);

void setup() {
    Serial.begin(9600);
    menu.initialize(mainMenu);
}

void loop() {
    /**
     * IMPORTANT: You must call this function for the timeout to work
     * The default timeout is 10000ms
     */
    lcdAdapter.updateTimer();

    // Listen to key
    if (!Serial.available()) return;
    char command = Serial.read();

    processMenuCommand(menu, command, UP, DOWN, ENTER, BACK);
}