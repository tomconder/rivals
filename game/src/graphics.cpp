#include "graphics.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <SDL.h>
#include <filesystem>
#include <iostream>

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
    int origFormat;
    constexpr int depth = 32;
    int height;
    int width;
    constexpr int channels = STBI_rgb_alpha;

    const std::filesystem::path name{ file };

    void *data = stbi_load(name.string().data(), &width, &height, &origFormat, channels);

    if (data == nullptr) {
        // error loading image
        std::cout << "loadImage failed: " << name.string().data() << std::endl;
        return nullptr;
    }

    if (images.count(file) == 0) {

#if SDL_BYTEORDER == SDL_LIL_ENDIAN
    constexpr uint32_t rmask = 0x000000FF;
    constexpr uint32_t gmask = 0x0000FF00;
    constexpr uint32_t bmask = 0x00FF0000;
    constexpr uint32_t amask = 0xFF000000;
#else
    constexpr uint32_t rmask = 0xFF000000;
    constexpr uint32_t gmask = 0x00FF0000;
    constexpr uint32_t bmask = 0x0000FF00;
    constexpr uint32_t amask = 0x000000FF;
#endif

    images[file] =
        SDL_CreateRGBSurfaceFrom(data, width, height, depth, channels * width,
                                 rmask, gmask, bmask, amask);
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
