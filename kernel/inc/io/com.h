//
// Created by sergal on 01.10.2019.
//

#pragma once

#include <def.h>
#include <cpu/port.h>

typedef enum {
    RECIEVED = 1,
    EMPTY = 32
} SERIAL_STATE;

#define COM1 0x3F8
#define COM2 0x2F8
#define COM3 0x3E8
#define COM4 0x2E8

u32 serial_check(u32 port, SERIAL_STATE state) {
    return inb(port + 5) & state;
}

s8 serial_read(u32 port) {
    while (serial_check(port, RECIEVED) == 0);
    return inb(port);
}

void serial_write(u32 port, s8 value) {
    while (serial_check(port, EMPTY) == 0);
    outb(port, value);
}

void serial_write_string(u32 port, s8 *string) {
    u32 i = 0;
    while (1) {
        if (string[i] == 0)
            break;
        serial_write(port, string[i]);
        i++;
    }
}


void serial_init(u32 port) {
    outb(port + 1, 0);
    outb(port + 3, 0x80);
    outb(port + 0, 3);
    outb(port + 1, 0);
    outb(port + 3, 3);
    outb(port + 2, 0xC7);
    outb(port + 4, 0x0B);
}