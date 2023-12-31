#ifndef EASY_SERIAL_
#define EASY_SERIAL_

#include <stdio.h>
#include <iostream>
#include "../serial/serial.h"
#include <EasyRender/EasyRender.h>
#include <EasyRender/json/json.h>
#include <EasyRender/logging/loguru.h>


class easy_serial{
    public:
        serial::Serial serial;
        std::string connect_description;
        bool auto_connect;
        int baudrate;
        bool is_connected;
        std::string serial_port;
        void (*read_line_handler)(std::string);
        bool (*read_byte_handler)(uint8_t); //returns true if byte is to be left off line and false if it is to be included!
        std::vector<std::string> split (const std::string &s, char delim);
        easy_serial(std::string c, bool (*b)(uint8_t), void (*r)(std::string))
        {
            connect_description = c;
            auto_connect = true;
            baudrate = 115200;
            read_line_handler = r;
            read_byte_handler = b;
            connection_retry_timer = 0;
            serial_port = "";
            logged_devices_once = false;
        }
        /*
            access to main loop
        */
        void tick();

        /*
            Send a single byte
        */
        void send_byte(uint8_t b);

        /*
            Send a un-encoded string
        */
        void send_string(std::string s);

        /*
            Equivilent to arduino delay
        */
        void delay(int ms);

        /*
           Re-send last sent un-encoded string
        */
        void resend();

    private:
        std::string read_line;
        unsigned long connection_retry_timer;
        bool logged_devices_once;
        /* 
            CRC-32C (iSCSI) polynomial in reversed bit order.
        */
        #define POLY 0x82f63b78
        uint32_t crc32c(uint32_t crc, const char *buf, size_t len);

        


};

#endif