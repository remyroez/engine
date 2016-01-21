#ifndef HEX_SDL2_WINDOW_HPP_
#define HEX_SDL2_WINDOW_HPP_

#include <utility>

#include <SDL2/SDL.h>

namespace hex { namespace sdl2 {

class Window {
public:
	// default ctor
	Window () : _data(nullptr) {}

	// ctor
	template <typename... Args>
	Window(Args&&... args) {
		create(std::forward<Args>(args)...);
	}

	// dtor
	virtual ~Window () {
		destroy();
	}

	// SDL_CreateWindow
	bool create(const char *title, int x, int y, int w, int h, unsigned int flags) {
		_data = SDL_CreateWindow(title, x, y, w, h, flags);
		return valid();
	}

	// SDL_DestroyWindow
	void destroy() {
		SDL_DestroyWindow(_data);
		_data = nullptr;
	}

	// return raw data.
	const SDL_Window *data() const { return _data; }

	// data validation.
	bool valid() const { return (_data != nullptr); }

private
	// raw data
	SDL_Window *_data;
};

} /* sdl2 */ } /* hex */

#endif // HEX_SDL2_WINDOW_HPP_
