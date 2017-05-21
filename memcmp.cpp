#include <cstring>

template <class TYPE>
int isequal(const TYPE &data1, const TYPE &data2) {
	return (memcmp(reinterpret_cast<const void *>(&data1), reinterpret_cast<const void *>(&data2), sizeof(TYPE)) == 0);
}