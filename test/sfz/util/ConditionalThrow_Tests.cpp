#include "sfz/util/ConditionalThrow.hpp"
#include <stdexcept>

int main(int argc, char** argv)
{
	sfz_throw<std::domain_error>("Can't divide by 0.");
	return 0;
}