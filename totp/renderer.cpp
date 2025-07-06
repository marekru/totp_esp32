#include <renderer.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>


void Renderer::init()
{
  _display.init(); // enable diagnostic output on Serial
  _display.setRotation(1);
  _display.setFont(&FreeMonoBold12pt7b); // TODO:
}

void Renderer::show()
{
  _display.update();
  _display.powerDown(); // we can power down display until next update (which should poweron display again)
}

void Renderer::clear()
{
  _display.fillScreen(_bkgColor);  
}

void Renderer::renderText(String* text, int posx, int posy)
{
  if (_renderTextWithBkg)
  {
    int16_t nX = 0, nY = 0;
    uint16_t nWidth = 0, nHeight = 0;
    _display.getTextBounds(text->c_str(), 0, 0, &nX, &nY, &nWidth, &nHeight);
    _display.fillRect(nX, nY, nWidth, nHeight, _bkgColor);
  }

  _display.setTextColor(_textColor);
  _display.setCursor(posx, posy);
  _display.println(*text);
}

void Renderer::renderTextCentered(String* text, int x, int y, int width, int height)
{
  //
  //  |    |-------|     |
  //  x   x0   nWidth
  //  delta = (width - nWidth) / 2

  int16_t nX = 0, nY = 0;
  uint16_t nWidth = 0, nHeight = 0;
  _display.getTextBounds(text->c_str(), 0, 0, &nX, &nY, &nWidth, &nHeight);

  int posx = x - nX + (width - nWidth) / 2;
  int posy = y - nY + (height - nHeight) / 2; // text is drawn from bottom-left, but the screen coordinates are from top-left

  renderText(text, posx, posy);  
}

void Renderer::renderTextScreenCentered(String* text)
{
  renderTextCentered(text, 0, 0, _display.width(), _display.height());
}