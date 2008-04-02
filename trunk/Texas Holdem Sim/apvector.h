#ifndef _APVECTOR_H
#define _APVECTOR_H


#define explicit



template <class itemType>
class apvector
{
  public:

  // constructors/destructor
    apvector( );                        // default constructor (size==0)
    explicit apvector( int size );      // initial size of vector is size
    apvector( int size, const itemType & fillValue ); // all entries == fillValue
    apvector( const apvector & vec );   // copy constructor
    ~apvector( );                       // destructor

  // assignment
    const apvector & operator = ( const apvector & vec );

  // accessors
    int  length( ) const;                   // capacity of vector

  // indexing
    itemType &       operator [ ] ( int index );       // indexing with range checking
    const itemType & operator [ ] ( int index ) const; // indexing with range checking

  // modifiers
    void resize( int newSize );             // change size dynamically;
                                            // can result in losing values
  private:

    int  mySize;                            // # elements in array
    itemType * myList;                      // array used for storage
};


#include "apvector.cpp"
#endif


