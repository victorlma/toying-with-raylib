#include "stdio.h"

#include "raylib.h"


enum block_types {
    NORMAL,
    FIZZ,
    BUZZ,
    FIZZBUZZ,
    LAST_BLOCK_TYPE
};

int     FONT_SIZE = 18;
typedef struct {
    int       starti;
    float     w;
    float     h;
    float     block_w;
    float     block_h;
    char    title[255];
} WinProps;

void normal(float x, float y, float w, float h, int n);
void fizz(float x, float y, float w, float h, int n);
void buzz(float x, float y, float w, float h, int n);
void fizzbuzz(float x, float y, float w, float h, int n);

void (*drawblock[LAST_BLOCK_TYPE])(float x, float y, float w, float h, int n) =
{
    normal,
    fizz,
    buzz,
    fizzbuzz
};



void normal(float x, float y, float w, float h, int n)
{
    char text[100];
    sprintf(text, "%d\0",n);
    Vector2 text_size = MeasureTextEx(GetFontDefault(), text, FONT_SIZE, 0.5);
    
    Vector2 text_vec = {
        .x = (text_size.x / 2) + x + w/4, 
        .y = (text_size.y / 2) + y + h/4
    };
    DrawRectangle(x, y, w, h, GetColor(0x55e986ff));
    DrawRectangleLines(x, y, w, h, GetColor(0x005f5fff));
    DrawTextEx(GetFontDefault(), text, text_vec, FONT_SIZE, 0.5, RED);
}

void fizz(float x, float y, float w, float h, int n)
{
    char *text = "FIZZ";
    Vector2 text_size = MeasureTextEx(GetFontDefault(), text, FONT_SIZE, 0.5);
    
    Vector2 text_vec = {
        .x = (text_size.x / 2) + x, 
        .y = (text_size.y / 2) + y + h/4
    };
    DrawRectangleLines(x, y, w, h, GetColor(0x005f5fff));
    DrawTextEx(GetFontDefault(), text, text_vec, FONT_SIZE, 0.5, RAYWHITE);
}

void buzz(float x, float y, float w, float h, int n)
{
    char *text = "BUZZ";
    Vector2 text_size = MeasureTextEx(GetFontDefault(), text, FONT_SIZE, 0.5);
    
    Vector2 text_vec = {
        .x = (text_size.x / 2) + x, 
        .y = (text_size.y / 2) + y + h/4
    };
    DrawRectangle(x, y, w, h, RAYWHITE);
    DrawRectangleLines(x, y, w, h, WHITE);
    DrawTextEx(GetFontDefault(), text, text_vec, FONT_SIZE, 0.5, BLACK);
}

void fizzbuzz(float x, float y, float w, float h, int n)
{
    char *text = "FizzBuzZ";
    Vector2 text_size = MeasureTextEx(GetFontDefault(), text, FONT_SIZE, 0.5);
    
    Vector2 text_vec = {
        .x = x + 10,  
        .y = (text_size.y / 2) + y + h/4
    };
    DrawRectangleGradientEx((Rectangle) {x, y, w, h}, BLACK, RAYWHITE, BLUE, LIME);
    DrawRectangleLines(x, y, w, h, WHITE);
    DrawTextEx(GetFontDefault(), text, text_vec, FONT_SIZE, 0.5, ORANGE);
}


void
update(WinProps *win)
{

    win->w =  GetScreenWidth();
    win->h =  GetScreenHeight();

    win->block_w = win->w / 10;
    win->block_h = win->h / 10;
    FONT_SIZE = win->w / 50;


    if (IsKeyPressed(KEY_UP)){
        ++win->starti;
    }
    if (IsKeyPressed(KEY_DOWN)){
        --win->starti;
    }

}

void
draw(WinProps *win)
{
    for (int j = 0; j < 10; ++j)
    {
        for(int k = 0; k < 10; ++k)
        {
           int current_block = (j * 10) + k + win->starti;

           int is;

           if (current_block % 5 == 0 && current_block % 3 == 0)
           {
                is = FIZZBUZZ;
           }
           
           else if (current_block % 5 == 0)
           {
                is = BUZZ;
           }
           else if (current_block % 3 == 0)
           {
                is = FIZZ;
           }
           else {
                is = NORMAL;
           }


           drawblock[is](
                        k * win->block_w,
                        j * win->block_h,
                        win->block_w,
                        win->block_h,
                        current_block);


        }
    }
    

}

int main(void)
{
    WinProps    win = {
        .w = 900,
        .h = 600,
        .title = "Raylib Fizz Buzz Blocks",
        .starti = 1
    };

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(win.w, win.h, win.title);
    SetTargetFPS(30);

    while(!WindowShouldClose()){

        update(&win);


        BeginDrawing();

            ClearBackground(BLACK);
            draw(&win);
        EndDrawing();
    }


    CloseWindow();
    return 0;
}
