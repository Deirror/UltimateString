#pragma once

#include <specdefvals_core>
#include <sdlexcept>

_SDL_BEGIN

typedef class comparer {

public:
	_SDL_FUNC comparer() = default;

	_SDL_FUNC comparer(small_num _number) {

		set_res(_number);

	}

	_SDL_FUNC bool is_greater() const {

		return _compr_res == _ONE;

	}

	_SDL_FUNC bool is_equal() const {

		return _compr_res == _NULL;

	}

	_SDL_FUNC bool is_less() const {

		return _compr_res == _M_ONE;

	}

	_SDL_FUNC void set_res(small_num _number) {

		if (_number >= _M_ONE && _number <= _ONE) {

			_compr_res = _number;

		}
		else {

			_THROW_DEXCEPTION(invalid_args, "Given number is not in the range!");

		}
		
	}

	_SDL_FUNC small_num get_res() const {

		return _compr_res;

	}

	_SDL_FUNC _SDL_FR sdl::dostream& operator<<(sdl::dostream& dos, const comparer& other) {

		return dos << other._compr_res;

	}

private:
	small_num _compr_res = _NULL;

} compr;

_SDL_END