#include <dstring>

int main() {

	sdl::dstring deirror_string;

	deirror_string.append("dddh");

	sdl::dcout << deirror_string.at(3) << '\n';

	sdl::dcin >> deirror_string;

	sdl::dstring to_copy;

	to_copy.assign(deirror_string);

	char_ptr _data = nullptr;

	to_copy.copy_to(_data, _BIN, _BIN);

	sdl::dcout << deirror_string.to_lower() << '\n';

	sdl::dcout << deirror_string.to_upper() << '\n';

	sdl::dcout << deirror_string.trim("at");

	_DELETE_ARRAY(_data);

	return 0;
}