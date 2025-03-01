// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : MaxPower(mp), BitField(mp) { }

// конструктор копирования
TSet::TSet(const TSet &s) : MaxPower(s.GetMaxPower()), BitField(s.BitField) { }

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : MaxPower(bf.GetLength()), BitField(bf) { }

TSet::operator TBitField() { return TBitField(BitField); }

// получить макс. к-во эл-тов 
int TSet::GetMaxPower(void) const { return MaxPower; }

// элемент множества ?
int TSet::IsMember(const int Elem) const
{
    if (Elem < 0 || Elem >= MaxPower)
        throw std::out_of_range("element is out of set possible range");
    return BitField.GetBit(Elem);
}

// включение элемента множества
void TSet::InsElem(const int Elem) 
{
    if (Elem < 0 || Elem >= MaxPower)
        throw std::out_of_range("element is out of set possible range");
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    if (Elem < 0 || Elem >= MaxPower)
        throw std::out_of_range("element is out of set possible range");
    BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
    if (this == &s)
        return *this;
    MaxPower = s.GetMaxPower();
    BitField = s.BitField;
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    return BitField == s.BitField;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    return BitField != s.BitField;
}

TSet TSet::operator+(const TSet &s) // объединение
{
    return TSet(BitField | s.BitField);
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    if (Elem < 0 || Elem >= MaxPower)
        throw std::out_of_range("element is out of set possible range");

    TSet tmp(*this);
    tmp.InsElem(Elem);
    return tmp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    if (Elem < 0 || Elem >= MaxPower)
        throw std::out_of_range("element is out of set possible range");

    TSet tmp(*this);
    tmp.DelElem(Elem);
    return tmp;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    return TSet(BitField & s.BitField);
}

TSet TSet::operator~(void) // дополнение
{
    return TSet(~BitField);
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    int max_size, size;

    istr >> max_size;
    if (max_size <= 0) throw std::invalid_argument("entered set max size has invalid value");
    istr >> size;
    if ((size <= 0) || (size > max_size)) throw std::invalid_argument("entered set size has invalid value");

    TSet buff(max_size);

    for (int i = 0; i < size; i++)
    {
        int tmp;
        istr >> tmp;
        buff.InsElem(tmp);
    }

    s = buff;
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    int size = 0;
    for (int i = 0; i < s.MaxPower; i++)
        if (s.IsMember(i)) size++;
    ostr << s.GetMaxPower() << " " << size << " ";

    for (int i = 0; i < s.MaxPower; i++)
        if (s.IsMember(i))
            ostr << i << " ";
    
    return ostr;
}
