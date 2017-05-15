#ifndef CBITBLOCK_H
#define CBITBLOCK_H

class CBitBlock {
public:
    CBitBlock() {ConstructImpl();}
    CBitBlock(unsigned int size) {ConstructImpl(size);}
    CBitBlock(unsigned int size, unsigned int value) {ConstructImpl(size, value);}
    CBitBlock(const CBitBlock& block) {ConstructImpl(block);}

    bool IsEmpty()const {return (mSize == 0);}

    unsigned int Size() const {return mSize;}
    unsigned int AsInt() const {return AsIntImpl();}

    const CBitBlock BitsAt(unsigned int up, unsigned int lo) const;

    void CopyFrom(const CBitBlock& bits, unsigned int i = 0);

    void SetAll() {SwitchAllTo(true);}
    void SetAt(unsigned int i) {SwitchBitTo(i, true);}
    void SetRange(unsigned int m, unsigned int n) {SwitchRangeTo(m, n, true);}

    void ClearAll() {SwitchAllTo(false);}
    void ClearAt(unsigned int i) {SwitchBitTo(i, false);}
    void ClearRange(unsigned int hi, unsigned int lo) {SwitchRangeTo(hi, lo, false);}

    void SwitchAllTo(bool value);
    void SwitchBitTo(unsigned int i, bool value);
    void SwitchRangeTo(unsigned int hi, unsigned int lo, bool value);

    bool IsSetAt(unsigned int i) const;
    bool IsClearAt(unsigned int i) const {return !IsSetAt(i);}

    void SetBoolAt(unsigned int i, bool value);

    void Inc();
    void Dec();

    void Shr(bool shiftValue=false);
    void Shl(bool shiftValue=false);

    void Shr2(bool shiftValue=false);
    void Shl2(bool shiftValue=false);

    CBitBlock& operator= (const CBitBlock& other) {CopyFrom(other); return *this;}
    CBitBlock& operator^=(const CBitBlock& other) {return XorWithImpl(other);}
    CBitBlock& operator&=(const CBitBlock& other) {return AndWithImpl(other);}
    CBitBlock& operator|=(const CBitBlock& other) {return OrWithImpl(other);}
    CBitBlock  operator~ () const {return NotImpl();}

    CBitBlock& operator+=(const CBitBlock& other) {return AddWithImpl(other);}

    bool IsEqual(const CBitBlock& other) const {return (Size() == other.Size()) && (AsInt() == other.AsInt());}

private:
    unsigned int mSize;
    unsigned int mValue;

    void ConstructImpl() {ConstructImpl(0);}
    void ConstructImpl(unsigned int size) {mSize = size; mValue = 0;}
    void ConstructImpl(unsigned int size, unsigned int value) {mSize = size; mValue = value;}
    void ConstructImpl(const CBitBlock& block) {mSize = block.mSize; mValue = block.mValue;}

    unsigned int AsIntImpl() const {return mValue & ((1 << mSize) - 1);}

    CBitBlock& XorWithImpl(const CBitBlock& other);
    CBitBlock& AndWithImpl(const CBitBlock& other);
    CBitBlock& OrWithImpl(const CBitBlock& other);
    CBitBlock& AddWithImpl(const CBitBlock& other);
    CBitBlock  NotImpl() const;

    static void swap(unsigned int &a, unsigned int &b) {unsigned int t = a; a = b; b = t;}
};

CBitBlock operator^(const CBitBlock& x, const CBitBlock& y);
CBitBlock operator&(const CBitBlock& x, const CBitBlock& y);
CBitBlock operator|(const CBitBlock& x, const CBitBlock& y);

bool operator==(const CBitBlock& x, const CBitBlock& y);
bool operator!=(const CBitBlock& x, const CBitBlock& y);


#endif // CBITBLOCK_H
