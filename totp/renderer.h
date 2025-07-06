#ifndef RENDERER_H
#define RENDERER_H

#include "defines.h"

#include <boards.h>
#include <GxEPD.h>

#include <GxDEPG0213BN/GxDEPG0213BN.h>    // 2.13" b/w  form DKE GROUP

#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>

class Renderer
{
  private:
    GxIO_Class _io;
    GxEPD_Class _display;
    int _textColor = GxEPD_BLACK;
    int _bkgColor = GxEPD_WHITE;
    bool _renderTextWithBkg = true;
  public:

  Renderer() : _io(SPI, EPD_CS, EPD_DC, EPD_RSET), _display(_io, EPD_RSET, EPD_BUSY) {}

  void init();

  void show();

  void clear();

  // TODO: use const char* instead of String* or String&
  void renderText(String* text, int posx, int posy);

  void renderTextCentered(String* text, int x, int y, int width, int height);

  void renderTextScreenCentered(String* text);
};


#endif // RENDERER_H