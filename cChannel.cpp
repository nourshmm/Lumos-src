#include "cChannel.h"


#include "Lut.h"
#include <string>
#include "cChannel.h"


cChannel::cChannel() {
	this->channel = NULL;
	this->a = 0;
	this->b = 0;
	this->size = 0;
	this->size_l = 0;
	val = NULL;

}

cChannel::cChannel(uint* channel, uint a, uint b, int size, int size_l) {
	this->channel = (uint*)malloc(size * sizeof(uint));
	this->a = a;
	this->b = b;
	this->size = size;
	this->size_l = size_l;
	val = (uint*)malloc(size_l * sizeof(uint));

}

uint* cChannel::get_channel() {
	return channel;
}
void cChannel::set_bound(uint a, uint b) {
	this->a = a;
	this->b = b;

}//(uint a, uint b,double gamma,uchar * new_val, int size)
/*uint* Channel::get_newChannel() {
	uchar* new_val;
	new_val = (uchar*)(65536 * sizeof(uchar));

	val = (uint *) l.setVal(a, b, 1,new_val,size_l);
	this->channel = l.lut(channel, val, size);
	return this->channel;
}*/
