
start api:

uvicorn main:app --host 0.0.0.0 --port 8000 --reload


## Requirements

To build and run `tictactoe3`, make sure the following dependencies are installed:

- C compiler with C11 support (e.g., `gcc`, `clang`)
- CMake >= 3.10
- [SDL2](https://www.libsdl.org/)
- [SDL2_mixer](https://www.libsdl.org/projects/SDL_mixer/)
- [SDL2_image](https://www.libsdl.org/projects/SDL_image/)
- [libcurl](https://curl.se/libcurl/)
- [cJSON](https://github.com/DaveGamble/cJSON)
- `pkg-config`

### macOS (Homebrew)
```bash
brew install sdl2 sdl2_mixer sdl2_image curl cjson pkg-config