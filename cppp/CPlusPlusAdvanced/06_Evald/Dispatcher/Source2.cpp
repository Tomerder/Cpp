
// usage example for dispatcher

class Thermometer
{
public:

	void  ChangeTemp(int _change)
	{
		//notify observers for any temperature change
		if (_change) { m_dispatcher.Dispatch(); }
	}

private:
	m_temp;
	//Dispatcher m_dispatcher<int, Thermometer> ??
};


class Dog
{
public:
	void Tongue();
}

// implementation of Notify for Dog
template <class T, class D, class O>
void ObserverCB::Notify()
{
	m_observer->Tongue();
}


typedef ObserverCB<int, Thremometer, Dog>		DogTCB;


int main()
{
	Dog d;
	Thermometer t;

	DogTCB(&t, &d); // register dog as observer for thermometer

}



/*
flow:	DogTCB CTOR - 
*/