#pragma once

#include <specdefvals_core.h>

template<typename T>
class sdl_iterator {

public:
    _SDL_FUNC sdl_iterator(T* _it) : _it(_it) {}

    _SDL_FUNC sdl_iterator& operator++() {

        ++_it;

        return *this;

    }

    _SDL_FUNC sdl_iterator operator++(int) {
        
        sdl_iterator temp = *this;

        ++_it;

        return temp;

    }

    _SDL_FUNC sdl_iterator& operator--() {

        --_it;

        return *this;

    }

    _SDL_FUNC sdl_iterator operator--(int) {

        sdl_iterator temp = *this;

        --_it;

        return temp;

    }

    _SDL_FUNC bool operator==(const sdl_iterator& other) const {

        return _it == other._it;

    }

    _SDL_FUNC bool operator!=(const sdl_iterator& other) const {

        return _it != other._it;

    }

    _SDL_FUNC T& operator*() const {

        return *_it;

    }

    _SDL_FUNC T* operator->() const {

        return &(*_it);

    }

private:
    T* _it;

};

template<typename T>
class sdl_const_iterator {

public:
    _SDL_FUNC sdl_const_iterator(const T* _it) : _it(_it) {}

    _SDL_FUNC sdl_const_iterator& operator++() {

        ++_it;

        return *this;

    }

    _SDL_FUNC sdl_const_iterator operator++(int) {

        sdl_const_iterator temp = *this;

        ++_it;

        return temp;

    }

    _SDL_FUNC sdl_const_iterator& operator--() {

        --_it;

        return *this;

    }

    _SDL_FUNC sdl_const_iterator operator--(int) {

        sdl_iterator temp = *this;

        --_it;

        return temp;

    }

    _SDL_FUNC bool operator==(const sdl_const_iterator& other) const {

        return _it == other._it;

    }

    _SDL_FUNC bool operator!=(const sdl_const_iterator& other) const {

        return _it != other._it;

    }

    _SDL_FUNC const T& operator*() const {

        return *_it;

    }

    _SDL_FUNC const T* operator->() const {

        return &(*_it);

    }

private:
    const T* _it;

};

#pragma once

template<typename T>
class sdl_reverse_iterator {

public:
    _SDL_FUNC sdl_reverse_iterator(T* _it) : _it(_it) {}

    _SDL_FUNC sdl_reverse_iterator& operator++() {

        --_it;

        return *this;

    }

    _SDL_FUNC sdl_reverse_iterator operator++(int) {

        sdl_reverse_iterator temp = *this;

        --_it;

        return temp;

    }

    _SDL_FUNC sdl_reverse_iterator& operator--() {

        ++_it;

        return *this;

    }

    _SDL_FUNC sdl_reverse_iterator operator--(int) {

        sdl_reverse_iterator temp = *this;

        ++_it;

        return temp;

    }

    _SDL_FUNC bool operator==(const sdl_reverse_iterator& other) const {

        return _it == other._it;

    }

    _SDL_FUNC bool operator!=(const sdl_reverse_iterator& other) const {

        return _it != other._it;

    }

    _SDL_FUNC T& operator*() const {

        return *_it;

    }

    _SDL_FUNC T* operator->() const {

        return &(*_it);

    }

private:
    T* _it;

};

template<typename T>
class sdl_const_reverse_iterator {

public:
    _SDL_FUNC sdl_const_reverse_iterator(const T* _it) : _it(_it) {}

    _SDL_FUNC sdl_const_reverse_iterator& operator++() {

        --_it;

        return *this;

    }

    _SDL_FUNC sdl_const_reverse_iterator operator++(int) {

        sdl_const_reverse_iterator temp = *this;

        --_it;

        return temp;

    }

    _SDL_FUNC sdl_const_reverse_iterator& operator--() {

        ++_it;

        return *this;

    }

    _SDL_FUNC sdl_const_reverse_iterator operator--(int) {

        sdl_const_reverse_iterator temp = *this;

        ++_it;

        return temp;

    }

    _SDL_FUNC bool operator==(const sdl_const_reverse_iterator& other) const {

        return _it == other._it;

    }

    _SDL_FUNC bool operator!=(const sdl_const_reverse_iterator& other) const {

        return _it != other._it;

    }

    _SDL_FUNC const T& operator*() const {

        return *_it;

    }

    _SDL_FUNC const T* operator->() const {

        return &(*_it);

    }

private:
    const T* _it;

};