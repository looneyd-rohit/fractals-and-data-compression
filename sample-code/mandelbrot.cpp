#include "SDL2/SDL.h"
#include <complex>
#include <numeric>

using namespace std;

#define MAX_ITERATIONS 25

double lerp(double a, double b, double t) { return a + t * (b - a); }

int is_in_set(complex<double> c) {
  complex<double> z(0, 0);
  for (int i = 0; i < MAX_ITERATIONS; i++) {
    z = pow<double>(z, 2) + c;
    if (norm(z) > 10) {
      return i;
    }
  }
  return 0;
}

int main() {
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;
  SDL_CreateWindowAndRenderer(2000, 2000, 0, &window, &renderer);
  SDL_RenderSetScale(renderer, 2, 2);

  for (double x = 0.0; x < 1.0; x += 0.001) {
    for (double y = 0.0; y < 1.0; y += 0.001) {
      double point_x = lerp(-2.0, 2.0, x);
      double point_y = lerp(-2.0, 2.0, y);
      int iterations = is_in_set(complex<double>(point_x, point_y));
      if (iterations == 0) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawPointF(renderer, x * 1000, y * 1000);
      } else {
        SDL_SetRenderDrawColor(renderer, 255 - iterations, 255 - iterations,
                               255 - iterations, 255);
        SDL_RenderDrawPointF(renderer, x * 1000, y * 1000);
      }
    }
  }

  SDL_RenderPresent(renderer);
  SDL_Delay(10000);

  return 0;
}