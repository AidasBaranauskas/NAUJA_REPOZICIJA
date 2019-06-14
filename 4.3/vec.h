#include <algorithm>

template <class T> class Vector {
public://                                                                                               PUBLIC
    typedef       T*       iterator; // rodykle i elementa
    typedef const T* const_iterator;
    typedef       size_t   size_type;//talpina dydi
    typedef       T        value_type;

          size_type size() const { return avail - data; }
//size_t - store any size, for recursion and classes
          iterator begin()       { return data; }//grazina pradzios,
    const_iterator begin() const { return data; }
          iterator end()         { return avail; }//pabaigos adresus
    const_iterator end()   const { return avail; }

    Vector() { create(); }   // paskiria atminti inicializuojant ji
    explicit Vector(size_t n, const T& val = T{}) { create(n, val); }
//explicit - cannot be used for implicit conversions and copy-initialization.
//kitaip pasakius, class_name B, A{B}; neiskvies sios funkcijos

    Vector(const Vector& v) { create(v.begin(), v.end()); }//copy konstruktoriai

    /////////Operatoriai
    Vector<T>& operator=(const Vector& rhs)//atlaisvint atminti, ja uzpildyt nauja                      OPERATOR =
    {
    if (&rhs != this){
        uncreate();
        create(rhs.begin(), rhs.end());
    }
    return *this;
    }

    ~Vector() { uncreate();}

          T& operator[](size_type i)       {
              if (i < 0 || size() <= i) throw std::out_of_range {"Vector::operator[]"};//        `      OPERATOR []
              return data[i]; }

    const T& operator[](size_type i) const {
              if (i < 0 || size() <= i) throw std::out_of_range {"Vector::operator[]"};//
              return data[i]; }

    /////////Kitos Funkcijos
    void push_back(const T& val) {//                                                                    PUSH_BACK
    if (avail == limit) //
    grow();
    unchecked_append(val) ; // įdėti naują elementą
    }

    void reserve(const size_type i)//                                                                   RESERVE
    {
        //zingsniai: allocate if need be, move it all if need be. limit-data =i
    if(limit-data<i){
        //grow(i);//jei ne eroras, reserve'as naudotu grow funkcija
     size_type new_size = data+i;
    iterator new_data = alloc.allocate(new_size);
    iterator new_avail = std::uninitialized_copy(data, avail, new_data);
    uncreate();
    data = new_data;//i pirma naujos atminties elementa
    avail = new_avail;
    limit = data + new_size;

    }
    }//*/
private://                                                                                              PRIVATE
    iterator data; // pointer to first of initialized
    iterator avail; // pointer to last of initialized
    iterator limit; // pointer to last of reserved

    std::allocator<T> alloc; // objektas atminties valdymui allocate
 // išskirti atmintį (array) ir ją inicializuoti

    void create() ;
    void create(size_type, const T&);
    void create(const_iterator, const_iterator);
 // sunaikinti elementus array ir atlaisvinti atmintį
    void uncreate();
 // pagalbinės funkcijos push_back realizacijai
    void grow(/*size_type new_size = std::max(2 * (limit - data), ptrdiff_t(1))*/);
    void unchecked_append(const T&);
};

template <class T> void Vector<T>::create() {//                                                         CREATE
 data = avail = limit = nullptr;//first, last of size, last of reserved made null
};

template <class T> void Vector<T>::create(size_type n, const T& val) {
 data = alloc.allocate(n); // grąžina ptr į array pirmą elementą
 limit = avail = data + n; // sustato rodykles į vietas
 uninitialized_fill(data, limit, val); // inicializuoja elementus val reikšme
};
//(de)allocate: (de)allocates memory
template <class T> void Vector<T>::create(const_iterator i, const_iterator j) {
 data = alloc.allocate(j - i); // išskirti vietos j-i elementams
 limit = avail = std::uninitialized_copy(i, j, data); // nukopijuoja elementus iš intervalo
 //"Copies the given value to an uninitialized memory area, defined by the range"
};

template <class T> void Vector<T>::uncreate() {//                                                       UNCREATE
 if (data) {//jei i kazka pointina tai true
 // sunaikinti (atbuline tvarka) sukonstruotus elementus
 iterator it = avail;
 while (it != data)
 alloc.destroy(--it);
 // atlaisvinti išskirtą atmintį. Turi būti data != nullptr
 alloc.deallocate(data, limit - data);
 }

 // reset'inam pointer'ius - Vector'ius tuščias
 data = limit = avail = nullptr;
};


template <class T> void Vector<T>::grow(/*size_type new_size*/) {//                                     GROW
 // dvigubai daugiau vietos, nei buvo
 size_type new_size = std::max(2 * (limit - data), ptrdiff_t(1));
 //renkasi didesni
 //ptrdiff_t: "is the signed integer type of the result of subtracting two pointers"
 // išskirti naują vietą ir perkopijuoti egzistuojančius elementus
 iterator new_data = alloc.allocate(new_size);
 iterator new_avail = std::uninitialized_copy(data, avail, new_data);
 // atlaisvinti seną vietą
 uncreate();
 // reset'int rodykles į naujai išskirtą vietą
 //nes tai geriau, nei pildyt elementus ir atsimust i siena ir pradet is naujo kitoj atminty
 data = new_data;//i pirma naujos atminties elementa
 avail = new_avail;
 limit = data + new_size;
}
// tariame, kad `avail` point'ina į išskirtą, bet neinicializuotą vietą
template <class T> void Vector<T>::unchecked_append(const T& val) {//                                   UNCHECKED_APPEND
 alloc.construct(avail++, val);
//nuo c++20 construct construct nebeveiks
};


