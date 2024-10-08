/*
 Charset Input

 https://lcdmenu.forntoh.dev/examples/input-from-character-set

*/

#include <ItemInput.h>
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

#define CHARSET_SIZE 10
// Create your charset
char charset[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
// Active index of the charset
int8_t charsetPosition = -1;

// Declare the call back function
void inputCallback(char* value);

MAIN_MENU(
    ITEM_INPUT("Con", inputCallback),
    ITEM_BASIC("Connect to WiFi"),
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
    if (!Serial.available()) return;
    char command = Serial.read();
    processMenuCommand(menu, command, charsetPosition, charset, CHARSET_SIZE,
                       UP, DOWN, ENTER, BACK, CLEAR, BACKSPACE, LEFT, RIGHT);
}
/**
 * Define callback
 */
void inputCallback(char* value) {
    // Do stuff with value
    Serial.print(F("# "));
    Serial.println(value);
}