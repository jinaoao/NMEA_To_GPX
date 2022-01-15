#include "test.h"

// º¯Êý£ºÇåÆÁ²âÊÔ
//
void LCD_ClearTest(void)
{
	u16 time = 1000;	//ÑÓÊ±Ê±¼ä

	LCD_SetFont(&Font24);		//ÉèÖÃ×ÖÌå
	LCD_SetColor(LCD_BLACK);	//ÉèÖÃ»­±ÊÑÕÉ«

	LCD_SetBackColor(LCD_RED);    LCD_Clear();  delay_ms(time);
	LCD_SetBackColor(LCD_GREEN);  LCD_Clear();  delay_ms(time);
	LCD_SetBackColor(LCD_BLUE);   LCD_Clear();  delay_ms(time);
	LCD_SetBackColor(LCD_GREY);   LCD_Clear();  delay_ms(time);	
	LCD_SetBackColor(LCD_WHITE);   LCD_Clear();  delay_ms(time);
	LCD_SetBackColor(LCD_BLACK);   LCD_Clear();  delay_ms(time);
}
// º¯Êý£ºÎÄ±¾²âÊÔ
//
void LCD_TextTest(void)
{
	u16 time = 100;
	LCD_SetBackColor(LCD_BLACK); //ÉèÖÃ±³¾°É«
	LCD_Clear(); //ÇåÆÁ£¬Ë¢±³¾°É«

	LCD_SetColor(LCD_WHITE);
	LCD_SetFont(&Font32); LCD_DisplayString(0, 0,"!#$%&'()*+,-.01"); 				delay_ms(time);		
	LCD_SetFont(&Font24); LCD_DisplayString(0,32,"!#$%&'()*+,-.01234"); 			delay_ms(time);
	LCD_SetFont(&Font20); LCD_DisplayString(0,56,"!#$%&'()*+,-.012345"); 		delay_ms(time);	
	LCD_SetFont(&Font16); LCD_DisplayString(0,76,"!#$%&'()*+,-.01234567"); 		delay_ms(time);	
	LCD_SetFont(&Font12); LCD_DisplayString(0,92,"!#$%&'()*+,-.0123456789:"); 	delay_ms(time);	

	LCD_SetColor(LCD_CYAN);                                                      
	LCD_SetFont(&Font12); LCD_DisplayString(0,104,"!#$%&'()*+,-.0123456789:"); delay_ms(time);	
	LCD_SetFont(&Font16); LCD_DisplayString(0,116,"!#$%&'()*+,-.01234567"); 	delay_ms(time);	
	LCD_SetFont(&Font20); LCD_DisplayString(0,132,"!#$%&'()*+,-.012345"); 		delay_ms(time);		
	LCD_SetFont(&Font24); LCD_DisplayString(0,152,"!#$%&'()*+,-.01234"); 		delay_ms(time);		
	LCD_SetFont(&Font32); LCD_DisplayString(0,176,"!#$%&'()*+,-.01"); 			delay_ms(time);	

	LCD_SetFont(&Font32);
	LCD_SetColor(LCD_YELLOW);
	LCD_DisplayNumber( 0,220,429496729,9);   delay_ms(time);	
	LCD_ShowNumMode(Fill_Zero);	
	LCD_DisplayNumber( 0,252,123456,9);	     delay_ms(time);
	LCD_ShowNumMode(Fill_Space);	
	LCD_DisplayNumber( 0,284,1234,9);		  delay_ms(time);		

	delay_ms(2000);	
}

