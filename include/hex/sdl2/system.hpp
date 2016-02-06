#ifndef HEX_SDL2_SYSTEM_HPP_
#define HEX_SDL2_SYSTEM_HPP_

namespace hex { namespace sdl2 {

template <unsigned int I>
class System {
public:
	System () : _result(-1) {
		init();
	}

	virtual ~System () {
		quit();
	}

	bool init() {
		_result = SDL_InitSubSystem(I);
		return valid();
	}

	void quit() {
		SDL_QuitSubSystem(I);
	}

	bool valid() const { return (_result == 0); }

private:
	int _result;
};

} /* sdl2 */ } /* hex */

#endif // HEX_SDL2_SYSTEM_HPP_
