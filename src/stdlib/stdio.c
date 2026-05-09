#include "stdio.h"

uint16_t* const vga_addr = (uint16_t* const)0xB8000;
const uint16_t default_color = (COLOR8_LIGHT_GREY << 8) | (COLOR8_BLACK << 12);
const uint16_t tablen = 4;

uint16_t current_color = default_color;
uint16_t row = 0;
uint16_t column = 0;

void reset(){
    row = 0;
    column = 0;
    for(;row < row_limit;row++){
        for(;column < column_limit; column ++){
            vga_addr[row*column_limit + column] = ' ' | default_color;
        }
    }

    row = 0;
    column = 0;

    return;
}

void scrollup(){
    uint16_t save_row = row;
    uint16_t save_column = column;

    for(row = 0; row < row_limit-1;row++){
        for(column = 0;column < column_limit; column ++){
            vga_addr[row*column_limit + column] = vga_addr[(row+1)*column_limit + column];
        }
    }
    row = row + 1;

    for(column = 0;column < column_limit; column ++){
        vga_addr[row*column_limit + column] = ' ' | current_color;
    }

    row = save_row;
    column = save_column;

    return;
}

void newLine(){
    if(row <79){
        row++;
        column = 0;
    }
    else{
        scrollup();
        column = 0;
    }
}

void print(const char* str){
    while(*str){
        switch(*str){
            case '\n':
                newLine();
                break;
            case '\t':
                uint16_t tab_needed = 4-(column%4);
                if(column == column_limit){
                    newLine();
                }
                while(tab_needed > 0){
                    vga_addr[row*column_limit + (column++)] = ' ' | current_color;
                    tab_needed--;
                    column++;
                }
                break;
            default:
                if(column == column_limit){
                    newLine();
                }
                vga_addr[row*column_limit + (column++)] = *str | current_color;
                break;

        }
        str = str + 1;
    }
    return;
}