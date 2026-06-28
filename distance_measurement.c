/*
 * Ultrasonic Distance Measurement using 8051 (AT89S52)
 * --------------------------------------------------
 * Sensor   : HC-SR04 Ultrasonic Sensor
 * Display  : 16x2 LCD
 * Author   : Govind Tard (2022BTECE005)
 * Project  : Embedded and Microcontrollers Lab, CURAJ
 * Guide    : Dr. Kapil Saraswat
 *
 * Logic:
 *  1. Send a 10us trigger pulse on TRIG pin.
 *  2. Wait for ECHO pin to go HIGH, start Timer0.
 *  3. Wait for ECHO pin to go LOW, stop Timer0.
 *  4. Timer0 count = pulse width (time taken by sound to travel to
 *     object and back).
 *  5. Distance (cm) = pulseWidth / 58  (derived from speed of sound).
 *  6. Show distance on LCD; sound buzzer if object is too close (<=5cm).
 */

#include <reg51.h>

sbit rs     = P2^0;   // LCD Register Select
sbit rw     = P2^1;   // LCD Read/Write
sbit en     = P2^2;   // LCD Enable
sbit buzzer = P2^3;   // Buzzer output (active LOW here)
sbit echo   = P2^4;   // HC-SR04 ECHO pin
sbit trig   = P2^5;   // HC-SR04 TRIG pin

void delay_ms(unsigned int ms);
void lcdcmd(unsigned char cmd);
void lcddata1(unsigned char data1);
void lcd_init(void);

void main(void)
{
    unsigned int pulseWidth;
    unsigned int distance;

    echo = 1;
    trig = 0;
    TMOD = 0x01;   // Timer0 in 16-bit mode

    lcd_init();

    while (1) {
        TH0 = 0;
        TL0 = 0;

        // Send 10us trigger pulse to HC-SR04
        trig = 1;
        delay_ms(10);
        trig = 0;

        while (!echo);   // Wait for echo to go HIGH
        TR0 = 1;          // Start Timer0

        while (echo);    // Wait for echo to go LOW
        TR0 = 0;          // Stop Timer0

        pulseWidth = TL0 | (TH0 << 8);
        distance = pulseWidth / 58;   // Convert timer count to cm

        lcdcmd(0x86);     // Move cursor to desired position
        delay_ms(2);

        lcddata1((distance / 10) + '0');  // Tens digit
        lcddata1((distance % 10) + '0');  // Ones digit

        if (distance <= 5) {
            buzzer = 0;   // Object too close -> buzzer ON
        } else {
            buzzer = 1;   // Buzzer OFF
        }
    }
}

void delay_ms(unsigned int ms)
{
    unsigned int i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 127; j++) {
            // Adjust loop count if delay timing needs tuning
        }
    }
}

void lcdcmd(unsigned char cmd)
{
    P1 = cmd;
    rs = 0;
    rw = 0;
    en = 1;
    delay_ms(1);
    en = 0;
}

void lcddata1(unsigned char data1)
{
    P1 = data1;
    rs = 1;
    rw = 0;
    en = 1;
    delay_ms(1);
    en = 0;
}

void lcd_init(void)
{
    delay_ms(20);
    lcdcmd(0x38);   // 8-bit mode, 2 lines, 5x7 font
    delay_ms(5);
    lcdcmd(0x0C);   // Display ON, cursor OFF
    delay_ms(5);
    lcdcmd(0x01);   // Clear display
    delay_ms(5);
    lcdcmd(0x06);   // Auto-increment cursor
    delay_ms(5);
}