// º¯Êý£º¾ØÐÎÌî³ä²âÊÔ
//
void LCD_FillTest(void)
{
	LCD_SetBackColor(LCD_BLACK); //ÉèÖÃ±³¾°É«
	LCD_Clear(); //ÇåÆÁ£¬Ë¢±³¾°É«

	LCD_SetFont(&Font16);
	LCD_SetColor(LCD_BLUE);	  	  LCD_FillRect(110,  3,130,16);	LCD_DisplayString(0,  3,"LCD_BLUE");		
	LCD_SetColor(LCD_GREEN);  	  LCD_FillRect(110, 25,130,16);  LCD_DisplayString(0, 25,"LCD_GREEN");		
	LCD_SetColor(LCD_RED);    	  LCD_FillRect(110, 47,130,16);  LCD_DisplayString(0, 47,"LCD_RED");			
	LCD_SetColor(LCD_CYAN);   	  LCD_FillRect(110, 69,130,16);  LCD_DisplayString(0, 69,"LCD_CYAN");		
	LCD_SetColor(LCD_MAGENTA);	  LCD_FillRect(110, 91,130,16);  LCD_DisplayString(0, 91,"LCD_MAGENTA");	
	LCD_SetColor(LCD_YELLOW); 	  LCD_FillRect(110,113,130,16);  LCD_DisplayString(0,113,"LCD_YELLOW");		
	LCD_SetColor(LCD_GREY);   	  LCD_FillRect(110,135,130,16);	LCD_DisplayString(0,135,"LCD_GREY");		
                                      
	LCD_SetColor(LIGHT_BLUE);	  LCD_FillRect(110,157,130,16);  LCD_DisplayString(0,157,"LIGHT_BLUE");		
	LCD_SetColor(LIGHT_GREEN);   LCD_FillRect(110,179,130,16);  LCD_DisplayString(0,179,"LIGHT_GREEN");	
	LCD_SetColor(LIGHT_RED);     LCD_FillRect(110,201,130,16);  LCD_DisplayString(0,201,"LIGHT_RED");	   
	LCD_SetColor(LIGHT_CYAN);    LCD_FillRect(110,223,130,16);  LCD_DisplayString(0,223,"LIGHT_CYAN");	   
	LCD_SetColor(LIGHT_MAGENTA); LCD_FillRect(110,245,130,16);  LCD_DisplayString(0,245,"LIGHT_MAGENTA");	
	LCD_SetColor(LIGHT_YELLOW);  LCD_FillRect(110,267,130,16);  LCD_DisplayString(0,267,"LIGHT_YELLOW");	
	LCD_SetColor(LIGHT_GREY);    LCD_FillRect(110,289,130,16);	LCD_DisplayString(0,289,"LIGHT_GREY");  	
                                                     
	delay_ms(2000);
}

