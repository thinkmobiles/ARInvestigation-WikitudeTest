#include <stdlib.h>
#include <string.h>
#include "zbar.h"

zbar::Image* _image;
zbar::ImageScanner* _imageScanner;

extern "C" {
    void initialize(int width, int height);
    const char* get_barcode(int width, int height, unsigned char* data);
    void destroy();
}

void initialize(int width, int height)
{
    _image = new zbar::Image(width, height, "Y800", nullptr, 0);
    _imageScanner = new zbar::ImageScanner();
    _imageScanner->set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 1);
}

const char* get_barcode(int width, int height, unsigned char* data)
{
    _image->set_data(data, width * height);
    int n = _imageScanner->scan(*_image);
    
    if (n) 
    {
        zbar::Image::SymbolIterator symbol = _image->symbol_begin();
        return strdup(symbol->get_data().c_str());
    }
    else
    {
        return nullptr;
    }
}

void destroy()
{
    _image->set_data(nullptr, 0);
    
    delete _image;
    delete _imageScanner;
}
