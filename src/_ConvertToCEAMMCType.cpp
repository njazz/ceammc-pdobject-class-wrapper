#include "_Converters.hpp"

// 1. atoms
template <>
void toAtomList(AtomList& out, float& v) { out.at(0).setFloat(v);}

template <>
void toAtomList(AtomList& out, double& v) { out.at(0).setFloat(v);}

template <>
void toAtomList(AtomList& out, std::string& v) { out.at(0).setSymbol(gensym(v.c_str()));}

template <>
void toAtomList(AtomList& out, int& v) { out.at(0).setFloat(v);}

template <>
void toAtomList(AtomList& out, long& v) { out.at(0).setFloat(v);}

template <>
void toAtomList(AtomList& out, const char*& v) { out.at(0).setSymbol(gensym(v));}

template <>
void toAtomList(AtomList& out, char *& v) { out.at(0).setSymbol(gensym(v));}


