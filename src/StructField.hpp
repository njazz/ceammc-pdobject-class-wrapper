


template<typename T, typename U>
U __Getter(U* f) {return *f;};


template<typename T, typename U>
void __Setter(U* f, U v) {*f = v;};
