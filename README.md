# Minimalistic Game Engine (Enguin)

## About:
Enguin is minimalistic game engine based in terminal technology. It is pretty much like ncurses but worse

## There are some demos too

### What needs to be done?
    [?]add sound - probably impossible without any other dependencies 
    []fix some of bugs
    []add some new features
    [x]image editor
    []write docs

## How to use Enguin?
1. Download Enguin folder
2. 
        #include"Enguin/Enguin.h"
3. Use functions as needed
4. Compile with

        gcc {files} -LEnguin -lEnguin -o {name}
5. run

        ./{name}

### Enguin structures:
    // Surface
    typedef struct{
        EnguinApi_Canvas canvas;
        EnguinApi_Cell* cells;
        int width, height; // window dimensions
        char default_char; // character after erease
        int default_back[3]; // background color after erease
        int default_fore[3]; // foreground color after erease
    }Enguin_Surface;

    // Pixel
    typedef struct{
        char ch;
        int fore[3]; // foreground color
        int back[3]; // background color
    }Enguin_ImagePixel;

    // Image
    typedef struct{
        int w;
        int h;
        Enguin_ImagePixel* pixels;
    }Enguin_Image;

### Enguin functions:

    // Surface
    // wantF & wantB -> set to 1 if you want either background or foreground colors rendering (may be slower)
    Enguin_Surface Enguin_Surface_Init(int width, int height, char ch, int wantF, int wantB, int fore[3], int back[3]);
    void Enguin_Surface_Draw(Enguin_Surface* surface);
    void Enguin_Surface_Update(Enguin_Surface* surface);

    // Text
    void Enguin_Text_Draw(Enguin_Surface* surface, int x, int y, char* text, int fore[3], int back[3]);

    // Graphics
    void Enguin_Pixel_Draw(Enguin_Surface* surface, int x, int y, char pixel, int fore[3], int back[3]);
    void Enguin_Line_Draw(Enguin_Surface* surface, int x1, int y1, int x2, int y2, char pixel, int fore[3], int back[3]);
    void Enguin_Rect_Draw(Enguin_Surface* surface, int x, int y, int w, int h, char pixel, int fore[3], int back[3]);
    void Enguin_Rect_Fill(Enguin_Surface* surface, int x, int y, int w, int h, char pixel, int fore[3], int back[3]);
    void Enguin_Ellipse_Draw(Enguin_Surface* surface, int xc, int yc, int rx, int ry, char ch, int fore[3], int back[3]);
    void Enguin_Ellipse_Fill(Enguin_Surface* surface, int xc, int yc, int rx, int ry, char ch, int fore[3], int back[3]);

    // Image
    Enguin_Image Enguin_Image_Create(int w, int h);
    void Enguin_Image_Save(char* fn, Enguin_Image* img);
    Enguin_Image Enguin_Image_Open(char* fn);
    void Enguin_Image_Draw(Enguin_Surface* surface, Enguin_Image* img, int x, int y);

    // Utilities
    int EnguinApi_Utils_RandomNumber(int, int);
    int EnguinApi_Utils_CountDigits(int);
    void EnguinApi_Utils_Sleep(float);
    int EnguinApi_Utils_GetTicks();
    void EnguinApi_Utils_Kill();