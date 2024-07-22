#pragma once

#include <specdefvals_core.h>
#include <specfuncs_core.h>
#include <sdliterator.h>
#include <sdlexcept.h>
#include <sdlios.h>
#include <compr.h>

/*
DEIRROR'S STRING -> dstring
*/

_SDL_BEGIN

#define _DEFAULT_CAPACITY _OCT
#define _FACTOR _BIN
#define _DOWN_FACTOR _QUAT

#define _NOT_FOUND _M_ONE

typedef class dstring {

public:
	_SDL_FUNC dstring() : _capacity(_DEFAULT_CAPACITY) {

		_ALLOCATE_NEW_ARRAY(_data, char, _capacity + _ONE);

		*(_data) = _TERM_NULL;

	}

	_SDL_FUNC dstring(const_char_ptr _new_data) {
	
		_length = string_length(_new_data);

		_capacity = upper_power_of_two(_length);

		_ALLOCATE_NEW_ARRAY(_data, char, _capacity + _ONE);

		string_copy(_data, _new_data);
	
	}

	_SDL_FUNC dstring(const dstring& other) {

		copy_from(other);

	}

	_SDL_FUNC dstring& operator=(const dstring& other) {

		if (this != &other) {

			free();

			copy_from(other);

		}

		return *this;

	}

	_SDL_FUNC dstring(dstring&& other) noexcept {

		move_from(sdl::move(other));

	}

	_SDL_FUNC dstring& operator=(dstring&& other) noexcept {

		if (this != &other) {

			free();

			move_from(sdl::move(other));

		}

		return *this;

	}

	_SDL_FUNC ~dstring() noexcept {

		free();

	}


	_SDL_FUNC char_count length() const {

		return _length;

	}

	_SDL_FUNC char_count capacity() const {

		return _capacity;

	}

	_SDL_FUNC const_char_ptr data() const {

		return _data;

	}

	_SDL_FUNC const_char_ptr d_str() const {

		return _data;

	}

	_SDL_FUNC char_count max_size() const {

		return _SIZE_MAX / sizeof(char);

	}


	_SDL_FUNC void push_back(const char _ch) {

		if (_length == _capacity) {

			resize(_capacity * _FACTOR);

		}

		_data[_length++] = _ch;

	}

	_SDL_FUNC void pop_back() {

		if (_length * _DOWN_FACTOR == _capacity) {

			resize(_capacity / _FACTOR);

		}

		_data[--_length] = _TERM_NULL;

	}

	_SDL_FUNC char& back() {

		return _data[_length - _ONE];

	}

	_SDL_FUNC const char& back() const {

		return _data[_length - _ONE];

	}


	_SDL_FUNC dstring& operator+=(const dstring& other) {

		char_count _new_length = _length + other._length;

		if (_new_length > _capacity) {

			resize(upper_power_of_two(_new_length));

		}

		string_concat(_data, other._data);

		_length = _new_length;

		return *this;
	}

	_SDL_FUNC dstring& operator+=(char _ch) {

		push_back(_ch);

		return *this;

	}

	_SDL_FUNC _SDL_FR dstring operator+(const dstring& lhs, const dstring& rhs) {

		dstring res(lhs._length + rhs._length);

		res += lhs;

		res += rhs;

		return res;

	}

	_SDL_FUNC dstring& append(const dstring& other) {

		return this->operator+=(other);

	}


	_SDL_FUNC _SDL_FR sdl::dostream& operator<<(sdl::dostream& dos, const dstring& other) {

		return dos << other._data;

	}

	_SDL_FUNC _SDL_FR sdl::distream& operator>>(sdl::distream& dis, dstring& other) {

		buffer _buff;

		sdl::dcin >> _buff;

		char_count _length = string_length(_buff);

		if (_length > other._capacity) {

			other.resize(upper_power_of_two(_length));

		}

                other._length = _length; 

		string_copy(other._data, _buff);

		return dis;

	}


	_SDL_FUNC char& operator[](index _idx) {

		return _data[_idx];

	}

	_SDL_FUNC const char& operator[](index _idx) const {

		return _data[_idx];

	}

	_SDL_FUNC char& at(index _idx) {

		if (_idx >= _length) {

			_THROW_DEXCEPTION(out_of_range, "Index out of range");

		}

		return _data[_idx];

	}

	_SDL_FUNC const char& at(index _idx) const {

		if (_idx >= _length) {

			_THROW_DEXCEPTION(out_of_range, "Index out of range");

		}

		return _data[_idx];

	}

	_SDL_FUNC char& front() {
	
		if (_length == _NULL) {

			_THROW_DEXCEPTION(empty_dexcept, "Empty string");

		}

		return _data[_NULL];

	}

	_SDL_FUNC const char& front() const {
	
		if (_length == _NULL) {

			_THROW_DEXCEPTION(empty_dexcept, "Empty string");

		}

		return _data[_NULL];

	}


	_SDL_FUNC void assign(const dstring& other) {

		assign(other._data);

	}

	_SDL_FUNC void assign(const_char_ptr _ptr) {

		if (!_ptr) {

			_THROW_DEXCEPTION(nullptr_dexcept, "Nullptr");

		}

		char_count _ptr_length = string_length(_ptr);

		_length = _ptr_length;

		_capacity = upper_power_of_two(_length);

		_DELETE_ARRAY(_data);

		_ALLOCATE_NEW_ARRAY(_data, char, _capacity + _ONE);

		string_copy(_data, _ptr);

	}


	_SDL_FUNC compr compare(const dstring& other) const {

		return string_compare(_data, other._data);

	}

	_SDL_FUNC void copy_to(char_ptr& _ptr, index _start_idx, char_count _count) const {

		if (_CSTYLE_CAST(unsigned long long, _ptr) == 0xcccccccccccccccc) {

			_THROW_DEXCEPTION(invalid_args, "Pointer not set/invalid adress");
		
		}

		if (_start_idx + _count > _length) {

			_THROW_DEXCEPTION(invalid_args, "Indexes are invalid");

		}

		_DELETE_ARRAY(_ptr);

		//Please delete the allocated memory!!!
		_ALLOCATE_NEW_ARRAY(_ptr, char, _count + _ONE);

		string_copy(_ptr, _data, _count, _start_idx);

	}

	_SDL_FUNC dstring& erase(index _from) {

		if (_from >= _length) {

			_THROW_DEXCEPTION(out_of_range, "Index out of range");

		}

		char_count _erase_count = (_length - _from);

		set_defvals(*this, _length, _TERM_NULL, static_cast<index>(_length - _erase_count));

		down_size(_erase_count);

		return *this;

	}

	_SDL_FUNC dstring& erase(index _from, char_count _count) {

		if (_from + _count > _length) {

			_THROW_DEXCEPTION(out_of_range, "Too many characters to erase");

		}

		elz_erase(*this, _length, _count, _from);

		set_defvals(*this, _length, _TERM_NULL, static_cast<index>(_length - _count));

		down_size(_count);

		return *this;

	}

	_SDL_FUNC dstring& trim(const dstring& exclude) {

		return trim(exclude._data);

	}

	_SDL_FUNC dstring& trim(const_char_ptr _exclude) {

		if (!_exclude) {

			_THROW_DEXCEPTION(nullptr_dexcept,"Nullptr");

		}

		char_count _exclude_length = string_length(_exclude);

		for (index _iter = _NULL; _iter < _exclude_length; _iter++) {

			for (index _idx = _NULL; _idx < _length; _idx++) {

				if (_exclude[_iter] == _data[_idx]) {

					erase(_idx, _ONE);

				}

			}

		}

		return *this;

	}

	_SDL_FUNC dstring& trim(char _exclude) {

		char _arr_exclude_ch[_BIN]{};

		_arr_exclude_ch[_NULL] = _exclude;

		return trim(_arr_exclude_ch);

	}

	_SDL_FUNC dstring to_upper() const {

		dstring result = *this;

		for (index _iter = _NULL; _iter < result._length; _iter++) {

			if (result._data[_iter] >= _STR_LOWER && result._data[_iter] <= _END_LOWER) {

				result._data[_iter] -= _LOW_UP_DIFF;

			}

		}

		return result;

	}

	_SDL_FUNC dstring to_lower() const {

		dstring result = *this;

		for (index _iter = _NULL; _iter < result._length; _iter++) {

			if (result._data[_iter] >= _STR_UPPER && result._data[_iter] <= _END_UPPER) {

				result._data[_iter] += _LOW_UP_DIFF;

			}

		}

		return result;

	}


	_SDL_FUNC index find(const dstring& searched, index _from = _NULL) const {

		return find(searched._data, _from);

	}

	_SDL_FUNC index find(const_char_ptr _ptr, index _from = _NULL) const {

		if (_from >= _length) {

			return _NOT_FOUND;

		}

		const_char_ptr _result = sdl::string_string(_data + _from, _ptr);

		return _result ? static_cast<index>(_result - _data) : _NOT_FOUND;

	}

	_SDL_FUNC index find(char _ch, index _from = _NULL) const {

		if (_from >= _length) {

			return _NOT_FOUND;

		}

		const_char_ptr _result = sdl::string_char(_data + _from, _ch);

		return _result ? static_cast<index>(_result - _data) : _NOT_FOUND;

	}


	_SDL_FUNC index rfind(const dstring& searched, index _from = _NULL) const {

		return rfind(searched._data, _from);

	}

	_SDL_FUNC index rfind(const_char_ptr _ptr, index _from = _NULL) const {

		if (_from >= _length) {

			return _NOT_FOUND;

		}

		for (index _iter = static_cast<index>(_length - _ONE); _iter >= _from; _iter--) {

			if (sdl::string_string(_data + _iter, _ptr)) {

				return _iter;

			}

		}

		return _NOT_FOUND;

	}

	_SDL_FUNC index rfind(char _ch, index _from = _NULL) const {

		if (_from >= _length) {

			return _NOT_FOUND;

		}

		char _arr_ch[_BIN]{};

		_arr_ch[_NULL] = _ch;

		return rfind(_arr_ch, _from);

	}


	_SDL_FUNC index find_first_of(const dstring& searched, index _from = _NULL) const {

		return find_first_of(searched._data, _from);

	}

	_SDL_FUNC index find_first_of(const_char_ptr _ptr, index _from = _NULL) const {

		if (_from >= _length) {

			return _NOT_FOUND;

		}

		char_count _ptr_length = string_length(_ptr);

		for (index _iter = _NULL; _iter < _ptr_length; _iter++) {

			const_char_ptr _result = sdl::string_char(_data + _from, *(_ptr + _iter));

			if (_result) {

				return static_cast<index>(_result - _data);

			}

		}
		
		return _NOT_FOUND;

	}

	_SDL_FUNC index find_first_of(char _ch, index _from = _NULL) const {

		return find(_ch, _from);

	}


	_SDL_FUNC index find_first_not_of(const dstring& searched, index _from = _NULL) const {

		return find_first_not_of(searched._data, _from);

	}

	_SDL_FUNC index find_first_not_of(const_char_ptr _ptr, index _from = _NULL) const {

		if (_from >= _length) {

			return _NOT_FOUND;

		}

		for (index _iter = _NULL; _iter < _length; _iter++) {

			if (!string_char(_ptr, _data[_iter])) {

				return _iter;

			}

		}

		return _NOT_FOUND;

	}

	_SDL_FUNC index find_first_not_of(char _ch, index _from = _NULL) const {

		if (_from >= _length) {

			return _NOT_FOUND;

		}

		char _arr_ch[_BIN]{};

		_arr_ch[_NULL] = _ch;

		return find_first_not_of(_arr_ch, _from);

	}


	_SDL_FUNC index find_last_of(const dstring& searched, index _from = _NULL) const {

		return find_last_of(searched._data, _from);

	}

	_SDL_FUNC index find_last_of(const_char_ptr _ptr, index _from = _NULL) const {

		if (_from >= _length) {

			return _NOT_FOUND;

		}

		char_count _ptr_length = string_length(_ptr);

		for (index _iter = static_cast<index>(_ptr_length - _ONE); _iter >= _from; _iter--) {

			const_char_ptr _result = sdl::string_char(_data + _from, *(_ptr + _iter));

			if (_result) {

				return static_cast<index>(_result - _data);

			}

		}

		return _NOT_FOUND;

	}

	_SDL_FUNC index find_last_of(char _ch, index _from = _NULL) const {

		if (_from >= _length) {

			return _NOT_FOUND;

		}

		char _arr_ch[_BIN]{};

		_arr_ch[_NULL] = _ch;

		return find_last_of(_arr_ch, _from);

	}


	_SDL_FUNC index find_last_not_of(const dstring& searched, index _from = _NULL) const {

		return find_last_not_of(searched._data, _from);

	}

	_SDL_FUNC index find_last_not_of(const_char_ptr _ptr, index _from = _NULL) const {

		if (_from >= _length) {

			return _NOT_FOUND;

		}

		for (index _iter = static_cast<index>(_length - _ONE); _iter >= _from; _iter--) {

			if (!string_char(_ptr, _data[_iter])) {

				return _iter;

			}

		}

		return _NOT_FOUND;

	}

	_SDL_FUNC index find_last_not_of(char _ch, index _from = _NULL) const {

		if (_from >= _length) {

			return _NOT_FOUND;

		}

		char _arr_ch[_BIN]{};

		_arr_ch[_NULL] = _ch;

		return find_last_not_of(_arr_ch, _from);

	}

	_SDL_FUNC bool contains(const_char_ptr _ptr) const {

		return (find(_ptr) != _NOT_FOUND);

	}

	_SDL_FUNC bool contains(char _ch) const {

		return (find(_ch) != _NOT_FOUND);

	}

	using iterator = sdl_iterator<char>;
	using const_iterator = sdl_const_iterator<const char>;

	using reversed_iterator = sdl_reverse_iterator<char>;
	using const_reversed_iterator = sdl_const_reverse_iterator<char>;

	_SDL_FUNC iterator begin() const {

		return iterator(_data);

	}

	_SDL_FUNC iterator end() const {

		return iterator(_data + _length);

	}

	_SDL_FUNC const_iterator cbegin() const {

		return const_iterator(_data);

	}

	_SDL_FUNC const_iterator cend() const {

		return const_iterator(_data + _length);

	}


	_SDL_FUNC reversed_iterator rbegin() const {

		return reversed_iterator(_data + _length - _ONE);

	}

	_SDL_FUNC reversed_iterator rend() const {

		return reversed_iterator(_data - _ONE);

	}

	_SDL_FUNC const_reversed_iterator crbegin() const {

		return const_reversed_iterator(_data + _length - _ONE);

	}

	_SDL_FUNC const_reversed_iterator crend() const {

		return const_reversed_iterator(_data - _ONE);

	}


	_SDL_FUNC void reserve(char_count _new_length) {

		if (upper_power_of_two(_new_length) > _capacity) {

			resize(upper_power_of_two(_new_length));

		}

	}
	
	_SDL_FUNC void shrink_to_fit() {

		if (upper_power_of_two(_length) < _capacity) {

			resize(upper_power_of_two(_length));

		}

	}


	_SDL_FUNC dstring& insert(const dstring& other, index _from = _NULL) {

		return insert(other._data, _from);;

	}

	_SDL_FUNC dstring& insert(const_char_ptr _ptr, index _from = _NULL) {

		if (_from > _length) {

			_THROW_DEXCEPTION(out_of_range,"Index out of range");

		}

		char_count _ptr_length = string_length(_ptr);

		if (_ptr_length + _length > _capacity) {

			resize(upper_power_of_two(_ptr_length + _length));

		}

		elz_insert(*this, _length, _ptr, _ptr_length, _from);

		_length += _ptr_length;

		return *this;
	}

	_SDL_FUNC dstring& replace(const dstring& searched, const dstring& replace_with, index _from = _NULL) {

		return replace(searched._data, replace_with._data, _from);

	}

	_SDL_FUNC dstring& replace(const_char_ptr _searched, const_char_ptr _replace_with, index _from = _NULL) {

		if (_from > _length) {

			_THROW_DEXCEPTION(out_of_range, "Index out of range");

		}

		index _idx = _from;

		char_count _searched_length = string_length(_searched);

		while (_idx <= _length) {

			_idx = find(_searched, _idx);

			if (_idx == _NOT_FOUND) {

				break;

			}

			erase(_idx, _searched_length);

			insert(_replace_with, _idx);

		}

		return *this;

	}

	_SDL_FUNC dstring& replace(char _searched, char _replace_with, index _from = _NULL) {

		char _arr_searched_ch[_BIN]{};

		_arr_searched_ch[_NULL] = _searched;

		char _arr_replace_with_ch[_BIN]{};

		_arr_replace_with_ch[_NULL] = _replace_with;

		return replace(_arr_searched_ch, _arr_replace_with_ch, _from);

	}


	_SDL_FUNC dstring subdstr(index _from, char_count _count) const {

		if (_from + _count > _length) {

			_THROW_DEXCEPTION(out_of_range, "Length out of range");

		}

		dstring result;

		char_count _length = _from + _count;

		for (index _iter = _from; _iter < _length; _iter++) {

			result += _data[_iter];

		}

		return result;

	}

	_SDL_FUNC void swap(dstring& other) {

		sdl::swap(*this, other);

	}

	_SDL_FUNC bool empty() const {

		return _length == _NULL;

	}

	_SDL_FUNC void clear() {

		_length = _NULL;

		_capacity = _DEFAULT_CAPACITY;

		_DELETE_ARRAY(_data);

		_ALLOCATE_NEW_ARRAY(_data, char, _capacity + _ONE);

		*(_data) = _TERM_NULL;

	}

private:
	_SDL_FUNC _SDL_EXPL dstring(char_count _length) {
		
		_capacity = upper_power_of_two(_length);

		_ALLOCATE_NEW_ARRAY(_data, char, _capacity + _ONE);

	}

	_SDL_FUNC void down_size(char_count _count) {

		for (char_count _iter = _NULL; _iter <= _count; _iter++) {

			if (_length * _DOWN_FACTOR == _capacity) {

				resize(upper_power_of_two(_capacity / _FACTOR));

			}

			_length--;

		}

		_length++;

	}

	_SDL_FUNC void free() {

		_DELETE_ARRAY(_data);

		_data = _NULLPTR;

		_length = _capacity = _NULL;

	}

	_SDL_FUNC void copy_from(const dstring& other) {
			
		_length = other._length;

		_capacity = other._capacity;

		_ALLOCATE_NEW_ARRAY(_data, char, _capacity + _ONE);

		string_copy(_data, other._data);

	}

	_SDL_FUNC void move_from(dstring&& other) {

		_length = other._length;

		_capacity = other._capacity;

		other._length = other._capacity = _NULL;

		_data = other._data;

		other._data = _NULLPTR;

	}

	_SDL_FUNC void resize(char_count _new_capacity) {

		if (_capacity == _new_capacity) {

			return;

		}

		char_ptr _resized_data = _NULLPTR; 

		_ALLOCATE_NEW_ARRAY(_resized_data, char, _new_capacity + _ONE);

		string_copy(_resized_data, _data);

		_DELETE_ARRAY(_data);

		_data = _resized_data;

		_capacity = _new_capacity;

	}

private:
	char_ptr _data = _NULLPTR;

	char_count _length = _NULL;

	char_count _capacity = _NULL;

} ultimate_string;

_SDL_FUNC bool operator==(const dstring& lhs, const dstring& rhs) {

	return string_compare(lhs.d_str(), rhs.d_str()) == _NULL;

}

_SDL_FUNC bool operator!=(const dstring& lhs, const dstring& rhs) {

	return !(lhs == rhs);

}

_SDL_FUNC bool operator<(const dstring& lhs, const dstring& rhs) {

	return string_compare(lhs.d_str(), rhs.d_str()) < _NULL;

}

_SDL_FUNC bool operator<=(const dstring& lhs, const dstring& rhs) {

	return string_compare(lhs.d_str(), rhs.d_str()) <= _NULL;

}

_SDL_FUNC bool operator>(const dstring& lhs, const dstring& rhs) {

	return string_compare(lhs.d_str(), rhs.d_str()) > _NULL;

}

_SDL_FUNC bool operator>=(const dstring& lhs, const dstring& rhs) {

	return string_compare(lhs.d_str(), rhs.d_str()) >= _NULL;

}

_SDL_END