// º¯Êý£ºÑÕÉ«²âÊÔ
//
void LCD_ColorTest(void)
{
	u16 i;

	LCD_SetBackColor(LCD_BLACK); //ÉèÖÃ±³¾°É«
	LCD_Clear(); //ÇåÆÁ£¬Ë¢±³¾°É«
	LCD_SetFont(&Font32);
	LCD_SetColor(LCD_BLACK);

	LCD_SetBackColor(LIGHT_MAGENTA); LCD_DisplayString(0,  0,"   Color Test   "); 
	LCD_SetBackColor(LCD_YELLOW);  	LCD_DisplayString(0, 40,"   Color Test   ");
	LCD_SetBackColor(LCD_CYAN);  	 	LCD_DisplayString(0, 80,"   Color Test   ");

	//Ê¹ÓÃ»­Ïßº¯Êý»æÖÆÈý»ùÉ«É«Ìõ
	for(i=0;i<240;i++)
	{
		LCD_SetColor( LCD_RED-(i<<16) );
		LCD_DrawLine(i,150,i,190);			
	}
	for(i=0;i<240;i++)
	{
		LCD_SetColor( LCD_GREEN-(i<<8) );
		LCD_DrawLine(i,200,i,240);	
	}
	for(i=0;i<240;i++)
	{
		LCD_SetColor( LCD_BLUE-i );
		LCD_DrawLine(i,250,i,290);	
	}	
	delay_ms(2000);	
}
// º¯Êý£º»æÍ¼²âÊÔ
//
void LCD_GrahicTest(void)
{
	u16 time = 80;

	LCD_SetBackColor(LCD_BLACK); //ÉèÖÃ±³¾°É«
	LCD_Clear(); //ÇåÆÁ£¬Ë¢±³¾°É«	

	LCD_SetColor(LCD_RED);
	LCD_DrawLine(0,10,240,10);	delay_ms(time);	//»­Ö±Ïß
	LCD_DrawLine(0,20,240,20);	delay_ms(time);
	LCD_DrawLine(0,30,240,30); delay_ms(time);
	LCD_DrawLine(0,40,240,40);	delay_ms(time);	
	
	LCD_SetColor(LCD_YELLOW);	
	LCD_DrawRect( 5, 85,240,150); delay_ms(time);	//»æÖÆ¾ØÐÎ
	LCD_DrawRect(30,100,190,120); delay_ms(time);
	LCD_DrawRect(55,115,140,90);  delay_ms(time);
	LCD_DrawRect(80,135,90,60);   delay_ms(time);	

	LCD_SetColor(LIGHT_CYAN);
	LCD_DrawCircle(120,170,100);	delay_ms(time);	//»æÖÆÔ²ÐÎ
	LCD_DrawCircle(120,170,80);   delay_ms(time);
	LCD_DrawCircle(120,170,60);   delay_ms(time);
	LCD_DrawCircle(120,170,40);   delay_ms(time);

	LCD_SetColor(DARK_CYAN);
	LCD_DrawLine(0,285,240,285);	delay_ms(time);	//»­Ö±Ïß
	LCD_DrawLine(0,295,240,295);	delay_ms(time);
	LCD_DrawLine(0,305,240,305);  delay_ms(time);
	LCD_DrawLine(0,315,240,315);	delay_ms(time);	
	delay_ms(1000);

	LCD_SetBackColor(LCD_BLACK); //ÉèÖÃ±³¾°É«
	LCD_Clear(); //ÇåÆÁ£¬Ë¢±³¾°É«	
	
	LCD_SetColor(LCD_RED);    LCD_FillCircle( 60,80,60);		//Ìî³äÔ²ÐÎ
	LCD_SetColor(LCD_GREEN);  LCD_FillCircle(120,80,60); 	
	LCD_SetColor(LCD_BLUE);   LCD_FillCircle(160,80,60);  	

	LCD_SetColor(LIGHT_BLUE);
	LCD_DrawEllipse(120,250,110,50);  delay_ms(time);	//»æÖÆÍÖÔ²
	LCD_DrawEllipse(120,250, 95,40);  delay_ms(time);
	LCD_DrawEllipse(120,250, 80,30);  delay_ms(time);
	LCD_DrawEllipse(120,250, 65,20);  delay_ms(time);

	delay_ms(2000);	
}

