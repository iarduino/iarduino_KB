#include "iarduino_KB.h"
		iarduino_KB::iarduino_KB(uint8_t i0, uint8_t i1, uint8_t i2, uint8_t i3, uint8_t i4, uint8_t i5, uint8_t i6, uint8_t i7, uint8_t i8, uint8_t i9){
			KB_pins_NUM[0]=i0; KB_pins_NUM[1]=i1; KB_pins_NUM[2]=i2; KB_pins_NUM[3]=i3; KB_pins_NUM[4]=i4; KB_pins_NUM[5]=i5; KB_pins_NUM[6]=i6; KB_pins_NUM[7]=i7; KB_pins_NUM[8]=i8; KB_pins_NUM[9]=i9;
		}

//		инициализация клавиатуры
void	iarduino_KB::begin(uint8_t i){
			KB_type_NUM=i;
//			присваиваем номера выводов из объявленных п/п в соответствии с типом клавиатуры

//			устанавливаем выводы в соответствующие им состояния
			switch(KB_type_NUM){
				case KB1:
				case KB2:
					pinMode(KB_pins_NUM[0], OUTPUT); digitalWrite(KB_pins_NUM[4], HIGH);			//	переводим вывод в режим передачи и устанавливаем состояние «1»
					pinMode(KB_pins_NUM[1], OUTPUT); digitalWrite(KB_pins_NUM[4], HIGH);			//	переводим вывод в режим передачи и устанавливаем состояние «1»
					pinMode(KB_pins_NUM[2], OUTPUT); digitalWrite(KB_pins_NUM[4], HIGH);			//	переводим вывод в режим передачи и устанавливаем состояние «1»
					pinMode(KB_pins_NUM[3], OUTPUT); digitalWrite(KB_pins_NUM[4], HIGH);			//	переводим вывод в режим передачи и устанавливаем состояние «1»
					pinMode(KB_pins_NUM[4], INPUT_PULLUP);											//	переводим вывод в режим приёма с подтягивающим резистором
					pinMode(KB_pins_NUM[5], INPUT_PULLUP);											//	переводим вывод в режим приёма с подтягивающим резистором
					pinMode(KB_pins_NUM[6], INPUT_PULLUP);											//	переводим вывод в режим приёма с подтягивающим резистором
					pinMode(KB_pins_NUM[7], INPUT_PULLUP);											//	переводим вывод в режим приёма с подтягивающим резистором
				break;
			}
		}

//		определение нажимаемой/отпускаемой/удерживаемой кнопки
bool	iarduino_KB::check(uint8_t i){
			bool n=false; KB_pres_NOW=255;
//			определяем номер кнопки нажатой в данный момент времени
			switch(KB_type_NUM){
				case KB1:
				case KB2:
					for(uint8_t j=0; j<4; j++){	digitalWrite(KB_pins_NUM[j], LOW);
					for(uint8_t k=0; k<4; k++){ if(!digitalRead(KB_pins_NUM[k+4])){KB_pres_NOW=j*4+k;}}
												digitalWrite(KB_pins_NUM[j], HIGH);
					}
				break;
			}
//			определяем и выводим ответ
			switch(i){
				case KEY_PRESS: n=KB_pres_NOW!=0xFF&&KB_pres_NOW==KB_pres_WAS?true:false; getNum=KB_nums_KB[KB_type_NUM][KB_pres_NOW]; getChar=KB_char_KB[KB_type_NUM][KB_pres_NOW]; break;
				case KEY_DOWN:  n=KB_pres_NOW!=0xFF&&KB_pres_NOW!=KB_pres_WAS?true:false; getNum=KB_nums_KB[KB_type_NUM][KB_pres_NOW]; getChar=KB_char_KB[KB_type_NUM][KB_pres_NOW]; break;
				case KEY_UP:    n=KB_pres_NOW==0xFF&&KB_pres_NOW!=KB_pres_WAS?true:false; getNum=KB_nums_KB[KB_type_NUM][KB_pres_WAS]; getChar=KB_char_KB[KB_type_NUM][KB_pres_WAS]; break;
			}	if(n){delay(10);} KB_pres_WAS=KB_pres_NOW; return n;
		}


