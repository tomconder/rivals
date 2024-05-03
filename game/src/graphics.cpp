#include <SDL.h>
#include <SDL_image.h>
#include "graphics.h"

void Graphics::blitSurface(SDL_Texture *texture, SDL_Rect *srcrect, SDL_Rect *dstrect) {
    SDL_RenderCopy(renderer, texture, srcrect, dstrect);
}

void Graphics::cleanup() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void Graphics::clear() {
    SDL_SetRenderDrawColor(renderer, 90, 90, 90, 255);
    SDL_RenderClear(renderer);
}

void Graphics::create(int w, int h) {
    SDL_CreateWindowAndRenderer(w,
                                h,
                                SDL_RENDERER_ACCELERATED,
                                &window,
                                &renderer);
}

void Graphics::flip() {
    SDL_RenderPresent(renderer);
}

SDL_Surface *Graphics::loadImage(const std::string &file) {
    if (images.count(file) == 0) {
        images[file] = IMG_Load(file.c_str());
    }
    return images[file];
}

SDL_Renderer *Graphics::getRenderer() const {
    return renderer;
}

SDL_Window *Graphics::getWindow() const {
    return window;
}

void Graphics::setWindowTitle(const std::string &title) {
    SDL_SetWindowTitle(window, title.c_str());
}
