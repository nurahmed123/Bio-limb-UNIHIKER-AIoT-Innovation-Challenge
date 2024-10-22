/*************************************** lcd.cpp ****************************************************************/

//add header file
#include <Wire.h>
#include "Arduino.h"
#include "lcd.h"
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display (address, col, row)






void i2c_lcd_setup()
{
  lcd.init();                      // initialize the lcd
  //lcd.init();
  // Print a message to the LCD.
  lcd.backlight();  //on back lED
  lcd.setCursor(1, 0);  //col, row
  lcd.print("LCD is Working."); //show msg 
  lcd.noBacklight();  //off back lED
}


void show_lcd(int col, int row, String message)
{
  lcd.backlight();
  lcd.setCursor(col, row);
  lcd.print(message);
  Serial.print("show_lcd message:  ");
  Serial.println(message);
}

void lcdClear()
{
  lcd.clear();  //clear all text
}

void show_lcd(int col, int row, String message, int value1)
{
  lcd.backlight();
  lcd.setCursor(col, row);
  lcd.print(message);
  lcd.print(value1);
}

void show_lcd(int col, int row, String message, int value1, String message2)
{
  lcd.backlight();
  lcd.setCursor(col, row);
  lcd.print(message);
  lcd.print(value1);
  lcd.print(message2);
}
