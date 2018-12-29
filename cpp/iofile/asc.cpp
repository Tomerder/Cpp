#include <string.h>
#include <iostream>

#include "asc.h"

using namespace std;

/*--------------------------------------------------------------------------------*/


int asciiIO_t::write(const void* _dataToWrite, int _len) 	
{
	int i;	
	char c;
	
	if(!isWriteLegal()){
		setStatus(WRITE_ERR_E); 
		return 0;
	}		
	
	for(i=0; i<_len && isGood() ; i++){
		c = *((char*)((char*)_dataToWrite+i));
		fputc(c ,getFile() ); 
	}

	if(i != _len){
		setStatus(WRITE_ERR_E); 
	}

	return i;
}



int asciiIO_t::read(void* _dataToRead, int _len)  
{
	int i;
	char c;	

	if(!isReadLegal()){
		setStatus(READ_ERR_E); 
		return 0;
	}		

	for(i=0; i<_len && isGood() ; i++){
		c = fgetc( getFile() ); 
		*((char*)((char*)_dataToRead+i)) = c;
	}

	if(i != _len){
		setStatus(READ_ERR_E); 
	}

	return i;
}


/*--------------------------------------------------------------------------------*/


virtIO_t& asciiIO_t::operator>>(int& _intToRead)
{	
	if(isReadLegal()){
		if( fscanf(getFile() ,  "%d" , &_intToRead )   <  0 ){
			setStatus(WRITE_ERR_E);
		}
	}else{
		setStatus(READ_ERR_E); 
	}	
	
	return *this;
}

virtIO_t& asciiIO_t::operator<<(int _intToWrt)
{
	if(isWriteLegal()){
		if( fprintf(getFile(),  "%d" , _intToWrt )  <  0){
			setStatus(WRITE_ERR_E);
		}
	}else{
		setStatus(WRITE_ERR_E);
	}

	return *this;
}

/*--------------------------------------------------------------------------------*/


virtIO_t& asciiIO_t::operator>>(unsigned int& _intToRead)
{	
	if(isReadLegal()){
		if( fscanf(getFile() ,  "%u" , &_intToRead )   <  0 ){
			setStatus(WRITE_ERR_E);
		}
	}else{
		setStatus(READ_ERR_E); 
	}	
	
	return *this;
}

virtIO_t& asciiIO_t::operator<<(unsigned int _intToWrt)
{
	if(isWriteLegal()){
		if( fprintf(getFile(),  "%u" , _intToWrt )  <  0){
			setStatus(WRITE_ERR_E);
		}
	}else{
		setStatus(WRITE_ERR_E);
	}

	return *this;
}

/*--------------------------------------------------------------------------------*/
 
virtIO_t& asciiIO_t::operator>>(char& _intToRead)
{	
	if(isReadLegal()){
		if( fscanf(getFile() ,  "%c" , &_intToRead )   <  0 ){
			setStatus(WRITE_ERR_E);
		}
	}else{
		setStatus(READ_ERR_E); 
	}	
	
	return *this;
}

virtIO_t& asciiIO_t::operator<<(char _intToWrt)
{
	if(isWriteLegal()){
		if( fprintf(getFile(),  "%c" , _intToWrt )  <  0){
			setStatus(WRITE_ERR_E);
		}
	}else{
		setStatus(WRITE_ERR_E);
	}

	return *this;
}


/*--------------------------------------------------------------------------------*/
 
virtIO_t& asciiIO_t::operator>>(unsigned char& _intToRead)
{	
	if(isReadLegal()){
		if( fscanf(getFile() ,  "%c" , &_intToRead )   <  0 ){
			setStatus(WRITE_ERR_E);
		}
	}else{
		setStatus(READ_ERR_E); 
	}	
	
	return *this;
}

virtIO_t& asciiIO_t::operator<<(unsigned char _intToWrt)
{
	if(isWriteLegal()){
		if( fprintf(getFile(),  "%c" , _intToWrt )  <  0){
			setStatus(WRITE_ERR_E);
		}
	}else{
		setStatus(WRITE_ERR_E);
	}

	return *this;
}
/*--------------------------------------------------------------------------------*/
 
