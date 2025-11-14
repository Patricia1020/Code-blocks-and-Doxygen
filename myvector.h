//Doxygen comments are placed .h files
// All commands in the documentation start with a backslash (\) or an at-sign
// Use one or the other and stay with it.
// Read the doxygen manual. The above instruction is taken from section 21.
// Summary with links are found there.
//---------------------------------------------------------------------------------
#ifndef MYVECTOR_H
#define MYVECTOR_H
#include <iostream>
#include <string>
using namespace std;
template <class T>
class MyVector
{	public:
    /**
        * @brief this is specific constructor. so the aim of this method is to set the size of array
        * @return void
        */
    MyVector();
     /**
        * @brief this is constructor. so the aim of this method is like setter
        * @return void
        */
    MyVector(int size);
    /**
        * @brief destructor method
        * @return void
        */
    ~MyVector();
    /** @brief to store data into array and this method. if the data exceed the maximum index, the array can resize itself
      * @param data
      * @return true or false
      */
    bool push(const T &data);

    /** @brief to delete the rightmost index of the record if the user want it
      * @param data,
      * @return true or false
      */
    bool pop(T &data);

    T at(int i);

    /** @brief to print the data on the screen
      * @return void
      */
    void printlist() const;
	private:
		T *m_data; //variable for memory
		int m_size;//variable for size of memory
		int m_current;// variable of capacity of memory or how many memory that are provided in the program
};
    template <class T>
    MyVector<T>::MyVector()
    {
        m_data = new T[5];
        m_size = 5;
        m_current = 0;
    }

    template <class T>
    MyVector<T>::MyVector(int size)
    {
        m_data = new T[size];
        m_size = size;
        m_current = 0;
    }

    template <class T>
    MyVector<T>::~MyVector()
    {delete[] m_data;}

    template <class T>
    bool MyVector<T>::push(const T &data)
    {
        if(m_current >= m_size)
        {
                m_size = m_size * 2;
                T *m_data_2 = new T[m_size];
                copy(m_data, m_data + m_current, m_data_2);

                delete[] m_data;
                m_data = m_data_2;

                m_data[m_current] = data;
                m_current++;
                return true;
        }
        else if (m_current < m_size)
        {
               m_data[m_current] = data;
               m_current++;
               return true;
        }
        else
        {return false;}
    }

    template <class T>
    bool MyVector<T>::pop(T &data)
    {
        if (m_current==0)
        {
           cout << "Nothing to pop";
           return false;
        }
        else
        {
           data = m_data[m_current];
           m_current--;
           return true;
        }
    }

    template <class T>
    T MyVector<T>::at(int i)
    {
      if(i >= 0 && i < m_current)
      {return m_data[i];}
      return m_data[0];
    }

    template <class T>
    void MyVector<T>::printlist() const
    {
       for(int i=0; i<m_current; i++)
       {cout << m_data[i] << endl; }
    }

#endif


