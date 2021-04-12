#ifndef INCLUDE_GRAPHICS_H
#define INCLUDE_GRAPHICS_H

#include <SDL.h>
#include <map>
#include <string>

class Graphics {
public:
    void blitSurface(SDL_Texture *source, SDL_Rect *srcrect, SDL_Rect *dstrect);
    void cleanup();
    void clear();
    void create(int w, int h);
    void flip();

    SDL_Surface *loadImage(const std::string &file);
    SDL_Renderer *getRenderer() const;
    SDL_Window *getWindow() const;

    void setWindowTitle(const std::string &title);

private:
    SDL_Window *window;
    SDL_Renderer *renderer;

    std::map<std::string, SDL_Surface *> images;
};

#endif //INCLUDE_GRAPHICS_H