void LCD_HorizontalText(void)
{
	u16 time = 100;
	
	LCD_ClearTest();	// ÇåÆÁ²âÊÔº¯Êý

	
	LCD_SetBackColor(LCD_BLACK); //ÉèÖÃ±³¾°É«
	LCD_Clear(); //ÇåÆÁ£¬Ë¢±³¾°É«
	LCD_SetColor(LCD_WHITE);
	LCD_SetFont(&Font32); LCD_DisplayString(0, 0,"!#$%&'()*+,-.0123456"); 		delay_ms(time);	// ×Ö·ûÏÔÊ¾²âÊÔ
	LCD_SetFont(&Font24); LCD_DisplayString(0,32,"!#$%&'()*+,-.0123456789:"); 	delay_ms(time);	// ×Ö·ûÏÔÊ¾²âÊÔ
	LCD_SetFont(&Font20); LCD_DisplayString(0,56,"!#$%&'()*+,-.0123456789:"); 	delay_ms(time);	// ×Ö·ûÏÔÊ¾²âÊÔ
	LCD_SetFont(&Font16); LCD_DisplayString(0,76,"!#$%&'()*+,-.0123456789:"); 	delay_ms(time);	// ×Ö·ûÏÔÊ¾²âÊÔ
	LCD_SetFont(&Font12); LCD_DisplayString(0,92,"!#$%&'()*+,-.0123456789:"); 	delay_ms(time);	// ×Ö·ûÏÔÊ¾²âÊÔ
	LCD_SetColor(LIGHT_YELLOW);                                                      
	LCD_SetFont(&Font12); LCD_DisplayString(0,104,"!#$%&'()*+,-.0123456789:"); delay_ms(time);	// ×Ö·ûÏÔÊ¾²âÊÔ
	LCD_SetFont(&Font16); LCD_DisplayString(0,116,"!#$%&'()*+,-.0123456789:"); delay_ms(time);	// ×Ö·ûÏÔÊ¾²âÊÔ
	LCD_SetFont(&Font20); LCD_DisplayString(0,132,"!#$%&'()*+,-.0123456789:"); delay_ms(time);	// ×Ö·ûÏÔÊ¾²âÊÔ	
	LCD_SetFont(&Font24); LCD_DisplayString(0,152,"!#$%&'()*+,-.0123456789:"); delay_ms(time);	// ×Ö·ûÏÔÊ¾²âÊÔ	
	LCD_SetFont(&Font32); LCD_DisplayString(0,176,"!#$%&'()*+,-.0123456"); 		delay_ms(time);	// ×Ö·ûÏÔÊ¾²âÊÔ
	delay_ms(2000);		
	
	LCD_SetBackColor(LCD_BLACK); //ÉèÖÃ±³¾°É«
	LCD_Clear(); //ÇåÆÁ£¬Ë¢±³¾°É«
	LCD_SetFont(&Font16);
	LCD_SetColor(LCD_BLUE);	  	  LCD_FillRect(110,  3,210,16);	LCD_DisplayString(0,  3,"LCD_BLUE");		// ¾ØÐÎÌî³ä²âÊÔ
	LCD_SetColor(LCD_GREEN);  	  LCD_FillRect(110, 25,210,16);  LCD_DisplayString(0, 25,"LCD_GREEN");		// ¾ØÐÎÌî³ä²âÊÔ
	LCD_SetColor(LCD_RED);    	  LCD_FillRect(110, 47,210,16);  LCD_DisplayString(0, 47,"LCD_RED");			// ¾ØÐÎÌî³ä²âÊÔ
	LCD_SetColor(LCD_CYAN);   	  LCD_FillRect(110, 69,210,16);  LCD_DisplayString(0, 69,"LCD_CYAN");		// ¾ØÐÎÌî³ä²âÊÔ
	LCD_SetColor(LCD_MAGENTA);	  LCD_FillRect(110, 91,210,16);  LCD_DisplayString(0, 91,"LCD_MAGENTA");	// ¾ØÐÎÌî³ä²âÊÔ
	LCD_SetColor(LCD_YELLOW); 	  LCD_FillRect(110,113,210,16);  LCD_DisplayString(0,113,"LCD_YELLOW");		// ¾ØÐÎÌî³ä²âÊÔ
	LCD_SetColor(LCD_GREY);   	  LCD_FillRect(110,135,210,16);	LCD_DisplayString(0,135,"LCD_GREY");		// ¾ØÐÎÌî³ä²âÊÔ
                                                     
	LCD_SetColor(LIGHT_BLUE);	  LCD_FillRect(110,157,210,16);  LCD_DisplayString(0,157,"LIGHT_BLUE");		// ¾ØÐÎÌî³ä²âÊÔ
	LCD_SetColor(LIGHT_GREEN);   LCD_FillRect(110,179,210,16);  LCD_DisplayString(0,179,"LIGHT_GREEN");	// ¾ØÐÎÌî³ä²âÊÔ
	LCD_SetColor(LIGHT_RED);     LCD_FillRect(110,201,210,16);  LCD_DisplayString(0,201,"LIGHT_RED");	   // ¾ØÐÎÌî³ä²âÊÔ
	LCD_SetColor(LIGHT_CYAN);    LCD_FillRect(110,223,210,16);  LCD_DisplayString(0,223,"LIGHT_CYAN");	   // ¾ØÐÎÌî³ä²âÊÔ                                         
	delay_ms(2000);	
	
	LCD_SetBackColor(LCD_BLACK); //ÉèÖÃ±³¾°É«
	LCD_Clear(); //ÇåÆÁ£¬Ë¢±³¾°É«		
	LCD_SetColor(LCD_RED);    LCD_FillCircle( 80,120,80);		//Ìî³äÔ²ÐÎ
	LCD_SetColor(LCD_GREEN);  LCD_FillCircle(160,120,80); 	//Ìî³äÔ²ÐÎ
	LCD_SetColor(LCD_BLUE);   LCD_FillCircle(240,120,80);  	//Ìî³äÔ²ÐÎ
	delay_ms(2000);		
}

