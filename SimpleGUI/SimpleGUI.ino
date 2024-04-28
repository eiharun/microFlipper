#include <Arduino.h>
#include <U8g2lib.h>
#include "menu.h"
#include "game.h"
#include "idle.h"

U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI u8g2(U8G2_R2, /* cs=*/9, /* dc=*/4, /* reset=*/6);

//https://github.com/olikraus/u8g22/wiki/u8g22reference

int backlight_tgl_State=LOW;            
// int backlight_tgl_lastState = LOW;  
int sel_state=LOW;
int sel_lastState=LOW;
int up_lastState=LOW;
int down_lastState=LOW;

int item_sel = 0;
int item_prev;
int item_next;
int idle=0;

void setup(void) {
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(5,INPUT);
  u8g2.begin();
  u8g2.setBitmapMode(1);
  u8g2.setColorIndex(1);
//   Serial.begin(9600);
}

void loop() {
  int up = digitalRead(2);
  int down = digitalRead(5);
  // int backlight_tgl = digitalRead(3);
  // toggle(backlight_tgl_State, backlight_tgl, backlight_tgl_lastState);
  int sel = digitalRead(3);
  toggle(sel_state, sel, sel_lastState);
  if(!sel_state){
    oneclick(up, down);
  }
  item_prev = item_sel-1;
  if (item_prev <0){
    item_prev = icon_len-1;
  }
  item_next = item_sel+1;
  if(item_next >= icon_len){
    item_next = 0;
  }
  //
  u8g2.clearBuffer();
  switch(backlight_tgl_State){
    default: break;
    case LOW:
      base();
      break;
    case HIGH:
      base();
      u8g2.setDrawColor(2);//XOR mode
      u8g2.drawBox(0,0,128,64);  //Inverts the image https://github.com/olikraus/u8g2/issues/1729
      break;
  }
  u8g2.sendBuffer();

}

void toggle(int &state, int reading, int &last_state){
  if (reading != last_state) {
    state ^= reading;
    last_state = reading;
  }
}

void oneclick(int &up, int &down){
  if((up==HIGH) && (up_lastState==HIGH)){
    item_sel += 1;
    up_lastState=LOW;
    if(item_sel >=icon_len){
      item_sel = 0;
    }
  }
  else if((down==HIGH) && (down_lastState==HIGH)){
    item_sel -= 1;
    down_lastState=LOW;
    if(item_sel <0){
      item_sel = icon_len-1;
    }
  }
  //Reset
  if(!up && !up_lastState){
    up_lastState=HIGH;
  }
  if(!down && !down_lastState){
    down_lastState=HIGH;
  }
}

void menu_screen(){
  u8g2.setDrawColor(1);//Reg mode
  u8g2.drawBox(128-3, (64/icon_len)*item_sel, 3, (64/icon_len) + ((64%icon_len) * ((item_sel/(icon_len-1)))));
  u8g2.drawXBMP(128-ScrollBar_width, 0, ScrollBar_width,  ScrollBar_height, ScrollBar_bits);
  u8g2.drawXBMP(4, 2, icon_wh,  icon_wh, menu_item[item_prev].icon);
  u8g2.setFont(u8g_font_7x14);
  u8g2.drawStr(26, 15, menu_item[item_prev].icon_name);
  u8g2.drawXBMP(0, 22, Select_width,  Select_height, Select_bits);
  u8g2.drawXBMP(4, (64/2)-8, icon_wh,  icon_wh, menu_item[item_sel].icon);
  u8g2.setFont(u8g_font_7x14B);
  u8g2.drawStr(26, 37, menu_item[item_sel].icon_name);
  u8g2.drawXBMP(4, 64-2-16, icon_wh,  icon_wh, menu_item[item_next].icon);
  u8g2.setFont(u8g_font_7x14);
  u8g2.drawStr(26, 59, menu_item[item_next].icon_name);
}