virtIO_t& asciiIO_t::operator>>(short& _intToRead)
{	
	if(isReadLegal()){
		if( fscanf(getFile() ,  "%hd" , &_intToRead )   <  0 ){
			setStatus(WRITE_ERR_E);
		}
	}else{
		setStatus(READ_ERR_E); 
	}	
	
	return *this;
}

virtIO_t& asciiIO_t::operator<<(short _intToWrt)
{
	if(isWriteLegal()){
		if( fprintf(getFile(),  "%hd" , _intToWrt )  <  0){
			setStatus(WRITE_ERR_E);
		}
	}else{
		setStatus(WRITE_ERR_E);
	}

	return *this;
}

/*--------------------------------------------------------------------------------*/
 
virtIO_t& asciiIO_t::operator>>(unsigned short& _intToRead)
{	
	if(isReadLegal()){
		if( fscanf(getFile() ,  "%hu" , &_intToRead )   <  0 ){
			setStatus(WRITE_ERR_E);
		}
	}else{
		setStatus(READ_ERR_E); 
	}	
	
	return *this;
}

virtIO_t& asciiIO_t::operator<<(unsigned short _intToWrt)
{
	if(isWriteLegal()){
		if( fprintf(getFile(),  "%hu" , _intToWrt )  <  0){
			setStatus(WRITE_ERR_E);
		}
	}else{
		setStatus(WRITE_ERR_E);
	}

	return *this;
}

/*--------------------------------------------------------------------------------*/
 
virtIO_t& asciiIO_t::operator>>(long& _intToRead)
{	
	if(isReadLegal()){
		if( fscanf(getFile() ,  "%ld" , &_intToRead )   <  0 ){
			setStatus(WRITE_ERR_E);
		}
	}else{
		setStatus(READ_ERR_E); 
	}	
	
	return *this;
}

virtIO_t& asciiIO_t::operator<<(long _intToWrt)
{
	if(isWriteLegal()){
		if( fprintf(getFile(),  "%ld" , _intToWrt )  <  0){
			setStatus(WRITE_ERR_E);
		}
	}else{
		setStatus(WRITE_ERR_E);
	}

	return *this;
}
/*--------------------------------------------------------------------------------*/
 
virtIO_t& asciiIO_t::operator>>(unsigned long& _intToRead)
{	
	if(isReadLegal()){
		if( fscanf(getFile() ,  "%lu" , &_intToRead )   <  0 ){
			setStatus(WRITE_ERR_E);
		}
	}else{
		setStatus(READ_ERR_E); 
	}	
	
	return *this;
}

virtIO_t& asciiIO_t::operator<<(unsigned long _intToWrt)
{
	if(isWriteLegal()){
		if( fprintf(getFile(),  "%lu" , _intToWrt )  <  0){
			setStatus(WRITE_ERR_E);
		}
	}else{
		setStatus(WRITE_ERR_E);
	}

	return *this;
}
/*--------------------------------------------------------------------------------*/
 
virtIO_t& asciiIO_t::operator>>(float& _intToRead)
{	
	if(isReadLegal()){
		if( fscanf(getFile() ,  "%f" , &_intToRead )   <  0 ){
			setStatus(WRITE_ERR_E);
		}
	}else{
		setStatus(READ_ERR_E); 
	}	
	
	return *this;
}

virtIO_t& asciiIO_t::operator<<(float _intToWrt)
{
	if(isWriteLegal()){
		if( fprintf(getFile(),  "%f" , _intToWrt )  <  0){
			setStatus(WRITE_ERR_E);
		}
	}else{
		setStatus(WRITE_ERR_E);
	}

	return *this;
}

/*--------------------------------------------------------------------------------*/
 
virtIO_t& asciiIO_t::operator>>(double& _intToRead)
{	
	if(isReadLegal()){
		if( fscanf(getFile() ,  "%f" , &_intToRead )   <  0 ){
			setStatus(WRITE_ERR_E);
		}
	}else{
		setStatus(READ_ERR_E); 
	}	
	
	return *this;
}

virtIO_t& asciiIO_t::operator<<(double _intToWrt)
{
	if(isWriteLegal()){
		if( fprintf(getFile(),  "%f" , _intToWrt )  <  0){
			setStatus(WRITE_ERR_E);
		}
	}else{
		setStatus(WRITE_ERR_E);
	}

	return *this;
}
/*--------------------------------------------------------------------------------*/









