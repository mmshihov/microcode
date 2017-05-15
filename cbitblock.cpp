#include "cbitblock.h"

#include<QObject>

CBitBlock &CBitBlock::XorWithImpl(const CBitBlock &other) {
    unsigned int value = (mValue ^ other.AsInt());
    CBitBlock block(Size(), value);

    CopyFrom(block);
    return *this;
}

CBitBlock &CBitBlock::AndWithImpl(const CBitBlock &other) {
    unsigned int value = (mValue & other.AsInt());
    CBitBlock block(Size(), value);

    CopyFrom(block);
    return *this;
}

CBitBlock &CBitBlock::OrWithImpl(const CBitBlock &other) {
    unsigned int value = (mValue | other.AsInt());
    CBitBlock block(Size(), value);

    CopyFrom(block);
    return *this;
}

CBitBlock &CBitBlock::AddWithImpl(const CBitBlock &other) {
    unsigned int value = (mValue + other.AsInt());
    CBitBlock block(Size(), value);

    CopyFrom(block);
    return *this;
}

CBitBlock CBitBlock::NotImpl() const {
    unsigned int value = ~AsInt();
    CBitBlock block(Size(), value);

    return block;
}

CBitBlock operator^(const CBitBlock& x, const CBitBlock& y) {
    CBitBlock z(x);
    return (z ^= y);
}

CBitBlock operator&(const CBitBlock& x, const CBitBlock& y) {
    CBitBlock z(x);
    return (z &= y);
}

CBitBlock operator|(const CBitBlock& x, const CBitBlock& y)  {
    CBitBlock z(x);
    return (z |= y);
}

bool operator==(const CBitBlock& x, const CBitBlock& y) {return x.IsEqual(y);}
bool operator!=(const CBitBlock& x, const CBitBlock& y) {return !(x == y);}

const CBitBlock CBitBlock::BitsAt(unsigned int hi, unsigned int lo) const {
    if (hi < lo)
        swap(hi,lo);

    if (lo >= Size())
        return CBitBlock();

    if (hi >= Size())
        hi = Size();

    unsigned int newSize = (hi - lo) + 1;
    return CBitBlock(newSize, (mValue >> lo) & ((1 << newSize) - 1));
}

void CBitBlock::CopyFrom(const CBitBlock &bits, unsigned int i) {
    if (i >= Size())
        return;

    unsigned int mask = (((1 << bits.Size()) - 1) << i) & ((1 << mSize) - 1);

    mValue = (mValue & ~mask) | ((bits.mValue << i) & mask);
}

void CBitBlock::SwitchAllTo(bool value) {
    SwitchRangeTo(Size() - 1, 0, value);
}

void CBitBlock::SwitchBitTo(unsigned int i, bool value) { SwitchRangeTo(i,i,value); }

void CBitBlock::SwitchRangeTo(unsigned int hi, unsigned int lo, bool value) {
    if (hi < lo)
        swap(hi, lo);

    unsigned int mask = (((1 << ((hi - lo) + 1)) - 1) << lo) & ((1 << mSize) - 1);

    mValue |= mask;
    if (!value)
        mValue &= ~mask;
}

bool CBitBlock::IsSetAt(unsigned int i) const {
    return (mValue & (1 << i)) != 0;
}

void CBitBlock::Shr(bool shiftValue) {
    if (mSize == 0)
        return;

    mValue = (mValue >> 1);

    unsigned int msb = (1 << (mSize - 1));

    mValue &= (~msb);
    if (shiftValue)
        mValue |= msb;

    unsigned int mask = ((1 << mSize) - 1);
    mValue &= mask;
}

void CBitBlock::Shl(bool shiftValue) {
    if (mSize == 0)
        return;

    mValue = (mValue << 1);

    unsigned int msb = 1;

    mValue &= (~msb);
    if (shiftValue)
        mValue |= msb;

    unsigned int mask = ((1 << mSize) - 1);
    mValue &= mask;
}

void CBitBlock::SetBoolAt(unsigned int i, bool value) {
    ClearAt(i);
    if (value)
        SetAt(i);
}

void CBitBlock::Inc() {mValue++;}

void CBitBlock::Dec() {mValue--;}
