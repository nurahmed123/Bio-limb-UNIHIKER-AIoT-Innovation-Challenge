/************************************ lcd.h ***************************************************************/


void lcdClear();
void i2c_lcd_setup();
void show_lcd(int col, int row, String message, int value1);  //function overloading
void show_lcd(int col, int row, String message, int value1, String message2);
void show_lcd(int col, int row, String message);
void display_all_data();

//void show_lcd(int col, int row, String message, int value);
