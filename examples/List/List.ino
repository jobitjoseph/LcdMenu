/*
 Menu Item List

 https://lcdmenu.forntoh.dev/examples/string-list

*/

#include <ItemList.h>
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

// Declare the callbacks
void colorsCallback(uint16_t pos);
void numsCallback(uint16_t pos);

// Declare the array
extern String colors[];
// Initialize the array
String colors[] = {"Red",  "Green",  "Blue",   "Orange",
                   "Aqua", "Yellow", "Purple", "Pink"};

// Declare the array
extern String nums[];
// Initialize the array
String nums[] = {
    "5", "7", "9", "12", "32",
};

// Initialize the main menu items
MAIN_MENU(
    ITEM_BASIC("List demo"),
    ITEM_STRING_LIST("Col", colors, 8, colorsCallback),
    ITEM_STRING_LIST("Num", nums, 5, numsCallback),
    ITEM_BASIC("Example")
);

// Construct the LcdMenu
LiquidCrystalI2CAdapter lcdAdapter(0x27, LCD_COLS, LCD_ROWS);
LcdMenu menu(lcdAdapter);

void setup() {
    Serial.begin(9600);
    // Initialize LcdMenu with the menu items
    menu.initialize(mainMenu);
}

void loop() {
    if (!Serial.available()) return;
    char command = Serial.read();
    processMenuCommand(menu, command, UP, DOWN, ENTER, BACK, LEFT, RIGHT);
}

// Define the callbacks
void colorsCallback(uint16_t pos) {
    // do something with the index
    Serial.println(colors[pos]);
}

void numsCallback(uint16_t pos) {
    // do something with the index
    Serial.println(nums[pos]);
}
