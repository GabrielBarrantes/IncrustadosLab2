/*
 * RefreshScreen.cpp
 *
 *  Created on: May 13, 2018
 *      Author: gab
 */

#include "globals.hpp"
#include "RefreshScreen.hpp"
#include <stdio.h>

uint8_t RefreshScreen::run()
{
    //#########################
    // Read the message, and retrieve h
    int32_t l_h;
    st_Message l_stMessage;

    l_stMessage = this->getMessage(m_u8TaskID);
    l_h = (int32_t) l_stMessage.u32MessageData;
    //l_h = l_stMessage.u32MessageData;

    if(currentH != l_h)
    {
    if(currentH < l_h){currentH++;}
    if(currentH > l_h){currentH--;}


    Graphics_setForegroundColor(&g_sContext, 0x00FF0000);
    Graphics_drawLineH(&g_sContext, 0, 127, 64-currentH);

    Graphics_setForegroundColor(&g_sContext, 0x000000FF);
    Graphics_drawLineH(&g_sContext, 0, 127, 64-currentH-1);

    Graphics_setForegroundColor(&g_sContext, 0x00DAA520);
    Graphics_drawLineH(&g_sContext, 0, 127, 64-currentH+1);
    ////
    ////
    Graphics_setForegroundColor(&g_sContext, 0x00FFFFFF);
    Graphics_drawLineH(&g_sContext, 48, 80, 64+31);// 30 grados
    Graphics_drawLineH(&g_sContext, 58, 70, 64+21);// 20 grados
    Graphics_drawLineH(&g_sContext, 48, 80, 64+11);// 10 grados
    Graphics_drawLineH(&g_sContext, 58, 70, 64+54);// 60 grados
    Graphics_drawLineH(&g_sContext, 48, 80, 64-31);//-30 grados
    Graphics_drawLineH(&g_sContext, 58, 70, 64-21);//-20 grados
    Graphics_drawLineH(&g_sContext, 48, 80, 64-11);//-10 grados
    Graphics_drawLineH(&g_sContext, 58, 70, 64-54);//-60 grados
/* Indicadores Numericos
    GrContextFontSet(&g_sContext, &g_sFontCm12);
    Graphics_drawStringCentered(&g_sContext,(int8_t *)"10",AUTO_STRING_LENGTH,36,75,TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext,(int8_t *)"30",AUTO_STRING_LENGTH,36,95,TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext,(int8_t *)"60",AUTO_STRING_LENGTH,36,118,TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext,(int8_t *)"10",AUTO_STRING_LENGTH,92,75,TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext,(int8_t *)"30",AUTO_STRING_LENGTH,92,95,TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext,(int8_t *)"60",AUTO_STRING_LENGTH,92,118,TRANSPARENT_TEXT);

    Graphics_drawStringCentered(&g_sContext,(int8_t *)"10",AUTO_STRING_LENGTH,36,53,TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext,(int8_t *)"30",AUTO_STRING_LENGTH,36,33,TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext,(int8_t *)"60",AUTO_STRING_LENGTH,36,10,TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext,(int8_t *)"10",AUTO_STRING_LENGTH,92,53,TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext,(int8_t *)"30",AUTO_STRING_LENGTH,92,33,TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext,(int8_t *)"60",AUTO_STRING_LENGTH,92,10,TRANSPARENT_TEXT);
*/
    }

    /*
    Graphics_setForegroundColor(&g_sContext, 0x000000FF);
    //Graphics_drawRectangle(&g_sContext,&g_sRectangle);
    g_sRectangle.xMax = 0;
    g_sRectangle.xMin = 127;//127;
    g_sRectangle.yMax = 0;
    g_sRectangle.yMin = 62-h;//127;
    Graphics_fillRectangle(&g_sContext,&g_sRectangle);
    //Graphics_drawLineH(&g_sContext, 0, 127, 63);

    Graphics_setForegroundColor(&g_sContext, 0x00DAA520);
    //Graphics_drawRectangle(&g_sContext,&g_sRectangle);
    g_sRectangle.xMax = 0;
    g_sRectangle.xMin = 127;//127;
    g_sRectangle.yMax = 64-h;
    g_sRectangle.yMin = 127;//127;
    Graphics_fillRectangle(&g_sContext,&g_sRectangle);
    //#########################*/
    return(NO_ERR);
}

uint8_t RefreshScreen::setup()
{
    this->currentH = 0x0;
    return(NO_ERR);
}



