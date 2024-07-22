#pragma once

#include <specdefvals_core.h>

_SDL_BEGIN

#define _STRINGIFY(any) #any 

#pragma warning(push)
#pragma warning(disable : 6297)
#pragma warning(disable : 4334)

_SDL_FUNC long_pos_number upper_power_of_two(long_pos_number _number) {

	small_pos_num sn = 3;

	while (_number > (1 << sn)) {
		sn++;
	}

	return (1 << sn);

}

#pragma warning(pop)

_SDL_FUNC void string_copy(char_ptr _destination, const_char_ptr _source) {

	index _idx = _NULL;

	while (_source[_idx]) {

		_destination[_idx] = _source[_idx];

		_idx += _ONE;
	}

	_destination[_idx] = _TERM_NULL;

}

_SDL_FUNC void string_copy(char_ptr _destination, const_char_ptr _source, char_count _count, index _idx) {

	for (index _iter = _NULL; _iter < _count; _iter++ ) {

		_destination[_iter] = _source[_idx + _iter];
	}

	_destination[_count] = _TERM_NULL;

}

_SDL_FUNC char_count string_length(const_char_ptr _string) {

	char_count length = _NULL;

	while (_string[length++]);

	return --length;

}

_SDL_FUNC void string_concat(char_ptr _destination, const_char_ptr _source) {

	index _dest_idx = static_cast<index>(string_length(_destination));

	index _src_idx = _NULL;

	while (_source[_src_idx]) {

		_destination[_dest_idx] = _source[_src_idx];

		_dest_idx += _ONE;
		_src_idx  += _ONE;
	}

	_destination[_dest_idx] = _TERM_NULL;

}

_SDL_FUNC const_char_ptr string_string(const_char_ptr _string, const_char_ptr _substring) {

	while (*_string) {

		const_char_ptr _copy_string = _string;

		const_char_ptr _copy_substring = _substring;

		while (*_copy_string == *_copy_substring && (*_copy_string != _TERM_NULL && *_copy_substring != _TERM_NULL)) {

			_copy_string++;

			_copy_substring++;

		}

		if (*(_copy_substring) == _TERM_NULL) {

			break;

		}

		_string++;

	}

	if (*_string != _TERM_NULL) {

		return _string;

	}

	return nullptr;

}

_SDL_FUNC const_char_ptr string_char(const_char_ptr _string, char _ch) {

	while (*_string != _ch && *_string != _TERM_NULL) {

		_string++;

	}

	if (*_string != _TERM_NULL) {

		return _string;
	}

	return nullptr;

}

_SDL_FUNC small_num string_compare(const_char_ptr _lhs, const_char_ptr _rhs) {

	char_count _lhs_length = string_length(_lhs);

	char_count _rhs_length = string_length(_rhs);

	char_count _shorter_length = (_lhs_length < _rhs_length) ? _lhs_length : _rhs_length;

	for (index _idx = _NULL; _idx < _shorter_length; _idx++) {

		if (_lhs[_idx] > _rhs[_idx]) {

			return _ONE;

		}
		else if (_lhs[_idx] < _rhs[_idx]) {

			return _M_ONE;

		}

	}

	if (_lhs_length == _rhs_length) {

		return _NULL;

	}

	return (_shorter_length == _lhs_length) ? _M_ONE : _ONE;

}

_SDL_2TMP
_SDL_FUNC void elz_insert(T& _col, size _col_size, const D& _elz, size _elz_size = _ONE, index _from = _NULL) {

	for (index _iter = static_cast<index>(_col_size - _ONE); _iter >= _from; _iter--) {

		_col[_iter + static_cast<index>(_elz_size)] = _col[_iter];

	}

	for (index _iter = _from; _iter < _from + _elz_size; _iter++) {

		_col[_iter] = _elz[_iter - _from];

	}

}

_SDL_TMP
_SDL_FUNC void elz_erase(T& _col, size _col_size, size _erase_count, index _from) {

	for (index _iter = _from; _iter < _col_size; _iter++) {

		_col[_iter] = _col[_iter + static_cast<index>(_erase_count)];

	}

}

_SDL_2TMP
_SDL_FUNC void set_defvals(T& _col, size _col_size, const D& _def_val, index _from = _NULL) {

	for (index _iter = _from; _iter < _col_size; _iter++) {

		_col[_iter] = _def_val;

	}

}

_SDL_TMP
_SDL_FUNC T&& move(T& arg) {

	return static_cast<T&&>(arg);

}

_SDL_TMP
_SDL_FUNC T&& move(T&& arg) {

	return static_cast<T&&>(arg);

}

_SDL_TMP
_SDL_FUNC void swap(T& lhs, T& rhs) {

	T buff = lhs;

	lhs = rhs;

	rhs = buff;

}

_SDL_END