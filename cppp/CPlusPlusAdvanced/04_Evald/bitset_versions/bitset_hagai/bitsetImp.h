/**************************************************************************************
    Author: Hagai Moshe
    Creation date :      
    Last modified date:  
    Description : .
***************************************************************************************/



class BitSetImp_t 
{
protected:

	static bool GetBit(size_t _index, const std::vector<size_t>& _bitVec);
	static void SetBit(size_t _index, bool _value, std::vector<size_t>& _bitVec);

	static void OrAssingment( std::vector<size_t>& _bitVecToChange, const std::vector<size_t>& _bitVecB);
	static void AndAssingment( std::vector<size_t>& _bitVecToChange, const std::vector<size_t>& _bitVecB);

	static void LeftShiftAssingment( size_t _shift, size_t _numOfBits, std::vector<size_t>& _bitVec);


private:
	


};