void base(){
  idle++;
  int screen = ((sel_state)|(sel_state<<1)|(sel_state<<2)) & (item_sel+1);
  switch(screen){
    default:
      // menu_screen();
      u8g2.setFont(u8g_font_7x14);
      u8g2.drawStr(5, 15, "WELCOME!!");
      delay(1000);
      break;
    case 0:
      menu_screen();
      break;
    case 1:
      // u8g2.setFont(u8g_font_7x14);
      // u8g2.drawStr(5, 15, menu_item[item_sel].icon_name);
      displayIdleanim(idle);
      //if any button is pressed: case 0 (screen=0)
      break;
    case 2:
      u8g2.setFont(u8g_font_7x14);
      u8g2.drawStr(5, 15, menu_item[item_sel].icon_name);
      break;
    case 3:
      u8g2.setFont(u8g_font_7x14);
      u8g2.drawStr(5, 15, menu_item[item_sel].icon_name);
      break;
    case 4:
      u8g2.setFont(u8g_font_7x14);
      u8g2.drawStr(5, 15, menu_item[item_sel].icon_name);
      break;
    case 5:
      play_game();
      break;
    case 6:
      u8g2.setFont(u8g_font_7x14);
      u8g2.drawStr(5, 15, menu_item[item_sel].icon_name);
      break;

  }
}

void displayIdleanim(int &frame){
  if (frame>=num_frames){
    frame=0;
  }
  u8g2.drawHLine((frame-64)%num_frames,64/4,21);
  u8g2.drawHLine((frame-42)%num_frames,64/2,21);
  u8g2.drawHLine((frame-21)%num_frames,64*3/4,21);
  delay(5);
}


void play_game(){
  

  pong player={1,64/2,1,8};
  pong ping={126,64/2,1,8};
  pong ball={128/2,64/2,2,2,UP,LEFT};
  int defeat=0;
  int victory=0;
  while((!victory) && (!defeat)){
    int player_up = digitalRead(2);
    int player_down = digitalRead(5);
    int exit = digitalRead(3);
    if(exit){
      return;
    }
    u8g2.clearBuffer();
    ping.y_pos = ball.y_pos-(ping.h_size/2);//Game is impossible to win
    u8g2.drawBox(player.x_pos, player.y_pos, player.w_size, player.h_size);
    u8g2.drawBox(ping.x_pos, ping.y_pos, ping.w_size, ping.h_size);
    u8g2.drawBox(ball.x_pos, ball.y_pos, ball.w_size, ball.h_size);

    if((player_up)&&(player.y_pos<(127-player.h_size))){
      player.y_pos++;
    }
    if((player_down)&&(player.y_pos>=0)){
      player.y_pos--;
    }

    if ((ball.x_pos<player.x_pos) && ((ball.y_pos < player.y_pos+player.h_size) && (ball.y_pos > player.y_pos)) ){
      ball.directionlr=RIGHT;
    }

    if ((ball.x_pos>ping.x_pos) && ((ball.y_pos < ping.y_pos+ping.h_size) && (ball.y_pos > ping.y_pos)) ){
      ball.directionlr=LEFT;
    }

    if(ball.y_pos<=0){
      ball.directionud=DOWN;
    }
    if(ball.y_pos>63){
      ball.directionud=UP;
    }

    if(ball.directionlr==LEFT){
      ball.x_pos--;
    }
    if(ball.directionlr==RIGHT){
      ball.x_pos++;
    }
    if(ball.directionud==UP){
      ball.y_pos--;
    }
    if(ball.directionud==DOWN){
      ball.y_pos++;
    }


    if(ball.x_pos >127){
      victory=1;
      
    }
    if(ball.x_pos < player.x_pos-1){
      defeat=1;
      
    }

    if(victory){
      u8g2.clearBuffer();
      u8g2.setFont(u8g_font_7x14);
      u8g2.drawStr(5, 15, "Victory!");
      u8g2.sendBuffer();
      delay(1000);
      return;
    }
    if(defeat){
      u8g2.clearBuffer();
      u8g2.setFont(u8g_font_7x14);
      u8g2.drawStr(5, 15, "Defeat!");
      u8g2.sendBuffer();
      delay(1000);
      return;
    }
    delay(35); 
    u8g2.sendBuffer();
  }
}
