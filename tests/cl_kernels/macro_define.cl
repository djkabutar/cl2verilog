#define HELLO 123

__kernel void hello(__global int *a) {
	a[get_global_id(0) = HELLO;
}
