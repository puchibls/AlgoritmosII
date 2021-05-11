class bignum
{
private:
unsigned short *digits;
// ...
public:
// ...
friend bignum operator+(const bignum&, const bignum&);
friend bignum operator-(const bignum&, const bignum&);
friend bignum operator*(const bignum&, const bignum&);
friend std::ostream& operator<<(std::ostream&, const bignum&);
friend std::istream& operator>>(std::istream&, bignum&);
};